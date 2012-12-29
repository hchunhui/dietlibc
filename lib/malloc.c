#include <sys/types.h>
#include <string.h>
#define G 8
#define MAGIC 0x112255aa
struct alloc_stru {
	struct alloc_stru *next;
	size_t len;
	char mem[];
};

static struct alloc_stru *flist;

static void _alloc_libc_free(void *ptr)
{
	struct alloc_stru *q, *p, *r;
	if(ptr == NULL || flist == NULL)
		return;
	p = (struct alloc_stru *)(((char *)ptr) - sizeof(struct alloc_stru));
	if(p->next != (void *)MAGIC)
		return;
	q = flist;
	/* loop invariant: r && q < q+qlen {<= p < p+plen , < r} */
	for(r = q->next; r;)
	{
		if(q->mem + q->len == (char *)p)
		{
			q->len += p->len + sizeof(struct alloc_stru);
			p = r;
			r = r->next;
			continue;
		}
		if(p->mem + p->len < (char *)r)
		{
			q->next = p;
			p->next = r;
			return;
		}
		if(p->mem + p->len == (char *)r)
		{
			r = r->next;
		}
		else
		{
			q = r;
			r = r->next;
		}
	}
	/* q < q+qlen <= p < p+plen && r == NULL */
	if(q->mem + q->len < (char *)p)
	{
		q->next = p;
		p->next = NULL;
	}
	else if(q->mem + q->len == (char *)p)
	{
		q->len += p->len + sizeof(struct alloc_stru);
	}
}

static struct alloc_stru *get_free_mem(size_t size)
{
	struct alloc_stru *p, *q, *r;
	q = flist;
	for(p = flist->next; p; q = p, p = p->next)
	{
		if(p->len == size)
		{
			q->next = p->next;
			return p;
		}
		if(p->len > size)
		{
			if(p->len > 4*sizeof(struct alloc_stru) + size)
			{
				r = (struct alloc_stru *)(p->mem + size);
				r->next = p->next;
				q->next = r;
				r->len = p->len - size - sizeof(struct alloc_stru);
				p->len = size;
			}
			else
			{
				q->next = p->next;
			}
			return p;
		}
	}
	return NULL;
}

void* __libc_sbrk(ptrdiff_t increment);

static void *_alloc_libc_malloc(size_t size)
{
	struct alloc_stru *p;
	size_t rsize;
	if(size == 0)
		return NULL;
	rsize = (size+G-1)/G*G;
	if(!flist)
	{
		p = __libc_sbrk(G+sizeof(struct alloc_stru));
		p->next = NULL;
		p->len = 0;
		flist = p;
	}
	if((p = get_free_mem(rsize)) == NULL)
	{
		p = __libc_sbrk(rsize+sizeof(struct alloc_stru));
		if(p == (void *)-1)
			return NULL;
		p->len = rsize;
	}
	p->next = (void *)MAGIC;
	return (void *)p->mem;
}

static void *_alloc_libc_realloc(void *ptr, size_t size)
{
	struct alloc_stru *p;
	void *q;
	if(ptr == NULL)
		return _alloc_libc_malloc(size);
	if(size == 0)
	{
		_alloc_libc_free(ptr);
		return NULL;
	}
	p = (struct alloc_stru *)(((char *)ptr) - sizeof(struct alloc_stru));
	if(p->next != (void *)MAGIC)
		return ptr;
	if(p->len >= size)
		return ptr;
	if((q = _alloc_libc_malloc(size)))
	{
		memcpy(q, ptr, p->len);
		_alloc_libc_free(ptr);
		return q;
	}
	return NULL;
}

void *__libc_malloc(size_t size) __attribute__((alias("_alloc_libc_malloc")));
void *malloc(size_t size) __attribute__((weak,alias("_alloc_libc_malloc")));
void *__libc_realloc(void *ptr, size_t size) __attribute__((alias("_alloc_libc_realloc")));
void *realloc(void *ptr, size_t size) __attribute__((weak,alias("_alloc_libc_realloc")));
void __libc_free(void *ptr) __attribute__((alias("_alloc_libc_free")));
void free(void *ptr) __attribute__((weak,alias("_alloc_libc_free")));
void if_freenameindex(void *ptr) __attribute__((alias("free")));


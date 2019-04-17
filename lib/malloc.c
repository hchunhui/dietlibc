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
	for(r = q->next; r;)
	{
		if(q < p && p < r)
		{
			if(q->mem + q->len == (char *)p)
			{
				q->len += p->len + sizeof(struct alloc_stru);
				p = q;
			}
			if(p->mem + p->len == (char *)r)
			{
				p->len += r->len + sizeof(struct alloc_stru);
				r = p;
			}
			if(p != q && r != p)
			{
				p->next = q->next;
				q->next = p;
			}
			break;
		}
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

void* __libc_calloc(size_t nmemb, size_t _size);
void* __libc_calloc(size_t nmemb, size_t _size) {
  register size_t size=_size*nmemb;
  return malloc(size);
}
void* calloc(size_t nmemb, size_t _size) __attribute__((weak,alias("__libc_calloc")));

void *memalign(size_t al, size_t sz)
{
	// We need extra bytes to store the original value returned by malloc.
	if (al < sizeof(void*))
		al = sizeof(void*);
	void* const malloc_ptr = malloc(sz + al);
	if (!malloc_ptr)
		return NULL;
	// Align to the requested value, leaving room for the original malloc value.
	void* const aligned_ptr = (void *) (((uintptr_t) malloc_ptr + al) & -al);

	// Store the original malloc value where it can be found by operator delete.
	((void **) aligned_ptr)[-1] = malloc_ptr;

	return aligned_ptr;
}

#define _POSIX_SOURCE
#include "dietdirent.h"
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <os/dirent.h>

int readdir_r(DIR *d,struct dirent* entry, struct dirent** result) {
  struct os_dirent* od;
  *result=0;
  if (!d->num || (d->cur += ((struct dirent*)(d->buf+d->cur))->d_reclen)>=d->num) {
    int res=getdents(d->fd,(struct dirent*)d->buf, 1);
    if (res<=0)
      return res<0;
    d->num=res; d->cur=0;
  }
  od=(struct os_dirent*)(d->buf+d->cur);
  if (od->d_reclen < sizeof(struct os_dirent))
    return 0;	/* can't happen */
  *result=entry;
  entry->d_ino=od->d_ino;
  entry->d_off=od->d_off;
  entry->d_reclen=od->d_reclen;
  memcpy(entry->d_name,od->d_name,od->d_reclen-offsetof(struct os_dirent,d_name));
  return 0;
}

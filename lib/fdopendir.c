#include "dietdirent.h"
#include <sys/mman.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>

DIR*  fdopendir ( int fd ) {
  DIR*  t  = NULL;

  if ( fd >= 0 ) {
    t = (DIR *) malloc(PAGE_SIZE);
    if (t == NULL)
lose:
      close (fd);
    else
      t->fd = fd;
  }


  return t;
}

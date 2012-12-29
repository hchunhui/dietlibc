#include "dietdirent.h"
#include <sys/mman.h>
#include <unistd.h>
#include <dirent.h>
#include <stdlib.h>
#include <fcntl.h>

DIR*  opendir ( const char* name ) {
  int   fd = open (name, O_RDONLY | O_DIRECTORY);
  DIR*  t  = NULL;

  if ( fd >= 0 ) {
	  t = malloc(sizeof(DIR));
	  memset(t, 0, sizeof(DIR));
	  if (t == NULL)
		  close (fd);
	  else
		  t->fd = fd;
  }
  return t;
}

#include <unistd.h>
#include <fcntl.h>
#include <string.h>
#include <stdlib.h>
#include <errno.h>
#include <time.h>
#include "dietfeatures.h"

char* mkdtemp(char* template) {
  char *tmp=template+strlen(template)-6;
  int i;
  unsigned int random;
  if (tmp<template) goto error;
  srand(time(NULL));
  for (i=0; i<6; ++i) if (tmp[i]!='X') { error: errno=EINVAL; return 0; }
  for (;;) {
    random = rand();
    for (i=0; i<6; ++i) {
      int hexdigit=(random>>(i*5))&0x1f;
      tmp[i]=hexdigit>9?hexdigit+'a'-10:hexdigit+'0';
    }
    if (mkdir(template,0700)==0) break;
    if (errno==EEXIST) continue;
    return 0;
  }
  return template;
}

#include <unistd.h>
#include <time.h>

unsigned int sleep(unsigned int secs) {
  int i;
  for(i = 0; i < secs; i++)
    usleep(1000000);
  return 0;
}

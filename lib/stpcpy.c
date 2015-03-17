/* fast strcpy -- Copyright (C) 2003 Thomas M. Ogrisegg <tom@hi-tek.fnord.at> */
#include <string.h>
#include "dietfeatures.h"
#include "dietstring.h"

char *
stpcpy (char *s1, const char *s2)
{
    while ((*s1++ = *s2++));
    return s1 - 1;
}

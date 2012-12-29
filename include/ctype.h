#ifndef	_CTYPE_H
#define _CTYPE_H

#include <sys/cdefs.h>

__BEGIN_DECLS

extern int isascii (int c) __THROW __attribute__ ((__const__));
extern int isblank (int c) __THROW __attribute__ ((__const__));
extern int isalnum (int c) __THROW __attribute__ ((__const__));
extern int isalpha (int c) __THROW __attribute__ ((__const__));
extern int isdigit (int c) __THROW __attribute__ ((__const__));
extern int isspace (int c) __THROW __attribute__ ((__const__));

extern int isupper (int c) __THROW __attribute__ ((__const__));
extern int islower (int c) __THROW __attribute__ ((__const__));

extern int toascii(int c) __THROW __attribute__ ((__const__));
extern int tolower(int c) __THROW __attribute__ ((__const__));
extern int toupper(int c) __THROW __attribute__ ((__const__));

extern int isprint(int c) __THROW __attribute__ ((__const__));
extern int ispunct(int c) __THROW __attribute__ ((__const__));
extern int iscntrl(int c) __THROW __attribute__ ((__const__));

/* fscking GNU extensions! */
extern int isxdigit(int c) __THROW __attribute__ ((__const__));

extern int isgraph(int c) __THROW __attribute__ ((__const__));

#define	_U	01
#define	_L	02
#define	_N	04
#define	_S	010
#define _P	020
#define _C	040
#define _X	0100
#define	_B	0200
extern const char _ctype_[1 + 256];
__END_DECLS

#endif

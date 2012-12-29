#ifndef _ASM_TYPES_H
#define _ASM_TYPES_H

#include <sys/types.h>
#include <endian.h>

__BEGIN_DECLS

#ifdef __alpha__
typedef uint32_t umode_t;
#else
typedef uint16_t umode_t;
#endif

#define __force
typedef uint16_t __le16;
typedef uint16_t __be16;
typedef uint32_t __le32;
typedef uint32_t __be32;
typedef uint64_t __le64;
typedef uint64_t __be64;

typedef uint16_t __sum16;
typedef uint32_t __wsum;

typedef uint16_t __kernel_sa_family_t;

__END_DECLS

#endif

#ifndef __HACKED_MINIX_TYPE_INCLUDED
#define __HACKED_MINIX_TYPE_INCLUDED

#ifdef __cplusplus
extern "C" {
#define protected _protected
#endif

#include_next <minix/type.h>

#ifdef __cplusplus
#undef protected
}
#endif

#endif

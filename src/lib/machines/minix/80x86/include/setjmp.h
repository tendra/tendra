#ifndef __HACKED_SETJMP_INCLUDED
#define __HACKED_SETJMP_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

#ifndef _SETJMP_H
#define _SETJMP_H

#ifndef _ANSI_H
#include <ansi.h>
#endif

#include <sys/types.h>  /* sigset_t */

typedef struct {
  int __regs[6];
  int __flag;
  sigset_t __mask;
} jmp_buf[1];

#define JB_BX	0
#define JB_SI	1
#define JB_DI	2
#define JB_BP	3
#define JB_SP	4
#define JB_PC	5

_PROTOTYPE( int __setjmp, (jmp_buf env, int savemask)			);
_PROTOTYPE( void __longjmp, (jmp_buf env, int val)			);

#define setjmp(env)	  __setjmp((env), 1)
#define longjmp(env, val) __longjmp((env), (val))

#ifdef _POSIX_SOURCE
typedef jmp_buf sigjmp_buf;
#define sigsetjmp(env, savemask) __setjmp((env), (savemask))
#define siglongjmp(env, val)     __longjmp((env), (val))
#endif

#ifdef _MINIX
#define _setjmp(env)	   __setjmp((env), 0)
#define _longjmp(env, val) __longjmp((env), (val))
#endif

#endif  /* _SETJMP_H */

#ifdef __cplusplus
}
#endif

#endif  /* __HACKED_SETJMP_INCLUDED */

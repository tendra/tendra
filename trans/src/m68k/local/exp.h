/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCAL_EXP_H
#define LOCAL_EXP_H

#ifndef tdf3
#define frame_al_of_ptr(x) (x)->child.ald->al.frame
#define frame_al1_of_offset(x) (x)->child.ald->al.frame
#define al_includes_vcallees 16
#define al_includes_caller_args 6
#endif

/*
 * PROPERTIES OF IDENTITY DECLARATIONS
 */

#define set_intnl_call(X)	(X)->props |= 0x80
#define has_intnl_call(X)	((X)->props & 0x80)

#define setismarked(X)       (X)->props |= 0x100
#define ismarked(X)		((X)->props & 0x100)


#ifndef tdf3
/* parameter used for output (needs to be in memory for 68k) */
#define setoutpar(x) setvis(x)
#define isoutpar(x) isvis(x)
#define clearoutpar(x)
#else
#define setoutpar(x) (x)->props |= 0x8000
#define isoutpar(x) (((x)->props & 0x8000) != 0)
#define clearoutpar(x) (x)->props &= ~0x8000
#endif

#ifndef tdf3
#define set_proc_needs_envsize(x) (x)->props = (prop) ((x)->props | 0x8000)
#define proc_needs_envsize(x) ((x)->props & 0x8000)
#define call_has_checkstack(e) (next(child(e))->props & 8)
#endif

#endif

/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1996, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LOCALEXPMACS_H
#define LOCALEXPMACS_H

#ifndef tdf3
#define frame_al_of_ptr(x) (x)->son.ald->al.al_val.al_frame
#define frame_al1_of_offset(x) (x)->son.ald->al.al_val.al_frame
#define al_includes_vcallees 16
#define al_includes_caller_args 6
#endif

/*
 * PROPERTIES OF IDENTITY DECLARATIONS
 */

#define set_intnl_call(X)	props (X) |= 0x80
#define has_intnl_call(X)	(props (X) & 0x80)

#define setismarked(X)       props (X) |= 0x100
#define ismarked(X)		(props (X) & 0x100)


#ifndef tdf3
/* parameter used for output (needs to be in memory for 68k) */
#define setoutpar(x) setvis(x)
#define isoutpar(x) isvis(x)
#define clearoutpar(x)
#else
#define setoutpar(x) props(x) |= 0x8000
#define isoutpar(x) ((props(x) & 0x8000) != 0)
#define clearoutpar(x) props(x) &= ~0x8000
#endif

#ifndef tdf3
#define set_proc_needs_envsize(x) props(x) = (prop)(props(x) | 0x8000)
#define proc_needs_envsize(x) (props(x) & 0x8000)
#define call_has_checkstack(e) (props(bro(son(e))) & 8)
#endif

#endif

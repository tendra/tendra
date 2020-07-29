/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 * Copyright 1993, Open Software Foundation, Inc.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef FRAMES_H
#define FRAMES_H  1

extern void set_up_frame_pointer(procrec *,exp);
extern void set_up_frame_info(procrec *,exp);
extern long frame_offset(exp);

#endif

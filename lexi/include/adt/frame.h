/* $Id$ */

/*
 * Copyright 2002-2014, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef LEXI_FRAME_H
#define LEXI_FRAME_H

struct cmd;
struct locals;

struct frame {
	struct cmd *cmds;
	struct local *locals;
};

struct frame *add_frame(void);

#endif


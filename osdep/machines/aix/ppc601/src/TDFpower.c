/*
 * Copyright (c) 2002-2005 The TenDRA Project <http://www.tendra.org/>.
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *
 * 1. Redistributions of source code must retain the above copyright notice,
 *    this list of conditions and the following disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright notice,
 *    this list of conditions and the following disclaimer in the documentation
 *    and/or other materials provided with the distribution.
 * 3. Neither the name of The TenDRA Project nor the names of its contributors
 *    may be used to endorse or promote products derived from this software
 *    without specific, prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
 * IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
 * THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
 * OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
 * WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
 * OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
 * ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 * $Id$
 */

/*
    Copyright (c) 1993 Open Software Foundation, Inc.


    All Rights Reserved


    Permission to use, copy, modify, and distribute this software
    and its documentation for any purpose and without fee is hereby
    granted, provided that the above copyright notice appears in all
    copies and that both the copyright notice and this permission
    notice appear in supporting documentation.


    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING
    ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A
    PARTICULAR PURPOSE.


    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
    WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
*/

/*
    		 Crown Copyright (c) 1997

    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-

        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;

        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;

        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;

        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


/* from float.h */
#define FP_RND_RZ		0
#define FP_RND_RN		1
#define FP_RND_RP		2
#define FP_RND_RM		3

typedef unsigned short fprnd_t;
extern fprnd_t fp_read_rnd(void);
extern fprnd_t fp_swap_rnd(fprnd_t);

/* from math.h */
extern unsigned uitrunc(double);
extern int itrunc(double);
extern double rint(double);

/* from limits.h */
#define INT_MAX			(2147483647)
#define INT_MIN			(- (INT_MAX + 1))

extern int __TDFrnd_error;
extern unsigned int __TDFrnd_unsgned(double, fprnd_t);
extern int __TDFrnd_sgned(double, fprnd_t);
extern void __TDFerr_rnd_unsgned(double, fprnd_t);
extern void __TDFerr_rnd_sgned(double, fprnd_t);

int __TDFrnd_error = 0;

unsigned int
__TDFrnd_unsgned(double f, fprnd_t rnd_mode)
{
    fprnd_t swap;
    unsigned int ret_value;
    swap = fp_swap_rnd(rnd_mode);
    ret_value = uitrunc(rint(f));
   (void)fp_swap_rnd(swap);
    return ret_value;
}

int
__TDFrnd_sgned(double f, fprnd_t rnd_mode)
{
    fprnd_t swap;
    int ret_value;
    swap = fp_swap_rnd(rnd_mode);
    ret_value = itrunc(rint(f));
   (void)fp_swap_rnd(swap);
    return ret_value;
}

void
__TDFerr_rnd_unsgned(double f, fprnd_t rnd_mode)
{
    double fmin = 0.0;
    double fmax = 4294967295.0;
    switch (rnd_mode) {
	case FP_RND_RN: {
	    fmin += -0.5;
	    fmax += 0.5;
	    if (f < fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RZ: {
	    fmin += -1.0;
	    fmax += 1.0;
	    if (f <= fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RP: {
	    fmin += -1.0;
	    if (f <= fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RM: {
	    fmax += 1.0;
	    if (f < fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
    }
    return;
}

void
__TDFerr_rnd_sgned(double f, fprnd_t rnd_mode)
{
    double fmin = -2147483648.0;
    double fmax = 2147483647.0;

    switch (rnd_mode) {
	case FP_RND_RN: {
	    fmin += -0.5;
	    fmax += 0.5;
	    if (f < fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		 __TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RZ: {
	    fmin += -1.0;
	    fmax += 1.0;
	    if (f <= fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RP: {
	    fmin += -1.0;
	    if (f <= fmin || f > fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
	case FP_RND_RM: {
	    fmax += 1.0;
	    if (f < fmin || f >= fmax) {
		__TDFrnd_error = 1;
	    } else {
		__TDFrnd_error = -1;
	    }
	    break;
	}
    }
    return;
}

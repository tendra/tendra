/*
 * Copyright (c) 2004, The Tendra Project <http://www.ten15.org/>
 * Copyright (c) 2004, Boris Popov
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * 1. Redistributions of source code must retain the above copyright
 *    notice unmodified, this list of conditions, and the following
 *    disclaimer.
 * 2. Redistributions in binary form must reproduce the above copyright
 *    notice, this list of conditions and the following disclaimer in the
 *    documentation and/or other materials provided with the distribution.
 *
 * THIS SOFTWARE IS PROVIDED BY THE AUTHOR ``AS IS'' AND ANY EXPRESS OR
 * IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED WARRANTIES
 * OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE DISCLAIMED.
 * IN NO EVENT SHALL THE AUTHOR BE LIABLE FOR ANY DIRECT, INDIRECT,
 * INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT
 * NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE,
 * DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY
 * THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF
 * THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 *
 *
 * $TenDRA$
 */

#define MSG_NO_CATSTD

#include "config.h"
#include <stdarg.h>
#include <limits.h>

#include "catstd.h"
#include "catstdn.h"
#include "cstring.h"
#include "fmm.h"
#include "msgcat.h"
#include "ostream.h"
#include "tenapp.h"

struct msg_sev {
	int			severity;
	int			enabled;
	OStreamT	*stream;
	struct msg_sev *next;
};

struct msg_user_handler {
	char		type;
	msg_uh_t	*handler;
	struct msg_user_handler	*next;
};

/*
 * Stream used to report errors.
 */
OStreamT *msg_stream = NULL;
OStreamT *old_stream = NULL;

int msgcat_show_progname = 1;

int msg_max_reported_severity;

msg_on_message_t *msg_on_message;

int crt_line_no = 1;
const char *crt_file_name = NULL;


static struct msg_sev* msg_sev_list;

static struct msg_user_handler* msg_uh_list;

union msg_param {
	char		as_char;
	int		as_int;
	unsigned	as_uint;
	long		as_long;
	unsigned long	as_ulong;
	size_t		as_size_t;
	const char *	as_ccp;
	void *		as_vp;
};

static union msg_param msg_params[MSGCAT_MAXPARAMS];

static struct fmm_type *memtype_msgcat;

void
msg_init(void)
{
#ifndef MSG_USE_STDOUT
	msg_stream = (OStreamP const)ostream_error;
#else
	msg_stream = ostream_output;
#endif

	memtype_msgcat = fmm_type_add("MsgCat", "Message catalog");

	/*
	 * Setup default reporting level
	 */
	msg_sev_set(MSG_SEV_NONE, 1);	/* raw messages, enabled by default */
	msg_sev_set(MSG_SEV_INFO, 0);	/* verbose comment/info messages */
	msg_sev_set(MSG_SEV_ASSERT, 0);
	msg_sev_set(MSG_SEV_DEBUG, 0);	/* debug messages */
	msg_sev_set(MSG_SEV_WARNING, 1);
	msg_sev_set(MSG_SEV_ERROR, 1);
	msg_sev_set(MSG_SEV_FATAL, 1);
	msg_sev_set(MSG_SEV_INTERNAL, 1);
}

static struct msg_sev*
msg_sev_lookup(int severity)
{
	struct msg_sev *msp;

	for (msp = msg_sev_list; msp; msp = msp->next) {
		if (msp->severity == severity)
			return msp;
	}
	return NULL;
}

void
msg_sev_set(int severity, int enabled)
{
	struct msg_sev *msp;

	msp = msg_sev_lookup(severity);
	if (msp == NULL) {
		msp = fmm_malloc(sizeof(*msp), memtype_msgcat);
		msp->severity = severity;
		msp->next = msg_sev_list;
		msg_sev_list = msp;
	}
	msp->enabled = enabled;
}

void
msg_sev_stream(int severity, struct OStreamT *stream)
{
	struct msg_sev *msp;

	msg_sev_set(severity, 1);
	msp = msg_sev_lookup(severity);
	msp->stream = stream;
}


static struct msg_user_handler*
msg_uh_lookup(char type)
{
	struct msg_user_handler *uhp;

	for (uhp = msg_uh_list; uhp; uhp = uhp->next) {
		if (uhp->type == type)
			return uhp;
	}
	return NULL;
}

void
msg_uh_add(char type, msg_uh_t *hp)
{
	struct msg_user_handler *uhp;

	uhp = msg_uh_lookup(type);
	if (uhp == NULL) {
		uhp = fmm_malloc(sizeof(*uhp), memtype_msgcat);
		uhp->type = type;
		uhp->next = msg_uh_list;
		msg_uh_list = uhp;
	}
	uhp->handler = hp;
}

/*
 * Append a symbol to msg_stream.
 */
void
msg_append_char(char ch)
{
	write_char(msg_stream, ch);
}

/*
 * Append a string to msg_stream.
 */
void
msg_append_string(const char *src)
{
	write_cstring(msg_stream, src);
}

/*
 * Append an array of chars to msg_buffer.
 */
void
msg_append_nstring(const char *src, size_t slen)
{
	write_chars(msg_stream, src, slen);
}

void
msg_append_newline(void)
{
	msg_append_char('\n');
}

const char *
msg_get_raw(int n)
{
	MSG_DATA *mp;

	mp = MSG_CATALOG + n;
	return mp->key_STD;
}


/*
 * Format specified message into temporary buffer.
 * todo: make it public without the need to pull stdarg.h.
 */
static MSG_DATA*
msg_get(int n, struct msg_sev **mspp, va_list args)
{
	MSG_DATA *mp, *sp;
	struct msg_sev *msp;
	union msg_param *pp;
	size_t i, pcount, aid;
	const char *sig, *s;
	char ch;
	int sev;

	*mspp = NULL;

	if (msg_stream == NULL)
		msg_init();

	mp = MSG_CATALOG + n;
	if (mp->key_STD == NULL)
		return NULL;

	sev = mp->usage;
	msp = msg_sev_lookup(sev);
	/*
	 * Check if one want to see that message.
	 */
	if (msp && msp->enabled == 0)
		return NULL;

	*mspp = msp;
	if (msp->stream != NULL) {
		old_stream = msg_stream;
		msg_stream = msp->stream;
	} else if (msgcat_show_progname) {
		msg_append_string(progname);
		msg_append_string(": ");
	}
	if (sev > msg_max_reported_severity)
		msg_max_reported_severity = sev;

	/*
	 * Determine standard prefix
	 */
	switch (sev) {
	case MSG_SEV_NONE:
		sp = NULL;
		break;
	case MSG_SEV_DEBUG:
		sp = MSG_CATALOG + MID__prefix_debug;
		break;
	case MSG_SEV_WARNING:
		sp = MSG_CATALOG + MID__prefix_warning;
		break;
	case MSG_SEV_ERROR:
		exit_status = EXIT_FAILURE;
		sp = MSG_CATALOG + MID__prefix_error;
		break;
	case MSG_SEV_FATAL:
		exit_status = EXIT_FAILURE;
		sp = MSG_CATALOG + MID__prefix_fatal;
		break;
	case MSG_SEV_ASSERT:
		sp = MSG_CATALOG + MID__prefix_assert;
		break;
	case MSG_SEV_INTERNAL:
		exit_status = EXIT_FAILURE;
		sp = MSG_CATALOG + MID__prefix_internal;
		break;
	case MSG_SEV_INFO:
	default:
		sp = MSG_CATALOG + MID__prefix_info;
	}
	if (msp->stream == NULL && sp) {
		msg_append_string(sp->key_STD);
		msg_append_string(": ");
	}

	pp = NULL;
	pcount = 0;
	aid = 0;
	/*
	 * At first, move argument values from stack to array.
	 */
	sig = mp->signature;
	if (sig != NULL) {
		pcount = strlen(sig);
		for (i = 0; i < pcount; i++) {
			pp = msg_params + i;
			switch (sig[i]) {
			case MSG_KEY_int:
			case MSG_KEY_hex2_t:
				pp->as_int = va_arg(args, int);
				break;
			case MSG_KEY_unsigned:
			case MSG_KEY_char:	/* it is possible due to promotion */
			case MSG_KEY_esc_char:
				pp->as_uint = va_arg(args, unsigned int);
				break;
			case MSG_KEY_long:
			case MSG_KEY_hex4_t:
			case MSG_KEY_hex8_t:
				pp->as_long = va_arg(args, long);
				break;
			case MSG_KEY_size_t:
				pp->as_size_t = va_arg(args, size_t);
				break;
			case MSG_KEY_ccp:
				pp->as_ccp = va_arg(args, ccp);
				break;
			default:
				/*
				 * For everything else we assume a pointer
				 * to the object which covers almost
				 * all reasonable cases.
				 */
				pp->as_vp = va_arg(args, void *);
			}
		}
	}
	/*
	 * Now, format message as necessary.
	 */
	s = mp->key_STD;
	while (ch = *s++, ch) {
		if (ch != '%') {
			msg_append_char(ch);
			continue;
		}
		ch = *s;
		if (ch == 0)
			break;	/* wrong formatting */
		s++;
		if (ch >= '0' && ch <= '9') {
			aid = (unsigned)(ch - '0');
			/* Find argument type */
			if (aid < pcount) {
				ch = sig[aid];
				pp = msg_params + aid;
			} else {
				ch = '?';
				pp = NULL;
			}
		} else if (ch >= 'a' && ch <= 'z') {
			pp = msg_params + 0;	/* global variable */
		} else {
			if (ch != '%')
				ch = '?';	/* syntax */
			msg_append_char(ch);
			continue;
		}

		/* Print appropriate argument */
		switch (ch) {
		case MSG_KEY_int:
			write_int(msg_stream, pp->as_int);
			break;
		case MSG_KEY_unsigned:
			write_unsigned(msg_stream, pp->as_uint);
			break;
		case MSG_KEY_long:
			write_fmt(msg_stream, "%ld", pp->as_long);
			break;
		case MSG_KEY_size_t:
			/* not every platform have format for size_t */
			if (sizeof(int) == sizeof(size_t))
				write_fmt(msg_stream, "%u", pp->as_uint);
			else
				write_fmt(msg_stream, "%lu", pp->as_ulong);
			break;
		case MSG_KEY_char:
			msg_append_char(pp->as_char);
			break;
		case MSG_KEY_esc_char:
			write_escaped_char(msg_stream, pp->as_char);
			break;
		case MSG_KEY_hex2_t:
			write_fmt(msg_stream, "0x%02X", pp->as_uint);
			break;
		case MSG_KEY_hex4_t:
			write_fmt(msg_stream, "0x%04lX", pp->as_ulong);
			break;
		case MSG_KEY_hex8_t:
			write_fmt(msg_stream, "0x%08lX", pp->as_ulong);
			break;
		case MSG_KEY_pointer_t:
			write_fmt(msg_stream, "0x%p", pp->as_vp);
			break;
		case MSG_KEY_ccp:
			msg_append_string(pp->as_ccp);
			continue;
		case MSG_GLOB_strerror:
			write_system_error(msg_stream);
			break;
		case MSG_GLOB_iline:
			write_fmt(msg_stream, "%s: %d: ", crt_file_name, crt_line_no);
			break;
		default:
			/*
			 * Arguments with unknown formatting passed
			 * to external handler.
			 */
			if (pp == NULL) {
				write_fmt(msg_stream, "<arg%d>", aid);
			} else {
				struct msg_user_handler *uhp;

				uhp = msg_uh_lookup(ch);
				if (uhp) {
					uhp->handler(ch, pp->as_vp);
					continue;
				} else
					write_fmt(msg_stream, "<no handler for %c>", ch);
			}
		}
	}
	return mp;
}

void
msg_print(int n, ...)
{
	MSG_DATA *mp;
	struct msg_sev *msp;
	va_list ap;

	va_start(ap, n);
	mp = msg_get(n, &msp, ap);
	va_end(ap);
	if (mp == NULL)
		return;
	if (msg_on_message)
		msg_on_message(mp);
	write_newline(msg_stream);
	ostream_flush(msg_stream);
	if (msp->stream != NULL)
		msg_stream = old_stream;
	if (mp->usage == MSG_SEV_FATAL || (mp->props & MSG_PROP_FATAL)) {
		tenapp_exit();
	}
}

/*
 * Output a simple printf style message.
 * This routine could be used for testing, or when catalog is not
 * available.
 */
void
msg_simple(const char *s, ...)
{
	va_list ap;

	va_start(ap, s);
	write_fmt(msg_stream, s, ap);
	va_end(ap);
	write_newline(msg_stream);
	ostream_flush(msg_stream);
}


/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * bostream.c - Binary output stream handling.
 *
 * This file implements the binary output stream facility specified in the
 * file "bostream.h".  See that file for more details.
 */

#include <stdio.h>
#include <stddef.h>

#include <shared/check.h>

#include <exds/common.h>
#include <exds/exception.h>
#include <exds/bostream.h>
#include <exds/cstring.h>

ExceptionT *XX_bostream_write_error = EXCEPTION("error writing to binary stream");

void
bostream_init(BOStreamT *bostream)
{
	bostream->name = NULL;
}

BoolT
bostream_open(BOStreamT *bostream, const char *name)
{
	if ((bostream->file = fopen(name, "w")) == NULL) {
		return FALSE;
	}

	bostream->name = name;
	return TRUE;
}

void
bostream_assign(BOStreamT *to, BOStreamT *from)
{
	to->file = from->file;
	to->name = from->name;
}

BoolT
bostream_is_open(BOStreamT *bostream)
{
	return bostream->name != NULL;
}

void
bostream_write_chars(BOStreamT *bostream, size_t length, const char *chars)
{
	size_t bytes_read = fwrite(chars, sizeof(char),
		length, bostream->file);

	if (bytes_read != length && ferror(bostream->file)) {
		char *name = cstring_duplicate(bostream->name);

		THROW_VALUE(XX_bostream_write_error, name);
		UNREACHED;
	}
}

void
bostream_write_bytes(BOStreamT *bostream, size_t length, const ByteT *bytes)
{
	size_t bytes_read = fwrite(bytes, sizeof(ByteT),
		length, bostream->file);

	if (bytes_read != length && ferror(bostream->file)) {
		char *name = cstring_duplicate(bostream->name);

		THROW_VALUE(XX_bostream_write_error, name);
		UNREACHED;
	}
}

void
bostream_write_byte(BOStreamT *bostream, ByteT byte)
{
	if (fputc((int) byte, bostream->file) == EOF && ferror(bostream->file)) {
		char *name = cstring_duplicate(bostream->name);

		THROW_VALUE(XX_bostream_write_error, name);
		UNREACHED;
	}
}

const char *
bostream_name(BOStreamT *bostream)
{
	return bostream->name;
}

void
bostream_close(BOStreamT *bostream)
{
	if (fclose(bostream->file)) {
		char *name = cstring_duplicate(bostream->name);

		THROW_VALUE(XX_bostream_write_error, name);
		UNREACHED;
	}

	bostream_init(bostream);
}

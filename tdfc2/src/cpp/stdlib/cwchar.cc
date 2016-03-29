/* $Id$ */

/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Standard wide string function definitions
 *
 * These routines define the standard C wide string functions which C++ overloads.
 * They are defined in terms of the C versions.
 */

#include <cstddef>

using namespace std;

extern "C" {
	wchar_t *wcschr(const wchar_t *, wchar_t);
	wchar_t *wcsrchr(const wchar_t *, wchar_t);
	wchar_t *wcspbrk(const wchar_t *, const wchar_t *);
	wchar_t *wcsstr(const wchar_t *, const wchar_t *);
	wchar_t *wmemchr(const wchar_t *, wchar_t, size_t);
}

namespace std {

	wchar_t *
	wcschr(wchar_t *s, wchar_t c)
	{
		return ::wcschr(s, c);
	}

	const wchar_t *
	wcschr(const wchar_t *s, wchar_t c)
	{
		return (const wchar_t *) ::wcschr(s, c);
	}

	wchar_t *
	wcsrchr(wchar_t *s, wchar_t c)
	{
		return ::wcsrchr(s, c);
	}

	const wchar_t *
	wcsrchr(const wchar_t *s, wchar_t c)
	{
		return (const wchar_t *) ::wcsrchr(s, c);
	}

	wchar_t *
	wcspbrk(wchar_t *s, const wchar_t *t)
	{
		return ::wcspbrk(s, t);
	}

	const wchar_t *
	wcspbrk(const wchar_t *s, const wchar_t *t)
	{
		return (const wchar_t *) ::wcspbrk(s, t);
	}

	wchar_t *
	wcsstr(wchar_t *s, const wchar_t *t)
	{
		return ::wcsstr(s, t);
	}

	const wchar_t *
	wcsstr(const wchar_t *s, const wchar_t *t)
	{
		return (const wchar_t *) ::wcsstr(s, t);
	}

	wchar_t *
	wmemchr(wchar_t *s, wchar_t c, size_t n)
	{
		return ::wmemchr(s, c, n);
	}

	const wchar_t *
	wmemchr(const wchar_t *s, wchar_t c, size_t n)
	{
		return (const wchar_t *) ::wmemchr(s, c, n);
	}

}


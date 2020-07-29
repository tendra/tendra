/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include "c89.h"
#define __WRONG_C95_WCHAR_H
#define __WRONG_C95_WCTYPE_H

/* Only implemented from version 2.4 */
#include <limits.h>
#ifndef _POSIX2_BC_BASE_MAX
#define __NO_WCHAR_H		1
#endif

#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(sparc)
#assert cpu(sparc)
#assert system(unix)
#unassert lint
#endif

#define sparc		1
#define sun		1
#define unix		1
#define __sparc		1
#define __sun		1
#define __svr4		1
#define __unix		1
#define __sparc__	1
#define __sun__		1
#define __svr4__	1
#define __unix__	1
#define _NO_LONGLONG	1

#pragma TenDRA begin
#pragma TenDRA no external declaration allow
#pragma TenDRA directive ident allow
#pragma TenDRA directive assert allow
#pragma TenDRA directive unassert allow
#pragma TenDRA directive include_next allow

#ifndef __NO_BUILTIN_ASSERTIONS
#assert machine(i386)
#assert cpu(i386)
#assert system(unix)
#unassert lint
#endif

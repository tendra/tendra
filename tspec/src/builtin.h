/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * BUILT IN TYPES
 *
 * These are the fundamental types which are built into the system.
 */

#ifdef BUILTIN
BUILTIN(type_char, "char", no_version, TYPE_INT);
BUILTIN(type_schar, "signed char", no_version, TYPE_SIGNED);
BUILTIN(type_uchar, "unsigned char", no_version, TYPE_UNSIGNED);
BUILTIN(type_short, "short", no_version, TYPE_SIGNED);
BUILTIN(type_sshort, "signed short", no_version, TYPE_SIGNED);
BUILTIN(type_ushort, "unsigned short", no_version, TYPE_UNSIGNED);
BUILTIN(type_int, "int", no_version, TYPE_SIGNED);
BUILTIN(type_sint, "signed int", no_version, TYPE_SIGNED);
BUILTIN(type_uint, "unsigned int", no_version, TYPE_UNSIGNED);
BUILTIN(type_long, "long", no_version, TYPE_SIGNED);
BUILTIN(type_slong, "signed long", no_version, TYPE_SIGNED);
BUILTIN(type_ulong, "unsigned long", no_version, TYPE_UNSIGNED);
BUILTIN(type_llong, "long long", no_version, TYPE_SIGNED);
BUILTIN(type_sllong, "signed long long", no_version, TYPE_SIGNED);
BUILTIN(type_ullong, "unsigned long long", no_version, TYPE_UNSIGNED);
BUILTIN(type_float, "float", no_version, TYPE_FLOAT);
BUILTIN(type_double, "double", no_version, TYPE_FLOAT);
BUILTIN(type_ldouble, "long double", no_version, TYPE_FLOAT);
BUILTIN(type_void, "void", no_version, TYPE_VOID);
BUILTIN(type_bottom, "void", 1, TYPE_VOID);
BUILTIN(type_printf, "const char *", 1, TYPE_GENERIC);
BUILTIN(type_scanf, "const char *", 2, TYPE_GENERIC);
BUILTIN(type_ellipsis, "...", no_version, TYPE_GENERIC);
BUILTIN(type_none, "void", 2, TYPE_VOID);
#undef BUILTIN
#endif


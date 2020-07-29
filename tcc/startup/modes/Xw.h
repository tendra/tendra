/*
 * Copyright 2011, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * STARTUP FILE FOR COMPILATION MODE XW
 *
 * Xw represents a "warning" oriented compilation mode.
 * Many non ANSI C features are permitted with a warning.
 * Extra checks are performed again producing warnings.
 * This will compile most code, possibly generating many
 * warnings that can be used to progressively improve the code.
 */

#pragma TenDRA declaration block Xw__startup begin
#pragma TenDRA begin

/* Xs level checks, but set to warn */
#pragma TenDRA complete struct/union analysis warning
#pragma TenDRA conversion analysis (int-int implicit) warning
#pragma TenDRA conversion analysis (int-enum implicit) warning
#pragma TenDRA conversion analysis (int-pointer) warning
#pragma TenDRA conversion analysis (pointer-pointer explicit) warning
#pragma TenDRA discard analysis warning
/* #pragma TenDRA fall into case warning */	/* too noisy */
#pragma TenDRA function pointer as pointer warning
#pragma TenDRA implicit function declaration warning
#pragma TenDRA implicit int type for function return warning
#pragma TenDRA incompatible interface declaration warning
#pragma TenDRA incompatible void return warning
#pragma TenDRA unreachable code warning
#pragma TenDRA variable analysis warning
#pragma TenDRA weak prototype analysis warning

#pragma TenDRA linkage resolution : (internal) warning

#pragma TenDRA no external declaration warning
#pragma TenDRA unknown pragma warning

#pragma TenDRA unmatched quote warning
#pragma TenDRA incompatible linkage warning
#pragma TenDRA writeable string literal warning

/* relaxations from Xa, but set to warn */
#pragma TenDRA unify external linkage warning

#pragma TenDRA unknown directive warning
#pragma TenDRA directive assert warning
#pragma TenDRA directive file warning
#pragma TenDRA directive ident warning
#pragma TenDRA directive unassert warning
#pragma TenDRA directive weak warning

#pragma TenDRA conditional lvalue disallow /* warning not possible */
#pragma TenDRA extra ; warning
#pragma TenDRA extra bitfield int type warning
#pragma TenDRA extra type definition warning
#pragma TenDRA ignore struct/union/enum tag warning
#pragma TenDRA text after directive warning
#pragma TenDRA unknown escape warning
#pragma TenDRA weak macro equality warning

#pragma TenDRA extra ... warning
#pragma TenDRA extra , warning
#pragma TenDRA incomplete type as object type warning
#pragma TenDRA incompatible type qualifier warning
#pragma TenDRA no directive/nline after ident warning
#pragma TenDRA no ident after # warning
#pragma TenDRA block function static warning
#pragma TenDRA indented # directive warning


#pragma TenDRA compatible type : char * == void * : warning
#pragma TenDRA character escape overflow warning
#pragma TenDRA no nline after file end warning
#pragma TenDRA bitfield overflow warning

/* Additional checks set to warn */

#pragma TenDRA assignment as bool warning
#pragma TenDRA const conditional warning
#pragma TenDRA directive as macro argument warning
#pragma TenDRA enum switch analysis warning
#pragma TenDRA extra ; after conditional warning
#pragma TenDRA integer operator analysis warning
#pragma TenDRA integer overflow analysis warning
#pragma TenDRA nested comment analysis warning
#pragma TenDRA operator precedence analysis warning
#pragma TenDRA unify incompatible string literal warning
#pragma TenDRA variable hiding analysis warning

#pragma TenDRA declaration block end


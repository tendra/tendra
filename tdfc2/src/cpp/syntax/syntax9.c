/*
 * Automatically generated from the files:
 *	syntax.sid
 * and
 *	syntax.act
 * by:
 *	sid
 */

/* BEGINNING OF HEADER */

#define __SID_SPLIT
#line 176 "syntax.act"


/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#include <stdio.h>

#include <shared/check.h>

#include <utility/config.h>
#include "c_types.h"

#include "ctype_ops.h"
#include "exp_ops.h"
#include "hashid_ops.h"
#include "id_ops.h"
#include "nspace_ops.h"
#include "type_ops.h"
#include <utility/error.h>
#include <utility/catalog.h>
#include <utility/buffer.h>
#include <utility/option.h>
#include <construct/access.h>
#include <construct/allocate.h>
#include <construct/assign.h>
#include <construct/basetype.h>
#include <construct/cast.h>
#include <construct/chktype.h>
#include <construct/class.h>
#include <parse/constant.h>
#include <construct/construct.h>
#include <construct/convert.h>
#include <construct/declare.h>
#include <construct/derive.h>
#include <output/dump.h>
#include <construct/exception.h>
#include <construct/expression.h>
#include <construct/function.h>
#include <parse/preproc.h>
#include <parse/hash.h>
#include <construct/identifier.h>
#include <construct/initialise.h>
#include <construct/inttype.h>
#include <construct/label.h>
#include <parse/lex.h>
#include <parse/literal.h>
#include <construct/member.h>
#include <construct/namespace.h>
#include <parse/parse.h>
#include <parse/pragma.h>
#include <parse/predict.h>
#include <parse/preproc.h>
#include <construct/redeclare.h>
#include <construct/rewrite.h>
#include <construct/statement.h>
#include <parse/symbols.h>
#include <construct/template.h>
#include <construct/tokdef.h>
#include <construct/token.h>
#include <construct/typeid.h>
#include <construct/variable.h>


/*
    These are the aliases for the compound types used in the parser.
*/

typedef LIST ( EXP ) SID_LIST_EXP ;
typedef LIST ( TYPE ) SID_LIST_TYPE ;


/*
    The function declarations are included at this point so that the
    type definitions are in scope.
*/

#include <syntax/syntax.h>


#line 98 "syntax9.c"

void
ZR888(BASE_TYPE *ZIb1, TYPE *ZIt1, CV_SPEC *ZIcv1, BASE_TYPE *ZObt, TYPE *ZOt, CV_SPEC *ZOcv)
{
	BASE_TYPE ZIbt;
	TYPE ZIt;
	CV_SPEC ZIcv;

	if ((CURRENT_TERMINAL) == 356) {
		return;
	}
	{
		TYPE ZIs;
		BASE_TYPE ZI1393;
		TYPE ZI1394;
		CV_SPEC ZI1395;
		BASE_TYPE ZIb2;
		TYPE ZIt2;
		CV_SPEC ZIcv2;

		/* BEGINNING OF ACTION: is_type_specifier */
		{
#line 2110 "syntax.act"

    /* Resolve type-specifiers from other declarators */
    (ZI0) = predict_tspec ( 0 ) ;
#line 125 "syntax9.c"
		}
		/* END OF ACTION: is_type_specifier */
		if (!ZI0)
			goto ZL2;
		/* BEGINNING OF ACTION: type_none */
		{
#line 1262 "syntax.act"

    (ZIs) = NULL_type ;
#line 135 "syntax9.c"
		}
		/* END OF ACTION: type_none */
		ZRtype_Hspecifier (ZIs, &ZI1393, &ZI1394, &ZI1395);
		ZR888 (&ZI1393, &ZI1394, &ZI1395, &ZIb2, &ZIt2, &ZIcv2);
		if ((CURRENT_TERMINAL) == 356) {
			RESTORE_LEXER;
			goto ZL1;
		}
		/* BEGINNING OF ACTION: btype_join */
		{
#line 1241 "syntax.act"

    if ( (*ZIb1) & (ZIb2) ) {
	(ZIbt) = join_pre_types ( (*ZIb1), (ZIb2) ) ;
    } else {
	(ZIbt) = ( (*ZIb1) | (ZIb2) ) ;
    }
#line 153 "syntax9.c"
		}
		/* END OF ACTION: btype_join */
		/* BEGINNING OF ACTION: type_join */
		{
#line 1296 "syntax.act"

    /* Join two partial types */
    if ( IS_NULL_type ( (*ZIt1) ) ) {
	(ZIt) = (ZIt2) ;
    } else if ( IS_NULL_type ( (ZIt2) ) ) {
	(ZIt) = (*ZIt1) ;
    } else {
	report ( crt_loc, ERR_dcl_type_simple_many ( (*ZIt1), (ZIt2) ) ) ;
	(ZIt) = (ZIt2) ;
    }
#line 169 "syntax9.c"
		}
		/* END OF ACTION: type_join */
		/* BEGINNING OF ACTION: cv_join */
		{
#line 1211 "syntax.act"

    CV_SPEC c = ( (*ZIcv1) & (ZIcv2) ) ;
    if ( c ) report ( crt_loc, ERR_dcl_type_cv_dup ( c ) ) ;
    (ZIcv) = ( (*ZIcv1) | (ZIcv2) ) ;
#line 179 "syntax9.c"
		}
		/* END OF ACTION: cv_join */
		goto ZL0;
	}
	UNREACHED;
ZL2:;
	switch (CURRENT_TERMINAL) {
	default:
		{
			ZIbt = *ZIb1;
			ZIt = *ZIt1;
			ZIcv = *ZIcv1;
		}
		break;
	}
	goto ZL0;
ZL1:;
	SAVE_LEXER (356);
	return;
ZL0:;
	*ZObt = ZIbt;
	*ZOt = ZIt;
	*ZOcv = ZIcv;
}

/* BEGINNING OF TRAILER */

#line 2163 "syntax.act"

#line 209 "syntax9.c"

/* END OF FILE */

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


#include "config.h"
#include "object.h"
#include "hash.h"
#include "name.h"
#include "type.h"
#include "utility.h"


/*
    CURRENT OBJECT

    This is the current object, which is affected by any file property
    changes.
*/

object *crt_object = null ;


/*
    SET A STRING VARIABLE

    This routine sets the string variable with identifier v to have value s.
*/

void set_string
    PROTO_N ( ( v, s ) )
    PROTO_T ( char *v X char *s )
{
    boolean known = 0 ;
    switch ( v [1] ) {
	case 'A' : {
	    if ( streq ( v, "$APINAME" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    i->api = s ;
		    i->prefix = null ;
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'B' : {
	    if ( streq ( v, "$BLOCKNAME" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    if ( *s ) {
			i->block = hack_name ( s, "_Aa0" ) ;
		    } else {
			i->block = null ;
		    }
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'F' : {
	    if ( streq ( v, "$FILE" ) ) {
		filename = s ;
		known = 1 ;
	    } else if ( streq ( v, "$FILENAME" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    i->file = s ;
		    i->prefix = null ;
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'I' : {
	    if ( streq ( v, "$INCLNAME" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    if ( *s ) {
			char *dir = output_incl_dir ;
			char *sub = null ;
			i->incl = include_name ( dir, i->api, s, sub ) ;
		    } else {
			i->incl = null ;
		    }
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'L' : {
	    if ( streq ( v, "$LINKAGE" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    if ( *s ) {
			i->linkage = s ;
		    } else {
			i->linkage = null ;
		    }
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'M' : {
	    if ( streq ( v, "$METHOD" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    i->method = s ;
		    if ( i->src && streq ( s, "TNC" ) ) {
			int n = ( int ) strlen ( i->src ) - 1 ;
			i->src [n] = 'p' ;
		    }
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'N' : {
	    if ( streq ( v, "$NAMESPACE" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    if ( *s ) {
			i->nspace = s ;
		    } else {
			i->nspace = null ;
		    }
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'P' : {
	    if ( streq ( v, "$PREFIX" ) ) {
		if ( crt_object ) crt_object->u.u_info->prefix = s ;
		known = 1 ;
	    } else if ( streq ( v, "$PROTECT" ) ) {
		if ( crt_object ) crt_object->u.u_info->protect = s ;
		known = 1 ;
	    }
	    break ;
	}
	case 'S' : {
	    if ( streq ( v, "$SOURCENAME" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    if ( *s ) {
			char *dir = output_src_dir ;
			char *sub = null ;
			i->src = src_name ( dir, i->api, s, sub ) ;
		    } else {
			i->src = null ;
		    }
		}
		known = 1 ;
	    } else if ( streq ( v, "$SUBSETNAME" ) ) {
		if ( crt_object ) {
		    info *i = crt_object->u.u_info ;
		    i->subset = s ;
		    i->prefix = null ;
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'V' : {
	    if ( streq ( v, "$VERSION" ) ) {
		if ( crt_object ) crt_object->u.u_info->version = s ;
		known = 1 ;
	    }
	    break ;
	}
    }
    if ( !known ) error ( ERR_SERIOUS, "Unknown string variable, '%s'", v ) ;
    return ;
}


/*
    SET AN INTEGER VARIABLE

    This routine sets the integer variable with identifier v to have value n.
*/

void set_integer
    PROTO_N ( ( v, n ) )
    PROTO_T ( char *v X int n )
{
    boolean known = 0 ;
    switch ( v [1] ) {
	case 'I' : {
	    if ( streq ( v, "$INTERFACE" ) ) {
		if ( crt_object ) {
		    crt_object->u.u_info->tokens = ( boolean ) n ;
		}
		known = 1 ;
	    }
	    break ;
	}
	case 'L' : {
	    if ( streq ( v, "$LINE" ) ) {
		line_no = n ;
		known = 1 ;
	    }
	    break ;
	}
	case 'U' : {
	    if ( streq ( v, "$UNIQUE" ) ) {
		unique_names = ( boolean ) n ;
		known = 1 ;
	    }
	    break ;
	}
	case 'V' : {
	    if ( streq ( v, "$VERBOSE" ) ) {
		verbose = n ;
		known = 1 ;
	    }
	    break ;
	}
    }
    if ( !known ) error ( ERR_SERIOUS, "Unknown integer variable, '%s'", v ) ;
    return ;
}

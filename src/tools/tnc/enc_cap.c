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
#include "types.h"
#include "enc_types.h"
#include "bitstream.h"
#include "encode.h"
#include "names.h"
#include "node.h"
#include "table.h"
#include "tdf.h"
#include "utility.h"


/*
    CURRENT BITSTREAM

    This is the main bitstream.
*/

static bitstream *crt_bitstream ;


/*
    NUMBERS OF EQUATIONS AND VARIABLE SORTS

    The number of equation types and variable sorts in the output capsule.
*/

static long eqn_total, var_total ;


/*
    LINKAGE INFORMATION ENCODING VARIABLES

    The tld2 unit gives information on the use, declaration and
    definition of the externally named tags and tokens.
*/

static bitstream *tld_bs ;


/*
    ALIGNMENT TAG ENCODING VARIABLES

    The alignment tag definitions are formed in the bitstream al_tag_defs_bs.
    There are al_tag_total alignment tags, of which al_tag_external have
    external names and al_tag_defs are defined.
*/

static long al_tag_total = 0 ;
static long al_tag_external = 0 ;
static long al_tag_defs = 0 ;
static bitstream *al_tag_defs_bs ;


/*
    AUXILIARY ALIGNMENT TAG ENCODING ROUTINE

    The alignment tag encoding variables are modified according to the
    construct p.
*/

static void enc_al_tag_aux
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    al_tag_info *info = get_al_tag_info ( p ) ;
    al_tag_total++ ;
    if ( p->ename ) {
	al_tag_external++ ;
	enc_tdf_int ( tld_bs, ( long ) ( info->def ? 5 : 1 ) ) ;
    }
    if ( info->def == null ) return ;
    al_tag_defs++ ;
    enc_aldef ( al_tag_defs_bs, p ) ;
    return ;
}


/*
    AUXILIARY ROUTINE FOR ENCODING ALIGNMENT TAG NAMES

    The external name (if any) of the alignment tag construct p is encoded.
*/

static void enc_al_tag_names
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    if ( p->ename == null ) return ;
    enc_external ( crt_bitstream, p ) ;
    return ;
}


/*
    TAG ENCODING VARIABLES

    The tag declarations are formed in the bitstream tag_decs_bs and
    the definitions in tag_defs_bs.  There are tag_total tags, of
    which tag_external have external names, tag_decs have declarations
    and tag_defs have definitions.
*/

static long tag_total = 0 ;
static long tag_external = 0 ;
static long tag_decs = 0 ;
static long tag_defs = 0 ;
static bitstream *tag_decs_bs ;
static bitstream *tag_defs_bs ;


/*
    AUXILIARY TAG ENCODING ROUTINE

    The tag encoding variables are modified according to the construct p.
*/

static void enc_tag_aux
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    tag_info *info = get_tag_info ( p ) ;
    tag_total++ ;
    if ( info->var == 3 ) return ;
    if ( p->ename ) {
	tag_external++ ;
	enc_tdf_int ( tld_bs, ( long ) ( info->def ? 7 : 3 ) ) ;
    }
    tag_decs++ ;
    enc_tagdec ( tag_decs_bs, p ) ;
    if ( info->def == null ) return ;
    tag_defs += enc_tagdef ( tag_defs_bs, p ) ;
    return ;
}


/*
    AUXILIARY ROUTINE FOR ENCODING TAG NAMES

    The external name (if any) of the tag construct p is encoded.
*/

static void enc_tag_names
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    tag_info *info = get_tag_info ( p ) ;
    if ( info->var == 3 ) return ;
    if ( p->ename == null ) return ;
    enc_external ( crt_bitstream, p ) ;
    return ;
}


/*
    TOKEN ENCODING VARIABLES

    The token declarations are formed in the bitstream tok_decs_bs and
    the definitions in tok_defs_bs.  There are tok_total tokens, of
    which tok_external have external names, tok_decs have declarations
    and tok_defs have definitions.
*/

static long tok_total = 0 ;
static long tok_external = 0 ;
static long tok_decs = 0 ;
static long tok_defs = 0 ;
static bitstream *tok_decs_bs ;
static bitstream *tok_defs_bs ;


/*
    AUXILIARY TOKEN ENCODING ROUTINE

    The token encoding variables are modified according to the construct p.
*/

static void enc_token_aux
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    tok_info *info = get_tok_info ( p ) ;
    if ( p->encoding == -1 ) return ;
    tok_total++ ;
    if ( info->dec == 0 ) return ;
    if ( p->ename ) {
	tok_external++ ;
	if ( info->def ) {
	    enc_tdf_int ( tld_bs, ( long ) 5 ) ;
	} else {
	    enc_tdf_int ( tld_bs, ( long ) 3 ) ;
	}
    }
    if ( info->def == null || !show_tokdefs ) {
	if ( info->args ) {
	    tok_decs++ ;
	    enc_tokdec ( tok_decs_bs, p ) ;
	}
    } else {
	tok_defs++ ;
	enc_tokdef ( tok_defs_bs, p ) ;
    }
    return ;
}


/*
    AUXILIARY ROUTINE FOR ENCODING TOKEN NAMES

    The external name (if any) of the token construct p is encoded.
*/

static void enc_token_names
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    tok_info *info = get_tok_info ( p ) ;
    if ( p->encoding == -1 ) return ;
    if ( info->dec == 0 ) return ;
    if ( p->ename == null ) return ;
    enc_external ( crt_bitstream, p ) ;
    return ;
}


/*
    LABEL ENCODING VARIABLES

    There are lab_total labels.
*/

static long lab_total = 0 ;


/*
    AUXILIARY LABEL ENCODING ROUTINE

    The label encoding variables are modified according to the construct p.
*/

/*ARGSUSED*/ static void enc_label_aux
    PROTO_N ( ( p ) )
    PROTO_T ( construct *p )
{
    UNUSED ( p ) ;
    lab_total++ ;
    return ;
}


/*
    ENCODE A SET OF LINKS

    A set of ntok token link, nalign alignment tag links and ntag tag
    nlinks are encoded into the bitstream p.  Since the same numbers
    are used for variable sorts in all the encoded units these links
    are identities.
*/

static void enc_links
    PROTO_N ( ( p, ntok, nalign, ntag ) )
    PROTO_T ( bitstream *p X long ntok X long nalign X long ntag )
{
    long i ;
    enc_tdf_int ( p, var_total ) ;
    if ( tok_total ) enc_tdf_int ( p, ntok ) ;
    if ( al_tag_total ) enc_tdf_int ( p, nalign ) ;
    if ( tag_total ) enc_tdf_int ( p, ntag ) ;
    enc_tdf_int ( p, var_total ) ;

    /* Token links */
    if ( tok_total ) {
	enc_tdf_int ( p, ntok ) ;
	for ( i = 0 ; i < ntok ; i++ ) {
	    enc_tdf_int ( p, i ) ;
	    enc_tdf_int ( p, i ) ;
	}
    }

    /* Alignment tag links */
    if ( al_tag_total ) {
	enc_tdf_int ( p, nalign ) ;
	for ( i = 0 ; i < nalign ; i++ ) {
	    enc_tdf_int ( p, i ) ;
	    enc_tdf_int ( p, i ) ;
	}
    }

    /* Tag links */
    if ( tag_total ) {
	enc_tdf_int ( p, ntag ) ;
	for ( i = 0 ; i < ntag ; i++ ) {
	    enc_tdf_int ( p, i ) ;
	    enc_tdf_int ( p, i ) ;
	}
    }
    return ;
}


/*
    EQUATION TYPES
*/

#define EQN_VERS	0
#define EQN_TLD		1
#define EQN_TOKDEC	2
#define EQN_TOKDEF	3
#define EQN_ALDEF	4
#define EQN_TAGDEC	5
#define EQN_TAGDEF	6


/*
    ENCODE AN EQUATION

    The ne equations of type t (see above) given in the bitstream q are
    encoded into the bitstream p.
*/

static void enc_equation
    PROTO_N ( ( p, ne, q, t ) )
    PROTO_T ( bitstream *p X long ne X bitstream *q X int t )
{
    long n ;
    bitstream *u ;

    if ( ne == 0 ) {
	/* There are no sets of equations */
	enc_tdf_int ( p, ( long ) 0 ) ;
	return ;
    }

    /* There is one set of equations */
    enc_tdf_int ( p, ( long ) 1 ) ;
    u = new_bitstream () ;

    /* Encode the links */
    switch ( t ) {
	case EQN_VERS : {
	    enc_links ( p, ( long ) 0, ( long ) 0, ( long ) 0 ) ;
	    enc_tdf_int ( u, ne ) ;
	    break ;
	}
	case EQN_TLD : {
	    enc_tdf_int ( p, ( long ) 0 ) ;
	    enc_tdf_int ( p, ( long ) 0 ) ;
	    break ;
	}
	case EQN_TOKDEC : {
	    enc_links ( p, tok_total, ( long ) 0, ( long ) 0 ) ;
	    enc_tdf_int ( u, ne ) ;
	    break ;
	}
	default : {
	    enc_links ( p, tok_total, al_tag_total, tag_total ) ;
	    enc_tdf_int ( u, lab_total ) ;
	    enc_tdf_int ( u, ne ) ;
	    break ;
	}
    }

    /* Append the body to the links */
    join_bitstreams ( u, q ) ;
    align_bitstream ( u ) ;

    /* Precede links and body by their length in bytes */
    n = bitstream_length ( u ) ;
    enc_tdf_int ( p, ( long ) ( n / BYTESIZE ) ) ;
    align_bitstream ( p ) ;
    join_bitstreams ( p, u ) ;
    return ;
}


/*
    VERSION NUMBERS

    These variables give the major and minor version numbers.
*/

static char *magic_number = VERSION_capsule ;
long version_major = VERSION_major ;
long version_minor = VERSION_minor ;


/*
    ENCODE A CAPSULE

    A complete capsule is encoded.
*/

void enc_capsule
    PROTO_Z ()
{
    long n ;
    bitstream *vers_bs ;
    char *m = magic_number ;
    bitstream *p = new_bitstream () ;

    /* Map to lowest applicable version number */
    if ( version_major == 4 ) {
	if ( version_minor == 1 ) version_minor = 0 ;
    }

    /* Initialize the equation bitstreams */
    tld_bs = new_bitstream () ;
    tok_decs_bs = new_bitstream () ;
    tok_defs_bs = new_bitstream () ;
    al_tag_defs_bs = new_bitstream () ;
    tag_decs_bs = new_bitstream () ;
    tag_defs_bs = new_bitstream () ;

    /* Analyse all the tags, tokens etc */
    enc_tdf_int ( tld_bs, ( long ) 1 ) ;
    apply_to_all ( enc_label_aux, SORT_label ) ;
    apply_to_all ( enc_token_aux, SORT_token ) ;
    apply_to_all ( enc_al_tag_aux, SORT_al_tag ) ;
    apply_to_all ( enc_tag_aux, SORT_tag ) ;

    /* Check on output options */
    if ( !show_tokdecs ) tok_decs = 0 ;
    if ( !show_tokdefs ) tok_defs = 0 ;
    if ( !show_aldefs ) al_tag_defs = 0 ;
    if ( !show_tagdecs ) tag_decs = 0 ;
    if ( !show_tagdefs ) tag_defs = 0 ;

    /* Output equation types */
    eqn_total = 2 ;
    if ( tok_decs ) eqn_total++ ;
    if ( tok_defs ) eqn_total++ ;
    if ( al_tag_defs ) eqn_total++ ;
    if ( tag_decs ) eqn_total++ ;
    if ( tag_defs ) eqn_total++ ;
    while ( n = ( long ) *( m++ ), n != 0 ) {
	enc_bits ( p, 8, n ) ;
    }
    enc_tdf_int ( p, version_major ) ;
    enc_tdf_int ( p, version_minor ) ;
    align_bitstream ( p ) ;
    enc_tdf_int ( p, eqn_total ) ;
    enc_aligned_string ( p, LINK_tld_props, ( long ) -1 ) ;
    enc_aligned_string ( p, LINK_version_props, ( long ) -1 ) ;
    if ( tok_decs ) {
	enc_aligned_string ( p, LINK_tokdec_props, ( long ) -1 ) ;
    }
    if ( tok_defs ) {
	enc_aligned_string ( p, LINK_tokdef_props, ( long ) -1 ) ;
    }
    if ( al_tag_defs ) {
	enc_aligned_string ( p, LINK_al_tagdef_props, ( long ) -1 ) ;
    }
    if ( tag_decs ) {
	enc_aligned_string ( p, LINK_tagdec_props, ( long ) -1 ) ;
    }
    if ( tag_defs ) {
	enc_aligned_string ( p, LINK_tagdef_props, ( long ) -1 ) ;
    }

    /* Adjust totals for removed variables */
    tok_total += sort_removed [ SORT_token ] ;
    tag_total += sort_removed [ SORT_tag ] ;
    al_tag_total += sort_removed [ SORT_al_tag ] ;
    lab_total += sort_removed [ SORT_label ] ;

    /* Output variable sorts */
    var_total = 0 ;
    if ( tok_total ) var_total++ ;
    if ( al_tag_total ) var_total++ ;
    if ( tag_total ) var_total++ ;
    enc_tdf_int ( p, var_total ) ;
    if ( tok_total ) {
	enc_aligned_string ( p, LINK_token, ( long ) -1 ) ;
	enc_tdf_int ( p, tok_total ) ;
    }
    if ( al_tag_total ) {
	enc_aligned_string ( p, LINK_al_tag, ( long ) -1 ) ;
	enc_tdf_int ( p, al_tag_total ) ;
    }
    if ( tag_total ) {
	enc_aligned_string ( p, LINK_tag, ( long ) -1 ) ;
	enc_tdf_int ( p, tag_total ) ;
    }

    /* Output external names */
    enc_tdf_int ( p, var_total ) ;
    crt_bitstream = p ;
    if ( tok_total ) {
	enc_tdf_int ( p, tok_external ) ;
	apply_to_all ( enc_token_names, SORT_token ) ;
    }
    if ( al_tag_total ) {
	enc_tdf_int ( p, al_tag_external ) ;
	apply_to_all ( enc_al_tag_names, SORT_al_tag ) ;
    }
    if ( tag_total ) {
	enc_tdf_int ( p, tag_external ) ;
	apply_to_all ( enc_tag_names, SORT_tag ) ;
    }

    /* Output equations */
    enc_tdf_int ( p, eqn_total ) ;
    enc_equation ( p, ( long ) 1, tld_bs, EQN_TLD ) ;
    vers_bs = new_bitstream () ;
    enc_version_bits ( vers_bs, ENC_make_version ) ;
    enc_tdf_int ( vers_bs, version_major ) ;
    enc_tdf_int ( vers_bs, version_minor ) ;
    enc_equation ( p, ( long ) 1, vers_bs, EQN_VERS ) ;
    if ( tok_decs ) enc_equation ( p, tok_decs, tok_decs_bs, EQN_TOKDEC ) ;
    if ( tok_defs ) enc_equation ( p, tok_defs, tok_defs_bs, EQN_TOKDEF ) ;
    if ( al_tag_defs ) {
	enc_equation ( p, al_tag_defs, al_tag_defs_bs, EQN_ALDEF ) ;
    }
    if ( tag_decs ) enc_equation ( p, tag_decs, tag_decs_bs, EQN_TAGDEC ) ;
    if ( tag_defs ) enc_equation ( p, tag_defs, tag_defs_bs, EQN_TAGDEF ) ;

    /* Send bitstream to output file */
    print_bitstream ( p ) ;
    return ;
}

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

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.2)
*/

#ifndef CMD_OPS_H_INCLUDED
#define CMD_OPS_H_INCLUDED

/* Operations for union COMMAND */

#define TAG_cmd( P )			( CHECK_NULL ( P )->ag_tag )


/* Operations for component line of union COMMAND */

#define cmd_line( P )			( CHECK_NULL ( P ) + 1 )


/* Operations for field simple of union COMMAND */

#define cmd_simple_tag			( ( unsigned ) 0 )
#define IS_cmd_simple( P )		( CHECK_NULL ( P )->ag_tag == 0 )

#define cmd_simple_text( P )		( CHECK_TAG ( ( P ), 0 ) + 2 )

#define MAKE_cmd_simple( line_, text_, calculus_cmd )\
    {\
	calculus *x186_ = GEN_calculus ( 3, TYPEID_cmd ) ;\
	x186_->ag_tag = 0 ;\
	COPY_int ( x186_ + 1, ( line_ ) ) ;\
	COPY_string ( x186_ + 2, ( text_ ) ) ;\
	( calculus_cmd ) = x186_ ;\
    }

#define DECONS_cmd_simple( line_, text_, calculus_cmd )\
    {\
	calculus *x187_ = CHECK_TAG ( ( calculus_cmd ), 0 ) ;\
	( line_ ) = DEREF_int ( x187_ + 1 ) ;\
	( text_ ) = DEREF_string ( x187_ + 2 ) ;\
    }

#define DESTROY_cmd_simple( destroyer_, line_, text_, calculus_cmd )\
    {\
	calculus *x188_ = CHECK_TAG ( ( calculus_cmd ), 0 ) ;\
	( line_ ) = DEREF_int ( x188_ + 1 ) ;\
	( text_ ) = DEREF_string ( x188_ + 2 ) ;\
	( destroyer_ ) ( x188_, ( unsigned ) 3 ) ;\
    }


/* Operations for field compound of union COMMAND */

#define cmd_compound_tag		( ( unsigned ) 1 )
#define IS_cmd_compound( P )		( CHECK_NULL ( P )->ag_tag == 1 )

#define cmd_compound_seq( P )		( CHECK_TAG ( ( P ), 1 ) + 2 )

#define MAKE_cmd_compound( line_, seq_, calculus_cmd )\
    {\
	calculus *x189_ = GEN_calculus ( 3, TYPEID_cmd ) ;\
	x189_->ag_tag = 1 ;\
	COPY_int ( x189_ + 1, ( line_ ) ) ;\
	COPY_list ( x189_ + 2, ( seq_ ) ) ;\
	( calculus_cmd ) = x189_ ;\
    }

#define DECONS_cmd_compound( line_, seq_, calculus_cmd )\
    {\
	calculus *x190_ = CHECK_TAG ( ( calculus_cmd ), 1 ) ;\
	( line_ ) = DEREF_int ( x190_ + 1 ) ;\
	( seq_ ) = DEREF_list ( x190_ + 2 ) ;\
    }

#define DESTROY_cmd_compound( destroyer_, line_, seq_, calculus_cmd )\
    {\
	calculus *x191_ = CHECK_TAG ( ( calculus_cmd ), 1 ) ;\
	( line_ ) = DEREF_int ( x191_ + 1 ) ;\
	( seq_ ) = DEREF_list ( x191_ + 2 ) ;\
	( destroyer_ ) ( x191_, ( unsigned ) 3 ) ;\
    }


/* Operations for field loop of union COMMAND */

#define cmd_loop_tag			( ( unsigned ) 2 )
#define IS_cmd_loop( P )		( CHECK_NULL ( P )->ag_tag == 2 )

#define cmd_loop_control( P )		( CHECK_TAG ( ( P ), 2 ) + 2 )
#define cmd_loop_body( P )		( CHECK_TAG ( ( P ), 2 ) + 3 )

#define MAKE_cmd_loop( line_, control_, body_, calculus_cmd )\
    {\
	calculus *x192_ = GEN_calculus ( 4, TYPEID_cmd ) ;\
	x192_->ag_tag = 2 ;\
	COPY_int ( x192_ + 1, ( line_ ) ) ;\
	COPY_string ( x192_ + 2, ( control_ ) ) ;\
	COPY_cmd ( x192_ + 3, ( body_ ) ) ;\
	( calculus_cmd ) = x192_ ;\
    }

#define DECONS_cmd_loop( line_, control_, body_, calculus_cmd )\
    {\
	calculus *x193_ = CHECK_TAG ( ( calculus_cmd ), 2 ) ;\
	( line_ ) = DEREF_int ( x193_ + 1 ) ;\
	( control_ ) = DEREF_string ( x193_ + 2 ) ;\
	( body_ ) = DEREF_cmd ( x193_ + 3 ) ;\
    }

#define DESTROY_cmd_loop( destroyer_, line_, control_, body_, calculus_cmd )\
    {\
	calculus *x194_ = CHECK_TAG ( ( calculus_cmd ), 2 ) ;\
	( line_ ) = DEREF_int ( x194_ + 1 ) ;\
	( control_ ) = DEREF_string ( x194_ + 2 ) ;\
	( body_ ) = DEREF_cmd ( x194_ + 3 ) ;\
	( destroyer_ ) ( x194_, ( unsigned ) 4 ) ;\
    }


/* Operations for field cond of union COMMAND */

#define cmd_cond_tag			( ( unsigned ) 3 )
#define IS_cmd_cond( P )		( CHECK_NULL ( P )->ag_tag == 3 )

#define cmd_cond_control( P )		( CHECK_TAG ( ( P ), 3 ) + 2 )
#define cmd_cond_true_code( P )		( CHECK_TAG ( ( P ), 3 ) + 3 )
#define cmd_cond_false_code( P )	( CHECK_TAG ( ( P ), 3 ) + 4 )

#define MAKE_cmd_cond( line_, control_, true_code_, false_code_, calculus_cmd )\
    {\
	calculus *x195_ = GEN_calculus ( 5, TYPEID_cmd ) ;\
	x195_->ag_tag = 3 ;\
	COPY_int ( x195_ + 1, ( line_ ) ) ;\
	COPY_string ( x195_ + 2, ( control_ ) ) ;\
	COPY_cmd ( x195_ + 3, ( true_code_ ) ) ;\
	COPY_cmd ( x195_ + 4, ( false_code_ ) ) ;\
	( calculus_cmd ) = x195_ ;\
    }

#define DECONS_cmd_cond( line_, control_, true_code_, false_code_, calculus_cmd )\
    {\
	calculus *x196_ = CHECK_TAG ( ( calculus_cmd ), 3 ) ;\
	( line_ ) = DEREF_int ( x196_ + 1 ) ;\
	( control_ ) = DEREF_string ( x196_ + 2 ) ;\
	( true_code_ ) = DEREF_cmd ( x196_ + 3 ) ;\
	( false_code_ ) = DEREF_cmd ( x196_ + 4 ) ;\
    }

#define DESTROY_cmd_cond( destroyer_, line_, control_, true_code_, false_code_, calculus_cmd )\
    {\
	calculus *x197_ = CHECK_TAG ( ( calculus_cmd ), 3 ) ;\
	( line_ ) = DEREF_int ( x197_ + 1 ) ;\
	( control_ ) = DEREF_string ( x197_ + 2 ) ;\
	( true_code_ ) = DEREF_cmd ( x197_ + 3 ) ;\
	( false_code_ ) = DEREF_cmd ( x197_ + 4 ) ;\
	( destroyer_ ) ( x197_, ( unsigned ) 5 ) ;\
    }


#endif

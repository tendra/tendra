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
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.2)
*/

#ifndef MSG_OPS_H_INCLUDED
#define MSG_OPS_H_INCLUDED

/* Operations for union MESSAGE */

#define TAG_msg( P )			( CHECK_NULL ( P )->ag_tag )


/* Operations for field param of union MESSAGE */

#define msg_param_tag			( ( unsigned ) 0 )
#define IS_msg_param( P )		( CHECK_NULL ( P )->ag_tag == 0 )

#define msg_param_arg( P )		( CHECK_TAG ( ( P ), 0 ) + 1 )

#define MAKE_msg_param( arg_, errors_msg )\
    {\
	errors *x53_ = GEN_errors ( 2, TYPEID_msg ) ;\
	x53_->ag_tag = 0 ;\
	COPY_param ( x53_ + 1, ( arg_ ) ) ;\
	( errors_msg ) = x53_ ;\
    }

#define DECONS_msg_param( arg_, errors_msg )\
    {\
	errors *x54_ = CHECK_TAG ( ( errors_msg ), 0 ) ;\
	( arg_ ) = DEREF_param ( x54_ + 1 ) ;\
    }

#define DESTROY_msg_param( destroyer_, arg_, errors_msg )\
    {\
	errors *x55_ = CHECK_TAG ( ( errors_msg ), 0 ) ;\
	( arg_ ) = DEREF_param ( x55_ + 1 ) ;\
	( destroyer_ ) ( x55_, ( unsigned ) 2 ) ;\
    }


/* Operations for field text of union MESSAGE */

#define msg_text_tag			( ( unsigned ) 1 )
#define IS_msg_text( P )		( CHECK_NULL ( P )->ag_tag == 1 )

#define msg_text_arg( P )		( CHECK_TAG ( ( P ), 1 ) + 1 )

#define MAKE_msg_text( arg_, errors_msg )\
    {\
	errors *x56_ = GEN_errors ( 2, TYPEID_msg ) ;\
	x56_->ag_tag = 1 ;\
	COPY_string ( x56_ + 1, ( arg_ ) ) ;\
	( errors_msg ) = x56_ ;\
    }

#define DECONS_msg_text( arg_, errors_msg )\
    {\
	errors *x57_ = CHECK_TAG ( ( errors_msg ), 1 ) ;\
	( arg_ ) = DEREF_string ( x57_ + 1 ) ;\
    }

#define DESTROY_msg_text( destroyer_, arg_, errors_msg )\
    {\
	errors *x58_ = CHECK_TAG ( ( errors_msg ), 1 ) ;\
	( arg_ ) = DEREF_string ( x58_ + 1 ) ;\
	( destroyer_ ) ( x58_, ( unsigned ) 2 ) ;\
    }


#endif

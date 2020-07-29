/*
    AUTOMATICALLY GENERATED FROM ALGEBRA errors (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef MSG_OPS_H_INCLUDED
#define MSG_OPS_H_INCLUDED

/* Operations for union MESSAGE */

#define TAG_msg(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for field param of union MESSAGE */

#define msg_param_tag			((unsigned)0)
#define IS_msg_param(P)			(CHECK_NULL(P)->ag_tag == 0)

#define msg_param_arg(P)		(CHECK_TAG((P), 0) + 1)

#define MAKE_msg_param(arg_, errors_msg)\
    {\
	errors *x53_ = GEN_errors(2, TYPEID_msg);\
	x53_->ag_tag = 0;\
	COPY_param(x53_ + 1, (arg_));\
	(errors_msg) = x53_;\
    }

#define DECONS_msg_param(arg_, errors_msg)\
    {\
	errors *x54_ = CHECK_TAG((errors_msg), 0);\
	(arg_) = DEREF_param(x54_ + 1);\
    }

#define DESTROY_msg_param(destroyer_, arg_, errors_msg)\
    {\
	errors *x55_ = CHECK_TAG((errors_msg), 0);\
	(arg_) = DEREF_param(x55_ + 1);\
	(destroyer_)(x55_, (unsigned)2);\
    }


/* Operations for field text of union MESSAGE */

#define msg_text_tag			((unsigned)1)
#define IS_msg_text(P)			(CHECK_NULL(P)->ag_tag == 1)

#define msg_text_arg(P)			(CHECK_TAG((P), 1) + 1)

#define MAKE_msg_text(arg_, errors_msg)\
    {\
	errors *x56_ = GEN_errors(2, TYPEID_msg);\
	x56_->ag_tag = 1;\
	COPY_string(x56_ + 1, (arg_));\
	(errors_msg) = x56_;\
    }

#define DECONS_msg_text(arg_, errors_msg)\
    {\
	errors *x57_ = CHECK_TAG((errors_msg), 1);\
	(arg_) = DEREF_string(x57_ + 1);\
    }

#define DESTROY_msg_text(destroyer_, arg_, errors_msg)\
    {\
	errors *x58_ = CHECK_TAG((errors_msg), 1);\
	(arg_) = DEREF_string(x58_ + 1);\
	(destroyer_)(x58_, (unsigned)2);\
    }


#endif

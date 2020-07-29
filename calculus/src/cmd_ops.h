/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA calculus (VERSION 1.2)
    BY calculus (VERSION 1.2)
*/

#ifndef CMD_OPS_H_INCLUDED
#define CMD_OPS_H_INCLUDED

/* Operations for union COMMAND */

#define TAG_cmd(P)			((P)->ag_tag)


/* Operations for component line of union COMMAND */

#define cmd_line(P)			((P) + 1)


/* Operations for field simple of union COMMAND */

#define cmd_simple_tag			((unsigned)0)
#define IS_cmd_simple(P)		((P)->ag_tag == 0)

#define cmd_simple_text(P)		((P) + 2)

#define MAKE_cmd_simple(line_, text_, calculus_cmd)\
    {\
	calculus *x203_ = GEN_calculus(3, TYPEID_cmd);\
	x203_->ag_tag = 0;\
	COPY_int(x203_ + 1, (line_));\
	COPY_string(x203_ + 2, (text_));\
	(calculus_cmd) = x203_;\
    }

#define DECONS_cmd_simple(line_, text_, calculus_cmd)\
    {\
	calculus *x204_ = (calculus_cmd);\
	(line_) = DEREF_int(x204_ + 1);\
	(text_) = DEREF_string(x204_ + 2);\
    }

#define DESTROY_cmd_simple(destroyer_, line_, text_, calculus_cmd)\
    {\
	calculus *x205_ = (calculus_cmd);\
	(line_) = DEREF_int(x205_ + 1);\
	(text_) = DEREF_string(x205_ + 2);\
	(destroyer_)(x205_, (unsigned)3);\
    }


/* Operations for field compound of union COMMAND */

#define cmd_compound_tag		((unsigned)1)
#define IS_cmd_compound(P)		((P)->ag_tag == 1)

#define cmd_compound_seq(P)		((P) + 2)

#define MAKE_cmd_compound(line_, seq_, calculus_cmd)\
    {\
	calculus *x206_ = GEN_calculus(3, TYPEID_cmd);\
	x206_->ag_tag = 1;\
	COPY_int(x206_ + 1, (line_));\
	COPY_list(x206_ + 2, (seq_));\
	(calculus_cmd) = x206_;\
    }

#define DECONS_cmd_compound(line_, seq_, calculus_cmd)\
    {\
	calculus *x207_ = (calculus_cmd);\
	(line_) = DEREF_int(x207_ + 1);\
	(seq_) = DEREF_list(x207_ + 2);\
    }

#define DESTROY_cmd_compound(destroyer_, line_, seq_, calculus_cmd)\
    {\
	calculus *x208_ = (calculus_cmd);\
	(line_) = DEREF_int(x208_ + 1);\
	(seq_) = DEREF_list(x208_ + 2);\
	(destroyer_)(x208_, (unsigned)3);\
    }


/* Operations for field loop of union COMMAND */

#define cmd_loop_tag			((unsigned)2)
#define IS_cmd_loop(P)			((P)->ag_tag == 2)

#define cmd_loop_control(P)		((P) + 2)
#define cmd_loop_body(P)		((P) + 3)

#define MAKE_cmd_loop(line_, control_, body_, calculus_cmd)\
    {\
	calculus *x209_ = GEN_calculus(4, TYPEID_cmd);\
	x209_->ag_tag = 2;\
	COPY_int(x209_ + 1, (line_));\
	COPY_string(x209_ + 2, (control_));\
	COPY_cmd(x209_ + 3, (body_));\
	(calculus_cmd) = x209_;\
    }

#define DECONS_cmd_loop(line_, control_, body_, calculus_cmd)\
    {\
	calculus *x210_ = (calculus_cmd);\
	(line_) = DEREF_int(x210_ + 1);\
	(control_) = DEREF_string(x210_ + 2);\
	(body_) = DEREF_cmd(x210_ + 3);\
    }

#define DESTROY_cmd_loop(destroyer_, line_, control_, body_, calculus_cmd)\
    {\
	calculus *x211_ = (calculus_cmd);\
	(line_) = DEREF_int(x211_ + 1);\
	(control_) = DEREF_string(x211_ + 2);\
	(body_) = DEREF_cmd(x211_ + 3);\
	(destroyer_)(x211_, (unsigned)4);\
    }


/* Operations for field cond of union COMMAND */

#define cmd_cond_tag			((unsigned)3)
#define IS_cmd_cond(P)			((P)->ag_tag == 3)

#define cmd_cond_control(P)		((P) + 2)
#define cmd_cond_true_code(P)		((P) + 3)
#define cmd_cond_false_code(P)		((P) + 4)

#define MAKE_cmd_cond(line_, control_, true_code_, false_code_, calculus_cmd)\
    {\
	calculus *x212_ = GEN_calculus(5, TYPEID_cmd);\
	x212_->ag_tag = 3;\
	COPY_int(x212_ + 1, (line_));\
	COPY_string(x212_ + 2, (control_));\
	COPY_cmd(x212_ + 3, (true_code_));\
	COPY_cmd(x212_ + 4, (false_code_));\
	(calculus_cmd) = x212_;\
    }

#define DECONS_cmd_cond(line_, control_, true_code_, false_code_, calculus_cmd)\
    {\
	calculus *x213_ = (calculus_cmd);\
	(line_) = DEREF_int(x213_ + 1);\
	(control_) = DEREF_string(x213_ + 2);\
	(true_code_) = DEREF_cmd(x213_ + 3);\
	(false_code_) = DEREF_cmd(x213_ + 4);\
    }

#define DESTROY_cmd_cond(destroyer_, line_, control_, true_code_, false_code_, calculus_cmd)\
    {\
	calculus *x214_ = (calculus_cmd);\
	(line_) = DEREF_int(x214_ + 1);\
	(control_) = DEREF_string(x214_ + 2);\
	(true_code_) = DEREF_cmd(x214_ + 3);\
	(false_code_) = DEREF_cmd(x214_ + 4);\
	(destroyer_)(x214_, (unsigned)5);\
    }


#endif

/*
    AUTOMATICALLY GENERATED FROM ALGEBRA tdf (VERSION 1.0)
    BY calculus (VERSION 1.3)
*/

#ifndef CMD_OPS_H_INCLUDED
#define CMD_OPS_H_INCLUDED

/* Operations for union COMMAND */

#define TAG_cmd(P)			(CHECK_NULL(P)->ag_tag)


/* Operations for component line of union COMMAND */

#define cmd_line(P)			(CHECK_NULL(P) + 1)


/* Operations for field simple of union COMMAND */

#define cmd_simple_tag			((unsigned)0)
#define IS_cmd_simple(P)		(CHECK_NULL(P)->ag_tag == 0)

#define cmd_simple_text(P)		(CHECK_TAG((P), 0) + 2)

#define MAKE_cmd_simple(line_, text_, tdf_cmd)\
    {\
	tdf *x102_ = GEN_tdf(3, TYPEID_cmd);\
	x102_->ag_tag = 0;\
	COPY_int(x102_ + 1, (line_));\
	COPY_string(x102_ + 2, (text_));\
	(tdf_cmd) = x102_;\
    }

#define DECONS_cmd_simple(line_, text_, tdf_cmd)\
    {\
	tdf *x103_ = CHECK_TAG((tdf_cmd), 0);\
	(line_) = DEREF_int(x103_ + 1);\
	(text_) = DEREF_string(x103_ + 2);\
    }

#define DESTROY_cmd_simple(destroyer_, line_, text_, tdf_cmd)\
    {\
	tdf *x104_ = CHECK_TAG((tdf_cmd), 0);\
	(line_) = DEREF_int(x104_ + 1);\
	(text_) = DEREF_string(x104_ + 2);\
	(destroyer_)(x104_, (unsigned)3);\
    }


/* Operations for field compound of union COMMAND */

#define cmd_compound_tag		((unsigned)1)
#define IS_cmd_compound(P)		(CHECK_NULL(P)->ag_tag == 1)

#define cmd_compound_seq(P)		(CHECK_TAG((P), 1) + 2)

#define MAKE_cmd_compound(line_, seq_, tdf_cmd)\
    {\
	tdf *x105_ = GEN_tdf(3, TYPEID_cmd);\
	x105_->ag_tag = 1;\
	COPY_int(x105_ + 1, (line_));\
	COPY_list(x105_ + 2, (seq_));\
	(tdf_cmd) = x105_;\
    }

#define DECONS_cmd_compound(line_, seq_, tdf_cmd)\
    {\
	tdf *x106_ = CHECK_TAG((tdf_cmd), 1);\
	(line_) = DEREF_int(x106_ + 1);\
	(seq_) = DEREF_list(x106_ + 2);\
    }

#define DESTROY_cmd_compound(destroyer_, line_, seq_, tdf_cmd)\
    {\
	tdf *x107_ = CHECK_TAG((tdf_cmd), 1);\
	(line_) = DEREF_int(x107_ + 1);\
	(seq_) = DEREF_list(x107_ + 2);\
	(destroyer_)(x107_, (unsigned)3);\
    }


/* Operations for field loop of union COMMAND */

#define cmd_loop_tag			((unsigned)2)
#define IS_cmd_loop(P)			(CHECK_NULL(P)->ag_tag == 2)

#define cmd_loop_control(P)		(CHECK_TAG((P), 2) + 2)
#define cmd_loop_body(P)		(CHECK_TAG((P), 2) + 3)

#define MAKE_cmd_loop(line_, control_, body_, tdf_cmd)\
    {\
	tdf *x108_ = GEN_tdf(4, TYPEID_cmd);\
	x108_->ag_tag = 2;\
	COPY_int(x108_ + 1, (line_));\
	COPY_string(x108_ + 2, (control_));\
	COPY_cmd(x108_ + 3, (body_));\
	(tdf_cmd) = x108_;\
    }

#define DECONS_cmd_loop(line_, control_, body_, tdf_cmd)\
    {\
	tdf *x109_ = CHECK_TAG((tdf_cmd), 2);\
	(line_) = DEREF_int(x109_ + 1);\
	(control_) = DEREF_string(x109_ + 2);\
	(body_) = DEREF_cmd(x109_ + 3);\
    }

#define DESTROY_cmd_loop(destroyer_, line_, control_, body_, tdf_cmd)\
    {\
	tdf *x110_ = CHECK_TAG((tdf_cmd), 2);\
	(line_) = DEREF_int(x110_ + 1);\
	(control_) = DEREF_string(x110_ + 2);\
	(body_) = DEREF_cmd(x110_ + 3);\
	(destroyer_)(x110_, (unsigned)4);\
    }


/* Operations for field cond of union COMMAND */

#define cmd_cond_tag			((unsigned)3)
#define IS_cmd_cond(P)			(CHECK_NULL(P)->ag_tag == 3)

#define cmd_cond_control(P)		(CHECK_TAG((P), 3) + 2)
#define cmd_cond_true_code(P)		(CHECK_TAG((P), 3) + 3)
#define cmd_cond_false_code(P)		(CHECK_TAG((P), 3) + 4)

#define MAKE_cmd_cond(line_, control_, true_code_, false_code_, tdf_cmd)\
    {\
	tdf *x111_ = GEN_tdf(5, TYPEID_cmd);\
	x111_->ag_tag = 3;\
	COPY_int(x111_ + 1, (line_));\
	COPY_string(x111_ + 2, (control_));\
	COPY_cmd(x111_ + 3, (true_code_));\
	COPY_cmd(x111_ + 4, (false_code_));\
	(tdf_cmd) = x111_;\
    }

#define DECONS_cmd_cond(line_, control_, true_code_, false_code_, tdf_cmd)\
    {\
	tdf *x112_ = CHECK_TAG((tdf_cmd), 3);\
	(line_) = DEREF_int(x112_ + 1);\
	(control_) = DEREF_string(x112_ + 2);\
	(true_code_) = DEREF_cmd(x112_ + 3);\
	(false_code_) = DEREF_cmd(x112_ + 4);\
    }

#define DESTROY_cmd_cond(destroyer_, line_, control_, true_code_, false_code_, tdf_cmd)\
    {\
	tdf *x113_ = CHECK_TAG((tdf_cmd), 3);\
	(line_) = DEREF_int(x113_ + 1);\
	(control_) = DEREF_string(x113_ + 2);\
	(true_code_) = DEREF_cmd(x113_ + 3);\
	(false_code_) = DEREF_cmd(x113_ + 4);\
	(destroyer_)(x113_, (unsigned)5);\
    }


/* Operations for field use of union COMMAND */

#define cmd_use_tag			((unsigned)4)
#define IS_cmd_use(P)			(CHECK_NULL(P)->ag_tag == 4)

#define cmd_use_sort(P)			(CHECK_TAG((P), 4) + 2)
#define cmd_use_cons(P)			(CHECK_TAG((P), 4) + 3)

#define MAKE_cmd_use(line_, sort_, cons_, tdf_cmd)\
    {\
	tdf *x114_ = GEN_tdf(4, TYPEID_cmd);\
	x114_->ag_tag = 4;\
	COPY_int(x114_ + 1, (line_));\
	COPY_string(x114_ + 2, (sort_));\
	COPY_string(x114_ + 3, (cons_));\
	(tdf_cmd) = x114_;\
    }

#define DECONS_cmd_use(line_, sort_, cons_, tdf_cmd)\
    {\
	tdf *x115_ = CHECK_TAG((tdf_cmd), 4);\
	(line_) = DEREF_int(x115_ + 1);\
	(sort_) = DEREF_string(x115_ + 2);\
	(cons_) = DEREF_string(x115_ + 3);\
    }

#define DESTROY_cmd_use(destroyer_, line_, sort_, cons_, tdf_cmd)\
    {\
	tdf *x116_ = CHECK_TAG((tdf_cmd), 4);\
	(line_) = DEREF_int(x116_ + 1);\
	(sort_) = DEREF_string(x116_ + 2);\
	(cons_) = DEREF_string(x116_ + 3);\
	(destroyer_)(x116_, (unsigned)4);\
    }


/* Operations for field special of union COMMAND */

#define cmd_special_tag			((unsigned)5)
#define IS_cmd_special(P)		(CHECK_NULL(P)->ag_tag == 5)

#define cmd_special_sort(P)		(CHECK_TAG((P), 5) + 2)
#define cmd_special_cons(P)		(CHECK_TAG((P), 5) + 3)

#define MAKE_cmd_special(line_, sort_, cons_, tdf_cmd)\
    {\
	tdf *x117_ = GEN_tdf(4, TYPEID_cmd);\
	x117_->ag_tag = 5;\
	COPY_int(x117_ + 1, (line_));\
	COPY_string(x117_ + 2, (sort_));\
	COPY_string(x117_ + 3, (cons_));\
	(tdf_cmd) = x117_;\
    }

#define DECONS_cmd_special(line_, sort_, cons_, tdf_cmd)\
    {\
	tdf *x118_ = CHECK_TAG((tdf_cmd), 5);\
	(line_) = DEREF_int(x118_ + 1);\
	(sort_) = DEREF_string(x118_ + 2);\
	(cons_) = DEREF_string(x118_ + 3);\
    }

#define DESTROY_cmd_special(destroyer_, line_, sort_, cons_, tdf_cmd)\
    {\
	tdf *x119_ = CHECK_TAG((tdf_cmd), 5);\
	(line_) = DEREF_int(x119_ + 1);\
	(sort_) = DEREF_string(x119_ + 2);\
	(cons_) = DEREF_string(x119_ + 3);\
	(destroyer_)(x119_, (unsigned)4);\
    }


#endif

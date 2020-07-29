# TPL

## Introduction

The basic idea is to produce the TDF bit encoding using language constructions
closely mapped to the TDF constructors given in the specification
document. These constructions have been produced automatically with make_tdf.

The template files are in templ/.
The machine-readable TDF spec is at tdf/db/def_4_0.db.

For every non-primitive TDF constructor, a macro has been defined to output
that construct. The macro name is given by prefixing o_ to the name of the
constructor, e.g. o_make_top for the EXP make_top. Each o_ macro has the same
number and order of parameters as its corresponding TDF constructor. The
expansion of the macro will check that each parameter outputs the correct TDF
SORT.

The o_ macros are defined in encodings.h, except for o_token_def which is
defined in streams.h.

There are also procedures for outputing primitive SORTS; e.g. out_tdfbool(b)
outputs b as a TDFBOOL. Only output procedures for primitive SORTs which
have simple representations in C have been provided, e.g. out_tdfint32(x)
outputs the 32 bit integer x as a TDFINT.

The out_ procedures are defined in streams.c

TDF *current_TDF represents the current output bitstream, which all output
macros and procedures write to. It is defined in streams.c.

## An example

To give a flavour of the intended use of the tool, in order to
produce the TDF for an assignment, one does:

o_assign(LHS, RHS)

where LHS and RHS are pieces of code which will output the EXPs for
the source and destination of the assignment. For example, LHS for a
simple variable as destination could be:

o_obtain_tag(o_make_tag(out_tdfint32(A)))

where A is the number chosen by the compiler for the variable. Of
course, it is unlikely that a compiler would do this directly. LHS
will usually be some conditional code which might choose this
expansion from its analysis of the program being compiled. Both LHS
and RHS (in common with all the parameters of the o_ macros) are
statements (not expessions!) whose sequencing is controlled by the
macro.

The expansion of o_assign (see encodings.h) is:

#define o_assign(p_arg1,p_arg2) \
{ \
  out_basic_int(e_assign, 7); \
  p_arg1; ASSERT_SORT(s_exp); \
  p_arg2; ASSERT_SORT(s_exp); \
  SET_RSORT(s_exp); \
}

The encoding for the EXP assign is given by e_assign (in enc_nos.h) while
s_exp (also in enc_nos.h) is a number chosen to represent the sort of an
EXP. The procedure out_basic_int (in streams.c) is the most primitive output
routine. The macros ASSERT_SORT and SET_RSORT are defined in errors.h and
used to implement the SORT checking.

/*
 * Copyright 2015, The TenDRA Project.
 *
 * See doc/copyright/ for the full copyright terms.
 */

#ifndef CONSTRUCT_CALLOP_H
#define CONSTRUCT_CALLOP_H

exp find_named_tag(char *n, shape s);
char *fn_of_op(int nm, int sngd);

exp TDFcallop1(error_treatment ov_err, exp arg1, int n);
exp TDFcallop2(error_treatment ov_err, exp arg1, exp arg2, int n);
exp TDFcallop3(exp arg1, exp arg2, int n);
exp TDFcallop4(exp arg1, int n);

exp TDFwithet(error_treatment ov_err, exp e);
exp TDFcallaux(error_treatment ov_err, exp arg1, char *nm, shape s);

#endif


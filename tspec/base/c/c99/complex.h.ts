# $Id$

# Copyright 2015, The TenDRA Project.
#
# See doc/copyright/ for the full copyright terms.

+TYPE ~float_Complex;
+TYPE ~float_Imaginary;

# 7.3.1.2
+DEFINE complex %% _Complex %%;
+CONST ~float_Complex _Complex;

# 7.3.1.3
+IFDEF ~have_imaginary
+DEFINE imaginary %% _Imaginary %%;
+CONST ~float_Imaginary _Imaginary;
+ENDIF

# 7.3.1.4
+IFDEF ~have_imaginary
+DEFINE I.1 %% _Imaginary_I %%;
+ELSE
+DEFINE I.2 %% _Complex_I   %%;
+ENDIF


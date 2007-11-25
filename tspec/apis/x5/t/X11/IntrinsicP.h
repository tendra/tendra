#   		 Crown Copyright (c) 1997
#   
#   This TenDRA(r) Computer Program is subject to Copyright
#   owned by the United Kingdom Secretary of State for Defence
#   acting through the Defence Evaluation and Research Agency
#   (DERA).  It is made available to Recipients with a
#   royalty-free licence for its use, reproduction, transfer
#   to other parties and amendment for any purpose not excluding
#   product development provided that any such use et cetera
#   shall be deemed to be acceptance of the following conditions:-
#   
#       (1) Its Recipients shall ensure that this Notice is
#       reproduced upon any copies or amended versions of it;
#   
#       (2) Any amended version of it shall be clearly marked to
#       show both the nature of and the organisation responsible
#       for the relevant amendment or amendments;
#   
#       (3) Its onward transfer from a recipient to another
#       party shall be deemed to be that party's acceptance of
#       these conditions;
#   
#       (4) DERA gives no warranty or assurance as to its
#       quality or suitability for any purpose and DERA accepts
#       no liability whatsoever in relation to any use to which
#       it may be put.
#
%%
#ifndef __X11_P_HEADERS
#error Unauthorized access to X11 P headers
#endif
%%

+DEFINE __TDF_INTRINSIC_P_INCLUDED %% %% ;	# Flag for Motif 1.2

+USE "x5/t", "X11/Intrinsic.h" ;

+SUBSET "intrinsix" := {
    +USE "x5/t", "X11/Intrinsic.h" ;

    # Widget Version Numbers (1.6.4)
    +TYPE ( int ) XtVersionType ;
    +CONST XtVersionType XtVersion, XtVersionDontCheck ;


    # Widget Subclass Verification (1.6.6)
    +MACRO void XtCheckSubclass ( Widget, WidgetClass, String ) ;


    # Class Initialization (1.6.8)
    +TYPEDEF void ( *XtProc ) () ;
    +TYPEDEF void ( *XtWidgetClassProc ) ( WidgetClass ) ;


    # Inheritance of Superclass Operations (1.6.10)
    +FUNC void _XtInherit ( void ) ;
} ;


# Widget Definitions

+USE "x5/t", "X11/CoreP.h" ;
+USE "x5/t", "X11/CompositeP.h" ;
+USE "x5/t", "X11/ConstrainP.h" ;
+USE "x5/t", "X11/ObjectP.h" ;
+USE "x5/t", "X11/RectObjP.h" ;

+FIELD (struct) WidgetClassRec := {
    CoreClassPart core_class ;
} ;

+EXP lvalue WidgetClassRec widgetClassRec ;

+FIELD (struct) WidgetRec := {
    CorePart core ;
} ;

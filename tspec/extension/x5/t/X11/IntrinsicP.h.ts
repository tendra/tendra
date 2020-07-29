# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __X11_P_HEADERS
#error Unauthorized access to X11 P headers
#endif
%%

+DEFINE __TDF_INTRINSIC_P_INCLUDED %% %% ;	# Flag for Motif 1.2

+USE "x5/t", "X11/Intrinsic.h.ts" ;

+SUBSET "intrinsix" := {
    +USE "x5/t", "X11/Intrinsic.h.ts" ;

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

+USE "x5/t", "X11/CoreP.h.ts" ;
+USE "x5/t", "X11/CompositeP.h.ts" ;
+USE "x5/t", "X11/ConstrainP.h.ts" ;
+USE "x5/t", "X11/ObjectP.h.ts" ;
+USE "x5/t", "X11/RectObjP.h.ts" ;

+FIELD (struct) WidgetClassRec := {
    CoreClassPart core_class ;
} ;

+EXP lvalue WidgetClassRec widgetClassRec ;

+FIELD (struct) WidgetRec := {
    CorePart core ;
} ;

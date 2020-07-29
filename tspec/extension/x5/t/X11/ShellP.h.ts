# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


%%
#ifndef __X11_P_HEADERS
#error Unauthorized access to X11 P headers
#endif
%%

+USE "x5/t", "X11/Shell.h.ts" ;
+USE "x5/t", "X11/IntrinsicP.h.ts" ;


# ShellClassPart Definition (4.1.1)

+FIELD ( struct ) ShellClassPart := { XtPointer extension ; } ;
+FIELD ( struct ) OverrideShellClassPart := { XtPointer extension ; } ;
+FIELD ( struct ) WMShellClassPart := { XtPointer extension ; } ;
+FIELD ( struct ) VendorShellClassPart := { XtPointer extension ; } ;
+FIELD ( struct ) TransientShellClassPart := { XtPointer extension ; } ;
+FIELD ( struct ) TopLevelShellClassPart := { XtPointer extension ; } ;
+FIELD ( struct ) ApplicationShellClassPart := { XtPointer extension ; } ;

+FIELD ShellClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ShellClassPart shell_class ;
} ;

+FIELD ( struct ) ShellClassExtensionRec := {
    XtPointer next_extension ;
    XrmQuark record_type ;
    long version ;
    Cardinal record_size ;
    XtGeometryHandler root_geometry_manager ;
} ;

+TYPEDEF ShellClassExtensionRec *ShellClassExtension ;
+CONST long XtShellExtensionVersion ;

+FIELD OverrideShellClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ShellClassPart shell_class ;
    OverrideShellClassPart override_shell_class ;
} ;

+FIELD WMShellClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ShellClassPart shell_class ;
    WMShellClassPart wm_shell_class ;
} ;

+FIELD VendorShellClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ShellClassPart shell_class ;
    WMShellClassPart wm_shell_class ;
    VendorShellClassPart vendor_shell_class ;
} ;

+FIELD TransientShellClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ShellClassPart shell_class ;
    WMShellClassPart wm_shell_class ;
    VendorShellClassPart vendor_shell_class ;
    TransientShellClassPart transient_shell_class ;
} ;

+FIELD TopLevelShellClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ShellClassPart shell_class ;
    WMShellClassPart wm_shell_class ;
    VendorShellClassPart vendor_shell_class ;
    TopLevelShellClassPart top_level_shell_class ;
} ;

+FIELD ApplicationShellClassRec := {
    CoreClassPart core_class ;
    CompositeClassPart composite_class ;
    ShellClassPart shell_class ;
    WMShellClassPart wm_shell_class ;
    VendorShellClassPart vendor_shell_class ;
    TopLevelShellClassPart top_level_shell_class ;
    ApplicationShellClassPart application_shell_class ;
} ;

+EXP lvalue ShellClassRec shellClassRec ;
+EXP lvalue OverrideShellClassRec overrideShellClassRec ;
+EXP lvalue WMShellClassRec wmShellClassRec ;
+EXP lvalue VendorShellClassRec vendorShellClassRec ;
+EXP lvalue TransientShellClassRec transientShellClassRec ;
+EXP lvalue TopLevelShellClassRec topLevelShellClassRec ;
+EXP lvalue ApplicationShellClassRec applicationShellClassRec ;


# ShellPart Definition (4.1.2)

+FIELD ( struct ) ShellPart {
    String geometry ;
    XtCreatePopupChildProc create_popup_child_proc ;
    XtGrabKind grab_kind ;
    Boolean spring_loaded ;
    Boolean popped_up ;
    Boolean allow_shell_resize ;
    Boolean client_specified ;
    Boolean save_under ;
    Boolean override_redirect ;
    XtCallbackList popup_callback ;
    XtCallbackList popdown_callback ;
    Visual *visual ;
} ;

+TYPE ( struct ) OverrideShellPart ;
+IF 0
+FIELD OverrideShellPart {
    int empty ;
} ;
+ENDIF

+FIELD struct ~OldXSizeHintsAspect := {
    int x ;
    int y ;
} ;

+FIELD struct _OldXSizeHints := {
    long flags ;
    int x, y ;
    int width, height ;
    int min_width, min_height ;
    int max_width, max_height ;
    int width_inc, height_inc ;
    struct ~OldXSizeHintsAspect min_aspect, max_aspect ;
    XWMHints wm_hints ;
    int base_width, base_height, win_gravity ;
    Atom title_encoding ;
} ;

+FIELD ( struct ) WMShellPart {
    String title ;
    int wm_timeout ;
    Boolean wait_for_wm ;
    Boolean transient ;
    struct _OldXSizeHints size_hints ;
    XWMHints wm_hints ;
    int base_width, base_height, win_gravity ;
    Atom title_encoding ;
} ;

+FIELD ( struct ) VendorShellPart {
    int vendor_specific ;
} ;

+FIELD ( struct ) TransientShellPart {
    Widget transient_for ;
} ;

+FIELD ( struct ) TopLevelShellPart {
    String icon_name ;
    Boolean iconic ;
    Atom icon_name_encoding ;
} ;

+FIELD ( struct ) ApplicationShellPart {
    char *class ;
    XrmClass xrm_class ;
    int argc ;
    char **argv ;
} ;

+FIELD ShellRec := {
    CorePart core ;
    CompositePart composite ;
    ShellPart shell ;
} ;

+FIELD OverrideShellRec := {
    CorePart core ;
    CompositePart composite ;
    ShellPart shell ;
    OverrideShellPart override ;
} ;

+FIELD WMShellRec := {
    CorePart core ;
    CompositePart composite ;
    ShellPart shell ;
    WMShellPart wm ;
} ;

+FIELD VendorShellRec := {
    CorePart core ;
    CompositePart composite ;
    ShellPart shell ;
    WMShellPart wm ;
    VendorShellPart vendor ;
} ;

+FIELD TransientShellRec := {
    CorePart core ;
    CompositePart composite ;
    ShellPart shell ;
    WMShellPart wm ;
    VendorShellPart vendor ;
    TransientShellPart transient ;
} ;

+FIELD TopLevelShellRec := {
    CorePart core ;
    CompositePart composite ;
    ShellPart shell ;
    WMShellPart wm ;
    VendorShellPart vendor ;
    TopLevelShellPart topLevel ;
} ;

+FIELD ApplicationShellRec := {
    CorePart core ;
    CompositePart composite ;
    ShellPart shell ;
    WMShellPart wm ;
    VendorShellPart vendor ;
    TopLevelShellPart topLevel ;
    ApplicationShellPart application ;
} ;


# Inheritance of Superclass Operations (1.6.10)

+EXP XtGeometryHandler XtInheritRootGeometryManager ;

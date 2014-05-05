# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;


# ShellClassPart Definition (4.1.1)

+TYPE ( struct ) ShellClassRec ;
+TYPEDEF ShellClassRec *ShellWidgetClass ;

+TYPE ( struct ) OverrideShellClassRec ;
+TYPEDEF OverrideShellClassRec *OverrideShellWidgetClass ;

+TYPE ( struct ) WMShellClassRec ;
+TYPEDEF WMShellClassRec *WMShellWidgetClass ;

+TYPE ( struct ) VendorShellClassRec ;
+TYPEDEF VendorShellClassRec *VendorShellWidgetClass ;

+TYPE ( struct ) TransientShellClassRec ;
+TYPEDEF TransientShellClassRec *TransientShellWidgetClass ;

+TYPE ( struct ) TopLevelShellClassRec ;
+TYPEDEF TopLevelShellClassRec *TopLevelShellWidgetClass ;

+TYPE ( struct ) ApplicationShellClassRec ;
+TYPEDEF ApplicationShellClassRec *ApplicationShellWidgetClass ;

+EXP lvalue WidgetClass shellWidgetClass ;
+EXP lvalue WidgetClass overrideShellWidgetClass ;
+EXP lvalue WidgetClass wmShellWidgetClass ;
+EXP lvalue WidgetClass vendorShellWidgetClass ;
+EXP lvalue WidgetClass transientShellWidgetClass ;
+EXP lvalue WidgetClass topLevelShellWidgetClass ;
+EXP lvalue WidgetClass applicationShellWidgetClass ;


# ShellPart Definition (4.1.2)

+TYPE ( struct ) ShellRec ;
+TYPEDEF ShellRec *ShellWidget ;

+TYPE ( struct ) OverrideShellRec ;
+TYPEDEF OverrideShellRec *OverrideShellWidget ;

+TYPE ( struct ) WMShellRec ;
+TYPEDEF WMShellRec *WMShellWidget ;

+TYPE ( struct ) VendorShellRec ;
+TYPEDEF VendorShellRec *VendorShellWidget ;

+TYPE ( struct ) TransientShellRec ;
+TYPEDEF TransientShellRec *TransientShellWidget ;

+TYPE ( struct ) TopLevelShellRec ;
+TYPEDEF TopLevelShellRec *TopLevelShellWidget ;

+TYPE ( struct ) ApplicationShellRec ;
+TYPEDEF ApplicationShellRec *ApplicationShellWidget ;


# Shell Resources (4.1.3) - also see StringDefs.h

+CONST String XtNallowShellResize, XtNargc, XtNargv, XtNbaseHeight ;
+CONST String XtNbaseWidth, XtNcreatePopupChildProc, XtNgeometry ;
+CONST String XtNheightInc, XtNiconMask, XtNiconName, XtNiconNameEncoding ;
+CONST String XtNiconPixmap, XtNiconWindow, XtNiconX, XtNiconY, XtNiconic ;
+CONST String XtNinitialState, XtNinput, XtNmaxAspectX, XtNmaxAspectY ;
+CONST String XtNmaxHeight, XtNmaxWidth, XtNminAspectX, XtNminAspectY ;
+CONST String XtNminHeight, XtNminWidth, XtNoverrideRedirect, XtNsaveUnder ;
+CONST String XtNtitle, XtNtitleEncoding, XtNtransient, XtNtransientFor ;
+CONST String XtNvisual, XtNwaitForWm, XtNwidthInc, XtNwinGravity ;
+CONST String XtNwindowGroup, XtNwmTimeout ;

+CONST String XtCAllowShellResize, XtCArgc, XtCArgv, XtCBaseHeight ;
+CONST String XtCBaseWidth, XtCCreatePopupChildProc, XtCGeometry ;
+CONST String XtCHeightInc, XtCIconMask, XtCIconName, XtCIconNameEncoding ;
+CONST String XtCIconPixmap, XtCIconWindow, XtCIconX, XtCIconY, XtCIconic ;
+CONST String XtCInitialState, XtCInput, XtCMaxAspectX, XtCMaxAspectY ;
+CONST String XtCMaxHeight, XtCMaxWidth, XtCMinAspectX, XtCMinAspectY ;
+CONST String XtCMinHeight, XtCMinWidth, XtCOverrideRedirect, XtCSaveUnder ;
+CONST String XtCTitle, XtCTitleEncoding, XtCTransient, XtCTransientFor ;
+CONST String XtCVisual, XtCWaitForWm, XtCWidthInc, XtCWinGravity ;
+CONST String XtCWindowGroup, XtCWmTimeout ;

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1994, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts" ;

+EXP lvalue WidgetClass xmBulletinBoardWidgetClass;

+TYPE (struct) _XmBulletinBoardClassRec;
+TYPE (struct) _XmBulletinBoardRec;

+TYPEDEF _XmBulletinBoardClassRec * XmBulletinBoardWidgetClass;
+TYPEDEF _XmBulletinBoardRec * XmBulletinBoardWidget;

+FUNC Widget XmCreateBulletinBoard( Widget parent, String name, ArgList arglist,                                                     Cardinal argcount) ;
+FUNC Widget XmCreateBulletinBoardDialog( Widget parent, String name,
                                         ArgList bb_args, Cardinal argcount) ;






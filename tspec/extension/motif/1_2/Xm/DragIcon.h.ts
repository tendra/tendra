# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1995-1996, IXI Ltd.
# Copyright 1995, Open Software Foundation, Inc.
#
# See doc/copyright/ for the full copyright terms.


+USE "motif/1_2","Xm/Xm.h.ts";


/* were enums */
+CONST int XmATTACH_NORTH_WEST;
+CONST int XmATTACH_NORTH;
+CONST int XmATTACH_NORTH_EAST;
+CONST int XmATTACH_EAST;
+CONST int XmATTACH_SOUTH_EAST;
+CONST int XmATTACH_SOUTH;
+CONST int XmATTACH_SOUTH_WEST;
+CONST int XmATTACH_WEST;
+CONST int XmATTACH_CENTER;
+CONST int XmATTACH_HOT;

+TYPE (struct) _XmDragIconRec;
+TYPE (struct) _XmDragIconClassRec;
+TYPEDEF _XmDragIconRec *XmDragIconObject;
+TYPEDEF _XmDragIconClassRec *XmDragIconObjectClass;

+EXP lvalue WidgetClass xmDragIconObjectClass;

+FUNC Widget XmCreateDragIcon (Widget parent, String name, ArgList arglist, Cardinal argCount);

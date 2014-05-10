# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


#
# This specification represents the X11 (Release 5) Miscellaneous Utilities
#

$UNIQUE = 1 ;
$VERSION = "2.6" ;

$INFO = "X11 Release 5 - Miscellaneous Utilities";

# Headers from Xt
+IMPLEMENT "x5/mu", "X11/StringDefs.h.ts" ;	# EXTENDED

# Headers from Xmu
+IMPLEMENT "x5/mu", "X11/Xmu/Atoms.h.ts" ;		# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/CharSet.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/CloseHook.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/Converters.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/CurUtil.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/DisplayQue.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/Drawing.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/Editres.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/Error.h.ts" ;		# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/Initer.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/StdCmap.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/StdSel.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/SysUtil.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/WidgetNode.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/WinUtil.h.ts" ;	# NEW
+IMPLEMENT "x5/mu", "X11/Xmu/Xct.h.ts" ;		# NEW

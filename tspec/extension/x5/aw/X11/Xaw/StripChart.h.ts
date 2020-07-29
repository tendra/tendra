# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "x5/t", "X11/Intrinsic.h.ts" ;
+USE "x5/aw", "X11/Xaw/Simple.h.ts" ;

# StripChart Widget (3.9)

+TYPE ( struct ) StripChartClassRec ;
+TYPEDEF StripChartClassRec *StripChartWidgetClass ;

+EXP lvalue WidgetClass stripChartWidgetClass ;

+TYPE ( struct ) StripChartRec ;
+TYPEDEF StripChartRec *StripChartWidget ;

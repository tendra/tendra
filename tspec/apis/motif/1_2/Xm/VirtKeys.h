/*
    COPYRIGHT NOTICE

    This program is the proprietary property of the Secretary of State
    for Defence (United Kingdom) acting through the Defence Research
    Agency (DRA).  Use, reproduction, production of amended versions
    and/or transfer of this program is permitted PROVIDED THAT:

    (a)	 This legend be preserved on any such reproduction and amended
	 version.

    (b)	 Any amended version of this program be clearly marked to show
	 the nature of the amendment and the name of the amending
	 organisation.

    (c)	 Any recipient of such reproduction or amended version accept
	 the conditions set out in this legend.

    The DRA accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Crown Copyright (c) 1994.
*/

/*
    COPYRIGHT NOTICE

    This program contains amendments to Motif 1.1 API headers in
    order to represent the Motif 1.2 API. These amendments are the
    property of IXI Ltd, a subsidiary of the Santa Cruz Operation (SCO).
    Use, reproduction, production of amended versions and/or transfer of
    this program is permitted PROVIDED THAT:

    (a)  This legend be preserved on any such reproduction and amended
         version.

    (b)  Any recipient of such reproduction or amended version accept
         the conditions set out in this legend.

    IXI accepts no liability whatsoever in relation to any use to
    which this program may be put and gives no warranty as to the
    program's suitability for any purpose.

    All rights reserved.

    Copyright (c) 1995, 1996
*/


/* SCO CID (IXI) VirtKeys.h,v 1.1 1996/08/08 14:13:55 wendland Exp */

#+USE "motif/1_2","Xm/Xm.h";

+USE "x5/t", "X11/Intrinsic.h";

+EXP unsigned long osfXK_BackSpace ;
+EXP unsigned long osfXK_Insert ;
+EXP unsigned long osfXK_Delete ;
+EXP unsigned long osfXK_Copy ;
+EXP unsigned long osfXK_Cut ;
+EXP unsigned long osfXK_Paste ;

+EXP unsigned long osfXK_AddMode ;
+EXP unsigned long osfXK_PrimaryPaste ;
+EXP unsigned long osfXK_QuickPaste ;

+EXP unsigned long osfXK_PageUp ;
+EXP unsigned long osfXK_PageDown ;

+EXP unsigned long osfXK_EndLine ;
+EXP unsigned long osfXK_BeginLine ;

+EXP unsigned long osfXK_Activate ;

+EXP unsigned long osfXK_MenuBar ;

+EXP unsigned long osfXK_Clear ;
+EXP unsigned long osfXK_Cancel ;
+EXP unsigned long osfXK_Help ;
+EXP unsigned long osfXK_Menu ;
+EXP unsigned long osfXK_Select ;
+EXP unsigned long osfXK_Undo ;

+EXP unsigned long osfXK_Left ;
+EXP unsigned long osfXK_Up ;
+EXP unsigned long osfXK_Right ;
+EXP unsigned long osfXK_Down ;


+EXP String XmVosfBackSpace ;
+EXP String XmVosfInsert ;
+EXP String XmVosfDelete ;
+EXP String XmVosfCopy ;
+EXP String XmVosfCut ;
+EXP String XmVosfPaste; 

+EXP String XmVosfAddMode; 
+EXP String XmVosfPrimaryPaste ;
+EXP String XmVosfQuickPaste ;

+EXP String XmVosfPageUp ;
+EXP String XmVosfPageDown; 

+EXP String XmVosfEndLine ;
+EXP String XmVosfBeginLine; 

+EXP String XmVosfActivate ;

+EXP String XmVosfMenuBar ;

+EXP String XmVosfClear ;
+EXP String XmVosfCancel ;
+EXP String XmVosfHelp ;
+EXP String XmVosfMenu ;
+EXP String XmVosfSelect; 
+EXP String XmVosfUndo ;

+EXP String XmVosfLeft ;
+EXP String XmVosfUp ;
+EXP String XmVosfRight ; 
+EXP String XmVosfDown ;

+FUNC void XmTranslateKey(Display *, KeyCode, Modifiers, Modifiers *, KeySym *);

+FUNC void _XmVirtKeysInitialize (Widget shell);






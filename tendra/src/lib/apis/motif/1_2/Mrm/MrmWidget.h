/*
    Copyright (c) 1995 Open Software Foundation, Inc.

    All Rights Reserved

    Permission to use, copy, modify, and distribute this software and its
    documentation for any purpose and without fee is hereby granted, provided
    that the above copyright notice appears in all copies and that both the
    copyright notice and this permission notice appear in supporting
    documentation.

    OSF DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE
    INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS
    FOR A PARTICULAR PURPOSE.

    IN NO EVENT SHALL OSF BE LIABLE FOR ANY SPECIAL, INDIRECT, OR
    CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
    LOSS OF USE, DATA OR PROFITS, WHETHER IN ACTION OF CONTRACT,
    NEGLIGENCE, OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN
    CONNECTION WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.
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



/* SCO CID (IXI) MrmWidget.h,v 1.1 1996/08/08 14:12:03 wendland Exp */

+USE "x5/t","X11/IntrinsicP.h";
+USE "x5/t","X11/CoreP.h";
+USE "x5/t","X11/CompositeP.h";
+USE "x5/t","X11/ConstrainP.h";
+USE "x5/t","X11/ShellP.h";
+USE "x5/t","X11/VendorP.h";
+USE "x5/t","X11/RectObjP.h";

+USE "motif/1_2", "Mrm/MrmAppl.h";
+USE "motif/1_2", "Xm/BulletinB.h";
+USE "motif/1_2", "Xm/BulletinBP.h";
+USE "motif/1_2", "Xm/RowColumn.h";
#+USE "motif/1_2", "Xm/RowColumnP.h";
+USE "motif/1_2", "Xm/ArrowB.h";
+USE "motif/1_2", "Xm/ArrowBG.h";
#+USE "motif/1_2", "Xm/ArrowBGP.h";
+USE "motif/1_2", "Xm/ArrowBP.h";
+USE "motif/1_2", "Xm/AtomMgr.h";
+USE "motif/1_2", "Xm/CascadeB.h";
+USE "motif/1_2", "Xm/CascadeBG.h";
#+USE "motif/1_2", "Xm/CascadeBGP.h";
#+USE "motif/1_2", "Xm/CascadeBP.h";
#+USE "motif/1_2", "Xm/SelectioBP.h";
#+USE "motif/1_2", "Xm/SelectioB.h";
+USE "motif/1_2", "Xm/Command.h";
#+USE "motif/1_2", "Xm/CommandP.h";
+USE "motif/1_2", "Xm/CutPaste.h";
#+USE "motif/1_2", "Xm/CutPasteP.h";
+USE "motif/1_2", "Xm/DialogS.h";
#+USE "motif/1_2", "Xm/DialogSP.h";
+USE "motif/1_2", "Xm/DrawingA.h";
#+USE "motif/1_2", "Xm/DrawingAP.h";
+USE "motif/1_2", "Xm/DrawnB.h";
#+USE "motif/1_2", "Xm/DrawnBP.h";
+USE "motif/1_2", "Xm/FileSB.h";
#+USE "motif/1_2", "Xm/FileSBP.h";
+USE "motif/1_2", "Xm/Form.h";
+USE "motif/1_2", "Xm/FormP.h";
+USE "motif/1_2", "Xm/Frame.h";
+USE "motif/1_2", "Xm/FrameP.h";
+USE "motif/1_2", "Xm/Label.h";
+USE "motif/1_2", "Xm/LabelG.h";
#+USE "motif/1_2", "Xm/LabelGP.h";
+USE "motif/1_2", "Xm/LabelP.h";
+USE "motif/1_2", "Xm/List.h";
+USE "motif/1_2", "Xm/ListP.h";
+USE "motif/1_2", "Xm/MainW.h";
#+USE "motif/1_2", "Xm/MainWP.h";
+USE "motif/1_2", "Xm/MenuShell.h";
#+USE "motif/1_2", "Xm/MenuShellP.h";
+USE "motif/1_2", "Xm/MessageB.h";
#+USE "motif/1_2", "Xm/MessageBP.h";
+USE "motif/1_2", "Xm/PanedW.h";
#+USE "motif/1_2", "Xm/PanedWP.h";
+USE "motif/1_2", "Xm/PushB.h";
+USE "motif/1_2", "Xm/PushBG.h";
#+USE "motif/1_2", "Xm/PushBGP.h";
+USE "motif/1_2", "Xm/PushBP.h";
+USE "motif/1_2", "Xm/SashP.h";
+USE "motif/1_2", "Xm/Scale.h";
#+USE "motif/1_2", "Xm/ScaleP.h";
+USE "motif/1_2", "Xm/ScrollBar.h";
+USE "motif/1_2", "Xm/ScrollBarP.h";
+USE "motif/1_2", "Xm/ScrolledW.h";
#+USE "motif/1_2", "Xm/ScrolledWP.h";
+USE "motif/1_2", "Xm/SeparatoG.h";
#+USE "motif/1_2", "Xm/SeparatoGP.h";
+USE "motif/1_2", "Xm/Separator.h";
+USE "motif/1_2", "Xm/SeparatorP.h";
+USE "motif/1_2", "Xm/Text.h";
#+USE "motif/1_2", "Xm/TextP.h";
#+USE "motif/1_2", "Xm/TextInP.h";
#+USE "motif/1_2", "Xm/TextOutP.h";
#+USE "motif/1_2", "Xm/TextStrSoP.h";
+USE "motif/1_2", "Xm/ToggleB.h";
+USE "motif/1_2", "Xm/ToggleBG.h";
#+USE "motif/1_2", "Xm/ToggleBGP.h";
#+USE "motif/1_2", "Xm/ToggleBP.h";
#+USE "motif/1_2", "Xm/XmP.h";

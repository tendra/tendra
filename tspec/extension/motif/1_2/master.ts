# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
# Copyright 1995-1996, IXI Ltd.
#
# See doc/copyright/ for the full copyright terms.


/*
    This specification represents the IEEE MTE 1295-1993 standard for
    the Motif 1.2 API.
*/


#Master file for Motif API
# rev. os_ri July 31st, 1996 [added uil/UilDef.h]
$UNIQUE = 1 ;
$VERSION = "2.6" ;

$INFO = "IEEE Std 1295-1993 - MTE";

+IMPLEMENT "motif/1_2", "Xm/ArrowBGP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ArrowB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ArrowBG.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ArrowBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/AtomMgr.h.ts";
+IMPLEMENT "motif/1_2", "Xm/BulletinB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/BulletinBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CascadeB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CascadeBG.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Command.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CutPaste.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DialogS.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Display.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DragC.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DragDrop.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DragIcon.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DrawingA.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DrawnB.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/ExtObject.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ExtObjectP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/FileSB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Form.h.ts";
+IMPLEMENT "motif/1_2", "Xm/FormP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Frame.h.ts";
+IMPLEMENT "motif/1_2", "Xm/FrameP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/GadgetP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Label.h.ts";
+IMPLEMENT "motif/1_2", "Xm/LabelG.h.ts";
+IMPLEMENT "motif/1_2", "Xm/LabelGP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/LabelP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/List.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ListP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MainW.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ManagerP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MenuShell.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MessageB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MwmUtil.h.ts";
+IMPLEMENT "motif/1_2", "Xm/PanedW.h.ts";
+IMPLEMENT "motif/1_2", "Xm/PrimitiveP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Protocols.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ProtocolsP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/PushB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/PushBG.h.ts";
+IMPLEMENT "motif/1_2", "Xm/PushBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/RepType.h.ts";
+IMPLEMENT "motif/1_2", "Xm/SashP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/RowColumn.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Scale.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Screen.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ScrollBar.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ScrollBarP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ScrolledW.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ScrolledWP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/SelectioB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/SeparatoG.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Separator.h.ts";
+IMPLEMENT "motif/1_2", "Xm/SeparatorP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Text.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextF.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ToggleB.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ToggleBG.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/Traversal.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/VaSimple.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/VendorE.h.ts";
+IMPLEMENT "motif/1_2", "Xm/VirtKeys.h.ts";
+IMPLEMENT "motif/1_2", "Xm/Xm.h.ts";
+IMPLEMENT "motif/1_2", "Xm/XmP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/BaseClassP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CacheP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CascadeBGP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CascadeBP.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/ColorObj.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/ColorObjP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CommandP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/CutPasteP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DesktopP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DialogSEP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DialogSP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DisplayP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DragCP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DragOverSP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DragIconP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DragOverS.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DrawingAP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DrawP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DropTransP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DrawnBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DropSMgr.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DropSMgrP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/DropTrans.h.ts";
+IMPLEMENT "motif/1_2", "Xm/FileSBP.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/IconFile.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/IconFileP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MainWP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MenuShellP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MenuUtilP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/MessageBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/PanedWP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/PushBGP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/RCUtilsP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/RowColumnP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ScaleP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ScreenP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/SelectioBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/SeparatoGP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ShellEP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/StringSrcP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TearOffBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TearOffP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextFP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextFSelP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextInP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextOutP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextSelP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TextStrSoP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ToggleBGP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/TransltnsP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/ToggleBP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/VaSimpleP.h.ts";
#+IMPLEMENT "motif/1_2", "Xm/VendorEP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/VendorS.h.ts";
+IMPLEMENT "motif/1_2", "Xm/VendorSEP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/VendorSP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/VirtKeysP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/WorldP.h.ts";
+IMPLEMENT "motif/1_2", "Xm/XmAll.h.ts";
+IMPLEMENT "motif/1_2", "Xm/XmStrDefs.h.ts";
+IMPLEMENT "motif/1_2", "Xm/XmosP.h.ts";
+IMPLEMENT "motif/1_2", "Mrm/MrmAppl.h.ts";
+IMPLEMENT "motif/1_2", "Mrm/MrmDecls.h.ts";
+IMPLEMENT "motif/1_2", "Mrm/MrmPublic.h.ts";
+IMPLEMENT "motif/1_2", "Mrm/MrmWidget.h.ts";
+IMPLEMENT "motif/1_2", "Mrm/Uil.h.ts";
+IMPLEMENT "motif/1_2", "uil/UilDef.h.ts";

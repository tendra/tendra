#############################################################################
#
#	docbook-to-man.ts
#
#	$TenDRA: doc/share/misc/docbook-to-man.ts,v 1.1 2004/08/07 23:01:17 verm Exp $
#
#############################################################################
#
# Copyright (c) 1996 X Consortium
# Copyright (c) 1996 Dalrymple Consulting
# 
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# 
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
# 
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT.  IN NO EVENT SHALL THE
# X CONSORTIUM OR DALRYMPLE CONSULTING BE LIABLE FOR ANY CLAIM, DAMAGES OR
# OTHER LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE,
# ARISING FROM, OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR
# OTHER DEALINGS IN THE SOFTWARE.
# 
# Except as contained in this notice, the names of the X Consortium and
# Dalrymple Consulting shall not be used in advertising or otherwise to
# promote the sale, use or other dealings in this Software without prior
# written authorization.
# 
#############################################################################
#
# Written 5/29/96 by Fred Dalrymple
#
#############################################################################
#
#  Variables
#
Var:	callout 0
Var:	orderlist 0
Var:	procstep 0
Var:	procsubstep 0
#
#
#
#
#############################################################################
#
#  Hierarchy (and document meta stuff)
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		REFENTRY
StartText:	^.\\" Copyright (c) 2002-2004 The TenDRA Project <http://www.ten15.org/>
		^.\\" All rights reserved.
		^.\\" 
		^.\\" Redistribution and use in source and binary forms, with or without
		^.\\" modification, are permitted provided that the following conditions
		^.\\" are met:
		^.\\" 1. Redistributions of source code must retain the above copyright
		^.\\"    notice, this list of conditions and the following disclaimer.
		^.\\" 2. Redistributions in binary form must reproduce the above copyright
		^.\\"    notice, this list of conditions and the following disclaimer in the
		^.\\"    documentation and/or other materials provided with the distribution.
		^.\\" 
		^.\\" THIS SOFTWARE IS PROVIDED BY THE AUTHOR AND CONTRIBUTORS ``AS IS'' AND
		^.\\" ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
		^.\\" IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
		^.\\" ARE DISCLAIMED.  IN NO EVENT SHALL THE AUTHOR OR CONTRIBUTORS BE LIABLE
		^.\\" FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL
		^.\\" DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS
		^.\\" OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION)
		^.\\" HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT
		^.\\" LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY
		^.\\" OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF
		^.\\" SUCH DAMAGE.
		^.\\"
		^.\\" $TenDRA$
		^.\\"
		^.TH "${_followrel descendant REFENTRYTITLE 1000}"
			"${_followrel descendant MANVOLNUM 1000}" "${date}"
			"The TenDRA Project" "The TenDRA Project"
		^.SH "NAME"
		^.PP
		^\\fB${_followrel descendant REFENTRYTITLE 1000}\\fP - ${_followrel descendant REFPURPOSE 1000}


EndText:	^...\\" created by instant / docbook-to-man, ${date}^
-
#
GI:		DOCINFO
Ignore:		all
-
#
GI:		TITLE
Context:	DOCINFO
#	inside DocInfo, which we're ignoring
-
#
GI:		REFMETA
Ignore:		all
-
#
GI:		REFNAMEDIV
#StartText:	^.SH "NAME"^
Ignore:		all
-
#
GI:		REFDESCRIPTOR
StartText:	\\fB
EndText:	\\fR\s
-
#
GI:		REFNAME
Relation:	sibling- REFDESCRIPTOR
#	inhibit REFNAMEs when a REFDESCRIPTOR is present
Ignore:		all
-
#
GI:		REFNAME
StartText:	${_isset refnameseen xxx 20}
EndText:	${_set refnameseen xxx}
-
#
GI:		_refname
SpecID:		20
StartText:	,\s
-
#
GI:		REFPURPOSE
StartText:	\s\\(em\s
EndText:	^
-
#
GI:		REFCLASS
StartText:	^.PP^
EndText:	^
-
#
GI:		REFSYNOPSISDIV
StartText:	^.SH "SYNOPSIS"^
EndText:	^
-
#
GI:		REFSECT1
StartText:	^.SH "${_followrel child TITLE 1000}"^
EndText:	^
-
#
GI:		REFSECT2
StartText:	^.SS "${_followrel child TITLE 1000}"^
EndText:	^
-
#
GI:		REFSECT3
StartText:	^.SS "${_followrel child TITLE 1000}"^
EndText:	^
-
#
GI:		BRIDGEHEAD
StartText:	^.PP^\\fB
EndText:	\\fP^.PP^
-
#
GI:		TITLE
Context:	REFSECT1
Ignore:		all
-
#
GI:		TITLE
Context:	REFSECT2
Ignore:		all
-
#
GI:		TITLE
Context:	REFSECT3
Ignore:		all
-
#
GI:		LEGALNOTICE
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		TITLE
Context:	LEGALNOTICE
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		REFENTRYTITLE
Context:	REFMETA
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		MANVOLNUM
Context:	REFMETA
#	part of the DocInfo structure, which is ignored, though this element
#	if accessed directly by the _followrel call from the REFENTRY element.
Ignore:		all
-
#
GI:		REFMISCINFO
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		SUBTITLE
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		AUTHORGROUP
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		AUTHOR
Context:	AUTHORGROUP
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		EDITOR
Context:	AUTHORGROUP
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		COLLAB
Context:	AUTHORGROUP
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		COLLABNAME
Context:	COLLAB
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		CORPAUTHOR
Context:	AUTHORGROUP
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
GI:		OTHERCREDIT
Context:	AUTHORGROUP
#	part of the DocInfo structure, which is ignored
Ignore:		all
-
#
#
#############################################################################
#
#  (before we get into the branch stuff, we turn off paragraphs in some
#   contexts where they would break the flow.  Generally, this happens
#   within indented areas, such as within lists.
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		PARA
Context:	LISTITEM
NthChild:	1
#	nothing in this context
-
#
GI:		PARA
Context:	GLOSSDEF
NthChild:	1
#	nothing in this context
-
#
GI:		PARA
Context:	STEP
NthChild:	1
#	nothing in this context
-
#
GI:		PARA
Context:	CALLOUT
NthChild:	1
#	nothing in this context
-
#
GI:		PARA
Context:	MSGTEXT
NthChild:	1
#	nothing in this context
-
#
#
#############################################################################
#
#  Regular "branch" stuff
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		FORMALPARA
#	it's all done in TITLE (FORMALPARA) and PARA
-
#
GI:		TITLE
Context:	FORMALPARA
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		PARA
Relation:	ancestor LISTITEM
StartText:	^.IP "" 5^
-
#
GI:		PARA
Relation:	ancestor STEP
StartText:	^.IP "" 5^
-
#
GI:		PARA
StartText:	^.PP^
-
#
GI:		SIMPARA
StartText:	^.PP^
-
#
GI:		PROGRAMLISTING
StartText:	^.PP^.nf^\\f(CW
EndText:	\\fR^.fi^.PP^
-
#
GI:		LITERALLAYOUT
StartText:	^.PP^.nf^
EndText:	^.fi^
-
#
GI:		BLOCKQUOTE
StartText:	^.PP^.RS^
EndText:	^.RE^
-
#
GI:		TITLE
Context:	BLOCKQUOTE
StartText:	^\\fB
EndText:	\\fR^.PP^
-
#
GI:		EPIGRAPH
StartText:	^.PP^.RS^
EndText:	^.RE^
-
#
GI:		ATTRIBUTION
StartText:	^\\fI
EndText:	\\fR^.PP^
-
#
GI:		ABSTRACT
Relation:	child TITLE
-
#
GI:		ABSTRACT
StartText:	^.SS "Abstract"^
-
#
GI:		TITLE
Context:	ABSTRACT
StartText:	^.SS "
EndText:	"^
-
#
GI:		REVHISTORY
StartText:	^.SS "Revision History"^
EndText:	^
-
#
GI:		REVISION
StartText:	^.PP^\\fBRevision:\\fR\s
EndText:	^
-
#
GI:		REVNUMBER
StartText:	#\s
EndText:	;\s
-
#
GI:		DATE
EndText:	;\s
-
#
GI:		AUTHORINITIALS
Context:	REVISION
StartText:	\s
-
#
GI:		REVREMARK
StartText:	;\s\s
EndText:	^
-
#
GI:		PROGRAMLISTINGCO
#	nothing to do specifically in ProgramListingCO -- it falls to
#	the content of ProgramListing and any callout list
-
#
GI:		SCREEN
StartText:	^.PP^.nf^
EndText:	^.fi^
-
#
GI:		SCREENCO
#	nothing to do specifically in ScreenCO -- it falls to
#	the content of Screen and any callout list
-
#
GI:		SCREENSHOT
#	nothing specific to do here -- defer to any ScreenInfo or the
#	included graphic
-
#
GI:		SCREENINFO
StartText:	^.PP^\\fI
EndText:	\\fR^.PP^
-
#
GI:		GRAPHICCO
#	nothing to do specifically in GraphicCO -- it falls to
#	the content of Graphic and any callout list
-
#
GI:		INFORMALEXAMPLE
#	nothing special to do here -- it falls to the content.
-
#
GI:		EXAMPLE
#	nothing special to do here -- it falls to the content.
-
#
GI:		TITLE
Context:	EXAMPLE
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		FIGURE
#	nothing special to do here -- it falls to the content.
-
#
GI:		TITLE
Context:	FIGURE
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		SIDEBAR
Relation:	child TITLE
StartText:	^.PP^.RS^
EndText:	^.RE^
-
#
GI:		SIDEBAR
StartText:	^.PP^.RS^\\fB[ Sidebar ]\\fR^
EndText:	^.RE^
-
#
GI:		TITLE
Context:	SIDEBAR
StartText:	^\\fB[ Sidebar:\s
EndText:	\s]\\fR^
-
#
GI:		HIGHLIGHTS
StartText:	^.SS "Highlights"^
-
#
GI:		AUTHORBLURB
#	nothing to do specially -- an included title may occur
-
#
GI:		TITLE
Context:	AUTHORBLURB
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
#
#############################################################################
#
#  Call-out material
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		CO
#	nothing to do for the anchor of a callout
-
#
GI:		AREASPEC
Ignore:		all
#	not much to do with representing the anchor of callouts in n/troff
-
#
GI:		AREA
Ignore:		all
#	part of AreaSpec, which is being ignored
-
#
GI:		AREASET
Ignore:		all
#	part of AreaSpec, which is being ignored
-
#
#
#############################################################################
#
#  Address block
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		ADDRESS
StartText:	^.PP^.nf^
EndText:	^.fi^
-
#
GI:		STREET
#	just the content...
-
#
GI:		POB
#	just the content...
-
#
GI:		POSTCODE
#	just the content...
-
#
GI:		CITY
EndText:	,\s
-
#
GI:		STATE
#	just the content
-
#
GI:		COUNTRY
#	just the content
-
#
GI:		PHONE
StartText:	^voice:\s
-
#
GI:		FAX
StartText:	^fax:\s
-
#
GI:		OTHERADDR
#	just the content..
-
#
GI:		EMAIL
Context:	ADDRESS
#	just the content..
-
#
#
#############################################################################
#
#  Lists
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		GLOSSLIST
Relation:	ancestor ITEMIZEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		GLOSSLIST
Relation:	ancestor GLOSSLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		GLOSSLIST
Relation:	ancestor ORDEREDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		GLOSSLIST
Relation:	ancestor SIMPLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		GLOSSLIST
Relation:	ancestor VARIABLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		GLOSSLIST
Relation:	ancestor SEGMENTEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		GLOSSLIST
#	Nothing to do here..  see glossentry, etc
-
#
GI:		GLOSSENTRY
#	nothing to do..
-
#
GI:		GLOSSTERM
Context:	GLOSSENTRY
StartText:	^.IP "
EndText:	" 10^
-
#
GI:		GLOSSTERM
StartText:	\\fB
EndText:	\\fP
-
#
GI:		ACRONYM
Context:	GLOSSENTRY
StartText:	(\\fIacronym:\s\\fR
EndText:	)\s\s
-
#
GI:		ABBREV
Context:	GLOSSENTRY
StartText:	(\\fIabbreviation:\s\\fR
EndText:	)\s\s
-
#
GI:		GLOSSSEE
StartText:	^\\fISee \\fR
-
#
GI:		GLOSSDEF
#	nothing special to do -- just pass the content.
-
#
GI:		GLOSSSEEALSO
StartText:	^^\\fISee Also \\fR
-
#
GI:		ITEMIZEDLIST
Relation:	ancestor ITEMIZEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ITEMIZEDLIST
Relation:	ancestor GLOSSLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ITEMIZEDLIST
Relation:	ancestor ORDEREDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ITEMIZEDLIST
Relation:	ancestor SIMPLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ITEMIZEDLIST
Relation:	ancestor VARIABLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ITEMIZEDLIST
Relation:	ancestor SEGMENTEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ITEMIZEDLIST
#	nothing to do..
-
#
GI:		LISTITEM
Context:	ITEMIZEDLIST
StartText:	^.IP "\ \ \ \\(bu" 6^
-
#
GI:		ORDEREDLIST
Relation:	ancestor ITEMIZEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ORDEREDLIST
Relation:	ancestor GLOSSLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ORDEREDLIST
Relation:	ancestor ORDEREDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ORDEREDLIST
Relation:	ancestor SIMPLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ORDEREDLIST
Relation:	ancestor VARIABLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ORDEREDLIST
Relation:	ancestor SEGMENTEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		ORDEREDLIST
StartText:	${_set orderlist 1}
-
#
GI:		LISTITEM
Context:	ORDEREDLIST
StartText:	^.IP "\ \ \ ${orderlist}." 6^
Increment:	orderlist
-
#
GI:		SIMPLELIST
Relation:	ancestor ITEMIZEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		SIMPLELIST
Relation:	ancestor GLOSSLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		SIMPLELIST
Relation:	ancestor ORDEREDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		SIMPLELIST
Relation:	ancestor SIMPLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		SIMPLELIST
Relation:	ancestor VARIABLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		SIMPLELIST
Relation:	ancestor SEGMENTEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		SIMPLELIST
#	nothing to do here..
-
#
GI:		MEMBER
PAttSet:	TYPE INLINE
NthChild:	1
-
#
GI:		MEMBER
PAttSet:	TYPE INLINE
StartText:	,\s
-
#
GI:		MEMBER
PAttSet:	TYPE HORIZ
NthChild:	1
StartText:	^.PP^\t
-
#
GI:		MEMBER
PAttSet:	TYPE HORIZ
StartText:	\t
-
#
GI:		MEMBER
PAttSet:	TYPE VERT
StartText:	^.IP "" 10^
EndText:	^
-
#
GI:		VARIABLELIST
Relation:	ancestor ITEMIZEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		VARIABLELIST
Relation:	ancestor GLOSSLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		VARIABLELIST
Relation:	ancestor ORDEREDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		VARIABLELIST
Relation:	ancestor SIMPLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		VARIABLELIST
Relation:	ancestor VARIABLELIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		VARIABLELIST
Relation:	ancestor SEGMENTEDLIST
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		VARIABLELIST
#	nothing to do now, see VarListEntry
-
#
GI:		VARLISTENTRY
#	nothing to do now, see Term
-
#
GI:		TERM
StartText:	^.IP "
EndText:	" 5^
-
#
GI:		LISTITEM
Context:	VARLISTENTRY
#	nothing special to do..
-
#
GI:		SEGMENTEDLIST
Relation:	ancestor ITEMIZEDLIST
StartText:	^.RS^${_followrel child TITLE 400}^.TS^tab();^l l l l l l l l l l l l l l l l l l.^
EndText:	^.TE^.RE^
-
#
GI:		SEGMENTEDLIST
Relation:	ancestor GLOSSLIST
StartText:	^.RS^${_followrel child TITLE 400}^.TS^tab();^l l l l l l l l l l l l l l l l l l.^
EndText:	^.TE^.RE^
-
#
GI:		SEGMENTEDLIST
Relation:	ancestor ORDETERLIST
StartText:	^.RS^${_followrel child TITLE 400}^.TS^tab();^l l l l l l l l l l l l l l l l l l.^
EndText:	^.TE^.RE^
-
#
GI:		SEGMENTEDLIST
Relation:	ancestor SIMPLELIST
StartText:	^.RS^${_followrel child TITLE 400}^.TS^tab();^l l l l l l l l l l l l l l l l l l.^
EndText:	^.TE^.RE^
-
#
GI:		SEGMENTEDLIST
Relation:	ancestor VARIABLELIST
StartText:	^.RS^${_followrel child TITLE 400}^.TS^tab();^l l l l l l l l l l l l l l l l l l.^
EndText:	^.TE^.RE^
-
#
GI:		SEGMENTEDLIST
Relation:	ancestor SEGMENTEDLIST
StartText:	^.RS^${_followrel child TITLE 400}^.TS^tab();^l l l l l l l l l l l l l l l l l l.^
EndText:	^.TE^.RE^
-
#
GI:		SEGMENTEDLIST
Relation:	child TITLE
StartText:	^${_followrel child TITLE 400}^.TS^tab();^l l l l l l l l l l l l l l l l l l.^
EndText:	^.TE^
-
#
GI:		TITLE
Context:	SEGMENTEDLIST
#	ignored by default -- must be called by SEGMENTEDLIST gi
Ignore:		all
-
#
GI:		_segmentedlist_title
SpecID:		400
StartText:	^.sp 1^\\fB
EndText:	\\fR^
-
#
GI:		SEGTITLE
StartText:	\\fB
EndText:	\\fR
-
#
GI:		SEGLISTITEM
StartText:	^
EndText:	^
-
#
GI:		SEG
EndText:	
-
#
GI:		PROCEDURE
#	defer to the content...
StartText:	${_set procstep 1}${_set procsubstep 1}
-
#
GI:		TITLE
Context:	PROCEDURE
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		STEP
Context:	SUBSTEPS
StartText:	^.PP^\\fISubstep ${procsubstep}.\s\s
EndText:	^
Increment:	procsubstep 1
-
#
GI:		STEP
StartText:	^.PP^\\fIStep ${procstep}.\s\s
EndText:	^
Increment:	procstep 1
-
#
GI:		TITLE
Context:	STEP
StartText:	^\\fB
EndText:	\\fR^.PP^
-
#
GI:		SUBSTEPS
StartText:	^.RS^
EndText:	^.RE^
-
#
GI:		CALLOUTLIST
StartText:	${_set callout 1}
#	nothing to do specifically, defer to the content...
-
#
GI:		TITLE
Context:	CALLOUTLIST
StartText:	^\\fB
EndText:	\\fR^.PP^
-
#
GI:		CALLOUT
StartText:	^.PP^\\fICallout ${callout}.\s\s\\fR
EndText:	^
Increment:	callout
-
#
#
#############################################################################
#
#  Messages
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		MSGSET
StartText:	^.SS "Message Set"^
-
#
GI:		MSGENTRY
StartText:	^.PP^\\fBMessage Entry\\fR^.RS^
EndText:	^.RE^
-
#
GI:		MSG
Relation:	child TITLE
StartText:	^.PP^
EndText:	^
-
#
GI:		MSG
StartText:	^.PP^\\fBMessage:\\fR^.PP^
EndText:	^
-
#
GI:		TITLE
Context:	MSG
StartText:	^.PP^\\fB
EndText:	\\fR^.PP^
-
#
GI:		MSGINFO
#	nothing specific -- just groups (MsgLevel | MsgOrig | MsgAud)*
-
#
GI:		MSGEXPLAN
#	nothing special -- defer to content
-
#
GI:		TITLE
Context:	MSGEXPLAN
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		MSGMAIN
#	defer to content
-
#
GI:		TITLE
Context:	MSGMAIN
StartText:	^\\fB
EndText:	\\fR^
-
#
GI:		MSGSUB
#	defer to content
-
#
GI:		TITLE
Context:	MSGSUB
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		MSGREL
#	defer to content
-
#
GI:		TITLE
Context:	MSGREL
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		MSGLEVEL
StartText:	^.PP^\\fIMessage level:\s\s\\fR
EndText:	^
-
#
GI:		MSGORIG
StartText:	^.PP^\\fIMessage origin:\s\s\\fR
EndText:	^
-
#
GI:		MSGAUD
StartText:	^.PP^\\fIMessage audience:\s\s\\fR
EndText:	^
-
#
GI:		MSGTEXT
Context:	PARA
StartText:	\\fI
EndText:	\\fP
-
#
GI:		MSGTEXT
StartText:	\\fR^\\fIMessage text:\\fR\s\s
EndText:	^
-
#
#
#############################################################################
#
#  Admonitions
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		CAUTION
Relation:	child TITLE
StartText:	^.PP^.RS
EndText:	^.RE^
-
#
GI:		CAUTION
StartText:	^.PP^.RS^\\fBCaution:\s\s
EndText:	^.RE^
-
#
GI:		TITLE
Context:	CAUTION
StartText:	^\\fBCaution:\s\s
EndText:	\\fR^.PP^
-
#
GI:		IMPORTANT
Relation:	child TITLE
StartText:	^.PP^.RS^
EndText:	^.RE^
-
#
GI:		IMPORTANT
StartText:	^.PP^.RS^\\fBImportant:\s\s
EndText:	^.RE^
-
#
GI:		TITLE
Context:	IMPORTANT
StartText:	^\\fBImportant:\s\s
EndText:	\\fR^.PP^
-
#
GI:		NOTE
Relation:	child TITLE
StartText:	^.PP^.RS
EndText:	^.RE^
-
#
GI:		NOTE
StartText:	^.PP^.RS^\\fBNote:\s\s
EndText:	^.RE^
-
#
GI:		TITLE
Context:	NOTE
StartText:	^\\fBNote:\s\s
EndText:	\\fR^.PP^
-
#
GI:		TIP
Relation:	child TITLE
StartText:	^.PP^.RS
EndText:	^.RE^
-
#
GI:		TIP
StartText:	^.PP^.RS^\\fBTip:\s\s
EndText:	^.RE^
-
#
GI:		TITLE
Context:	TIP
StartText:	^\\fBTip:\s\s
EndText:	\\fR^.PP^
-
#
GI:		WARNING
Relation:	child TITLE
StartText:	^.PP^.RS
EndText:	^.RE^
-
#
GI:		WARNING
StartText:	^.PP^.RS^\\fBWarning:\s\s
EndText:	^.RE^
-
#
GI:		TITLE
Context:	WARNING
StartText:	^\\fBWarning:\s\s
EndText:	\\fR^.PP^
-
#
#
#############################################################################
#
#  Synopses
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		SYNOPSIS
StartText:	^.PP^.nf^
EndText:	^.fi^
-
#
GI:		CMDSYNOPSIS
StartText:	^.PP^
EndText:	^
-
#
GI:		ARG
Context:	GROUP
NthChild:	1
EndText:	${_attval REP REPEAT 505}\s
-
#
GI:		ARG
Context:	GROUP
StartText:	\s|\s
EndText:	${_attval REP REPEAT 505}\s
-
#
GI:		ARG
AttValue:	CHOICE OPT
StartText:	\s[
EndText:	${_attval REP REPEAT 505}]\s
-
#
GI:		ARG
#	no special attrs -- just pass content through
EndText:	${_attval REP REPEAT 505}\s
-
#
GI:		_arg_group
SpecID:		505
StartText:	\s\\&...
Ignore:		all
-
#
GI:		GROUP
AttValue:	CHOICE OPT
StartText:	\s[
EndText:	]\s${_attval REP REPEAT 505}
-
#
GI:		GROUP
AttValue:	CHOICE REQ
StartText:	\s{
EndText:	}\s${_attval REP REPEAT 505}
-
#
GI:		GROUP
AttValue:	CHOICE OPTMULT
StartText:	\s[[
EndText:	]]\s${_attval REP REPEAT 505}
-
#
GI:		GROUP
AttValue:	CHOICE REQMULT
StartText:	\s{{
EndText:	}}\s${_attval REP REPEAT 505}
-
#
GI:		GROUP
AttValue:	CHOICE PLAIN
EndText:	${_attval REP REPEAT 505}
-
#
GI:		SBR
StartText:	^.br^
-
#
GI:		SYNOPFRAGMENT
#	nothing special to do here -- just pass through content (Arg | Group)+
-
#
GI:		SYNOPFRAGMENTREF
#	WHAT TO DO HERE??   pass through the content, but what about the
#	linkend?  (will call it across...)
EndText:	\s\\fI(refers to: ${_followlink LINKEND 1000})\\fR
-
#
GI:		FUNCSYNOPSIS
StartText:	^.PP^.nf^
EndText:	^.fi^
-
#
GI:		FUNCSYNOPSISINFO
StartText:	^
EndText:	^
-
#
GI:		FUNCPROTOTYPE
#	nothing special -- just pass through content (looks like
#	a function def
StartText:	^.sp 1^
-
#
GI:		FUNCDEF
StartText:	^\\fB
EndText:	\\fR(
-
#
GI:		FUNCPARAMS
StartText:	^\t\t\t\\fB
EndText:	\\fR^
-
#
GI:		VOID
StartText:	\\fBvoid\\fR)
-
#
GI:		VARARGS
StartText:	\\fB\\&...\\fR)
-
#
GI:		PARAMDEF
Relation:	sibling+ PARAMDEF
StartText:	^\\fB
EndText:	\\fR,^
-
#
GI:		PARAMDEF
StartText:	^\\fB
EndText:	\\fR);^
-
#
#
#############################################################################
#
#  Links
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		LINK
StartText:	\\fI
EndText:	\\fR
-
#
GI:		OLINK
StartText:	\\fI
EndText:	\s(link to external document ${TargetDocEnt})\s\\fR
-
#
GI:		ULINK
StartText:	\\fI
EndText:	\s(link to URL ${URL})\s\\fR
-
#
GI:		FOOTNOTEREF
#	just let the footnote ref mark come through
-
#
GI:		FOOTNOTE
#	just let footnote body come through (-man doesn't support footnotes)
-
#
GI:		XREF
AttValue:	ENDTERM
StartText:	\\fI(cross-reference to ``${_followlink ENDTERM 1000}'')\\fR\s
-
#
GI:		XREF
StartText:	\\fI(cross-reference to ``${_followlink LINKEND 600})''\\fR\s
-
#
GI:		_xref
SpecID:		600
StartText:	${XREFLABEL}
Ignore:		all
-
#
GI:		ANCHOR
#	nothing to do -- this just marks a place..
-
#
#
#############################################################################
#
#  Graphics and Equations
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		GRAPHIC
AttValue:	ENTITYREF
StartText:	^.PP^.if t .P! "${_filename}"^
-
#
GI:		INLINEGRAPHIC
StartText:	^.if t .P! "${_filename}"^
-
#
GI:		INFORMALEQUATION
#	nothing special to do -- defer to graphic content..
-
#
GI:		EQUATION
#	nothing special to do -- defer to graphic content..
-
#
GI:		TITLE
Context:	EQUATION
StartText:	^.PP^\\fB
EndText:	\\fR^
-
#
GI:		INLINEEQUATION
#	nothing special to do -- defer to graphic content..
-
#
#
#############################################################################
#
#  Tables
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
#
GI:		INFORMALTABLE
StartText:	^${_calstable tbl tablestart}^
EndText:	^${_calstable tbl tableend}^
-
#
GI:		TABLE
StartText:	^.PP^\\fB${_followrel child TITLE 1000}\\fR
		^${_calstable tbl tablestart}^
EndText:	^${_calstable tbl tableend}^
-
#
GI:		TITLE
Context:	TABLE
#	handled in TABLE element
Ignore:		all
-
#
GI:		TGROUP
StartText:	^${_calstable tbl tablegroup}^${_followrel child THEAD 700}${_followrel child TBODY 700}${_followrel child TFOOT 701}
EndText:	${_calstable tbl tablegroupend}
-
#
GI:		COLSPEC
Ignore:		all
-
#
GI:		SPANSPEC
Ignore:		all
-
#
GI:		THEAD TBODY TFOOT
#	they're called explicitly from TGROUP, but ignored here
Ignore:		all
-
#
GI:		_thead_tbody
SpecID:		700
#	nothing special to do -- just pass through content
-
#
GI:		_tfoot
SpecID:		701
StartText:	^${_calstable tbl tablefoot}^
-
#
GI:		ROW
StartText:	^${_calstable tbl rowstart}
EndText:	${_calstable tbl rowend}
-
#
GI:		ENTRY
StartText:	${_calstable tbl entrystart}
EndText:	${_calstable tbl entryend}
-
#
GI:		ENTRYTBL
StartText:
EndText:
Message:	^IMPLEMENT <${_gi} ${_allatts}>^
-
#
#
#############################################################################
#
#  Index terms
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		INDEXTERM
StartText:	^.iX\s
EndText:	^
-
#
GI:		PRIMARY
StartText:	"
EndText:	"
-
#
GI:		SECONDARY
StartText:	\s"
EndText:	"
-
#
GI:		TERTIARY
StartText:	\s"
EndText:	"
-
#
GI:		SEE
StartText:	\s"See:\s
EndText:	"
-
#
GI:		SEEALSO
StartText:	\s"SeeAlso:\s
EndText:	"
-
#
#
#############################################################################
#
#  Author / OtherCredit material
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		OTHERCREDIT
#	nothing specific -- defer to content
-
#
GI:		HONORIFIC
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		FIRSTNAME
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		SURNAME
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		LINEAGE
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		OTHERNAME
#	nothing specific -- defer to content
StartText:	(
EndText:	)\s
-
#
GI:		AFFILIATION
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		SHORTAFFIL
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		JOBTITLE
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		ORGNAME
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		ORGDIV
#	nothing specific -- defer to content
EndText:	\s
-
#
GI:		CONTRIB
#	nothing specific -- defer to content
EndText:	\s
-
#
#
#############################################################################
#
#  "Leaf" material
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		ABBREV
#	no special presentation
-
#
GI:		ACCEL
#	no special presentation
-
#
GI:		ACRONYM
#	no special presentation
-
#
GI:		AUTHORINITIALS
#	no special presentation
-
#
GI:		CITATION
StartText:	\\fI
EndText:	\\fP
-
#
GI:		CITETITLE
AttValue:	PUBWORK
StartText:	\\fI
EndText:	\\fP (${PUBWORK})\s
-
#
GI:		CITETITLE
StartText:	\\fI
EndText:	\\fP
-
#
GI:		CITEREFENTRY
#	defer to content..
-
#
GI:		REFENTRYTITLE
StartText:	\\fB
EndText:	\\fP
-
#
GI:		MANVOLNUM
StartText:	\\fB(
EndText:	)\\fP
-
#
GI:		COMMENT
#	docbook says to inhibit this from finished products...
Ignore:		all
-
#
GI:		EMAIL
#	no special presentation
-
#
GI:		EMPHASIS
StartText:	\\fI
EndText:	\\fP
-
#
GI:		FIRSTTERM
StartText:	\\fI
EndText:	\\fR
-
#
GI:		FOREIGNPHRASE
#	no special presentation
-
#
GI:		PHRASE
#	no special presentation
-
#
GI:		QUOTE
StartText:	``\\fI
EndText:	\\fP''
-
#
GI:		TRADEMARK
EndText:	\\u\\s-2TM\\s+2\\d
-
#
GI:		WORDASWORD
#	no special presentation
-
#
GI:		ACTION
#	no special presentation
-
#
GI:		APPLICATION
StartText:	\\fB
EndText:	\\fP
-
#
GI:		CLASSNAME
StartText:	\\fB
EndText:	\\fP
-
#
GI:		COMMAND
StartText:	\\fB
EndText:	\\fP
-
#
GI:		COMPUTEROUTPUT
StartText:	\\f(CW
EndText:	\\fP
-
#
GI:		DATABASE
#	no special presentation
-
#
GI:		ERRORNAME
StartText:	\\fB
EndText:	\\fP
-
#
GI:		ERRORTYPE
#	no special presentation
-
#
GI:		FILENAME
StartText:	\\fB
EndText:	\\fP
-
#
GI:		FUNCTION
StartText:	\\fB
EndText:	\\fP
-
#
GI:		GUIBUTTON
StartText:	\\fB
EndText:	\\fP
-
#
GI:		GUIICON
StartText:	\\fB
EndText:	\\fP
-
#
GI:		GUILABEL
#	no special presentation
-
#
GI:		GUIMENU
#	no special presentation
-
#
GI:		GUIMENUITEM
#	no special presentation
-
#
GI:		GUISUBMENU
#	no special presentation
-
#
GI:		HARDWARE
#	no special presentation
-
#
GI:		INTERFACE
#	no special presentation
-
#
GI:		INTERFACEDEFINITION
StartText:	\\fB
EndText:	\\fP
-
#
GI:		KEYCAP
StartText:	\\fB<
EndText:	>\\fP
-
#
GI:		KEYCODE
#	no special presentation
-
#
GI:		KEYCOMBO
#	no special presentation -- defer to the content
-
#
GI:		KEYSYM
StartText:	\\fB<
EndText:	>\\fP
-
#
GI:		LINEANNOTATION
StartText:	\\fI
EndText:	\\fP
-
#
GI:		LITERAL
StartText:	\\fB
EndText:	\\fP
-
#
GI:		MARKUP
StartText:	\\f(CW
EndText:	\\fP
-
#
GI:		MEDIALABEL
#	no special presentation
-
#
GI:		MENUCHOICE
#	no special presentation
-
#
GI:		SHORTCUT
#	no special presentation
-
#
GI:		MOUSEBUTTON
#	no special presentation
-
#
GI:		OPTION
StartText:	\\fB
EndText:	\\fP
-
#
GI:		OPTIONAL
StartText:	[
EndText:	]
-
#
GI:		PARAMETER
StartText:	\\fB
EndText:	\\fR
-
#
GI:		PROPERTY
StartText:	\\fB
EndText:	\\fP
-
#
GI:		REPLACEABLE
StartText:	\\fI
EndText:	\\fP
-
#
GI:		RETURNVALUE
StartText:	\\fB
EndText:	\\fR
-
#
GI:		SGMLTAG
AttValue:	CLASS ELEMENT
StartText:	\\fB<
EndText:	>\\fP
-
#
GI:		SGMLTAG
StartText:	\\fB
EndText:	\\fP
-
#
GI:		STRUCTFIELD
StartText:	\\fB
EndText:	\\fR
-
#
GI:		STRUCTNAME
StartText:	\\fB
EndText:	\\fR
-
#
GI:		SYMBOL
AttValue:	ROLE Variable
StartText:	\\fI
EndText:	\\fP
-
#
GI:		SYMBOL
StartText:	\\fI
EndText:	\\fP
-
#
GI:		SYSTEMITEM
AttValue:	CLASS CONSTANT
StartText:	\\fB
EndText:	\\fP
-
#
GI:		SYSTEMITEM
AttValue:	CLASS ENVIRONVAR
StartText:	\\fB
EndText:	\\fP
-
#
GI:		SYSTEMITEM
AttValue:	CLASS RESOURCE
StartText:	\\fB
EndText:	\\fP
-
#
GI:		SYSTEMITEM
StartText:	\\fB
EndText:	\\fP
-
#
GI:		TOKEN
StartText:	\\fB
EndText:	\\fP
-
#
GI:		TYPE
StartText:	\\fB
EndText:	\\fP
-
#
GI:		USERINPUT
StartText:	\\fB
EndText:	\\fP
-
#
GI:		AUTHOR
#	no special presentation - defer to content
-
#
GI:		CORPAUTHOR
#	no special presentation
-
#
GI:		MODESPEC
#	nothing to render (this is meta information for Links)
-
#
GI:		PRODUCTNAME
StartText:	\\fB
EndText:	\\fP
-
#
GI:		PRODUCTNUMBER
#	no special presentation
-
#
GI:		SUBSCRIPT
StartText:	\\d
EndText:	\\u
-
#
GI:		SUPERSCRIPT
StartText:	\\u
EndText:	\\d
-
#
#
#############################################################################
#
#  stuff that gets ignored (and doesn't belong elsewhere)
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		TITLEABBREV
#	this element is ignored in favor of the real title
Ignore:		all
-
#
#
#
#############################################################################
#
#  handle layout-specific stuff and PIs
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		BEGINPAGE
StartText:	^.br\s
EndText:	^
-
#
GI:		_x-break
StartText:	^.br\s
EndText:	^
-
#
GI:		_sml-break
StartText:	^.br\s
EndText:	^
-
#
GI:		_sml-need
StartText:	^.ne\s
EndText:	^
-
#
GI:		_sml-size
StartText:	^.ps\s
EndText:	^
-
#
GI:		_sml-indent
StartText:	^.in\s
EndText:	^
-
#
GI:		_sml-space
StartText:	^.sp\s
EndText:	^
-
#
GI:		_sml-tabset
StartText:	^.ta\s
EndText:	^
-
#
#
#############################################################################
#
#  General purpose transpecs
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		_passthrough
SpecID:		1000
-
#
GI:		_doTitle
SpecID:		1010
StartText:	^.PP^\\fB
EndText:	\\fR^.PP^
-
#
#
#############################################################################
#
#  Catch-all for unknown PIs -- ignore them...
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
GI:		_*
Ignore:		data
-
#
#
#############################################################################
#
#  Catch-all for unknown elements -- just output their content..
#
#   ####     #####     #####     #####     #####     #####     ####     #####     
#
#GI:	*
#-
#

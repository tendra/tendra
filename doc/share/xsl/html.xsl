<?xml version='1.0'?>
<xsl:stylesheet  
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="1.0">

  <xsl:import href="/usr/local/share/xsl/docbook/html/docbook.xsl" />
  <xsl:include href="common.xsl" />

<xsl:param name="glossary.as.blocks" select="1"/>

<!--
<xsl:param name="l10n.gentext.default.language" select="ru"/>
-->

<xsl:template name="user.head.content">
  <style>
    <xsl:comment>
BODY ADDRESS {
	line-height: 1.3;
	margin: .6em 0;
}

BODY BLOCKQUOTE {
	margin-top: .75em;
	line-height: 1.5;
	margin-bottom: .75em;
}

HTML BODY {
	margin: 1em 8% 1em 10%;
	line-height: 1.2;
}

.LEGALNOTICE {
	font-size: small;
	font-variant: small-caps;
}

BODY DIV {
	margin: 0;
}

BODY FORM {
	margin: .6em 0;
}

H1, H2, H3, H4, H5, H6,
DIV.EXAMPLE P B,
.QUESTION,
DIV.TABLE P B,
DIV.PROCEDURE P B {
	color: #6699CC;
}

BODY H1 {
	margin: .8em 0 0 -4%;
	line-height: 1.3;
}

BODY H2 {
	margin: .8em 0 0 -4%;
	line-height: 1.3;
}

BODY H3 {
	margin: .8em 0 0 -3%;
	line-height: 1.3;
}

BODY H4 {
	margin: .8em 0 0 -3%;
	line-height: 1.3;
}

BODY H5 {
	margin: .8em 0 0 -2%;
	line-height: 1.3;
}

BODY H6 {
	margin: .8em 0 0 -1%;
	line-height: 1.3;
}

BODY HR {
	margin: .6em
}

BODY IMG.NAVHEADER {
	margin: 0 0 0 -4%;
}

OL {
	margin: 0 0 0 5%;
	line-height: 1.2;
}

BODY P {
	margin: .6em 0;
	line-height: 1.2;
}

BODY PRE {
	margin: .75em 0;
	line-height: 1.0;
	color: #1414ba;
}

BODY TD {
	line-height: 1.2
}

BODY TH {
	line-height: 1.2;
}

UL, BODY DIR, BODY MENU {
	margin: 0 0 0 5%;
	line-height: 1.2;
}

HTML {
	margin: 0; 
	padding: 0;
}


.FILENAME {
	color: #1414ba;
}

BODY H1, BODY H2, BODY H3, BODY H4, BODY H5, BODY H6 {
	margin-left: 0
} 

.GUIMENU, .GUIMENUITEM, .GUISUBMENU,
.GUILABEL, .INTERFACE, .GUIBUTTON,
.SHORTCUT, .SHORTCUT .KEYCAP {
	background-color: #F0F0F0;
}

.ACCEL {
	background-color: #F0F0F0;
	text-decoration: underline;
} 

.nowrap {
	white-space: nowrap;
}

.programlisting {
    margin: .7em 3em;
    color: #1414ba;
}
    </xsl:comment>
  </style>
</xsl:template>



</xsl:stylesheet>



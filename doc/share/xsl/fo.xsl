<?xml version='1.0'?>
<xsl:stylesheet  
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    xmlns:fo="http://www.w3.org/1999/XSL/Format"
    version="1.0">


  <xsl:import href="/usr/local/share/xsl/docbook/fo/docbook.xsl"/>
  <xsl:include href="common.xsl" />

  <xsl:param name="paper.type" select="A4"/>

  <xsl:param name="page.margin.top">0.15in</xsl:param>
  <xsl:param name="page.margin.bottom">0.40in</xsl:param>
  <xsl:param name="body.margin.top">0.33in</xsl:param>
  <xsl:param name="body.margin.bottom">0.33in</xsl:param>

  <xsl:param name="draft.mode" select="no"/>

  <xsl:param name="header.rule" select="1"/>
  <xsl:param name="footer.rule" select="1"/>
  <xsl:param name="headers.on.blank.pages" select="0"/>
  <xsl:param name="footers.on.blank.pages" select="0"/>


  <!-- Depth of sections shown in the header. -->
  <xsl:param name="marker.section.level" select="2" />

  <xsl:param name="fop.extensions" select="1" />

<xsl:param name="linenumbering.extension" select="'1'" />
<xsl:param name="linenumbering.separator" select="' '" />


<xsl:attribute-set name="xref.properties">
  <xsl:attribute name="color">blue</xsl:attribute>
</xsl:attribute-set>

<xsl:attribute-set name="programlisting.properties">
  <xsl:attribute name="color">blue</xsl:attribute>
</xsl:attribute-set>


<xsl:attribute-set name="verbatim.properties">
  <xsl:attribute name="color">blue</xsl:attribute>
</xsl:attribute-set>


</xsl:stylesheet>

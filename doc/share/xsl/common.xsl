<?xml version='1.0'?>
<xsl:stylesheet
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
    version="1.0">

  <xsl:param name="chapter.autolabel" select="1"/>
  <xsl:param name="appendix.autolabel" select="1"/>
  <xsl:param name="section.autolabel" select="1"/>
  <xsl:param name="section.label.includes.component.label" select="1"/>
  <xsl:param name="insert.xref.page.number" select="1"/>
  <xsl:param name="generate.index" select="1"/>
  <xsl:param name="xref.with.number.and.title" select="1"/>


  <!-- Place a number on every line for <programlistings> -->
  <xsl:param name="linenumbering.everyNth" select="1"/>

  <!-- Turn on the docbook xsl extensions. -->
  <xsl:param name="use.extensions" select="1"/>
  <xsl:param name="callouts.extension" select="1"/>
  <xsl:param name="textinsert.extension" select="1"/>

  <!-- This extension does _weird_ things... -->
  <xsl:param name="tablecolumns.extension" select="1"/>


  <xsl:param name="use.role.for.mediaobject" select="1"/>


  <!-- **** HTML ONLY **** -->
<!--
  <xsl:template name="body.attributes">
    <xsl:attribute name="bgcolor">#eeeeee</xsl:attribute>
    <xsl:attribute name="text">#000000</xsl:attribute>
    <xsl:attribute name="link">#2276CB</xsl:attribute>
    <xsl:attribute name="vlink">#2276CB</xsl:attribute>
    <xsl:attribute name="alink">#999999</xsl:attribute>
  </xsl:template>
-->


  <!-- **** PRINT ONLY **** -->
  <xsl:param name="ulink.show" select="1"/>


</xsl:stylesheet>

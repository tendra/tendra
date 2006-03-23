<?xml version='1.0'?>
<xsl:stylesheet  
    xmlns:xsl="http://www.w3.org/1999/XSL/Transform" 
    version="1.0">

  <xsl:import href="/usr/local/share/xsl/docbook/html/docbook.xsl" />
  <xsl:include href="common.xsl" />

  <xsl:param name="html.stylesheet" select="'docbook.css'"/>

<xsl:param name="glossary.as.blocks" select="1"/>

<!--
<xsl:param name="l10n.gentext.default.language" select="ru"/>
-->

<!--
<xsl:template name="output.html.stylesheets">
  <style>
    <xsl:include href="../docbook.css" />
  </style>
</xsl:template>
-->

</xsl:stylesheet>

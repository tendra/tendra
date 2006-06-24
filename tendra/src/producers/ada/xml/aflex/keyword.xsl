<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<xsl:output method="text"/>

<xsl:template match="/">
  <xsl:apply-templates select="//keyword" />
</xsl:template>

<xsl:template match="keyword" >
<xsl:value-of select="@name"/>.<xsl:value-of select="@name"/>.<xsl:value-of select="@name"/>.
</xsl:template>

</xsl:stylesheet>

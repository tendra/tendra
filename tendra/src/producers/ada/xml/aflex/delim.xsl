<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<xsl:output method="text"/>

<xsl:template match="/">
  <xsl:apply-templates select="//delimiter" />
</xsl:template>

<xsl:template match="delimiter" >
"<xsl:value-of select="@text"/>" <xsl:value-of select="@name"/>
</xsl:template>

</xsl:stylesheet>

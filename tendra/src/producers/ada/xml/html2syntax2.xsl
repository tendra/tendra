<?xml version="1.0" encoding="utf-8"?>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<xsl:output method="text" indent="yes" encoding="utf-8"/>

<xsl:template match="/">
  <xsl:apply-templates select="*"/>
</xsl:template>

<xsl:template match="gramar">
begin_gramar
    <xsl:apply-templates select="*"/>
end_gramar
</xsl:template>


<xsl:template match="rule[count(span[@class='swiss']/text)=0]"/>

<xsl:template match="rule">
do_rule "<xsl:value-of select="span[@class='swiss'][1]/text/@value"/>" "<xsl:value-of select="label/@text"/>" 
<xsl:apply-templates select="*[position()>2]"/>
end_rule
</xsl:template>

<xsl:template match="span[count(*)=0]"/>

<xsl:template match="span">
  <xsl:if test="not((a[@href]/text)|text)">
ERROR
</xsl:if>
do_ref "<xsl:value-of select="descendant::text/@value"/>" "<xsl:if
  test="name(preceding-sibling::*[1])='i'">
  <xsl:value-of select="preceding-sibling::i[1]/text/@value"/>
</xsl:if>"
</xsl:template>

<xsl:template match="text">
  <xsl:variable name="quotion">'</xsl:variable>
  <xsl:if test='contains(@value,$quotion)'>
do_texts "<xsl:value-of select="@value"/>"
  </xsl:if>
  <xsl:if test="not(contains(@value,$quotion))">
do_texts '<xsl:value-of select="@value"/>'
  </xsl:if>
</xsl:template>

<xsl:template match="b">
do_keyword "<xsl:value-of select="text/@value"/>"
</xsl:template>

<xsl:template match="i|text()"/>

</xsl:stylesheet>

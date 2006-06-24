<?xml version='1.0'?>
<!DOCTYPE stylesheet [
<!ENTITY nbsp "&#160;">
]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<xsl:output method="html" indent="yes" encoding="utf-8"/>

<xsl:template match="/">
<html>
<head/>
    <xsl:apply-templates select="*"/>
</html>
</xsl:template>

<xsl:template match="gramar">
  <table border='0'>
    <xsl:apply-templates select="*">
      <xsl:sort select="@name"/>
    </xsl:apply-templates>
  </table>
</xsl:template>

<xsl:template match="rule">
   <xsl:apply-templates select="*"/>
</xsl:template>

<xsl:template match="alts">
  <xsl:apply-templates select="*"/>
</xsl:template>

<xsl:template match="seq">
  <xsl:if test="position()=1">
  <tr><td>&nbsp;</td></tr>
  </xsl:if>
  <tr>
    <td>
      <xsl:if test="position()=1">
        <a name="{ancestor::rule/@name}"/>
        <xsl:value-of select="ancestor::rule/@name"/>
      </xsl:if>
    </td>
    <td>
      <xsl:if test="not(@status)">
       <xsl:attribute name="style">background:#e0e0e0</xsl:attribute>
      </xsl:if>
      <xsl:if test="position()!=1"> | &nbsp;</xsl:if>
      <xsl:apply-templates select="*"/>
    </td>
  </tr>
</xsl:template>

<xsl:template match="deleted-seq">
  <xsl:if test="position()=1">
  <tr><td>&nbsp;</td></tr>
  </xsl:if>
  <tr>
    <td>
      <xsl:if test="position()=1">
        <xsl:value-of select="ancestor::rule/@name"/>
      </xsl:if>
    </td>
    <td style="text-decoration:line-through">
        <xsl:if test="position()!=1"> | &nbsp;</xsl:if>
        <xsl:apply-templates select="*"/>
    </td>
  </tr>
</xsl:template>

<xsl:template match="ref">
  <xsl:if test="@italic">
  <i><xsl:value-of select="@italic"/></i>
  </xsl:if>
  <a href="#{@name}"><xsl:value-of select="@name"/></a>&nbsp;
</xsl:template>

<xsl:template match="opt">
 [ &nbsp;
   <xsl:apply-templates select="seq/*"/>
 ] &nbsp;
</xsl:template>

<xsl:template match="list">
 { &nbsp;
   <xsl:apply-templates select="seq/*"/>
 } &nbsp;
</xsl:template>

<xsl:template match="keyword|delim">
  <b><xsl:value-of select="@text"/></b> &nbsp;
</xsl:template>

</xsl:stylesheet>

<?xml version="1.0" encoding="utf-8"?>
<!DOCTYPE xsl:stylesheet [
<!ENTITY nbsp "&#160;"> 
<!ENTITY ndash "&#8211;">
<!ENTITY cr "&#13;"> 
<!ENTITY nl "&#10;"> 
]>

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<!--  remove span class="deleteX" and copy span class=insertX -->

<xsl:output method="xml" indent="yes" encoding="utf-8"/>

<xsl:template match="/">
  <gramar>
    <xsl:apply-templates select="//div[@class='SyntaxSummary']"/>
  </gramar>
</xsl:template>

<xsl:template match="div[@style]"/>

<xsl:template match="div">
  <rule>
   <xsl:apply-templates select="*|text()"/>
  </rule>
</xsl:template>

<xsl:template match="@*|*">
  <xsl:copy>
   <xsl:apply-templates select="*|@*|text()"/>
  </xsl:copy>
</xsl:template>

<xsl:template match="span[@class='delete2']|span[@class='delete1']|br"/>

<xsl:template match="span[@class='insert2']|span[@class='insert1']|a[@name]">
   <xsl:apply-templates select="*|text()"/>
</xsl:template>

<xsl:template match="span[@class='swiss']">
   <xsl:if test="count(*|text())">
     <xsl:copy>
       <xsl:apply-templates select="*|@*|text()"/>
     </xsl:copy>
   </xsl:if>
</xsl:template>

<xsl:template match="text()">
  <xsl:variable name="val" select="translate(.,'&ndash;&nbsp;&cr;&nl;','-')"/>
  <xsl:variable name="value">
    <xsl:if test="contains($val,'::=')">
      <xsl:value-of select=
        "concat(substring-before($val,'::='),substring-after($val,'::='))"/>
    </xsl:if>
    <xsl:if test="not(contains($val,'::='))">
      <xsl:value-of select="$val"/>
    </xsl:if>
  </xsl:variable>
  <xsl:if test="string-length($value)>0 and
    ($value!=':' or name(following-sibling::*[1])!='br')">
    <text value="{$value}"/>
  </xsl:if>
</xsl:template>

<xsl:template match="a[@href][name(following-sibling::*[1])='br']">
  <label text="{text()}"/>
</xsl:template>

<xsl:template match="b">
  <xsl:copy>
    <text value="{translate(text(),'&nbsp;',' ')}"/>
  </xsl:copy>
</xsl:template>

</xsl:stylesheet>

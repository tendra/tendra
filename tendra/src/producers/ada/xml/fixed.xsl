<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<xsl:output method="xml" indent='yes'/>

<xsl:variable name="tokens" select="document('tokens.xml')"/>
<xsl:variable name="fix"    select="document('fix.xml')"/>

<xsl:template match="/|*|@*">
  <xsl:copy>
   <xsl:apply-templates select="*|@*"/>
  </xsl:copy>
</xsl:template>
  
<xsl:template match="rule" >
 <xsl:variable name="rule-name" select="@name"/>
 <xsl:if test="count($tokens//token[@name=$rule-name])=0">
  <xsl:copy>
   <xsl:apply-templates select="@*"/>
   <xsl:if test="count($fix//rule[@name=$rule-name])=0">
     <xsl:apply-templates select="*"/>
   </xsl:if>
   <xsl:if test="count($fix//rule[@name=$rule-name])!=0">
     <xsl:apply-templates select="$fix//rule[@name=$rule-name]/*"/>
   </xsl:if>
  </xsl:copy>
 </xsl:if>
</xsl:template>

<xsl:template match="gramar">
  <xsl:copy>
   <xsl:apply-templates select="*|@*"/>
   <xsl:apply-templates select="$fix//rule[@added='yes']"/>
  </xsl:copy>
</xsl:template>

<xsl:template match="deleted-seq"/>

</xsl:stylesheet>

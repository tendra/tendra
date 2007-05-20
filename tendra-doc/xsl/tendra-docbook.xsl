<?xml version="1.0"?>

<!-- $Id$ -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version='1.0'>

	<xsl:import href="http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl"/>

	<xsl:param name="css.decoration">0</xsl:param>
	<xsl:param name="paper.type">A4</xsl:param>
	<xsl:param name="section.autolabel">1</xsl:param>
	<xsl:param name="section.label.includes.component.label">1</xsl:param>

<!-- TODO prefix a header:
	<xsl:template name="allpages.banner">
		<h1 id="banner">
			<xsl:text>The </xsl:text>
			<span class="logo">
				<xsl:text>Ten</xsl:text>
				<span class="smallcaps">
					<xsl:text>DRA</xsl:text>
				</span>
			</span>
			<xsl:text> Project</xsl:text>
		</h1>
	</xsl:template>
-->

<!-- TODO use $Date$ for a footer similar to the website:

	$rcsdate is in Subversion's $Date$ format, e.g. "$Date: 2007-05-19 17:34:01 +0100 (Sat, 19 May 2007) $"
	<xsl:template name="rcsdate.format">
		<xsl:param name="rcsdate" select="./config[@param='rcsdate']/@value"/>
		<xsl:value-of select="substring-before(substring-after($rcsdate, '('), ')')"/>
	</xsl:template>
-->

</xsl:stylesheet>


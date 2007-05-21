<?xml version="1.0"?>

<!-- $Id$ -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version='1.0'>

	<xsl:import href="http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl"/>

	<xsl:param name="css.decoration">0</xsl:param>
	<xsl:param name="paper.type">A4</xsl:param>
	<xsl:param name="section.autolabel">1</xsl:param>
	<xsl:param name="section.label.includes.component.label">1</xsl:param>

	<xsl:template name="user.header.content">
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

<!-- TODO use $Date$ for a footer similar to the website:

	$rcsdate is in Subversion's $Date$ format, e.g. "$Date: 2007-05-19 17:34:01 +0100 (Sat, 19 May 2007) $"
	<xsl:template name="rcsdate.format">
		<xsl:param name="rcsdate" select="./config[@param='rcsdate']/@value"/>
		<xsl:value-of select="substring-before(substring-after($rcsdate, '('), ')')"/>
	</xsl:template>
-->

	<xsl:template name="user.footer.content">
		<div class="navfoot">
			<!-- This is a big nasty table to correspond to Website -->
			<table width="100%" border="0" summary="Footer navigation">
				<tr>
					<td>
						<span class="footdate">Sat, 19 May 2007</span>
					</td>
				</tr>
				<tr>
					<td>
						<span class="footcopy">
							<!-- TODO the © is redundant. override it from Website, and remove it here -->
							<span class="copyright">Copyright © 2007 The TenDRA Project. </span>
						</span>
					</td>
				</tr>
			</table>
		</div>
	</xsl:template>

	<!-- These make affliations a little less intrusive -->
	<xsl:template match="affiliation" mode="titlepage.mode">
		<xsl:text>, </xsl:text>
		<xsl:apply-templates mode="titlepage.mode"/>
	</xsl:template>

	<xsl:template match="othercredit" mode="titlepage.mode">
		<xsl:variable name="contrib" select="string(contrib)"/>
		<xsl:choose>
			<xsl:when test="contrib">
				<xsl:if test="not(preceding-sibling::othercredit[string(contrib)=$contrib])">
					<xsl:apply-templates mode="titlepage.mode" select="contrib"/>
					<xsl:text>: </xsl:text>
					<xsl:call-template name="person.name"/>
					<xsl:apply-templates mode="titlepage.mode" select="./affiliation"/>
					<xsl:apply-templates select="following-sibling::othercredit[string(contrib)=$contrib]" mode="titlepage.othercredits"/>
					<xsl:if test="@class">
						<xsl:text> (</xsl:text>
						<xsl:value-of select="@class"/>
						<xsl:text>)</xsl:text>
					</xsl:if>
				</xsl:if>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="person.name"/>
				<xsl:if test="@class">
					<xsl:text> (</xsl:text>
					<xsl:value-of select="@class"/>
					<xsl:text>)</xsl:text>
				</xsl:if>
				<xsl:apply-templates mode="titlepage.mode" select="./affiliation"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="author" mode="titlepage.mode">
		<div class="{name(.)}">
			<xsl:call-template name="person.name"/>
			<xsl:apply-templates mode="titlepage.mode" select="./contrib"/>
			<xsl:apply-templates mode="titlepage.mode" select="./affiliation"/>
			<xsl:apply-templates mode="titlepage.mode" select="./email"/>
		</div>
	</xsl:template>
</xsl:stylesheet>


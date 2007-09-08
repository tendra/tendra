<?xml version="1.0"?>

<!-- $Id$ -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version='1.0'>

	<xsl:param name="css.decoration">0</xsl:param>
	<xsl:param name="paper.type">A4</xsl:param>
	<xsl:param name="section.autolabel">1</xsl:param>
	<xsl:param name="section.label.includes.component.label">1</xsl:param>
	<xsl:param name="suppress.header.navigation">0</xsl:param>
	<xsl:param name="suppress.footer.navigation">0</xsl:param>
	<xsl:param name="navig.showtitles">1</xsl:param>

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

	<!--
	   - We we'd like header.navigation to be after our user.header.content banner,
	   - and likewise for the footer.
	  -->
	<xsl:template name="chunk-element-content">
		<xsl:param name="prev"/>
		<xsl:param name="next"/>
		<xsl:param name="nav.context"/>
		<xsl:param name="content">
			<xsl:apply-imports/>
		</xsl:param>

		<xsl:call-template name="user.preroot"/>

		<html>
			<xsl:call-template name="html.head">
				<xsl:with-param name="prev" select="$prev"/>
				<xsl:with-param name="next" select="$next"/>
			</xsl:call-template>

			<body>
				<xsl:call-template name="body.attributes"/>

				<xsl:call-template name="user.header.content"/>

				<xsl:call-template name="user.header.navigation"/>

				<xsl:call-template name="header.navigation">
					<xsl:with-param name="prev" select="$prev"/>
					<xsl:with-param name="next" select="$next"/>
					<xsl:with-param name="nav.context" select="$nav.context"/>
				</xsl:call-template>

				<xsl:copy-of select="$content"/>

				<xsl:call-template name="footer.navigation">
					<xsl:with-param name="prev" select="$prev"/>
					<xsl:with-param name="next" select="$next"/>
					<xsl:with-param name="nav.context" select="$nav.context"/>
				</xsl:call-template>

				<xsl:call-template name="user.footer.content"/>

				<xsl:call-template name="user.footer.navigation"/>
			</body>
		</html>
	</xsl:template>

</xsl:stylesheet>


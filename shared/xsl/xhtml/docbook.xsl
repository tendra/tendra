<?xml version="1.0"?>

<!-- $Id$ -->

<!--
	This stylesheet provides templates and parameters common to both
	single and chunked XHTML outputs.

	Do not include this file directly; use the docbook-{chunked,single}.xsl
	interfaces provided, instead.
-->

<xsl:stylesheet
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:str="http://exslt.org/strings"
	xmlns="http://www.w3.org/1999/xhtml"
	extension-element-prefixes="str"
	version="1.0">

	<xsl:import href="../common/common-dtns.xsl"/>
	<xsl:import href="../common/common-api.xsl"/>

	<xsl:import href="common-api.xsl"/>
	<xsl:import href="docbook-sanitize.xsl"/>

	<xsl:param name="tendra.base"/>     	<!-- e.g. 'http://www.tendra.org/' -->
	<xsl:param name="tendra.bodyclass"/>	<!-- e.g. 'single' -->
	<xsl:param name="tendra.chunk"/>    	<!-- e.g. 'yes' -->
	<xsl:param name="tendra.method"/>    	<!-- e.g. 'xml' -->
	<xsl:param name="tendra.ext"/>         	<!-- e.g. 'xhtml' -->

	<!-- TODO: i think these can just be select="" -->
	<xsl:param name="css.decoration"><xsl:text>0</xsl:text></xsl:param>
	<xsl:param name="paper.type"><xsl:text>A4</xsl:text></xsl:param>
	<xsl:param name="section.autolabel"><xsl:text>1</xsl:text></xsl:param>
	<xsl:param name="section.label.includes.component.label"><xsl:text>1</xsl:text></xsl:param>
	<xsl:param name="suppress.header.navigation"><xsl:text>0</xsl:text></xsl:param>
	<xsl:param name="suppress.footer.navigation"><xsl:text>0</xsl:text></xsl:param>
	<xsl:param name="navig.showtitles"><xsl:text>1</xsl:text></xsl:param>
	<xsl:param name="generate.meta.abstract"><xsl:text>1</xsl:text></xsl:param>
	<xsl:param name="html.cellspacing"><xsl:text>0</xsl:text></xsl:param>
	<xsl:param name="html.cellpadding"><xsl:text>0</xsl:text></xsl:param>
	<xsl:param name="table.borders.with.css"><xsl:text>1</xsl:text></xsl:param>

	<!--
		TODO: syntax hilighting for programlisting, based on @language
	-->

	<!--
		see http://www.sagehill.net/docbookxsl/HTMLHeaders.html

		Template name           When it is called
		user.header.navigation  Called before standard navigational header.
		header.navigation       The standard navigational header.
		user.header.content     Called after standard navigational header but before any other content.
		user.footer.content     Called after the chunk content but before the standard navigational footer.
		footer.navigation       The standard navigational footer.
		user.footer.navigation  Called after the standard navigational footer.
	-->

	<!-- see http://www.sagehill.net/docbookxsl/HtmlHead.html -->
	<xsl:template name="user.head.content">
		<link rel="stylesheet" type="text/css" media="screen" href="{$tendra.base}/css/common.css"/>
		<link rel="stylesheet" type="text/css" media="screen" href="{$tendra.base}/css/docbook.css"/>

		<script src="{$tendra.base}/js/linenumbers.js" type="text/javascript"></script>
	</xsl:template>

	<xsl:template name="body.attributes">
		<xsl:attribute name="onload"><xsl:text>init_linenumbers()</xsl:text></xsl:attribute>
		<xsl:attribute name="class"><xsl:value-of select="$tendra.bodyclass"/></xsl:attribute>
	</xsl:template>

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

		<xsl:if test="$tendra.chunk">
			<xsl:call-template name="chunklink"/>
		</xsl:if>
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


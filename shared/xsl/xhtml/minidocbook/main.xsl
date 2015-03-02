<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<!--
		This is an XSLT transformation to produce XHTML from the subset of Docbook
		which is actually used. This has two goals: two reduce dependencies (which
		often seem complex to users, especially with respect to XML catalogues),
		and to produce simple and clean XHTML output without requiring overriding
		templates.
	-->

	<xsl:import href="fallback.xsl"/>
	<xsl:import href="output.xsl"/>
	<xsl:import href="page.xsl"/>

	<xsl:import href="blocks.xsl"/>
	<xsl:import href="inline.xsl"/>
	<xsl:import href="links.xsl"/>
	<xsl:import href="lists.xsl"/>
	<xsl:import href="title.xsl"/>
	<xsl:import href="toc.xsl"/>
	<xsl:import href="frontmatter.xsl"/>
	<xsl:import href="table.xsl"/>
	<xsl:import href="footnotes.xsl"/>
	<xsl:import href="refentry.xsl"/>

	<xsl:param name="tendra.base" select="'.'"/>
	<xsl:param name="tendra.ext"  select="'xhtml'"/>

	<xsl:param name="tendra.url.ext" select="'http://wiki.tendra.org/FileTypes'"/>
	<xsl:param name="tendra.url.man" select="'http://man.tendra.org'"/>
	<xsl:param name="tendra.url.www" select="'http://www.tendra.org'"/>


	<xsl:template match="/refentry">
		<xsl:variable name="title">
			<xsl:apply-templates select="refmeta"/>
		</xsl:variable>

		<xsl:call-template name="page-single">
			<xsl:with-param name="title"     select="$title"/>
			<xsl:with-param name="filename"  select="'index'"/>
			<xsl:with-param name="chunklink" select="false"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="/article">
		<xsl:variable name="title">
			<xsl:apply-templates select="articleinfo/title" mode="title"/>
		</xsl:variable>

		<xsl:call-template name="page-single">
			<xsl:with-param name="title"     select="$title"/>
			<xsl:with-param name="filename"  select="'index'"/>
			<xsl:with-param name="chunklink" select="false"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="/book">
		<xsl:variable name="title">
			<xsl:apply-templates select="bookinfo/title" mode="title"/>
		</xsl:variable>

		<xsl:call-template name="page-single">
			<xsl:with-param name="title"     select="$title"/>
			<xsl:with-param name="filename"  select="'single'"/>
			<xsl:with-param name="chunklink" select="'index'"/>
		</xsl:call-template>

		<xsl:call-template name="page-toc">
			<xsl:with-param name="title" select="$title"/>
		</xsl:call-template>

		<xsl:call-template name="page-frontmatter">
			<xsl:with-param name="title" select="$title"/>
		</xsl:call-template>

		<xsl:for-each select="preface|chapter|appendix">
			<xsl:call-template name="page-chunk">
				<xsl:with-param name="title"    select="$title"/>
				<xsl:with-param name="filename">
					<xsl:apply-templates select="." mode="page-filename"/>
				</xsl:with-param>
			</xsl:call-template>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="text()">
		<!-- TODO: normalise spaces without trimming -->
		<xsl:copy-of select="."/>
	</xsl:template>

</xsl:stylesheet>


<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<!--
		TODO: when the dust settles, fold this all into output.xsl
	-->

	<xsl:template match="preface|chapter|appendix" mode="page-filename">
		<xsl:value-of select="name()"/>
		<xsl:value-of select="count(preceding-sibling::*[name() = name(current())]) + 1"/>
	</xsl:template>

	<xsl:template name="navlink">
		<xsl:param name="filename"/>
		<xsl:param name="name"/>

		<xsl:param name="predicate" select="$filename != ''"/>

		<xsl:choose>
			<xsl:when test="$predicate">
				<!-- TODO: @title. same for all <a> links. centralise that? -->
				<a href="{$filename}.{$tendra.ext}">
					<xsl:value-of select="$name"/>
				</a>
			</xsl:when>
			<xsl:otherwise>
				<xsl:value-of select="$name"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template name="navigation">
		<!-- TODO: i don't like that this requires chunking and filename knowledge.
			it should be done in the root xsl file -->
		<xsl:variable name="prev">
			<xsl:choose>
				<xsl:when test="name() = 'book'"/>
				<xsl:when test="preceding-sibling::preface
					|preceding-sibling::chapter
					|preceding-sibling::appendix">
					<xsl:apply-templates select="(preceding-sibling::preface
						|preceding-sibling::chapter
						|preceding-sibling::appendix)[position() = last()]" mode="page-filename"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:text>index</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="next">
			<xsl:choose>
				<xsl:when test="name() = 'book'">
					<xsl:apply-templates select="(preface|chapter|appendix)
						[position() = 1]" mode="page-filename"/>
				</xsl:when>
				<xsl:when test="following-sibling::preface
					|following-sibling::chapter
					|following-sibling::appendix">
					<xsl:apply-templates select="(following-sibling::preface
						|following-sibling::chapter
						|following-sibling::appendix)[position() = 1]" mode="page-filename"/>
				</xsl:when>
				<xsl:otherwise/>
			</xsl:choose>
		</xsl:variable>

		<div class="pages">
			<xsl:call-template name="navlink">
				<xsl:with-param name="filename"  select="$prev"/>
				<xsl:with-param name="name"      select="'Prev'"/>
			</xsl:call-template>

			<xsl:text>&#160;|&#160;</xsl:text>

			<xsl:call-template name="navlink">
				<xsl:with-param name="filename"  select="'index'"/>
				<xsl:with-param name="name"      select="'Home'"/>
				<xsl:with-param name="predicate" select="name() != 'book'"/>
			</xsl:call-template>

			<xsl:text>&#160;|&#160;</xsl:text>

			<xsl:call-template name="navlink">
				<xsl:with-param name="filename"  select="$next"/>
				<xsl:with-param name="name"      select="'Next'"/>
			</xsl:call-template>
		</div>
	</xsl:template>

	<xsl:template name="page-single">
		<xsl:param name="title"/>
		<xsl:param name="filename"/>
		<xsl:param name="chunklink"/>

		<xsl:call-template name="output">
			<xsl:with-param name="filename"    select="$filename"/>
			<xsl:with-param name="title"       select="$title"/>
			<xsl:with-param name="bottomright">
				<xsl:apply-templates select="/refentry/refmeta"/>
			</xsl:with-param>

			<xsl:with-param name="content">
				<xsl:if test="$chunklink">
					<div class="navigation">
						<a href="index.{$tendra.ext}">
							<xsl:text>Multiple pages</xsl:text>
						</a>
					</div>
				</xsl:if>

				<xsl:if test="name() != 'refentry'">
					<h1>
						<xsl:copy-of select="$title"/>
					</h1>

					<xsl:call-template name="toc">
						<xsl:with-param name="depth"  select="1"/>
					</xsl:call-template>
				</xsl:if>

				<xsl:choose>
					<xsl:when test="name() = 'refentry'">
						<xsl:apply-templates select="refnamediv|refsynopsisdiv|refsection"/>
					</xsl:when>
					<xsl:otherwise>
						<xsl:apply-templates select="preface|chapter|section|appendix"/>
					</xsl:otherwise>
				</xsl:choose>

				<xsl:if test="name() = 'article'">
					<xsl:call-template name="footnotes">
						<xsl:with-param name="predicate" select="'[not(ancestor::table)]'"/>
					</xsl:call-template>
				</xsl:if>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="page-toc">
		<xsl:param name="title"/>

		<xsl:call-template name="output">
			<xsl:with-param name="filename" select="'index'"/>
			<xsl:with-param name="title"    select="$title"/>

			<xsl:with-param name="content">
				<div class="navigation">
					<a href="single.{$tendra.ext}">
						<xsl:text>Single page</xsl:text>
					</a>

					<xsl:call-template name="navigation"/>
				</div>

				<h1>
					<xsl:copy-of select="$title"/>
				</h1>

				<xsl:call-template name="toc">
					<xsl:with-param name="depth"  select="1"/>
					<xsl:with-param name="single" select="false"/>
				</xsl:call-template>

				<div class="navigation bottom">
					<xsl:call-template name="navigation"/>
				</div>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<xsl:template name="page-chunk">
		<xsl:param name="title"/>
		<xsl:param name="filename"/>

		<xsl:call-template name="output">
			<xsl:with-param name="filename" select="$filename"/>
			<xsl:with-param name="title">
				<xsl:apply-templates select="title" mode="title"/>
			</xsl:with-param>

			<xsl:with-param name="content">
				<div class="navigation">
					<a href="single.{$tendra.ext}">
						<xsl:text>Single page</xsl:text>
					</a>

					<xsl:call-template name="navigation"/>
				</div>

				<xsl:apply-templates select="."/>

				<div class="navigation bottom">
					<xsl:call-template name="navigation"/>
				</div>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

</xsl:stylesheet>


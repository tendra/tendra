<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:mdb="http://xml.elide.org/minidocbook"
	xmlns:func="http://exslt.org/functions"
	xmlns="http://www.w3.org/1999/xhtml"

	extension-element-prefixes="func">

	<!--
		TODO: possibly merge with title.xsl
	-->

	<func:function name="mdb:sectionnumber">
		<xsl:variable name="n">
			<xsl:choose>
				<xsl:when test="ancestor-or-self::preface">
					<xsl:number count="preface|section" level="any" format="i.i."/>
				</xsl:when>
				<xsl:when test="ancestor-or-self::appendix">
					<xsl:number count="appendix|section" level="multiple" format="A.1."/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:number count="chapter|section|refnamediv|refsynopsisdiv|refsection" level="multiple" format="1.1."/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<func:result select="substring($n, 0, string-length($n))"/>
	</func:function>

	<func:function name="mdb:sectionnumber-link">
		<func:result select="concat('S', mdb:sectionnumber())"/>
	</func:function>

	<xsl:template name="toc">
		<xsl:param name="depth"/>
		<xsl:param name="single" select="true()"/>

		<xsl:if test="section|preface|chapter|appendix|bibliography|refnamediv|refsynopsisdiv|refsection">
			<ol class="toc">
				<xsl:apply-templates select="section|preface|chapter|appendix|refnamediv|refsynopsisdiv|refsection" mode="toc">
					<xsl:with-param name="depth"  select="$depth"/>
					<xsl:with-param name="single" select="$single"/>
				</xsl:apply-templates>
			</ol>
		</xsl:if>
	</xsl:template>

	<xsl:template match="section|preface|chapter|appendix|refnamediv|refsynopsisdiv|refsection" mode="toc">
		<xsl:param name="depth"/>
		<xsl:param name="single"/>

		<li>
			<a>
				<xsl:attribute name="href">
					<!-- TODO: rephrase this as an xsl:choose on $single -->
					<xsl:if test="not($single)">
						<xsl:apply-templates select="ancestor-or-self::preface
							|ancestor-or-self::chapter
							|ancestor-or-self::appendix" mode="page-filename"/>
						<xsl:value-of select="concat('.', $tendra.ext)"/>
					</xsl:if>

					<xsl:if test="$single
						or count(ancestor::preface|ancestor::section|ancestor::chapter|ancestor::appendix) &gt; 0">
						<xsl:text>#</xsl:text>
						<xsl:value-of select="mdb:sectionnumber-link()"/>
					</xsl:if>
				</xsl:attribute>

				<xsl:value-of select="mdb:sectionnumber()"/>
				<xsl:text>.&#160;</xsl:text>

				<!-- TODO: centralise against refentry.xsl -->
				<xsl:choose>
					<xsl:when test="name() = 'refsynopsisdiv'">
						<xsl:text>Synopsis</xsl:text>
					</xsl:when>
					<xsl:when test="name() = 'refnamediv'">
						<xsl:text>Name</xsl:text>
					</xsl:when>
					<xsl:otherwise>
						<xsl:apply-templates select="title" mode="title"/>
					</xsl:otherwise>
				</xsl:choose>
			</a>

			<xsl:if test="count(ancestor::preface|ancestor::section|ancestor::chapter|ancestor::appendix) &lt; $depth">
				<xsl:if test="section">
					<ol>
						<xsl:apply-templates select="section" mode="toc">
							<xsl:with-param name="depth"  select="$depth"/>
							<xsl:with-param name="single" select="$single"/>
						</xsl:apply-templates>
					</ol>
				</xsl:if>
			</xsl:if>
		</li>
	</xsl:template>

</xsl:stylesheet>


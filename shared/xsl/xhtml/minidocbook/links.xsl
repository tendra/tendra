<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:mdb="http://xml.elide.org/minidocbook"
	xmlns="http://www.w3.org/1999/xhtml">

	<!--
		Links
	-->

	<xsl:template match="xref">
		<!-- TODO: simplify -->

		<xsl:if test="count(
			 //preface [@id = current()/@linkend]
			|//chapter [@id = current()/@linkend]
			|//section [@id = current()/@linkend]
			|//appendix[@id = current()/@linkend]) = 0">
			<xsl:message>
				<xsl:text>Linkend </xsl:text>
				<xsl:value-of select="@linkend"/>
				<xsl:text> not found</xsl:text>
			</xsl:message>
		</xsl:if>

		<xsl:for-each select="
			 //preface [@id = current()/@linkend]
			|//chapter [@id = current()/@linkend]
			|//section [@id = current()/@linkend]
			|//appendix[@id = current()/@linkend]" mode="linkend">

			<!-- TODO: multi-page links -->
			<a href="#{mdb:sectionnumber-link()}">
				<xsl:text>&#167;</xsl:text>
				<xsl:value-of select="mdb:sectionnumber()"/>
			</a>

			<xsl:if test="position() > 0">
				<xsl:message>
					<xsl:text>Linkend </xsl:text>
					<xsl:value-of select="@linkend"/>
					<xsl:text> found multiple times</xsl:text>
				</xsl:message>
			</xsl:if>
		</xsl:for-each>
	</xsl:template>

	<xsl:template match="citerefentry">
		<xsl:choose>
			<!-- own page -->
			<xsl:when test="/refentry/refmeta/refentrytitle = refentrytitle
			            and /refentry/refmeta/manvolnum     = manvolnum">
				<tt class="command">
					<xsl:value-of select="refentrytitle"/>
				</tt>
			</xsl:when>

			<xsl:when test="ancestor::refsection/title = 'See Also'">
				<a href="{$mdb.url.man}/{refentrytitle}.{manvolnum}/">
					<xsl:call-template name="reftitle"/>
				</a>
			</xsl:when>

			<!-- first occurance -->
			<!-- TODO: maybe make this first occurance per section instead -->
			<xsl:when test="not(preceding::citerefentry
					[refentrytitle = current()/refentrytitle]
					[manvolnum     = current()/manvolnum])">
				<a href="{$mdb.url.man}/{refentrytitle}.{manvolnum}/">
					<xsl:call-template name="reftitle"/>
				</a>
			</xsl:when>

			<xsl:otherwise>
				<tt class="command">
					<xsl:value-of select="refentrytitle"/>
				</tt>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="ulink">
		<a href="{@url}">
			<xsl:apply-templates/>
		</a>
	</xsl:template>

	<xsl:template match="link">
		<!-- TODO: unimplemented -->
		<a href="#TODO">
			<xsl:apply-templates/>
		</a>
	</xsl:template>

</xsl:stylesheet>


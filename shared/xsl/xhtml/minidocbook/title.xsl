<?xml version="1.0" standalone="yes"?>


<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:mdb="http://xml.elide.org/minidocbook"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:template match="title" name="title" mode="title">
		<xsl:choose>
			<xsl:when test="processing-instruction('br')">
				<span class="multiline">
					<xsl:apply-templates/>
				</span>
			</xsl:when>
			<xsl:otherwise>
				<xsl:apply-templates/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="table/title|figure/title" mode="link">
		<a>
			<!-- TODO: merge with sectionnumber-link etc; switch on T/F/S prefix (pass it in?) -->
			<!-- TODO: centralise this somewhere, for arguments' "#arg-*", too, and all @names -->
			<xsl:attribute name="name">
				<xsl:value-of select="translate(substring(name(..), 1, 1), 'tf', 'TF')"/>	<!-- TODO: silly... -->
				<xsl:number count="*[name() = name(current()/..)][title]" level="any" format="1"/>
			</xsl:attribute>
		</a>
	</xsl:template>

	<xsl:template match="table/title|figure/title">
		<b>
			<xsl:value-of select="translate(name(..), 'tf', 'TF')"/>	<!-- TODO: silly... -->
			<xsl:text>&#160;</xsl:text>
			<xsl:number count="*[name() = name(current()/..)][title]" level="any" format="1"/>
			<xsl:text>.&#160;</xsl:text>
			<xsl:call-template name="title"/>
		</b>
	</xsl:template>

	<xsl:template name="title-output">
		<xsl:param name="toc"    select="false()"/>
		<xsl:param name="number" select="true()"/>
		<xsl:param name="level"  select="1"/>
		<xsl:param name="title"/>

		<xsl:element name="h{$level + 1}">
			<!-- TODO: find where @id comes from! -->
			<a name="{mdb:sectionnumber-link()}"/>

			<xsl:if test="$number">
				<xsl:value-of select="mdb:sectionnumber()"/>
				<xsl:text>.&#160;</xsl:text>
			</xsl:if>

			<xsl:copy-of select="$title"/>
		</xsl:element>
	</xsl:template>

	<xsl:template match="title">
		<xsl:param name="toc"    select="false()"/>
		<xsl:param name="number" select="true()"/>

		<xsl:variable name="level" select="count(
			 ancestor::preface
			|ancestor::chapter
			|ancestor::appendix
			|ancestor::section
			|ancestor::refsection)"/>

		<xsl:call-template name="title-output">
			<xsl:with-param name="toc"    select="$toc"/>
			<xsl:with-param name="number" select="$number"/>
			<xsl:with-param name="level"  select="$level"/>
			<xsl:with-param name="title">
				<xsl:call-template name="title"/>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

</xsl:stylesheet>


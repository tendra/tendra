<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:mdb="http://xml.elide.org/minidocbook">

	<mdb:disallowed>
		<!-- TODO: paths: also:
			perhaps produce a canonical list of permitted elements (maybe even a DTD?)
			xref/@endterm
		-->
		<mdb:element mdb:name="olink"/>
		<mdb:element mdb:name="bridgehead"/>       <!-- promotes poor structure -->
		<mdb:element mdb:name="note"/>             <!-- promotes poor writing -->
		<mdb:element mdb:name="warning"/>          <!-- promotes poor writing -->
		<mdb:element mdb:name="synopfragment"/>    <!-- overcomplex -->
		<mdb:element mdb:name="synopfragmentref"/> <!-- overcomplex -->
	</mdb:disallowed>

	<xsl:template match="@*">
		<xsl:message terminate="no">
			<xsl:text>Unimplemented attribute: </xsl:text>
			<xsl:value-of select="concat('@', .)"/>
		</xsl:message>
	</xsl:template>

	<xsl:template match="*">
		<!-- TODO: another (better?) approach would be to use dyn:evaluate() from a list of xpath expressions and find disallowed constructs like table/tr -->

		<xsl:message terminate="no">
			<xsl:choose>
				<xsl:when test="document('')//mdb:disallowed/mdb:element[name(current()) = @mdb:name]">
					<xsl:text>Disallowed element: </xsl:text>
				</xsl:when>

				<xsl:otherwise>
					<xsl:text>Unimplemented element: </xsl:text>
				</xsl:otherwise>
			</xsl:choose>
			<xsl:value-of select="concat('&lt;', name(), '/&gt;')"/>
		</xsl:message>
	</xsl:template>

	<xsl:template match="processing-instruction()">
		<xsl:message terminate="yes">
			<xsl:text>Unimplemented processing instruction: </xsl:text>
			<xsl:value-of select="concat('&lt;?', name(), '?&gt;')"/>
		</xsl:message>
	</xsl:template>

</xsl:stylesheet>


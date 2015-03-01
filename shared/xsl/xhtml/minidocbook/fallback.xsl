<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	xmlns:mb="http://xml.tendra.org/minidocbook">

	<mb:disallowed>
		<!-- TODO: paths: also:
			perhaps produce a canonical list of permitted elements (maybe even a DTD?)
			xref/@endterm
		-->
		<mb:element mb:name="olink"/>
		<mb:element mb:name="bridgehead"/>       <!-- promotes poor structure -->
		<mb:element mb:name="note"/>             <!-- promotes poor writing -->
		<mb:element mb:name="warning"/>          <!-- promotes poor writing -->
		<mb:element mb:name="synopfragment"/>    <!-- overcomplex -->
		<mb:element mb:name="synopfragmentref"/> <!-- overcomplex -->
	</mb:disallowed>

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
				<xsl:when test="document('')//mb:disallowed/mb:element[name(current()) = @mb:name]">
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


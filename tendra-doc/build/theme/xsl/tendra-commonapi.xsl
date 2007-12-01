<?xml version="1.0"?>

<!-- $Id$ -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:str="http://exslt.org/strings"
	extension-element-prefixes="str"
	version='1.0'>

	<!--
		This stylesheet provides templates for the doctools common
		API; these override doctool's defaults for dtns and such.
	-->


	<!--
		The root filename for the document is named after its directory.
		Document names are given as "path/to/directory".
	 -->
	<xsl:template name="dt-doc-filename">
		<xsl:param name="name"/>

		<!-- I hate dealing with strings in XSLT -->
		<xsl:for-each select="str:split($name, '/')">
			<xsl:choose>
				<!-- The root filename for the document is named after its directory -->
				<xsl:when test="position() = last()">
					<xsl:value-of select="text()"/>
					<xsl:text>/</xsl:text>
					<xsl:value-of select="text()"/>
					<xsl:text>.xml</xsl:text>
				</xsl:when>

				<xsl:otherwise>
					<xsl:value-of select="text()"/>
					<xsl:text>/</xsl:text>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:for-each>
	</xsl:template>

	<!-- Append a '/' for neatness; each document is rendered to the $name/index.html -->
    <xsl:template name="dt-doc-url">
		<xsl:param name="name"/>

		<xsl:value-of select="$name"/>
		<xsl:text>/</xsl:text>
	</xsl:template>

</xsl:stylesheet>


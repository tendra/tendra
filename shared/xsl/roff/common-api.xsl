<?xml version="1.0"?>


<!--
	This API serves as an output-specific interface called by common/
	templates. This API gives a mechanism for those output-neutral templates
	to generate output specific to whatever format is being used.

	This file is a Roff implementation of the API. It is expected that the
	API is implemented for other formats in a similar manner.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:ec="http://exslt.org/common"
	xmlns="http://www.w3.org/1999/xhtml"
	version='1.0'

	exclude-result-prefixes="ec">

	<!--
		- Output a hyperlink. Pass $url, optionally a $class and optionally
		- content which may be overridden by $content.
		-
		- An internal <span/> is included for convenienly prefixing icons.
	-->
	<xsl:template name="wpi-link">
		<xsl:param name="url"/>
		<xsl:param name="class"/>
		<xsl:param name="content"/>

		<!-- TODO -->
	</xsl:template>

	<!-- TODO -->
	<xsl:template name="wpi-unknown-item">
		<xsl:param name="item"/>

		<!-- Hopefully this coincides with docbook's ERROR class -->
		<!-- TODO -->
	</xsl:template>

</xsl:stylesheet>


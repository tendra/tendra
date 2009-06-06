<?xml version="1.0"?>

<!-- $Id$ -->

<!--
	This API serves as an output-specific interface called by common/
	templates. This API gives a mechanism for those output-neutral templates
	to generate output specific to whatever format is being used.

	This file is an XHTML implementation of the API. It is expected that the
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

		<!--
			- Here I could call docbook-xsl's templates to generate a link, but
			- their templates seem to keep getting renamed. I'd rather duplicate
			- a small amount of code here and have it stay still - kate.
		-->
		<a href="{$url}">
			<xsl:if test="$class">
				<xsl:attribute name="class">
					<xsl:value-of select="$class"/>
				</xsl:attribute>
			</xsl:if>

			<span class="icon">
				<xsl:choose>
					<xsl:when test="count(ec:node-set($content)/node()) != 0">
						<!-- We copy here, as $content is expected to have been applied already -->
						<xsl:copy-of select="$content"/>
					</xsl:when>

					<xsl:when test="count(*|text()) = 0">
						<xsl:value-of select="$url"/>
					</xsl:when>

					<xsl:otherwise>
						<xsl:apply-templates/>
					</xsl:otherwise>
				</xsl:choose>
			</span>
		</a>
	</xsl:template>

	<!-- TODO -->
	<xsl:template name="wpi-unknown-item">
		<xsl:param name="item"/>

		<!-- Hopefully this coincides with docbook's ERROR class -->
		<span class="ERROR">
			<xsl:copy-of select="$item"/>
		</span>
	</xsl:template>

</xsl:stylesheet>


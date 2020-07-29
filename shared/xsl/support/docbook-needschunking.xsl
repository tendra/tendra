<?xml version="1.0"?>


<!--
	Find if a document needs chunked output.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version='1.0'>

	<xsl:output method="text" encoding="utf-8"/>

	<xsl:template match="/">
		<!-- TODO: This ought to count() instead -->
		<xsl:if test="//chapter">
			<xsl:text>yes</xsl:text>
		</xsl:if>
		<xsl:text>&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>


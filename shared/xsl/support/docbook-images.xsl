<?xml version="1.0"?>


<!--
	Produce a list of images referenced by the document. This is intended for
	use by the makefiles, in order to automatically find dependencies.
-->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version='1.0'>

	<xsl:output method="text" encoding="utf-8"/>

	<xsl:template match="/">
		<xsl:for-each select="//graphic|//inlinegraphic|//imagedata">
			<xsl:value-of disable-output-escaping="yes" select="@fileref"/>
			<xsl:text> </xsl:text>
		</xsl:for-each>
		<xsl:text>&#10;</xsl:text>
	</xsl:template>

</xsl:stylesheet>


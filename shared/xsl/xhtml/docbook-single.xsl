<?xml version="1.0"?>

<!-- $Id$ -->

<xsl:stylesheet
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml"
	version="1.0">

	<xsl:import href="http://docbook.sourceforge.net/release/xsl/current/xhtml/docbook.xsl"/>

	<xsl:import href="docbook.xsl"/>

	<xsl:output method="xml" version="1.0" encoding="utf-8" indent="yes"/>

	<xsl:param name="tendra.bodyclass"><xsl:text>single</xsl:text></xsl:param>

	<xsl:template name="chunklink">
		<div class="chunklink">
			<a href="index.xhtml">
				<xsl:text>Multiple pages</xsl:text>
			</a>
		</div>
	</xsl:template>

</xsl:stylesheet>


<?xml version="1.0"?>

<!-- $Id$ -->

<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version='1.0'>

	<xsl:import href="http://docbook.sourceforge.net/release/xsl/current/xhtml/chunk.xsl"/>

	<xsl:import href="docbook.xsl"/>

	<xsl:output method="xml" version="1.0" encoding="utf-8" indent="yes"/>

	<xsl:param name="chunker.output.indent"><xsl:text>yes</xsl:text></xsl:param>
	<xsl:param name="chunker.output.encoding"><xsl:text>UTF-8</xsl:text></xsl:param>
	<xsl:param name="chunk.section.depth"><xsl:text>1</xsl:text></xsl:param>
	<xsl:param name="chunk.fast"><xsl:text>1</xsl:text></xsl:param>
	<xsl:param name="chunk.quietly"><xsl:text>1</xsl:text></xsl:param>
	<xsl:param name="html.ext"><xsl:text>.xhtml</xsl:text></xsl:param>
	<xsl:param name="inherit.keywords"><xsl:text>1</xsl:text></xsl:param>

	<!-- TODO: confirm name() is ok here -->
	<xsl:param name="tendra.bodyclass">
		<xsl:text>chunked </xsl:text>
		<xsl:value-of select="name()"/>
	</xsl:param>

</xsl:stylesheet>


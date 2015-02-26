<?xml version="1.0" encoding="utf-8"?>

<!-- $Id$ -->

<!--
	Add id="" to sections and chapters for Docbook documents.
	This script is a convenience to assist in doing it by hand.
-->

<xsl:stylesheet version="1.0" xmlns:xsl="http://www.w3.org/1999/XSL/Transform">
    <xsl:output method="xml" indent="yes" standalone="no"
		doctype-system="minidocbook.dtd"/>

    <xsl:template match="@* | node()">
        <xsl:copy>
            <xsl:apply-templates select="@* | node()"/>
        </xsl:copy>
    </xsl:template>

    <xsl:template match="section|chapter">
		<xsl:variable name="l" select="'abcdefghijklmnopqrstuvwxyz-'" />
		<xsl:variable name="u" select="'ABCDEFGHIJKLMNOPQRSTUVWXYZ '" />

		<section>
			<xsl:if test="not(@id) and title">
				<xsl:attribute name="id">
					<xsl:choose>
						<xsl:when test="translate(title, $l, $u) = title">
							<xsl:value-of select="title"/>
						</xsl:when>
						<xsl:otherwise>
							<xsl:value-of select="translate(title, $u, $l)"/>
						</xsl:otherwise>
					</xsl:choose>
				</xsl:attribute>
			</xsl:if>

			<xsl:apply-templates/>
		</section>
	</xsl:template>
</xsl:stylesheet>


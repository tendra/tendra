<?xml version="1.0" standalone="yes"?>


<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:template match="table">
		<div class="table">
			<xsl:apply-templates select="title" mode="link"/>

			<table>
				<xsl:apply-templates select="col"/>

				<xsl:apply-templates select="thead"/>
				<xsl:apply-templates select="tbody"/>
			</table>

			<xsl:apply-templates select="title"/>

			<xsl:call-template name="footnotes"/>
		</div>
	</xsl:template>

	<xsl:template match="informaltable">
		<table class="informal">
			<xsl:apply-templates select="col"/>

			<tbody>
				<xsl:apply-templates select="tr"/>
			</tbody>
		</table>
	</xsl:template>

	<xsl:template match="@align|@valign|@colspan|@rowspan">
		<xsl:attribute name="{name()}">
			<xsl:value-of select="."/>
		</xsl:attribute>
	</xsl:template>

	<xsl:template match="col">
		<col>
			<xsl:apply-templates select="@align|@valign|@colspan"/>
		</col>
	</xsl:template>

	<xsl:template match="thead">
		<thead>
			<xsl:apply-templates select="tr"/>
		</thead>
	</xsl:template>

	<xsl:template match="tbody">
		<tbody>
			<xsl:apply-templates select="tr"/>
		</tbody>

		<xsl:if test="following-sibling::tbody">
			<tbody class="sep">
				<tr>
					<!-- For some reason @colspan = 1 on elements which have no
					     colspan attribute. I have no idea why... -->
					<td colspan="{sum(../thead/tr/th/@colspan)}"/>
				</tr>
			</tbody>
		</xsl:if>
	</xsl:template>

	<xsl:template match="tr">
		<tr>
			<xsl:apply-templates select="td|th"/>
		</tr>
	</xsl:template>

	<xsl:template match="table/thead/tr/th|table/tbody/tr/td|informaltable/tr/td">
		<xsl:element name="{name()}">
			<xsl:apply-templates select="@align|@valign|@colspan|@rowspan"/>

			<xsl:if test="@role">
				<xsl:attribute name="class">
					<xsl:value-of select="@role"/>
				</xsl:attribute>
			</xsl:if>

			<xsl:apply-templates/>
		</xsl:element>
	</xsl:template>

</xsl:stylesheet>


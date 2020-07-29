<?xml version="1.0" standalone="yes"?>


<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:template match="orderedlist">
		<ol>
			<xsl:apply-templates/>
		</ol>
	</xsl:template>

	<xsl:template match="itemizedlist">
		<ul>
			<xsl:apply-templates/>
		</ul>
	</xsl:template>

	<xsl:template match="listitem">
		<li>
			<xsl:apply-templates/>
		</li>
	</xsl:template>

	<xsl:template match="variablelist">
		<dl>
			<xsl:apply-templates/>
		</dl>
	</xsl:template>

	<xsl:template match="varlistentry">
		<!-- TODO: sort by varlistentry -->
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="varlistentry/term">
		<dt>
			<xsl:if test="string-length(.) &lt;= 2">
				<xsl:attribute name="class">
					<xsl:text>narrow</xsl:text>
				</xsl:attribute>
			</xsl:if>

			<xsl:if test="option">
				<a name="arg{option}"/>
			</xsl:if>

			<xsl:apply-templates/>
		</dt>
	</xsl:template>

	<xsl:template match="varlistentry/listitem">
		<dd>
			<xsl:apply-templates/>
		</dd>
	</xsl:template>

</xsl:stylesheet>


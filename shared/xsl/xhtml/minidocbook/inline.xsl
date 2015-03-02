<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:template match="acronym">
		<xsl:choose>
			<xsl:when test="not(@role)">
				<acronym>
					<xsl:apply-templates/>
				</acronym>
			</xsl:when>

			<xsl:when test="ancestor::refnamediv">
				<acronym>
					<xsl:apply-templates/>
				</acronym>
			</xsl:when>

			<!-- first (non-refnamediv) occurance -->
			<xsl:when test="not(preceding::acronym
					[not(ancestor::refnamediv)]
					[. = current()])">
				<acronym class="title" title="{@role}">
					<xsl:apply-templates/>
				</acronym>
			</xsl:when>

			<xsl:otherwise>
				<acronym title="{@role}">
					<xsl:apply-templates/>
				</acronym>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="userinput|computeroutput|command">	<!-- TODO: dissallow -->
		<tt class="{name()}">
			<xsl:apply-templates/>
		</tt>
	</xsl:template>

	<xsl:template match="application">	<!-- TODO: dissalow? or use it to link to a project page? -->
		<span class="{name()}">
			<xsl:apply-templates/>
		</span>
	</xsl:template>

	<xsl:template match="code">
		<code>
			<xsl:apply-templates/>
		</code>
	</xsl:template>

	<xsl:template match="varname|type|token|parameter|constant|function|literal">	<!-- TODO: dissallow -->
		<code class="{name()}">
			<xsl:apply-templates/>
		</code>
	</xsl:template>

	<xsl:template match="emphasis">
		<em>
			<xsl:apply-templates/>
		</em>
	</xsl:template>

	<xsl:template match="superscript">	<!-- TODO: dissallow -->
		<sup>
			<xsl:apply-templates/>
		</sup>
	</xsl:template>

	<xsl:template match="subscript">	<!-- TODO: dissallow -->
		<sub>
			<xsl:apply-templates/>
		</sub>
	</xsl:template>

	<xsl:template match="option">
		<tt class="{name()}">
			<xsl:apply-templates/>
		</tt>
	</xsl:template>

	<xsl:template match="filename">
		<!-- TODO: simplify. maybe best to use a get-ext function -->
		<xsl:choose>
			<xsl:when test="substring-after(., '.') = ''">
				<tt class="{name()}">
					<xsl:apply-templates/>
				</tt>
			</xsl:when>

			<xsl:when test="ancestor::refsection[title = 'Files']">
				<a href="{$mdb.url.ext}#{substring-after(., '.')}">
					<tt class="{name()}">
						<xsl:apply-templates/>
					</tt>
				</a>
			</xsl:when>

			<xsl:when test="substring-before(., '.') and substring-before(., '.') != '*'">
				<tt class="{name()}">
					<xsl:apply-templates/>
				</tt>
			</xsl:when>

			<!-- first occurance -->
			<xsl:when test="not(preceding::filename[substring-after(., '.') = substring-after(current(), '.')])">
				<a href="{$mdb.url.ext}#{substring-after(., '.')}">
					<tt class="{name()}">
						<xsl:apply-templates/>
					</tt>
				</a>
			</xsl:when>

			<xsl:otherwise>
				<tt class="{name()}">
					<xsl:apply-templates/>
				</tt>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="replaceable|citetitle|firstterm">
		<i class="{name()}">
			<xsl:apply-templates/>
		</i>
	</xsl:template>

	<xsl:template match="quote">
		<q>
			<xsl:apply-templates/>
		</q>
	</xsl:template>

	<!-- an extension to docbook, intended for use in <title> and <td> -->
	<xsl:template match="processing-instruction('br')">
		<br/>
	</xsl:template>

</xsl:stylesheet>


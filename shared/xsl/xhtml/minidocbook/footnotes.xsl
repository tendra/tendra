<?xml version="1.0" standalone="yes"?>


<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:mdb="http://xml.elide.org/minidocbook"
	xmlns:dyn="http://exslt.org/dynamic"
	xmlns:func="http://exslt.org/functions"
	xmlns="http://www.w3.org/1999/xhtml"

	extension-element-prefixes="func">

	<!--
		TODO: I'm not particularly happy with any of this
	-->

	<func:function name="mdb:footnote">
		<xsl:param name="href"/>
		<xsl:param name="name"/>

		<xsl:variable name="n">
			<xsl:number count="footnote" level="any" format="a"/>
		</xsl:variable>

<!-- TODO: merge with title.xsl -->
<!-- TODO: i'd rather link to the footnotes block, not the indivual footnote, anyway -->
		<func:result>
			<sup class="footnote-number">
				<a name="{$name}{$n}" href="#{$href}{$n}">
					<xsl:text>[</xsl:text>
					<xsl:value-of select="$n"/>
					<xsl:text>]</xsl:text>
				</a>
			</sup>
		</func:result>
	</func:function>

	<xsl:template match="footnote">
		<xsl:copy-of select="mdb:footnote('N', 'D')"/>
	</xsl:template>

	<xsl:template name="footnotes">
		<xsl:param name="predicate" select="''"/>	<!-- TODO: e.g. 'parent::table' -->

		<xsl:if test="dyn:evaluate(concat('descendant::footnote', $predicate))">
<!-- TODO: #T1-footnotes or #S2.3-footnotes-->
			<ol class="footnotes">
				<xsl:apply-templates mode="summary"
					select="dyn:evaluate(concat('descendant::footnote', $predicate))"/>
			</ol>
		</xsl:if>
	</xsl:template>

	<xsl:template match="footnote" mode="summary">
		<li>
			<xsl:copy-of select="mdb:footnote('D', 'N')"/>

			<xsl:apply-templates select="para"/>
		</li>
	</xsl:template>

</xsl:stylesheet>


<?xml version="1.0" standalone="yes"?>


<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:template match="preface|chapter|appendix">
		<div class="chapter">
			<xsl:apply-templates select="title"/>

			<xsl:call-template name="toc">
				<xsl:with-param name="depth" select="2"/>
			</xsl:call-template>

			<xsl:apply-templates select="*[name() != 'title']"/>

			<xsl:call-template name="footnotes">
				<xsl:with-param name="predicate" select="'[not(ancestor::table)]'"/>
			</xsl:call-template>
		</div>
	</xsl:template>

	<xsl:template match="section|bibliography">
		<div class="section">
			<xsl:apply-templates/>
		</div>
	</xsl:template>

	<xsl:template match="graphic">
		<xsl:copy-of select="document(@fileref)"/>
	</xsl:template>

	<xsl:template match="figure">
		<div class="figure">
			<xsl:apply-templates select="title" mode="link"/>

			<xsl:apply-templates select="graphic|literallayout"/>

			<xsl:apply-templates select="title"/>
		</div>
	</xsl:template>

	<xsl:template match="informalfigure">
		<div class="figure">
			<xsl:apply-templates select="graphic|literallayout"/>
		</div>
	</xsl:template>

	<xsl:template match="para">
		<p>
			<xsl:apply-templates/>
		</p>
	</xsl:template>

	<xsl:template match="programlisting">
		<pre class="programlisting {@language}">
			<xsl:apply-templates/>
		</pre>
	</xsl:template>

	<xsl:template match="screen">
		<pre class="screen">
			<xsl:apply-templates/>
		</pre>
	</xsl:template>

	<xsl:template match="blockquote">
		<blockquote>
			<xsl:apply-templates/>
		</blockquote>
	</xsl:template>

	<xsl:template match="literallayout">
		<blockquote class="literallayout">
			<xsl:apply-templates/>
		</blockquote>
	</xsl:template>

	<!-- TODO: i don't like these much. they look tacky, and are too easy to overuse -->
	<xsl:template match="warning">
		<div class="{name()}">
			<xsl:apply-templates/>
		</div>
	</xsl:template>

</xsl:stylesheet>


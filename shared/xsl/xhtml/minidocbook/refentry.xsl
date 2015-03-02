<?xml version="1.0" standalone="yes"?>

<!-- $Id$ -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:template match="refmeta" name="reftitle">
		<tt class="command">
			<xsl:value-of select="refentrytitle"/>
		</tt>
		<xsl:text>(</xsl:text>
		<xsl:value-of select="manvolnum"/>
		<xsl:text>)</xsl:text>
	</xsl:template>

	<xsl:template match="refsection">
		<div class="refsection">
			<xsl:apply-templates select="title">
				<xsl:with-param name="number" select="false()"/>
			</xsl:apply-templates>

			<xsl:apply-templates select="*[name() != 'title']"/>

			<xsl:call-template name="footnotes">
				<xsl:with-param name="predicate" select="'[not(ancestor::table)]'"/>
			</xsl:call-template>
		</div>
	</xsl:template>

	<xsl:template match="refname|refpurpose">
		<xsl:apply-templates/>
	</xsl:template>

	<xsl:template match="refnamediv">
		<div class="refsection">
			<xsl:call-template name="title-output">
				<xsl:with-param name="number" select="false()"/>
				<xsl:with-param name="title"  select="'Name'"/>
			</xsl:call-template>

			<tt class="command">
				<xsl:apply-templates select="refname"/>
			</tt>
			<xsl:text>&#8212;</xsl:text>
			<xsl:apply-templates select="refpurpose"/>
		</div>
	</xsl:template>

	<xsl:template match="refsynopsisdiv">
		<div class="refsection">
			<xsl:call-template name="title-output">
				<xsl:with-param name="number" select="false()"/>
				<xsl:with-param name="title"  select="'Synopsis'"/>
			</xsl:call-template>

			<xsl:apply-templates select="cmdsynopsis|para"/>
		</div>
	</xsl:template>

	<xsl:template name="cmd-opt">
		<xsl:param name="content"/>

		<xsl:choose>
			<xsl:when test="not(@choice) or @choice = 'opt'">
				<xsl:text>[&#x202F;</xsl:text>
			</xsl:when>
			<xsl:when test="@choice = 'req'">
				<xsl:text>{&#x202F;</xsl:text>
			</xsl:when>
		</xsl:choose>

		<xsl:copy-of select="$content"/>

		<xsl:if test="@rep = 'repeat'">
			<xsl:text>&#8230;</xsl:text>
		</xsl:if>

		<xsl:choose>
			<xsl:when test="not(@choice) or @choice = 'opt'">
				<xsl:text>&#x202F;] </xsl:text>
			</xsl:when>
			<xsl:when test="@choice = 'req'">
				<xsl:text>&#x202F;} </xsl:text>
			</xsl:when>
			<xsl:when test="position() != last()">
				<xsl:text>&#160;</xsl:text>
			</xsl:when>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="cmdsynopsis">
		<p class="cmdsynopsis">
			<span class="cmd">
				<xsl:apply-templates select="command"/>
			</span>

			<xsl:text>&#160;</xsl:text>

			<div class="args">
				<xsl:apply-templates select="arg|group|sbr"/>
			</div>
		</p>
	</xsl:template>

	<xsl:template match="arg">
		<xsl:call-template name="cmd-opt">
			<xsl:with-param name="content">
				<!-- TODO: only link if the ancestor axis contains refsynopsisdiv -->
				<!-- TODO: this is a bit hacky; make it more unique somehow -->
				<a href="#arg{option}">
					<xsl:apply-templates/>
				</a>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="group">
		<xsl:call-template name="cmd-opt">
			<xsl:with-param name="content">
				<!-- TODO: considering sorting lexographically -->
				<xsl:for-each select="arg|group|option|replaceable">
					<xsl:if test="position() != 1">
						<xsl:text> | </xsl:text>
					</xsl:if>

					<xsl:apply-templates select="."/>
				</xsl:for-each>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="sbr">
		<br/>
	</xsl:template>

</xsl:stylesheet>


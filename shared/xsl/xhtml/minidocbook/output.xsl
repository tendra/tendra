<?xml version="1.0" standalone="yes"?>


<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:svg="http://www.w3.org/2000/svg"
	xmlns:xlink="http://www.w3.org/1999/xlink"
	xmlns="http://www.w3.org/1999/xhtml"

	xmlns:common="http://exslt.org/common"

	extension-element-prefixes="common">

	<xsl:template name="banner">
		<h1 id="banner">
			<a href="{$mdb.url.www}">
				<xsl:text>The </xsl:text>
				<span class="logo">
					<xsl:text>Ten</xsl:text>
					<span class="smallcaps">
						<xsl:text>DRA</xsl:text>
					</span>
				</span>
				<xsl:text> Project</xsl:text>
			</a>
		</h1>
	</xsl:template>

	<xsl:template name="footer">
		<xsl:param name="bottomright"/>

		<div class="footer">
			<xsl:if test="$bottomright">
				<div class="bottomright">
					<xsl:copy-of select="$bottomright"/>
				</div>
			</xsl:if>

			<!-- TODO: add generation date and document date -->
			<!-- TODO: leave copyrights to the frontmatter, instead -->
			<span class="copyright">&#169; 2011 The TenDRA Project.</span>
		</div>
	</xsl:template>


	<xsl:template name="output">
		<xsl:param name="filename"/>
		<xsl:param name="title"/>
		<xsl:param name="bottomright" select="/.."/>

		<xsl:param name="content"    select="false"/>

		<xsl:variable name="method">
			<xsl:choose>
				<xsl:when test="$mdb.ext = 'xhtml'">
					<xsl:value-of select="'xml'"/>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="'html'"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>
				

		<!-- TODO: have these as a database of tags in this .xsl file and use document() to get them -->
		<xsl:variable name="media">
			<xsl:choose>
				<xsl:when test="$method = 'xml'">
					<xsl:text>application/xhtml+xml'/xml</xsl:text>
				</xsl:when>
				<xsl:when test="$method = 'html'">
					<xsl:text>text/html</xsl:text>
				</xsl:when>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="doctype-public">
			<xsl:choose>
				<xsl:when test="$method = 'xml'">
					<xsl:text>-//W3C//DTD XHTML 1.0 Strict//EN</xsl:text>
				</xsl:when>
				<xsl:when test="$method = 'html'">
					<xsl:text>TODO</xsl:text>
				</xsl:when>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="doctype-system">
			<xsl:choose>
				<xsl:when test="$method = 'xml'">
					<xsl:text>DTD/xhtml1-strict.dtd</xsl:text>
				</xsl:when>
				<xsl:when test="$method = 'html'">
					<xsl:text>TODO</xsl:text>
				</xsl:when>
			</xsl:choose>
		</xsl:variable>

		<xsl:message>
			<xsl:text>Outputting </xsl:text>
			<xsl:value-of select="concat($filename, '.', $mdb.ext, ': &quot;', $title, '&quot;')"/>
		</xsl:message>

		<common:document
			href="{$filename}.{$mdb.ext}"
			method="{$method}"
			encoding="utf-8"
			indent="yes"
			omit-xml-declaration="no"
			cdata-section-elements="script"
			media-type="{$media}"
			doctype-public="{$doctype-public}"
			doctype-system="{$doctype-system}"
			standalone="yes">

			<html>
				<head>
					<title>
						<xsl:value-of select="$title"/>
					</title>

					<link rel="stylesheet" type="text/css" media="screen"
						href="{$mdb.base}/css/common.css"/>
					<link rel="stylesheet" type="text/css" media="screen"
						href="{$mdb.base}/css/minidocbook.css"/>

					<script type="text/javascript"
						src="{$mdb.base}/js/linenumbers.js"></script>
					<script type="text/javascript"
						src="{$mdb.base}/js/col.js"></script>
					<script type="text/javascript"
						src="{$mdb.base}/js/table.js"></script>
					<script type="text/javascript"
						src="{$mdb.base}/js/javascript-xpath-cmp.js"></script>

					<!-- TODO: meta headers for prev/next links -->

					<xsl:if test="$method = 'html'">
						<meta http-equiv="Content-Type"
							content="text/html; charset=utf-8"/>
					</xsl:if>
				</head>

				<body onload="var r = document.documentElement;
					Linenumbers.init(r);
					Colalign.init(r);
					Table.init(r)">

					<xsl:call-template name="banner"/>

					<xsl:copy-of select="$content"/>

					<xsl:call-template name="footer">
						<xsl:with-param name="bottomright" select="$bottomright"/>
					</xsl:call-template>
				</body>
			</html>

		</common:document>
	</xsl:template>

</xsl:stylesheet>


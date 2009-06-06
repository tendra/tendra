<?xml version='1.0'?>

<!-- $Id$ -->

<!--
	This stylesheet provides custom dt:docs namespace
	implementations which act as conveniences for documents.
-->

<xsl:stylesheet
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns:dt="http://xml.water-powered.com/docs"
	xmlns="http://www.w3.org/1999/xhtml"
	version="1.0"

	extension-element-prefixes="dt">	<!-- XXX? -->

	<!-- TODO rather than calling templates to output links, can we create a node and apply it? -->

	<xsl:param name="dt-glossfile"/>	<!-- glossary source file -->
	<xsl:param name="dt-docsdir"/>	<!-- base directory for the document source files -->

	<xsl:param name="dt-docsurl"/>	<!-- e.g. 'http://docs.tendra.org/' -->
	<xsl:param name="dt-glossurl"/>	<!-- e.g. concat($dt-docsurl, 'project/glossary/') -->
	<xsl:param name="dt-wikiurl"/>	<!-- e.g. concat($dt-tracurl, 'wiki/') -->
	<xsl:param name="dt-sourceurl"/>	<!-- e.g. concat($dt-tracurl, 'browser/') -->

	<!--
		This template is called to output items which cannot be linked to,
		either because their destination is not present, or because the
		linking mechanism (i.e. the global parameter specifiying, for example,
		the glossary location) is not set.

		This may be overridden to deal with these items in a different manner.
		The default is to output the item's identifier in square brackets.

		The rendering is output-specific, and is handled by wpi-unknown-item.
	-->
	<xsl:template name="dt-unknown-item">
		<xsl:param name="item"/>

		<xsl:call-template name="wpi-unknown-item">
			<xsl:with-param name="item">
				<xsl:text>[</xsl:text>
					<xsl:copy-of select="$item"/>
				<xsl:text>]</xsl:text>
			</xsl:with-param>
		</xsl:call-template>
	</xsl:template>

	<!--
		Link to a glossary entry. Requires @term; content optional.

		Only the first <glossterm/> from a glossary definition is used
		(for berevity). Therefore, put the most common term first.
	-->
	<xsl:template match="dt:gloss">
		<xsl:variable name="term" select="@term"/>

		<!-- TODO only link once per <section> or so. Perhaps borrow from
			origional Report xslt here. -->
		<xsl:choose>
			<xsl:when test="not($dt-glossfile)">
				<xsl:message>
					<xsl:text>Warning: $dt-glossfile not set; ignoring </xsl:text>
					<xsl:value-of select="@term"/>
				</xsl:message>

				<xsl:call-template name="dt-unknown-item">
					<xsl:with-param name="item">
						<xsl:value-of select="@term"/>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:when>

			<xsl:when test="document($dt-glossfile)//glossentry[@id = $term]/glossterm">
				<!-- TODO only link if dt-glossurl is present (ditto others) -->
				<xsl:call-template name="wpi-link">
					<xsl:with-param name="url" select="concat($dt-glossurl, '#', @term)"/>
					<xsl:with-param name="class" select="'gloss-link'"/>
					<xsl:with-param name="content">
						<xsl:choose>
							<xsl:when test="count(node()) = 0">
								<!-- XXX docbook helpfully adds a trailing comma; find how to remove it -->
								<xsl:apply-templates
									select="document($dt-glossfile)//glossentry[@id = $term]/glossterm[position() = 1]"/>
							</xsl:when>

							<xsl:otherwise>
								<xsl:value-of select="@term"/>
							</xsl:otherwise>
						</xsl:choose>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:when>

			<xsl:otherwise>
				<xsl:message>
					<xsl:text>Warning: glossary id </xsl:text>
					<xsl:value-of select="@term"/>
					<xsl:text> not found.</xsl:text>
				</xsl:message>

				<xsl:call-template name="dt-unknown-item">
					<xsl:with-param name="item">
						<xsl:value-of select="@term"/>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!--
		Link to a wiki page. Requires @page; content optional.
	-->
	<xsl:template match="dt:wiki">
		<xsl:choose>
			<xsl:when test="not($dt-wikiurl)">
				<xsl:message>
					<xsl:text>Warning: $dt-wikiurl not set; ignoring </xsl:text>
					<xsl:value-of select="@page"/>
				</xsl:message>

				<xsl:call-template name="dt-unknown-item">
					<xsl:with-param name="item">
						<xsl:value-of select="@page"/>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:when>

			<xsl:otherwise>
				<!-- TODO can we check if a wiki page exists? -->
				<xsl:call-template name="wpi-link">
					<xsl:with-param name="url" select="concat($dt-wikiurl, @page)"/>
					<xsl:with-param name="class" select="'wiki-link'"/>
					<xsl:with-param name="content">
						<xsl:if test="count(node()) = 0">
							<xsl:value-of select="@page"/>
						</xsl:if>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!--
		Workaround for no modeless <title> template in docbook
	-->
	<xsl:template match="title" mode="dtdoctitle">
		<xsl:apply-templates/>
	</xsl:template>

	<!--
		Return a text value of the path to a document, given the
		document name passed in. This is intended to be overidden by
		custom file layout schemes parsed out to suit specific projects
		based on their own format of $name, the only parameter.

		For example, if your document names were specified as something
		like "section:document", you might want to extract the "document"
		part and yield the path "section/document/document.xml".

		Output relative to $dt-docsdir.
	-->
	<xsl:template name="dt-doc-filename">
		<xsl:param name="name"/>

		<!-- TODO unit test this for us. "/a/b/c" => "c"; "a" => "a" -->
		<xsl:value-of select="$name"/>
	</xsl:template>

	<!--
		Return a text value of a document URL given by a document name passed
		in.  This is intended to be overridden by custom URL schemes parsed out
		to suit specific projects based on their own format of $name, the only
		parameter.

		Output relative to $dt-docsurl
	-->
	<xsl:template name="dt-doc-url">
		<xsl:param name="name"/>

		<xsl:value-of select="$name"/>
	</xsl:template>

	<!--
		Link to a document. Requires @name. @name is transformed into
		a path to the filename and a URL by calling dt-doc-filename and
		dt-doc-url respectively.

		TODO add optional @linkend which calls docbook's templates. Chunked
		output may make this tricky - I expect docbook has some mechanism to
		find the page.
	-->
	<xsl:template match="dt:doc">
		<xsl:variable name="docfile">
			<xsl:value-of select="concat($dt-docsdir, '/')"/>
			<xsl:call-template name="dt-doc-filename">
				<xsl:with-param name="name">
					<xsl:value-of select="@name"/>
				</xsl:with-param>
			</xsl:call-template>
		</xsl:variable>

		<xsl:choose>
			<xsl:when test="not($dt-docsdir)">
				<xsl:message>
					<xsl:text>Warning: $dt-docsdir not set; ignoring </xsl:text>
					<xsl:value-of select="@name"/>
				</xsl:message>

				<xsl:call-template name="dt-unknown-item">
					<xsl:with-param name="item">
						<xsl:value-of select="@name"/>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:when>

			<xsl:when test="count(document($docfile)/node()[name() = 'book' or name() = 'article']/node()[name() = 'bookinfo' or name() = 'articleinfo']/title) != 0">
				<xsl:call-template name="wpi-link">
					<xsl:with-param name="url">
						<xsl:value-of select="concat($dt-docsurl, '/')"/>
						<xsl:call-template name="dt-doc-url">
							<xsl:with-param name="name">
								<xsl:value-of select="@name"/>
							</xsl:with-param>
						</xsl:call-template>
					</xsl:with-param>
					<xsl:with-param name="class" select="'docs-link'"/>
					<xsl:with-param name="content">
						<xsl:if test="count(node()) = 0">
							<xsl:apply-templates
								select="document($docfile)/node()[name() = 'book' or name() = 'article']/node()[name() = 'bookinfo' or name() = 'articleinfo']/title" mode="dtdoctitle"/>
						</xsl:if>
					</xsl:with-param>
				</xsl:call-template>
				<!--
					TODO consider also providing chunked and PDF
					links here. Perhaps an index generated can
					also make use of this XSLT.
				-->
			</xsl:when>

			<xsl:otherwise>
				<xsl:message>
					<xsl:text>Warning: document </xsl:text>
					<xsl:value-of select="@name"/>
					<xsl:text> not found.</xsl:text>
				</xsl:message>

				<xsl:call-template name="dt-unknown-item">
					<xsl:with-param name="item">
						<xsl:value-of select="@name"/>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<!--
		Return a text value of a source code path. This is intended to be
		overridden by custom path schemes parsed out to suit specific projects
		based on their own format of $path, the only parameter. For example,
		this may include some project-specific prefix stating which source
		repository to browse.

		Additionally this provides a placeholder for overriding paths with
		a normalisation process. For example leading slashes may be removed.

		Output relative to $dt-docsurl
	-->
	<xsl:template name="dt-source-path">
		<xsl:param name="path"/>

		<xsl:value-of select="$path"/>
	</xsl:template>

	<!--
		Link to the source. Requires @path; content optional.
	-->
	<xsl:template match="dt:source">
		<xsl:choose>
			<xsl:when test="not($dt-sourceurl)">
				<xsl:message>
					<xsl:text>Warning: $dt-sourceurl not set; ignoring </xsl:text>
					<xsl:value-of select="@path"/>
				</xsl:message>

				<xsl:call-template name="dt-unknown-item">
					<xsl:with-param name="item">
						<xsl:value-of select="@path"/>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:when>

			<xsl:otherwise>
				<!-- TODO can we check if the source path exists? -->
				<xsl:call-template name="wpi-link">
					<xsl:with-param name="url" select="concat($dt-sourceurl, @path)"/>
					<xsl:with-param name="class" select="'source-link'"/>
					<xsl:with-param name="content">
						<xsl:if test="count(node()) = 0">
							<xsl:call-template name="dt-source-path">
								<xsl:with-param name="path">
									<xsl:value-of select="@path"/>
								</xsl:with-param>
							</xsl:call-template>
						</xsl:if>
					</xsl:with-param>
				</xsl:call-template>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

</xsl:stylesheet>


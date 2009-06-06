<?xml version="1.0"?>

<!-- $Id$ -->

<!--
	This is intended to be general cleanup and sane replacements for crazy
	docbook things, which we want whenever docbook is used, regardless of
	what style is being rendered. Nothing should be project-specific, here.
-->

<xsl:stylesheet xmlns="http://www.w3.org/1999/xhtml"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	version='1.0'>

	<!-- skip just the header title for navigation (often redundant to section titles) -->
	<xsl:param name="wpi.navig.showtitle.header"><xsl:text>0</xsl:text></xsl:param>

	<!-- These make affliations a little less intrusive -->
	<xsl:template match="affiliation" mode="titlepage.mode">
		<xsl:text>, </xsl:text>
		<xsl:apply-templates mode="titlepage.mode"/>
	</xsl:template>

	<xsl:template match="othercredit" mode="titlepage.mode">
		<xsl:variable name="contrib" select="string(contrib)"/>
		<xsl:choose>
			<xsl:when test="contrib">
				<xsl:if test="not(preceding-sibling::othercredit[string(contrib)=$contrib])">
					<xsl:apply-templates mode="titlepage.mode" select="contrib"/>
					<xsl:text>: </xsl:text>
					<xsl:call-template name="person.name"/>
					<xsl:apply-templates mode="titlepage.mode" select="./affiliation"/>
					<xsl:apply-templates select="following-sibling::othercredit[string(contrib)=$contrib]" mode="titlepage.othercredits"/>
					<xsl:if test="@class">
						<xsl:text> (</xsl:text>
						<xsl:value-of select="@class"/>
						<xsl:text>)</xsl:text>
					</xsl:if>
				</xsl:if>
			</xsl:when>
			<xsl:otherwise>
				<xsl:call-template name="person.name"/>
				<xsl:if test="@class">
					<xsl:text> (</xsl:text>
					<xsl:value-of select="@class"/>
					<xsl:text>)</xsl:text>
				</xsl:if>
				<xsl:apply-templates mode="titlepage.mode" select="./affiliation"/>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="author" mode="titlepage.mode">
		<div class="{name(.)}">
			<xsl:call-template name="person.name"/>
			<xsl:apply-templates mode="titlepage.mode" select="./contrib"/>
			<xsl:apply-templates mode="titlepage.mode" select="./affiliation"/>
			<xsl:apply-templates mode="titlepage.mode" select="./email"/>
		</div>
	</xsl:template>

	<!-- This differs from the default in placement of table cells and classes -->
	<xsl:template match="revision" mode="titlepage.mode">
		<xsl:variable name="revnumber" select="revnumber"/>
		<xsl:variable name="revdate"	 select="date"/>
		<xsl:variable name="revauthor" select="authorinitials"/>
		<xsl:variable name="revremark" select="revremark|revdescription"/>

		<tr>
			<xsl:if test="$revnumber">
				<td align="left" class="revnumber">
					<xsl:call-template name="gentext">
						<xsl:with-param name="key" select="'Revision'"/>
					</xsl:call-template>
					<xsl:call-template name="gentext.space"/>
					<xsl:apply-templates select="$revnumber"/>
				</td>
			</xsl:if>
			<td align="left" class="revdate">
				<xsl:apply-templates select="$revdate"/>
			</td>
			<td align="left" class="revauthor">
				<xsl:choose>
					<xsl:when test="count($revauthor)=0">
						<xsl:call-template name="dingbat">
							<xsl:with-param name="dingbat">nbsp</xsl:with-param>
						</xsl:call-template>
					</xsl:when>
					<xsl:otherwise>
						<xsl:apply-templates select="$revauthor"/>
					</xsl:otherwise>
				</xsl:choose>
			</td>
			<xsl:if test="$revremark">
				<td align="left" colspan="3">
					<xsl:apply-templates select="$revremark"/>
				</td>
			</xsl:if>
		</tr>
	</xsl:template>

	<!-- This differs in that the object.title.markup shares the same row as the
	   - previous and next links if the middle cell is otherwise unoccupied. Then
	   - the first row is dropped entirely, giving a more compact output. Additionally
	   - some classes for CSS are specified.
	  -->
	<xsl:template name="header.navigation">
		<xsl:param name="prev" select="/foo"/>
		<xsl:param name="next" select="/foo"/>
		<xsl:param name="nav.context"/>

		<xsl:variable name="home" select="/*[1]"/>
		<xsl:variable name="up" select="parent::*"/>

		<xsl:variable name="row1" select="$navig.showtitles != 0
			and (count($up) &gt; 0
				and generate-id($up) != generate-id($home))"/>
		<xsl:variable name="row2" select="count($prev) &gt; 0
			or (count($up) &gt; 0
				and generate-id($up) != generate-id($home)
				and $navig.showtitles != 0)
			or count($next) &gt; 0"/>

		<xsl:if test="$suppress.navigation = '0' and $suppress.header.navigation = '0'">
			<div class="navheader">
				<xsl:if test="$row1 or $row2">
					<table width="100%" summary="Navigation header">
						<xsl:if test="$row1">
							<tr>
								<th colspan="3" align="center" class="otm">
									<xsl:apply-templates select="." mode="object.title.markup"/>
								</th>
							</tr>
						</xsl:if>

						<xsl:if test="$row2">
							<tr>
								<td width="20%" align="left" class="prev">
									<xsl:if test="count($prev)&gt;0">
										<a accesskey="p">
											<xsl:attribute name="href">
												<xsl:call-template name="href.target">
													<xsl:with-param name="object" select="$prev"/>
												</xsl:call-template>
											</xsl:attribute>
											<xsl:call-template name="navig.content">
												<xsl:with-param name="direction" select="'prev'"/>
											</xsl:call-template>
										</a>
									</xsl:if>
									<xsl:text>&#160;</xsl:text>
								</td>
								<th width="60%" align="center" class="otm">
									<xsl:choose>
										<xsl:when test="count($up) &gt; 0
											and generate-id($up) != generate-id($home)
											and $navig.showtitles != 0">
											<xsl:apply-templates select="$up" mode="object.title.markup"/>
										</xsl:when>
										<xsl:when test="($navig.showtitles != 0) and ($row1 = false) and ($wpi.navig.showtitle.header != 0)">
											<xsl:apply-templates select="." mode="object.title.markup"/>
										</xsl:when>
										<xsl:otherwise>&#160;</xsl:otherwise>
									</xsl:choose>
								</th>
								<td width="20%" align="right" class="next">
									<xsl:text>&#160;</xsl:text>
									<xsl:if test="count($next)&gt;0">
										<a accesskey="n">
											<xsl:attribute name="href">
												<xsl:call-template name="href.target">
													<xsl:with-param name="object" select="$next"/>
												</xsl:call-template>
											</xsl:attribute>
											<xsl:call-template name="navig.content">
												<xsl:with-param name="direction" select="'next'"/>
											</xsl:call-template>
										</a>
									</xsl:if>
								</td>
							</tr>
						</xsl:if>
					</table>
				</xsl:if>
				<xsl:if test="$header.rule != 0">
					<hr/>
				</xsl:if>
			</div>
		</xsl:if>
	</xsl:template>

	<!--
	   - This differs in placement of <td> elements; the links are all
	   - on one line. Also, it specifies some classes for CSS.
	  -->
	<xsl:template name="footer.navigation">
		<xsl:param name="prev" select="/foo"/>
		<xsl:param name="next" select="/foo"/>
		<xsl:param name="nav.context"/>

		<xsl:variable name="home" select="/*[1]"/>
		<xsl:variable name="up" select="parent::*"/>

		<xsl:variable name="row1" select="count($prev) &gt; 0
			or count($up) &gt; 0
			or count($next) &gt; 0
			or (generate-id($home) != generate-id(.)
				or $nav.context = 'toc')"/>

		<xsl:variable name="row2" select="($prev and $navig.showtitles != 0)
			or ($chunk.tocs.and.lots != 0 and $nav.context != 'toc')
			or ($next and $navig.showtitles != 0)"/>

		<xsl:if test="$suppress.navigation = '0' and $suppress.footer.navigation = '0'">
			<div class="navfooter">
				<xsl:if test="$footer.rule != 0">
					<hr/>
				</xsl:if>

				<xsl:if test="$row1 or $row2">
					<table width="100%" summary="Navigation footer">
						<xsl:if test="$row1">
							<tr>
								<td width="40%" align="left" class="prev">
									<xsl:if test="count($prev)&gt;0">
										<a accesskey="p">
											<xsl:attribute name="href">
												<xsl:call-template name="href.target">
													<xsl:with-param name="object" select="$prev"/>
												</xsl:call-template>
											</xsl:attribute>
											<xsl:call-template name="navig.content">
												<xsl:with-param name="direction" select="'prev'"/>
											</xsl:call-template>
										</a>
									</xsl:if>
									<xsl:text>&#160;</xsl:text>
								</td>
								<td width="20%" align="center" class="toc">
									<xsl:choose>
										<xsl:when test="count($up) &gt; 0
											and generate-id($up) != generate-id($home)">
											<a accesskey="u">
												<xsl:attribute name="href">
													<xsl:call-template name="href.target">
														<xsl:with-param name="object" select="$up"/>
													</xsl:call-template>
												</xsl:attribute>
												<xsl:call-template name="navig.content">
													<xsl:with-param name="direction" select="'up'"/>
												</xsl:call-template>
											</a>
										</xsl:when>
										<xsl:when test="$home != . or $nav.context = 'toc'"/>
										<xsl:otherwise>&#160;</xsl:otherwise>
									</xsl:choose>

									<xsl:if test="(count($up) &gt; 0
										and generate-id($up) != generate-id($home))
										and ($home != .
											or $nav.context = 'toc')">
										<span class="sep"> | </span>
									</xsl:if>

									<xsl:choose>
										<xsl:when test="$home != . or $nav.context = 'toc'">
											<a accesskey="h">
												<xsl:attribute name="href">
													<xsl:call-template name="href.target">
														<xsl:with-param name="object" select="$home"/>
													</xsl:call-template>
												</xsl:attribute>
												<xsl:call-template name="navig.content">
													<xsl:with-param name="direction" select="'home'"/>
												</xsl:call-template>
											</a>
											<xsl:if test="$chunk.tocs.and.lots != 0 and $nav.context != 'toc'">
												<xsl:text>&#160;|&#160;</xsl:text>
											</xsl:if>
										</xsl:when>
										<xsl:otherwise>&#160;</xsl:otherwise>
									</xsl:choose>
								</td>
								<td width="40%" align="right" class="next">
									<xsl:text>&#160;</xsl:text>
									<xsl:if test="count($next)&gt;0">
										<a accesskey="n">
											<xsl:attribute name="href">
												<xsl:call-template name="href.target">
													<xsl:with-param name="object" select="$next"/>
												</xsl:call-template>
											</xsl:attribute>
											<xsl:call-template name="navig.content">
												<xsl:with-param name="direction" select="'next'"/>
											</xsl:call-template>
										</a>
									</xsl:if>
								</td>
							</tr>
						</xsl:if>

						<xsl:if test="$row2">
							<tr>
								<td width="40%" align="left" valign="top" class="prev">
									<xsl:if test="$navig.showtitles != 0">
										<xsl:apply-templates select="$prev" mode="object.title.markup"/>
									</xsl:if>
									<xsl:text>&#160;</xsl:text>
								</td>
								<td width="20%" align="center" class="toc">
									<xsl:if test="$chunk.tocs.and.lots != 0 and $nav.context != 'toc'">
										<a accesskey="t">
											<xsl:attribute name="href">
												<xsl:apply-templates select="/*[1]" mode="recursive-chunk-filename">
													<xsl:with-param name="recursive" select="true()"/>
												</xsl:apply-templates>
												<xsl:text>-toc</xsl:text>
												<xsl:value-of select="$html.ext"/>
											</xsl:attribute>
											<xsl:call-template name="gentext">
												<xsl:with-param name="key" select="'nav-toc'"/>
											</xsl:call-template>
										</a>
									</xsl:if>
								</td>
								<td width="40%" align="right" valign="top" class="next">
									<xsl:text>&#160;</xsl:text>
									<xsl:if test="$navig.showtitles != 0">
										<xsl:apply-templates select="$next" mode="object.title.markup"/>
									</xsl:if>
								</td>
							</tr>
						</xsl:if>
					</table>
				</xsl:if>
			</div>
		</xsl:if>
	</xsl:template>

	<!--
		This is overridden so that we may associate language names
		for each listing.
	-->
	<xsl:template match="programlisting|screen|synopsis">
		<xsl:param name="suppress-numbers" select="'0'"/>
		<xsl:variable name="id">
			<xsl:call-template name="object.id"/>
		</xsl:variable>

		<xsl:call-template name="anchor"/>

		<xsl:if test="$shade.verbatim != 0">
			<xsl:message>
				<xsl:text>The shade.verbatim parameter is deprecated. </xsl:text>
				<xsl:text>Use CSS instead,</xsl:text>
			</xsl:message>
			<xsl:message>
				<xsl:text>for example: pre.</xsl:text>
				<xsl:value-of select="local-name(.)"/>
				<xsl:text> { background-color: #E0E0E0; }</xsl:text>
			</xsl:message>
		</xsl:if>

		<div class="programlisting">
			<xsl:apply-templates select="@language"/>

			<xsl:choose>
				<xsl:when test="$suppress-numbers = '0'
					and @linenumbering = 'numbered'
					and $use.extensions != '0'
					and $linenumbering.extension != '0'">

					<xsl:variable name="rtf">
						<xsl:apply-templates/>
					</xsl:variable>

					<pre>
						<xsl:apply-templates select="." mode="class.attribute"/>
						<xsl:call-template name="number.rtf.lines">
							<xsl:with-param name="rtf" select="$rtf"/>
						</xsl:call-template>
					</pre>
				</xsl:when>

				<xsl:otherwise>
					<pre>
						<xsl:apply-templates select="." mode="class.attribute"/>
						<xsl:apply-templates/>
					</pre>
				</xsl:otherwise>
			</xsl:choose>
		</div>
	</xsl:template>

	<xsl:template match="programlisting/@language">
		<div class="programlisting-language">
			<xsl:value-of select="."/>
		</div>
	</xsl:template>

	<!--
		Overriding formal.xsl to introduce the xhtml namespace for <table>.
		The stylesheets (particularly htmltbl.xsl) copy through these
		nodes as-is, but omit their namespaces.

		This also adds @class, @cellpadding, @cellspacing and @border.
	-->

	<xsl:template match="table">
		<xsl:choose>
			<xsl:when test="tgroup|mediaobject|graphic">
				<xsl:call-template name="calsTable"/>
			</xsl:when>
			<xsl:otherwise>
				<table class="htmltable" cellpadding="0" cellspacing="0" border="0">
					<xsl:copy-of select="@*[not(local-name()='id')]"/>
					<xsl:attribute name="id">
						<xsl:call-template name="object.id"/>
					</xsl:attribute>
					<xsl:call-template name="htmlTable"/>
				</table>
			</xsl:otherwise>
		</xsl:choose>
	</xsl:template>

	<xsl:template match="tr" mode="htmlTable">
		<tr>
			<xsl:apply-templates mode="htmlTable"/>
		</tr>
	</xsl:template>

	<xsl:template match="th" mode="htmlTable">
		<th>
			<xsl:apply-templates/>
		</th>
	</xsl:template>

	<xsl:template match="td" mode="htmlTable">
		<td>
			<xsl:apply-templates/>
		</td>
	</xsl:template>

</xsl:stylesheet>


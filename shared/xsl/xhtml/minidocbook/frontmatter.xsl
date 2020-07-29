<?xml version="1.0" standalone="yes"?>


<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
	xmlns="http://www.w3.org/1999/xhtml">

	<xsl:template name="credit">
		<xsl:param name="name"/>
		<xsl:param name="role"        select="false()"/>
		<xsl:param name="affiliation" select="false()"/>
		<xsl:param name="contrib"     select="false()"/>

		<li>
			<xsl:value-of select="$name"/>

			<xsl:if test="$affiliation">
				<xsl:text>, </xsl:text>
				<xsl:value-of select="affiliation/orgname"/>
			</xsl:if>

			<xsl:if test="$role">
				<xsl:text> (</xsl:text>
				<xsl:value-of select="$role"/>
				<xsl:text>)</xsl:text>
			</xsl:if>

			<xsl:if test="$contrib">
				<xsl:text>; </xsl:text>
				<xsl:value-of select="$contrib"/>
			</xsl:if>
		</li>
	</xsl:template>

	<xsl:template match="corpauthor">
		<xsl:call-template name="credit">
			<xsl:with-param name="name"        select="."/>
			<xsl:with-param name="contrib"     select="contrib"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="othercredit">
		<xsl:call-template name="credit">
			<xsl:with-param name="name"        select="concat(firstname, ' ', surname)"/>
			<xsl:with-param name="role"        select="@class"/>
			<xsl:with-param name="affiliation" select="affiliation/orgname"/>
			<xsl:with-param name="contrib"     select="contrib"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="author">
		<xsl:call-template name="credit">
			<xsl:with-param name="name"        select="concat(firstname, ' ', surname)"/>
			<xsl:with-param name="affiliation" select="affiliation/orgname"/>
			<xsl:with-param name="contrib"     select="contrib"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="editor">
		<xsl:call-template name="credit">
			<xsl:with-param name="name"        select="concat(firstname, ' ', surname)"/>
			<xsl:with-param name="role"        select="'editor'"/>
			<xsl:with-param name="affiliation" select="affiliation/orgname"/>
			<xsl:with-param name="contrib"     select="contrib"/>
		</xsl:call-template>
	</xsl:template>

	<xsl:template match="authorgroup">
		<ul class="authorgroup">
			<xsl:apply-templates select="othercredit|editor|author|corpauthor"/>
		</ul>
	</xsl:template>

	<xsl:template match="pubdate">
		<p class="firstpub">
			<xsl:text>First published </xsl:text>
			<xsl:value-of select="."/>	<!-- TODO: format? -->
			<xsl:text>.</xsl:text>
		</p>
	</xsl:template>

	<xsl:template match="copyright">
		<p class="copyright">
			<xsl:text>&#169; </xsl:text>

			<xsl:for-each select="year">
				<xsl:sort/>	<!-- TODO: numerically -->

				<xsl:value-of select="."/>

				<xsl:if test="position() != last()">
					<xsl:text>, </xsl:text>
				</xsl:if>
			</xsl:for-each>
			<xsl:text> </xsl:text>

			<xsl:value-of select="holder"/>
			<xsl:text>.</xsl:text>
		</p>
	</xsl:template>

	<xsl:template match="abstract">
		<div class="abstract">
			<h3>
				<xsl:text>Abstract</xsl:text>
			</h3>

			<xsl:apply-templates/>
		</div>
	</xsl:template>

	<xsl:template match="revdescription/para[1]">
		<p>
			<!-- This is only prefixed if the description does not mention it already -->
			<xsl:if test="../../revnumber
				and not(contains(., ../../revnumber))
				and not(contains(., concat('version ', substring-after(../../revnumber, ' '))))">
				<xsl:value-of select="../../revnumber"/>
				<xsl:text>; </xsl:text>
			</xsl:if>

			<xsl:apply-templates/>
		</p>
	</xsl:template>

	<xsl:template match="revision">
		<xsl:if test="@role != 'dev'">
			<tr class="{@role}">
				<xsl:choose>
					<xsl:when test="date">
						<td class="date">
							<!-- TODO: formatted how? maybe pass in locale as a param? -->
							<xsl:value-of select="date"/>
						</td>
					</xsl:when>

					<xsl:otherwise>
						<td class="na" align="center">
							<xsl:text>&#8211;</xsl:text>
						</td>
					</xsl:otherwise>
				</xsl:choose>

				<td>
					<xsl:value-of select="authorinitials"/>
				</td>

				<xsl:choose>
					<xsl:when test="revdescription">
						<td class="revremark">
							<xsl:apply-templates select="revdescription/*"/>
						</td>
					</xsl:when>

					<xsl:otherwise>
						<td class="revremark na" align="left">
							<xsl:text>&#8211;</xsl:text>
						</td>
					</xsl:otherwise>
				</xsl:choose>
			</tr>
		</xsl:if>
	</xsl:template>

	<xsl:template match="revhistory">
		<h3>
			<xsl:text>Revision History</xsl:text>
		</h3>

		<table class="revhistory informal">
			<col align="right"/>
			<col align="center"/>
			<col align="left"/>

			<tbody>
				<!-- TODO: sort by reverse chronological order -->
				<xsl:apply-templates select="revision"/>
			</tbody>
		</table>
	</xsl:template>

	<xsl:template match="bookinfo|articleinfo">
		<xsl:apply-templates select="authorgroup"/>

		<xsl:apply-templates select="copyright"/>

		<xsl:apply-templates select="pubdate"/>

		<!-- TODO: don't need abstracts (maybe for papers) -->
		<xsl:apply-templates select="abstract"/>

		<xsl:apply-templates select="revhistory"/>
	</xsl:template>

	<xsl:template name="frontmatter">
		<xsl:apply-templates select="bookinfo|articleinfo"/>
	</xsl:template>

</xsl:stylesheet>


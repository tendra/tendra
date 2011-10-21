<?xml version="1.0" encoding="utf-8"?>

<!DOCTYPE xsl:stylesheet [
	<!ENTITY % ent-misc SYSTEM "ent-misc.dtd"> %ent-misc;
	<!ENTITY % ent-abbr SYSTEM "ent-abbr.dtd"> %ent-abbr;
	<!ENTITY % ent-ref  SYSTEM "ent-ref.dtd">  %ent-ref;
	<!ENTITY % ent-ext  SYSTEM "ent-ext.dtd">  %ent-ext;
	<!ENTITY % ent-arg  SYSTEM "ent-arg.dtd">  %ent-arg;

	<!ENTITY A.opt "<option>-A</option>&switch.arg;">
	<!ENTITY C.opt "<option>-C</option>&switch.arg;">
	<!ENTITY D.opt "<option>-D</option>&switch.arg;">
	<!ENTITY F.opt "<option>-F</option>&switch.arg;">
	<!ENTITY I.opt "<option>-I</option>&switch.arg;">
	<!ENTITY K.opt "<option>-K</option>&str.arg;">
	<!ENTITY M.opt "<option>-M</option>&switch.arg;">
	<!ENTITY R.opt "<option>-R</option>&switch.arg;">
	<!ENTITY U.opt "<option>-U</option>&switch.arg;">
	<!ENTITY X.opt "<option>-X</option>">
	<!ENTITY B.opt "<option>-B</option>&switch.arg;">
	<!ENTITY E.opt "<option>-E</option>">
	<!ENTITY H.opt "<option>-H</option>">
	<!ENTITY P.opt "<option>-P</option>">
	<!ENTITY Q.opt "<option>-Q</option>">
	<!ENTITY S.opt "<option>-S</option>">
	<!ENTITY V.opt "<option>-V</option>">
	<!ENTITY W.opt "<option>-W</option>&switch.arg;">
	<!ENTITY Z.opt "<option>-Z</option>">
]>

<!-- $Id -->

<xsl:stylesheet version="1.0"
	xmlns:xsl="http://www.w3.org/1999/XSL/Transform">

	<!--
		This is an XSLT transformation to produce Docbook XML.
		There are multiple different implementations of trans(1), all of which
		share most of their usage.
		This stylesheet centralises their individual differences, and
		conditionally outputs whichever page is relevant.
		It can also render out a consolidated page, documenting
		all implementations simultaneously.

		Most of the complexity here is due to sylistic minutiae and phrasing;
		when modifying it, please take care to test the various different
		outputs for readability.
	-->

	<xsl:output method="xml" indent="yes" encoding="utf-8"
		doctype-system="minidocbook.dtd"/>

	<xsl:param name="trans" select="'all'"/>

	<xsl:template name="pad-command">
		<xsl:param name="command" select="''"/>

		<xsl:variable name="spaces">
			<xsl:if test="$trans = 'all'">
				<xsl:value-of select="'         '"/>
			</xsl:if>
		</xsl:variable>

		<command>
			<xsl:value-of select="$command"/>
			<xsl:value-of select="substring(translate($spaces, ' ', '&#xA0;'), string-length($command))"/>
		</command>
	</xsl:template>

	<xsl:template name="synopsis-options">
		<arg choice="opt">&A.opt;</arg>
		<arg choice="opt">&C.opt;</arg>
		<arg choice="opt">&F.opt;</arg>
		<arg choice="opt">&I.opt;</arg>
		<arg choice="opt">&K.opt;</arg>
		<arg choice="opt">&M.opt;</arg>
		<arg choice="opt">&R.opt;</arg>
		<arg choice="opt">&U.opt;</arg>

		<sbr/>

		<arg choice="opt">&X.opt;</arg>
		<arg choice="opt">&B.opt;</arg>
		<arg choice="opt">&E.opt;</arg>
		<arg choice="opt">&H.opt;</arg>
		<arg choice="opt">&P.opt;</arg>
		<arg choice="opt">&Q.opt;</arg>
		<arg choice="opt">&W.opt;</arg>
		<arg choice="opt">&Z.opt;</arg>
	</xsl:template>

	<xsl:template name="synopsis">
		<xsl:param name="command"/>

		<xsl:variable name="options">
			<xsl:choose>
				<xsl:when test="$command = 'trans386'">
					<arg choice="opt">&D.opt;</arg>
					<arg choice="opt"><option>-a</option></arg>
					<arg choice="opt"><option>-h</option></arg>
					<arg choice="opt"><option>-k</option>&switch.arg;</arg>
				</xsl:when>
				<xsl:when test="$command = 'alphatrans'">
					<arg choice="opt">&D.opt;</arg>
					<arg choice="opt">&S.opt;</arg>
				</xsl:when>
				<xsl:when test="$command = 'hppatrans'">
					<arg choice="opt">&D.opt;</arg>
					<arg choice="opt"><option>-h</option></arg>
				</xsl:when>
				<xsl:when test="$command = 'mipstrans'">
					<arg choice="opt">&D.opt;</arg>
					<arg choice="opt">&S.opt;</arg>
				</xsl:when>
				<xsl:when test="$command = 'sparctrans'">
					<arg choice="opt">&D.opt;</arg>
				</xsl:when>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="output">
			<xsl:choose>
				<xsl:when test="$command = 'alphatrans'">
					<arg choice="plain"><replaceable>binary-assembler-file</replaceable></arg>
					<arg choice="plain"><replaceable>symbol-table-file</replaceable></arg>
					<arg choice="opt"><replaceable>symbolic-assembler-file</replaceable></arg>
				</xsl:when>
				<xsl:when test="$command = 'mipstrans'">
					<arg choice="plain"><replaceable>op.G</replaceable></arg>
					<arg choice="plain"><replaceable>op.H</replaceable></arg>
					<arg choice="opt"><replaceable>op.s</replaceable></arg>
				</xsl:when>
				<xsl:otherwise>
					<arg choice="plain"><replaceable>output-file</replaceable></arg>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<cmdsynopsis>
			<xsl:call-template name="pad-command">
				<xsl:with-param name="command" select="$command"/>
			</xsl:call-template>

			<xsl:if test="$trans != 'all'">
				<xsl:call-template name="synopsis-options"/>
			</xsl:if>

			<xsl:if test="$options != ''">
				<xsl:copy-of select="$options"/>

				<sbr/>
			</xsl:if>

			<xsl:if test="$trans != 'all' and $options = ''">
				<sbr/>
			</xsl:if>

   			<arg choice="plain"><replaceable>input-file</replaceable></arg>

			<xsl:copy-of select="$output"/>
		</cmdsynopsis>
	</xsl:template>

	<xsl:template match="/">
		<xsl:variable name="allorself">
			<xsl:choose>
				<xsl:when test="$trans = 'all'">
					<xsl:text>all translators</xsl:text>
				</xsl:when>
				<xsl:otherwise>
					<command>
						<xsl:value-of select="$trans"/>
					</command>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:variable name="transorself">
			<xsl:choose>
				<xsl:when test="$trans = 'all'">
					<replaceable>
						<xsl:text>trans</xsl:text>
					</replaceable>
				</xsl:when>
				<xsl:otherwise>
					<xsl:value-of select="$trans"/>
				</xsl:otherwise>
			</xsl:choose>
		</xsl:variable>

		<xsl:comment>
			Generated by trans-xsl.1.xsl. Do not edit.
		</xsl:comment>

		<refentry>
			<xsl:comment><![CDATA[
				Copyright (c) 2002-2007 The TenDRA Project <http://www.tendra.org/>.
				All rights reserved.
	
				Redistribution and use in source and binary forms, with or without
				modification, are permitted provided that the following conditions are met:
	
				1. Redistributions of source code must retain the above copyright notice,
				   this list of conditions and the following disclaimer.
				2. Redistributions in binary form must reproduce the above copyright notice,
				   this list of conditions and the following disclaimer in the documentation
				   and/or other materials provided with the distribution.
				3. Neither the name of The TenDRA Project nor the names of its contributors
				   may be used to endorse or promote products derived from this software
				   without specific, prior written permission.
	
				THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS ``AS
				IS'' AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
				THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
				PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR
				CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
				EXEMPLARY OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
				PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS;
				OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY,
				WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR
				OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF
				ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
			]]></xsl:comment>

			<xsl:comment><![CDATA[
							 Crown Copyright (c) 1997
				
				This TenDRA(r) Manual Page is subject to Copyright
				owned by the United Kingdom Secretary of State for Defence
				acting through the Defence Evaluation and Research Agency
				(DERA).	It is made available to Recipients with a
				royalty\-free licence for its use, reproduction, transfer
				to other parties and amendment for any purpose not excluding
				product development provided that any such use et cetera
				shall be deemed to be acceptance of the following conditions:\-
				
						(1) Its Recipients shall ensure that this Notice is
						reproduced upon any copies or amended versions of it;
				
						(2) Any amended version of it shall be clearly marked to
						show both the nature of and the organisation responsible
						for the relevant amendment or amendments;
				
						(3) Its onward transfer from a recipient to another
						party shall be deemed to be that party's acceptance of
						these conditions;
				
						(4) DERA gives no warranty or assurance as to its
						quality or suitability for any purpose and DERA accepts
						no liability whatsoever in relation to any use to which
						it may be put.
			]]></xsl:comment>

			<refmeta>
				<refentrytitle><xsl:value-of select="$transorself"/></refentrytitle>
				<manvolnum>1</manvolnum>
			</refmeta>

			<refnamediv>
				<refname>
					<xsl:value-of select="$transorself"/>
				</refname>

				<refpurpose>
					<xsl:text>DRA TDF to </xsl:text>
					<xsl:choose>
						<xsl:when test="$trans = 'trans386'">
							<xsl:text>80386, 80486 and Pentium translator</xsl:text>
						</xsl:when>
						<xsl:when test="$trans = 'alphatrans'">
							<xsl:text>DEC Alpha translator</xsl:text>
						</xsl:when>
						<xsl:when test="$trans = 'hppatrans' ">
							<xsl:text>HP PA-RISC translator</xsl:text>
						</xsl:when>
						<xsl:when test="$trans = 'mipstrans' ">
							<xsl:text>MIPS translator</xsl:text>
						</xsl:when>
						<xsl:when test="$trans = 'powertrans'">
							<xsl:text>POWER translator</xsl:text>
						</xsl:when>
						<xsl:when test="$trans = 'sparctrans'">
							<xsl:text>SPARC translator</xsl:text>
						</xsl:when>
						<xsl:otherwise>
							<xsl:text>assembly translators</xsl:text>
						</xsl:otherwise>
					</xsl:choose>
				</refpurpose>
			</refnamediv>

			<refsynopsisdiv>
				<xsl:choose>
					<xsl:when test="$trans != 'all'">
						<xsl:call-template name="synopsis">
							<xsl:with-param name="command" select="$trans"/>
						</xsl:call-template>
					</xsl:when>
					<xsl:otherwise>
						<xsl:call-template name="synopsis">
							<xsl:with-param name="command" select="'trans386'"/>
						</xsl:call-template>
						<xsl:call-template name="synopsis">
							<xsl:with-param name="command" select="'alphatrans'"/>
						</xsl:call-template>
						<xsl:call-template name="synopsis">
							<xsl:with-param name="command" select="'hppatrans'"/>
						</xsl:call-template>
						<xsl:call-template name="synopsis">
							<xsl:with-param name="command" select="'mipstrans'"/>
						</xsl:call-template>
						<xsl:call-template name="synopsis">
							<xsl:with-param name="command" select="'powertrans'"/>
						</xsl:call-template>
						<xsl:call-template name="synopsis">
							<xsl:with-param name="command" select="'sparctrans'"/>
						</xsl:call-template>
					</xsl:otherwise>
				</xsl:choose>

				<cmdsynopsis>
					<xsl:call-template name="pad-command">
						<xsl:with-param name="command">
							<xsl:choose>
								<xsl:when test="$trans = 'all'">
									<replaceable>
										<xsl:text>trans</xsl:text>
									</replaceable>
								</xsl:when>
								<xsl:otherwise>
									<xsl:value-of select="$trans"/>
								</xsl:otherwise>
							</xsl:choose>
						</xsl:with-param>
					</xsl:call-template>

					<group choice="req">
						<arg choice="plain">&V.opt;</arg>
					</group>
				</cmdsynopsis>

				<xsl:if test="$trans = 'all'">
					<para>Most options are common to all translators.
						For brevity, these are not repeated above:</para>

					<cmdsynopsis>
						<xsl:call-template name="pad-command"/>

						<xsl:call-template name="synopsis-options"/>
					</cmdsynopsis>
				</xsl:if>
			</refsynopsisdiv>

			<refsection>
				<title>Description</title>

				<para>The code production portion of the &tdf; compiler is under the
					control of a &tdf; translator, which translates a &tdf; capsule into
					assembly.</para>

				<xsl:if test="$trans = 'alphatrans' or $trans = 'all'">
					<para>&alphatrans; produces an AXP assembler file.</para>
				</xsl:if>

				<para>There are separate &tdf; translators for each target
					architecture.</para>

				<xsl:if test="$trans = 'hppatrans' or $trans = 'all'">
					<para>&hppatrans; produces assembly code for the
						HP PA-RISC machines.</para>
				</xsl:if>

				<xsl:if test="$trans = 'mipstrans' or $trans = 'all'">
					<para>&mipstrans; produces &mips; code.
						There are two versions, one for &irix;, and one for &ultrix;.
						Both produce &G.ext; and &H.ext; files required by
						<command>as1</command>, but may also optionally give
						&s.ext; assembly files using &S.opt;.
						Note that full run-time diagnostic information cannot be
						transmitted through the &mips; assembler, &as;.</para>
				</xsl:if>

				<xsl:if test="$trans = 'powertrans' or $trans = 'all'">
					<para>&powertrans; produces assembly code
						common to the rs6000 and the POWERPc.</para>
				</xsl:if>

				<xsl:if test="$trans = 'sparctrans' or $trans = 'all'">
					<para>&sparctrans; produces SPARC assembly code.
						There are two versions, one for SunOS, and one for
						Solaris.</para>
				</xsl:if>

				<para>The various different translators are referred to
					collectively as &trans;.</para>

				<para>It is recommended that &trans; should not be
					invoked directly, but via the user interface &tcc;.
					The file <option>-</option><replaceable>opt</replaceable> can
					be passed to &trans; by passing the option
					<option>-W</option><literal>t,-</literal><replaceable>opt</replaceable> to
					&tcc;.</para>
			</refsection>

			<refsection>
				<title>Options</title>

				<para>The options denoted by a capital letter are common to
					the &tdf; installers for all the architectures, although the
					defaults vary for each translator.</para>

				<para>Lowercase options are specific to each translator.</para>

				<xsl:if test="$trans = 'trans386' or $trans = 'all'">
					<para>The option <option>-a</option> is specific to
						&trans386;.</para>
				</xsl:if>

				<xsl:if test="$trans = 'hppatrans' or $trans = 'all'">
					<para>The options <option>-h</option> and <option>-d</option> are
						specific to &hppatrans;.</para>
				</xsl:if>

				<para>&switch.arg; stands for either <literal>0</literal>,
					to switch an option off, or <literal>1</literal>,
					to switch it on.</para>

				<xsl:if test="$trans = 'all'">
					<para>The default states for common options differ per
						translator:</para>

					<table>
						<title>Per-translator defaults for common options</title>

						<col align="left"/>
						<col align="center"/>
						<col align="center"/>
						<col align="center"/>
						<col align="center"/>
						<col align="center"/>
						<col align="center"/>

						<thead>
							<tr>
								<th>Option</th>
								<th><code>trans386</code></th>
								<th><code>alphatrans</code></th>
								<th><code>hppatrans</code></th>
								<th><code>mipstrans</code></th>
								<th><code>powertrans</code></th>
								<th><code>sparctrans</code></th>
							</tr>
						</thead>

						<tbody>
							<tr>
								<td>&A.opt;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
							</tr>
							<tr>
								<td>&F.opt;</td>
								<td>&check;</td>
								<td>&cross;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
							</tr>
							<tr>
								<td>&I.opt;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
							</tr>
							<tr>
								<td>&K.opt;</td>
								<td>&check;</td>
								<td role="na">(no effect)</td>
								<td role="na">(no effect)</td>
								<td role="na">(no effect)</td>
								<td>&cross;</td>
								<td role="na">(no effect)</td>
							</tr>
							<tr>
								<td>&M.opt;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
							</tr>
							<tr>
								<td>&R.opt;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&check;</td>
								<td>&cross;</td>
								<td>&check;</td>
								<td>&cross;</td>
							</tr>
							<tr>
								<td>&X.opt;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
							</tr>
						</tbody>

						<tbody>
							<tr>
								<td>&B.opt;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
							</tr>
							<tr>
								<td>&C.opt;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
							</tr>
							<tr>
								<td>&D.opt;</td>
								<td>&cross; <footnote>
										<para>This option is not supported on SCO or DragonFly, and on
											Linux is supported only for ELF.</para>
									</footnote></td>
								<td>&cross;</td>
								<td>&cross; <footnote>
										<para>See also <option>-d</option>.</para>
									</footnote></td>
								<td>&check; <footnote>
										<para>This option is not supported on &ultrix;.</para>
									</footnote></td>
								<td role="na">&ndash;</td>
								<td>&cross;</td>
							</tr>
							<tr>
								<td>&E.opt;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
							</tr>
							<tr>
								<td>&H.opt;</td>
								<td>&cross;</td>
								<td>&cross; <footnote>
										<para>See also <option>-h</option>.</para>
									</footnote></td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
							</tr>
							<tr>
								<td>&P.opt;</td>
								<td>&cross; <footnote>
										<para>Not supported on Solaris.</para>
									</footnote></td>
								<td>&cross; <footnote>
										<para>Not fully implemented.</para>
									</footnote></td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
							</tr>
							<tr>
								<td>&Q.opt;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
							</tr>
							<tr>
								<td>&S.opt;</td>
								<td role="na">&ndash;</td>
								<td>&cross;</td>
								<td role="na">&ndash;</td>
								<td>&cross;</td>
								<td role="na">&ndash;</td>
								<td role="na">&ndash;</td>
							</tr>
							<tr>
								<td>&U.opt;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
								<td>&check;</td>
							</tr>
							<tr>
								<td>&V.opt;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
							</tr>
							<tr>
								<td>&W.opt;</td>
								<td role="na">(no effect)</td>
								<td role="na">(no effect)</td>
								<td role="na">(no effect)</td>
								<td role="na">(no effect)</td>
								<td role="na">(no effect)</td>
								<td role="na">(no effect)</td>
							</tr>
							<tr>
								<td>&Z.opt;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
								<td>&cross;</td>
							</tr>
						</tbody>
					</table>
				</xsl:if>
			</refsection>

			<!-- TODO: TODO: now go through and find undocumented options... -->

			<refsection>
				<title>Optimisation-specific common options</title>

				<para>The common options pertaining to optimisation are:</para>

				<variablelist>
					<varlistentry>
						<term>&A.opt;</term>

						<listitem>
							<para>This option determines whether &trans;
								should inline calls to <code>alloca</code>.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is done by default.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&C.opt;</term>

						<listitem>
							<para>This option determines whether &trans;
								should apply the "constants out of loops"
								optimisation.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is done by default.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&F.opt;</term>

						<listitem>
							<xsl:if test="$trans = 'trans386' or $trans = 'all'">
								<para>For &trans386;, this option determines
									whether the "strength reduction" optimisation
									should be applied.</para>
							</xsl:if>

							<xsl:if test="$trans = 'alphatrans' or $trans = 'all'">
								<para>For &alphatrans;, this option determines
									whether or not the "for all" optimisation
									should be applied.</para>
							</xsl:if>

							<xsl:choose>
								<xsl:when test="$trans = 'all'">
									<para>For &hppatrans;, &mipstrans; and
										&sparctrans;, this option determines
										whether the "for all" optimisation
										should be applied.</para>
								</xsl:when>

								<xsl:when test="$trans = 'hppatrans'
							                 or $trans = 'mipstrans'
							                 or $trans = 'sparctrans'">
									<para>For <command><xsl:value-of select="$trans"/></command>,
										this option determines whether the
										"for all" optimisation should be applied.</para>
								</xsl:when>
							</xsl:choose>

							<xsl:choose>
								<xsl:when test="$trans = 'alphatrans'">
									<para>For <command><xsl:value-of select="$trans"/></command>,
										this is not done by default.</para>
								</xsl:when>

								<xsl:when test="$trans = 'all'">
									<para>For all translators except &alphatrans;,
										this is done by default.</para>
								</xsl:when>

								<xsl:otherwise>
									<para>For <command><xsl:value-of select="$trans"/></command>,
										this is done by default.</para>
								</xsl:otherwise>
							</xsl:choose>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&I.opt;</term>

						<listitem>
							<para>This option determines whether &trans;
								should apply the "inlining" optimisation.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is done by default.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&K.opt;</term>

						<listitem>
							<para>Causes &trans; to optimise its code for a
								particular processor model, determined by
								&str.arg;.</para>

							<xsl:if test="$trans = 'trans386' or $trans = 'all'">
								<para>For &trans386;, the available values of
									&str.arg; are:</para>

								<table>
									<col align="left"/>
									<col align="left"/>

									<thead>
										<tr>
											<th>Option</th>
											<th>Processor</th>
										</tr>
									</thead>

									<tbody>
										<tr>
											<td><code>-K3</code></td>
											<td>80386</td>
										</tr>
										<tr>
											<td><code>-K4</code> (default)</td>
											<td>80486</td>
										</tr>
										<tr>
											<td><code>-K5</code></td>
											<td>Pentium</td>
										</tr>
									</tbody>
								</table>
							</xsl:if>

							<xsl:if test="$trans = 'powertrans' or $trans = 'all'">
								<para>For &powertrans;, the available values
									of &str.arg; are:</para>

								<table>
									<col align="left"/>
									<col align="left"/>

									<thead>
										<tr>
											<th>Option</th>
											<th>Processor</th>
										</tr>
									</thead>

									<tbody>
										<tr>
											<td><code>-KP</code></td>
											<td>POWERPc</td>
										</tr>
										<tr>
											<td><code>-KR</code></td>
											<td>rs6000</td>
										</tr>
									</tbody>
								</table>
							</xsl:if>

							<xsl:choose>
								<xsl:when test="$trans = 'all'">
									<para>For all other translators, at present there are no
										valid values for &str.arg;.</para>
								</xsl:when>

								<xsl:when test="$trans = 'trans386'
								             or $trans = 'powertrans'">
								</xsl:when>

								<xsl:otherwise>
									<para>For <command><xsl:value-of select="$trans"/></command>,
										at present there are no valid values for
										&str.arg;.</para>
								</xsl:otherwise>
							</xsl:choose>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&M.opt;</term>

						<listitem>
							<para>If this option is on, &trans; preserves
								division by a floating point number rather
								than replacing it by multiplication by the
								reciprocal of the number.
								While the latter produces faster code, it may
								lead to rounding errors.</para>

							<para>For <xsl:value-of select="$allorself"/>, by
								default, division by constants is preserved.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&R.opt;</term>

						<listitem>
							<para>This option determines whether &trans;
								should immediately round every floating point operation
								to its appropriate range.
								This produces slower code, but is necessary for strict
								&ieee; conformance.</para>

							<xsl:choose>
								<xsl:when test="$trans = 'hppatrans' or $trans = 'powertrans'">
									<para>The default is to round after every operation
										for <command><xsl:value-of select="$trans"/></command>.</para>
								</xsl:when>

								<xsl:when test="$trans = 'all'">
									<para>The default is not to round after every operation
										for all translators except &hppatrans; and
										&powertrans;.</para>
								</xsl:when>

								<xsl:otherwise>
									<para>For <command><xsl:value-of select="$trans"/></command>,
										this is not done by default.</para>
								</xsl:otherwise>
							</xsl:choose>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&U.opt;</term>

						<listitem>
							<para>This option determines whether &trans;
								should apply the "loop unrolling" optimisation.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is done by default.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&X.opt;</term>

						<listitem>
							<para>This option disables all optimisations.
								All &trans;' optimisations are believed to be
								valid, so that any error in optimisation is a
								genuine bug.</para>

							<para>Various optimisations are performed by default for
								<xsl:value-of select="$allorself"/>.</para>
						</listitem>
					</varlistentry>
				</variablelist>
			</refsection>

			<refsection>
				<title>Other common options</title>

				<para>Common options not related to optimisation are:</para>

				<variablelist>
					<varlistentry>
						<term>&B.opt;</term>

						<listitem>
							<para>This option determines whether &trans; should
								report floating point constants which exceed
								their range.</para>
					
							<para>For <xsl:value-of select="$allorself"/>,
								this is done by default.</para>

							<para>If this option is switched off such constants are
								replaced by infinity.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&D.opt;</term>

						<listitem>
							<para>This option determines whether &trans; should
								produce Position Independent Code
								(<acronym>PIC</acronym>).</para>

							<xsl:if test="$trans = 'all'">
								<para>For all translators where it is supported,
									except &mipstrans;, this is not done by
									default.</para>
							</xsl:if>

							<xsl:if test="$trans != 'all' and $trans != 'mipstrans'">
								<para>For <command><xsl:value-of select="$trans"/></command>,
									this is not done by default.</para>
							</xsl:if>

							<xsl:if test="$trans = 'trans386' or $trans = 'all'">
								<para>For &trans386;, this option is not
									supported on the SCO or DragonFly platforms,
									and on the Linux platform it is supported
									only for ELF binary format.</para>
							</xsl:if>

							<xsl:if test="$trans = 'hppatrans' or $trans = 'all'">
								<para>For &hppatrans;, the translator-specific
									option <option>-d</option>&switch.arg;
									is also provided.
									The <option>-D</option> flag emulates &cc;'s
									<option>+Z</option> flag, <option>-d</option>
									emulates &cc;'s <option>+z</option> flag.
									Neither option has yet been tested.</para>
							</xsl:if>

							<xsl:if test="$trans = 'mipstrans' or $trans = 'all'">
								<para>For &mipstrans;, this is done by default
									in the &irix; version and not at all in
									the &ultrix; version.</para>
							</xsl:if>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&E.opt;</term>

						<listitem>
							<para>This option disables &trans;' constant
								overflow checks.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is done by default.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&H.opt;</term>

						<listitem>
							<para>This option causes &trans; to output
								debugging information in its output file.
								This will only work if the input &tdf; capsule contains
								debugging information.</para>

							<xsl:if test="$trans = 'trans386' or $trans = 'all'">
								<para>For &trans386;, on the SCO platform
									the format used by &dbxtra;
									and <application>codeview</application> is supported.
									On the SVR4.2 platform Dwarf 1 is supported,
									which is used by &debug;.
									On the Solaris, DragonFly, and Linux platforms,
									<application>stabs</application> is supported.
									The GNU debugger &gdb; may be used on all
									platforms.</para>
							</xsl:if>

							<xsl:if test="$trans = 'hppatrans' or $trans = 'all'">
								<para>For &hppatrans;, the <option>-H</option>
									flag causes hppatrans to output &xdb;
									compatible debugging information in its output file.
									This option is only available if the header
									file <filename>hpux_symtab.h</filename> was included
									whilst compiling &hppatrans;.<footnote>
										<para>hpux_symtab.h is available by anonymous FTP,
											but appears to have changed location over time.
											Your best option is to simply google for it.</para>
									</footnote></para>

								<para>Please note well that there is a known bug in the
									<option>-H</option> option for &hppatrans;.
									The bug sometimes prohibits &xdb;
									reading selective diagnostic information from a suite of
									two or more modules linked together.</para>
							</xsl:if>

							<xsl:if test="$trans = 'mipstrans' or $trans = 'all'">
								<para>For &mipstrans; the diagnostic format used is
									as used by the native compilers.</para>
							</xsl:if>

							<xsl:if test="$trans = 'sparctrans' or $trans = 'all'">
								<para>For &sparctrans;, the diagnostic format
									used is <application>stabs</application>
									for SunOS, and <application>stabs-in-elf</application>
									for Solaris (both as used by the native compilers).</para>
							</xsl:if>

							<para>Debugging information is not output by default
								for <xsl:value-of select="$allorself"/>.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&P.opt;</term>

						<listitem>
							<para>This option causes &trans; to output profiling
								information suitable for use with &prof; or a
								similar tool (see individual manual pages for
								details).</para>

							<xsl:if test="$trans = 'trans386' or $trans = 'all'">
								<para>On &trans386;, this option is currently
									not supported on the Solaris platform.</para>
							</xsl:if>

							<xsl:if test="$trans = 'alphatrans' or $trans = 'all'">
								<para>On &alphatrans;, this is not fully
									implemented.</para>
							</xsl:if>

							<xsl:if test="$trans = 'mipstrans' or $trans = 'all'">
								<para>On &mipstrans;, this option is untested
									at present, and should not be used.</para>
							</xsl:if>

							<para>Profiling information is not output by default
								for <xsl:value-of select="$allorself"/>.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&Q.opt;</term>

						<listitem>
							<para>This option causes &trans; to quit before
								processing its input files.
								This is particularly useful in conjunction with
								<option>-V</option>.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is not done by default.</para>
						</listitem>
					</varlistentry>

					<xsl:if test="$trans = 'mipstrans'
				               or $trans = 'alphatrans'
				               or $trans = 'all'">
						<varlistentry>
							<term>&S.opt;</term>

							<listitem>
								<xsl:if test="$trans = 'alphatrans' or $trans = 'all'">
									<para>For &alphatrans;, when this option is
										present &alphatrans; will produce a
										symbolic assembler file in addition to
										its normal outputs.
										In this case the name of the symbolic assembler file
										must be present on the command line.</para>
								</xsl:if>

								<xsl:if test="$trans = 'mipstrans' or $trans = 'all'">
									<para>For &mipstrans;, this option will produce
									assembly code in the optional &s.ext; file.</para>
								</xsl:if>

								<xsl:if test="$trans = 'all'">
									<para>This option is not present on all other
										translators.</para>
								</xsl:if>

								<xsl:choose>
									<xsl:when test="$trans = 'all'">
										<para>For all translators where it is supported,
											this is not done by default.</para>
									</xsl:when>

									<xsl:otherwise>
										<para>For <command><xsl:value-of select="$trans"/></command>,
											this is not done by default.</para>
									</xsl:otherwise>
								</xsl:choose>
							</listitem>
						</varlistentry>
					</xsl:if>

					<varlistentry>
						<term>&V.opt;</term>

						<listitem>
							<para>This option causes &trans; to print its
								version number and the version of the &tdf;
								specification it supports.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is not done by default.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&W.opt;</term>

						<listitem>
							<para>This option determines whether &trans; should
								make string literals writable.
								At present the C producer does not make use of this
								facility.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								at present all string literals
								are writable, and this cannot be altered.</para>
						</listitem>
					</varlistentry>

					<varlistentry>
						<term>&Z.opt;</term>

						<listitem>
							<para>This option causes &trans; to print the
								version number of all the &tdf; capsules
								it decodes.</para>

							<para>For <xsl:value-of select="$allorself"/>,
								this is not done by default.</para>
						</listitem>
					</varlistentry>
				</variablelist>
			</refsection>

			<refsection>
				<title>Translator-specific options</title>

				<xsl:if test="$trans = 'trans386' or $trans = 'all'">
					<para>The following options are specific to &trans386;:</para>

					<variablelist>
						<varlistentry>
							<term><option>-a</option></term>

							<listitem>
								<para>Always use a frame pointer.
									The default is to avoid using a frame pointer whenever possible.
									The default results in better performance, but in special
									cases where the stack is to be processed it may be necessary
									to enforce the use of a frame pointer.</para>
							</listitem>
						</varlistentry>

						<varlistentry>
							<term><option>-h</option></term>

							<listitem>
								<para>Do not use the <code>.bss</code> segment,
									always put data into the <code>.data</code>
									segment even if it is zero.
									This should very rarely be needed.
									The default is to use the <code>.bss</code>
									segment.</para>
							</listitem>
						</varlistentry>

						<varlistentry>
							<term><option>-k</option>&switch.arg;</term>

							<listitem>
								<!-- XXX: not just linux platforms only... also *BSD etc? -->
								<para>This option is applicable to DragonFly and Linux
									platforms only.
									If this option is on, &trans386; will
									produce output for an ELF binary format assembler,
									otherwise a.out binary format is assumed.
									By default this option is on, as appropriate for
									later versions of Linux.</para>
							</listitem>
						</varlistentry>
					</variablelist>
				</xsl:if>

				<xsl:if test="$trans = 'hppatrans' or $trans = 'all'">
					<para>The following options are specific to &hppatrans;:</para>

					<variablelist>
						<varlistentry>
							<term><option>-h</option></term>

							<listitem>
								<para>The <option>-h</option> flag causes hppatrans
									to output &gdb; compatible,
									i.e. <application>stabs</application>, debugging
									information in its output file.
									The <option>-h</option> flag is believed
									to be valid&mdash;any error is a genuine bug.</para>

								<para>The <option>-H</option> and <option>-h</option>
									options will only work if the input &tdf;
									capsule contains debugging information.</para>
							</listitem>
						</varlistentry>
					</variablelist>
				</xsl:if>

				<xsl:if test="$trans != 'trans386'
				          and $trans != 'hppatrans'
				          and $trans != 'all'">
					<para>There are no translator-specific options for
						<command><xsl:value-of select="$trans"/></command>.</para>
				</xsl:if>
			</refsection>

			<refsection>
				<title>See Also</title>

				<xsl:if test="$trans != 'all'">
					<para>&trans-all;.</para>
				</xsl:if>

				<para>&as;, &prof;, &tcc;.</para>
			</refsection>

		</refentry>
	</xsl:template>

</xsl:stylesheet>


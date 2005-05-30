<?xml version="1.0"?>

<!--
  $Id$
-->

<xsl:stylesheet version="1.0"
  xmlns="http://www.w3.org/1999/xhtml"
  xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
  xmlns:xalan="http://xml.apache.org/xslt">

  <xsl:import href="navigation.xsl"/>
  <xsl:output method="xml" indent="yes" xalan:indent-amount="2"/>
  <xsl:output doctype-public="-//W3C//DTD XHTML 1.0 Transitional//EN"
    doctype-system="http://www.w3.org/TR/xhtml1/DTD/xhtml1-transitional.dtd"/>

  <xsl:template match="news">
    <html dir="ltr" xml:lang="en">
      <head>
        <title>The TenDRA Compiler Project - FAQ</title>
        <link rel="shortcut icon"
          href="http://www.tendra.org/favicon.ico" type="image/x-icon"/>
        <link rel="stylesheet" href="style.css" type="text/css"/>
        <meta http-equiv="Content-Type"
          content="text/html; charset=ISO-8859-15"/>
      </head>

      <body>
        <xsl:apply-imports/>

        <div id="content">
          <h1><span>FAQ</span></h1>

          <p><span>Frequently Asked Questions</span></p>
          <ul>
            <xsl:for-each select="entry">
            <xsl:sort data-type="text" order="descending" select="date"/>
              <li>
                <b><xsl:value-of select="date"/></b>: <xsl:value-of select="content"/>
              </li>
            </xsl:for-each>
          </ul>
        </div>

        <div id="compliance">
          <p>
            <a href="http://validator.w3.org/check?uri=referer">
              <img src="valid-xhtml10.png" height="31" width="88"
                alt="Valid XHTML 1.0!"/>
            </a>

            <a href="http://jigsaw.w3.org/css-validator/">
              <img src="vcss.png" height="31" width="88" alt="Valid CSS!"/>
            </a>
          </p>
        </div>
      </body>
    </html>
  </xsl:template>
</xsl:stylesheet>

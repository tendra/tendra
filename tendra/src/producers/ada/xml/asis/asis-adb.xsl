<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<xsl:include href  = "common.xsl"/>

<xsl:output method="text"/>

<xsl:template match="/">

  <xsl:apply-templates select="//node[@name != 'Any_Compilation_Unit_Node']/attr">
    <xsl:sort select="@name"/>
  </xsl:apply-templates>

  <xsl:apply-templates select="//node[@abstract = 'y' and not(@helper)]">
    <xsl:sort select="@name"/>
  </xsl:apply-templates>

end Asis;

</xsl:template>
  


<xsl:template match="attr[../@name != 'Any_Compilation_Unit_Node']">
  <xsl:variable name="name" select="@name"/>

  <xsl:if test="generate-id() = generate-id(//attr[@name=$name][1]) 
                and not(@defer)">
    <xsl:apply-templates select="." mode="spec"/>
   is
   begin<xsl:choose>
    <xsl:when test="contains(@name, '_Kind')">
      return <xsl:call-template name="real-not-a-kind"/>;
</xsl:when>
    <xsl:otherwise>
      Raise_Inappropriate_Element
        (Get_Context (Element), "<xsl:call-template name="attr-name"/>");
      return <xsl:choose>
   <xsl:when test="starts-with (@type, 'Primary_')">Nil_Element_List</xsl:when>
   <xsl:when test="@type = 'Asis.Component_Definition'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Constraint'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Declaration'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Defining_Name'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Definition'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Discrete_Range'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Discrete_Subtype_Definition'"
       >Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Element'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Expression'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Identifier'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Name'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Range_Constraint'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Asis.Subtype_Indication'">Nil_Element</xsl:when>
   <xsl:when test="@type = 'Unbounded_Wide_String'">""</xsl:when>
   <xsl:when test="@type = 'Asis.Declaration_Origins'"
       >Not_A_Declaration_Origin</xsl:when>
   <xsl:when test="@type = 'Asis.Compilation_Unit'"
       >Nil_Compilation_Unit</xsl:when>
   <xsl:when test="@type = 'Asis.Text_Position'"
       >Nil_Text_Position</xsl:when>
   <xsl:when test="@type = 'Asis.ASIS_Integer'">0</xsl:when>
   <xsl:when test="@type = 'Boolean'">False</xsl:when>
   <xsl:when test="starts-with (@type, 'Secondary_')"
       >Nil_Element_List</xsl:when>
   <xsl:when test="starts-with (@name, 'Corresponding_')"
       >Nil_Element</xsl:when>   <xsl:otherwise>
    <xsl:call-template name="attr-name"/> (Element)</xsl:otherwise>
   </xsl:choose><xsl:text>;</xsl:text>
</xsl:otherwise>
</xsl:choose>
   end <xsl:call-template name="attr-name"/>;
</xsl:if>
</xsl:template>



<xsl:template match="node [@name='Discrete_Subtype_Definition_Node']">
</xsl:template>



<xsl:template match="node">
    <xsl:apply-templates select="." mode="kind-spec"/> is
   begin
      return Not_<xsl:call-template name="real-kind-name"/>;
   end <xsl:call-template name="kind-name"/>;
</xsl:template>

</xsl:stylesheet>

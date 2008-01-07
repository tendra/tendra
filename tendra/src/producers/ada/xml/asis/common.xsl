<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>


<xsl:template match="attr" mode="spec">
  <xsl:param name="type">Element_Node</xsl:param>

  <xsl:variable name="return">
    <xsl:call-template name="return-type"/>
  </xsl:variable>

  <xsl:text>
   function </xsl:text>

  <xsl:call-template name="attr-name"/>

  <xsl:text>
     (Element : </xsl:text>

  <xsl:value-of select="$type"/>

  <xsl:if test="$return = 'Asis.Element_List'">

    <xsl:text>;
      Include_Pragmas : in Boolean := False</xsl:text>

  </xsl:if>

  <xsl:text>) return </xsl:text>
  <xsl:value-of select="$return"/>

</xsl:template>



<xsl:template match="attr" mode="set-spec">
  <xsl:param name="type">Element_Node</xsl:param>

  <xsl:variable name="return">
    <xsl:call-template name="return-type"/>
  </xsl:variable>

  <xsl:text>
   procedure Set_</xsl:text>

  <xsl:value-of select="@name"/>

  <xsl:text>
     (Element : in out </xsl:text>

  <xsl:value-of select="$type"/>

    <xsl:text>;
      Value   : in     </xsl:text>

  <xsl:choose>
    <xsl:when test="@type = 'Unbounded_Wide_String'">Wide_String</xsl:when>
    <xsl:when test="starts-with(@type,'Primary_')">Asis.Element</xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="@type"/>
    </xsl:otherwise>
  </xsl:choose>

  <xsl:text>)</xsl:text>

</xsl:template>


<xsl:template name="attr-name">
  <xsl:choose>
    <xsl:when test="@name = 'Access_To_Object_Definition'">Get_</xsl:when>
    <xsl:when test="@name = 'Identifier'"                 >Get_</xsl:when>
    <xsl:when test="@name = 'Record_Definition'"          >Get_</xsl:when>
    <xsl:when test="@name = 'Subtype_Indication'"         >Get_</xsl:when>
    <xsl:when test="@name = 'Subtype_Mark'"               >Get_</xsl:when>
  </xsl:choose>

  <xsl:value-of select="@name"/>

</xsl:template>


<xsl:template name="return-type">
  <xsl:choose>
    <xsl:when test="@type = 'Unbounded_Wide_String'">Wide_String</xsl:when>

    <xsl:when test="@type = 'Secondary_Unit_Lists.List_Node'">Asis.Compilation_Unit_List</xsl:when>

    <xsl:when test="starts-with(@type,'Secondary_')">Asis.Element_List</xsl:when>
    <xsl:when test="starts-with(@type,'Primary_')">Asis.Element_List</xsl:when>

    <xsl:otherwise>
      <xsl:value-of select="@type"/>
    </xsl:otherwise>
  </xsl:choose>
</xsl:template>


<xsl:template match="node"
              mode="kind-spec">
   <xsl:param name="type">Element_Node</xsl:param>
   function <xsl:call-template name="kind-name"/> (Element : <xsl:value-of select="$type"/>)
      return <xsl:call-template name="kind-type"/>

</xsl:template>


<xsl:template name="kind-name">

  <xsl:choose>
    <xsl:when test="@name = 'Discrete_Subtype_Definition_Node'"
      >Discrete_Range</xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="substring-before(@name,'_Node')"/>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:text>_Kind</xsl:text>
</xsl:template>

<xsl:template name="kind-type">
  <xsl:text>Asis.</xsl:text>
  <xsl:choose>
    <xsl:when test="@name = 'Type_Definition_Node'">Type</xsl:when>

    <xsl:when test="@name = 'Formal_Type_Definition_Node'">Formal_Type</xsl:when>

    <xsl:when test="@name = 'Discrete_Subtype_Definition_Node'">Discrete_Range</xsl:when>

    <xsl:otherwise>
      <xsl:value-of select="substring-before(@name,'_Node')"/>
    </xsl:otherwise>
  </xsl:choose>
  <xsl:text>_Kinds</xsl:text>
</xsl:template>


<xsl:template name="real-kind-name">
  <xsl:text>A</xsl:text>
  <xsl:choose>
    <xsl:when test="starts-with(@name,'A')">n</xsl:when>
    <xsl:when test="starts-with(@name,'E')">n</xsl:when>
    <xsl:when test="starts-with(@name,'I')">n</xsl:when>
    <xsl:when test="starts-with(@name,'O')">n</xsl:when>
    <xsl:when test="starts-with(@name,'Use')"></xsl:when>
    <xsl:when test="starts-with(@name,'U')">n</xsl:when>
  </xsl:choose>

  <xsl:text>_</xsl:text>

  <xsl:choose>
    <xsl:when test="starts-with(@name,'S_')">
      <xsl:value-of
         select="substring-after(substring-before(@name,'_Node'),'S_')"/>
    </xsl:when>
    <xsl:otherwise>
      <xsl:value-of select="substring-before(@name,'_Node')"/>
    </xsl:otherwise>
  </xsl:choose>

  <xsl:if test="ancestor::node[@name='Type_Definition_Node' 
                or @name='Formal_Type_Definition_Node']">
    <xsl:text>_Definition</xsl:text>
  </xsl:if>
</xsl:template>


<xsl:template name="separator">
   <xsl:param name="text"/>
   <xsl:variable name="minus" 
    select="'--------------------------------------------------------------'"/>

   <xsl:variable name="sep"
     select="substring($minus, 1, string-length($text)+6)"/>

  <xsl:text>
   </xsl:text><xsl:value-of select="$sep"/>
   -- <xsl:value-of select="$text"/> --
   <xsl:value-of select="$sep"/>

</xsl:template>


<xsl:template name="package-name">
  <xsl:param name="text"/>

  <xsl:text>Asis.Gela</xsl:text>
  <xsl:choose>
    <xsl:when test="$text = 'Element_Node'">.Elements</xsl:when>
    <xsl:when test="$text = 'Defining_Name_Node'">.Elements.Def_Names</xsl:when>
    <xsl:when test="$text = 'Declaration_Node'">.Elements.Decl</xsl:when>
    <xsl:when test="$text = 'Definition_Node'">.Elements.Defs</xsl:when>
    <xsl:when test="$text = 'Type_Definition_Node'">.Elements.Defs.Types</xsl:when>
    <xsl:when test="$text = 'Constraint_Node'">.Elements.Defs.Const</xsl:when>
    <xsl:when test="$text = 'Formal_Type_Definition_Node'">.Elements.Defs.Formal</xsl:when>
    <xsl:when test="$text = 'Expression_Node'">.Elements.Expr</xsl:when>
    <xsl:when test="$text = 'Association_Node'">.Elements.Assoc</xsl:when>
    <xsl:when test="$text = 'Statement_Node'">.Elements.Stmt</xsl:when>
    <xsl:when test="$text = 'Path_Node'">.Elements.Pathes</xsl:when>
    <xsl:when test="$text = 'Clause_Node'">.Elements.Clause</xsl:when>
    <xsl:when test="$text = 'Fake_Element_Node'">.Elements.Helpers</xsl:when>
    <xsl:when test="$text = 'Representation_Clause_Node'">.Elements.Clause.Rep</xsl:when>
    <xsl:when test="$text = 'Discrete_Subtype_Definition_Node'">.Elements.Defs.Sub</xsl:when>
    <xsl:when test="$text = 'Discrete_Range_Node'">.Elements.Defs.Rng</xsl:when>
    <xsl:when test="$text = 'Access_Definition_Node'">.Elements.Defs.Accs</xsl:when>
    <xsl:when test="$text = 'Any_Compilation_Unit_Node'">.Units</xsl:when>

    <xsl:otherwise>
      <xsl:value-of select="$text"/>!!!!!!
    </xsl:otherwise>
  </xsl:choose>

</xsl:template>



<xsl:template name="ptr-type-name">
  <xsl:value-of select="substring-before(@name,'_Node')"/>
  <xsl:text>_Ptr</xsl:text>
</xsl:template>



<xsl:template name="real-not-a-kind">

  <xsl:choose>
    <xsl:when test="@name = 'Attribute_Kind'">Not_An_Attribute</xsl:when>
    <xsl:when test="@name = 'Default_Kind'">Not_A_Default</xsl:when>
    <xsl:when test="@name = 'Mode_Kind'">Not_A_Mode</xsl:when>
    <xsl:when test="@name = 'Operator_Kind'">Not_An_Operator</xsl:when>
    <xsl:when test="@name = 'Trait_Kind'">Not_A_Trait</xsl:when>
    <xsl:when test="@name = 'Unit_Kind'">Not_A_Unit</xsl:when>
    <xsl:when test="@name = 'Interface_Kind'">Not_An_Interface</xsl:when>
    <xsl:when test="@name = 'Access_Type_Kind'"
         >Not_An_Access_Type_Definition</xsl:when>
    <xsl:when test="@name = 'Overriding_Indicator_Kind'"
         >Not_An_Overriding_Indicator</xsl:when>
    <xsl:when test="contains(@name, '_Kind')">
      <xsl:for-each select=".."
         >Not_<xsl:call-template name="real-kind-name"/>
      </xsl:for-each>
    </xsl:when>
  </xsl:choose>
</xsl:template>

</xsl:stylesheet>

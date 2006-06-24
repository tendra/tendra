<?xml version='1.0'?>
<xsl:stylesheet xmlns:xsl="http://www.w3.org/1999/XSL/Transform"
                version='1.0'>

<xsl:include href  = "common.xsl"/>
<xsl:output method="text"/>



<xsl:template match="/">

with Asis.Gela.Lists;                  use Asis.Gela.Lists;
with Asis.Gela.Visibility;

  <xsl:apply-templates select="//node [@abstract and not(@helper)]"
                       mode="package"/>

  <xsl:apply-templates select="//node [@name='Fake_Element_Node']"
                       mode="package"/>

  <xsl:apply-templates select="//node [@name='Any_Compilation_Unit_Node']"
                       mode="package"/>

</xsl:template>



<xsl:template match="node" mode="package">

  <xsl:variable name="pkg">
    <xsl:call-template name="package-name">
      <xsl:with-param name="text" select="@name"/>
    </xsl:call-template>
  </xsl:variable>

  <xsl:if
    test="@name='Fake_Element_Node' or @name='Any_Compilation_Unit_Node'">
with Asis.Gela.Lists;                  use Asis.Gela.Lists;
with Asis.Gela.Compilations;
  </xsl:if>

  <xsl:text>
package </xsl:text>

  <xsl:value-of select="$pkg"/>

  <xsl:text> is
</xsl:text>

  <xsl:if
    test="@name='Fake_Element_Node' or @name='Any_Compilation_Unit_Node'">
    <xsl:apply-templates select="."/>
  </xsl:if>

  <xsl:apply-templates
   select="node[@name!='Fake_Element_Node' 
           and @name!='Any_Compilation_Unit_Node']"/>

<xsl:text>
private
</xsl:text>

  <xsl:if
    test="@name='Fake_Element_Node' or @name='Any_Compilation_Unit_Node'">
    <xsl:apply-templates select="." mode="private"/>
  </xsl:if>

  <xsl:apply-templates
   select="node[@name!='Fake_Element_Node' 
           and @name!='Any_Compilation_Unit_Node']"
   mode="private"/>

  <xsl:text>
end </xsl:text>

  <xsl:value-of select="$pkg"/>

  <xsl:text>;</xsl:text>

  <xsl:call-template name="package-body"/>

</xsl:template>

  

<xsl:template match="node">

  <xsl:call-template name="separator">
    <xsl:with-param name="text" select="@name"/>
  </xsl:call-template>

   type <xsl:value-of select="@name"/>
      <xsl:text> is </xsl:text>
      <xsl:if test="@abstract">abstract</xsl:if>
      new <xsl:call-template name="parent-type"/> with private;

   type <xsl:call-template name="ptr-type-name"/> is
      access all <xsl:value-of select="@name"/>;
   for <xsl:call-template name="ptr-type-name"/>'Storage_Pool use Lists.Pool;
<xsl:apply-templates select="attr"/>

  <xsl:variable name="parent"
     select="ancestor::node[@abstract and not(@helper)][1]"/>

  <xsl:if test="not(@helper) and @name!='Any_Compilation_Unit_Node' and not(attr[@name='Declaration_Kind'])">
    <xsl:apply-templates select="$parent" mode="kind-spec">
       <xsl:with-param name="type" select="@name"/>
    </xsl:apply-templates>
    <xsl:text>;
</xsl:text>
  </xsl:if>

  <xsl:if test="attr/@child">
   function Children (Element : access <xsl:value-of select="@name"/>)
     return Traverse_List;
</xsl:if>

  <xsl:if test="not(@abstract)">
   function Clone
     (Element : <xsl:value-of select="@name"/>;
      Parent  : Asis.Element)
     return Asis.Element;
<xsl:if test="ancestor-or-self::node/attr[@child]">
   procedure Copy
     (Source : in     Asis.Element;
      Target : access <xsl:value-of select="@name"/>;
      Cloner : in     Cloner_Class;
      Parent : in     Asis.Element);
</xsl:if>
  </xsl:if>

  <xsl:if test="(not(@abstract) or @helper) and @name!='Fake_Element_Node'">
    <xsl:apply-templates select="node"/>
  </xsl:if>

</xsl:template>



<xsl:template match="attr">
    <xsl:apply-templates select="." mode="spec">
       <xsl:with-param name="type" select="../@name"/>
    </xsl:apply-templates>

    <xsl:text>;
</xsl:text>

  <xsl:if test="not (starts-with(@type,'Secondary_'))">

    <xsl:apply-templates select="." mode="set-spec">
       <xsl:with-param name="type" select="../@name"/>
    </xsl:apply-templates>

    <xsl:text>;
</xsl:text>

  </xsl:if>

  <xsl:if test="starts-with(@type,'Secondary_')">

    <xsl:call-template name="add-to-spec"/>
    <xsl:text>;
</xsl:text>

  </xsl:if>

  <xsl:if test="starts-with(@type,'Primary_')">

    <xsl:call-template name="get-list-spec"/>
    <xsl:text>;
</xsl:text>

  </xsl:if>

</xsl:template>



<xsl:template match="node" mode="private">

   type <xsl:value-of select="@name"/>
      <xsl:text> is </xsl:text>
      <xsl:if test="@abstract">abstract</xsl:if>
      new <xsl:call-template name="parent-type"/> with
      record<xsl:apply-templates select="attr" mode="private"/>

      <xsl:if test="count(attr) = 0">
         null;</xsl:if>

<xsl:text>
      end record;
</xsl:text>

  <xsl:if test="(not(@abstract) or @helper) and @name!='Fake_Element_Node'">
    <xsl:apply-templates select="node" mode="private"/>
  </xsl:if>

</xsl:template>



<xsl:template match="attr" mode="private">
    <xsl:variable name="spaces"
     select="'                                                             '"/>

    <xsl:variable name="taba"
         select="substring($spaces, 1, 30 - string-length(@name))"/>

    <xsl:text>
         </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:value-of select="$taba"/> : aliased <xsl:value-of select="@type"/>
    <xsl:choose>
      <xsl:when test="@default">
        <xsl:text>
           := </xsl:text>
        <xsl:value-of select="@default"/>
      </xsl:when>
      <xsl:when test="@type = 'Boolean'">
        <xsl:text> := False</xsl:text>
      </xsl:when>
      <xsl:when test="@type = 'Asis.Trait_Kinds'">
        <xsl:text> := An_Ordinary_Trait</xsl:text>
      </xsl:when>
      <xsl:when test="contains (@type, '_Kind')">
        <xsl:text> := </xsl:text>
        <xsl:call-template name="real-not-a-kind"/>
      </xsl:when>
    </xsl:choose>
    <xsl:text>;</xsl:text>
</xsl:template>



<xsl:template name="parent-type">
  <xsl:if test="@name!='Any_Compilation_Unit_Node'">
    <xsl:value-of select="../@name"/>
  </xsl:if>

  <xsl:if test="@name='Any_Compilation_Unit_Node'">
    <xsl:text>Compilation_Unit_Node</xsl:text>
  </xsl:if>
</xsl:template>



<xsl:template name="package-body">

  <xsl:variable name="pkg">
    <xsl:call-template name="package-name">
      <xsl:with-param name="text" select="@name"/>
    </xsl:call-template>
  </xsl:variable>

  <xsl:text>
package body </xsl:text>

  <xsl:value-of select="$pkg"/>

  <xsl:text> is
</xsl:text>

  <xsl:if
    test="@name='Fake_Element_Node' or @name='Any_Compilation_Unit_Node'">
    <xsl:apply-templates select="." mode="body"/>
  </xsl:if>

  <xsl:apply-templates
   select="node[@name!='Fake_Element_Node' and @name!='Any_Compilation_Unit_Node']"
   mode="body"/>

  <xsl:text>
end </xsl:text>

  <xsl:value-of select="$pkg"/>

  <xsl:text>;</xsl:text>

</xsl:template>



<xsl:template match="node" mode="body">

  <xsl:apply-templates select="attr" mode="body"/>

  <xsl:if test="not(@helper) and @name!='Any_Compilation_Unit_Node' and not(attr[@name='Declaration_Kind'])">
    <xsl:variable name="parent"
      select="ancestor::node[@abstract and not(@helper)][1]"/>

    <xsl:apply-templates select="$parent" mode="kind-spec">
       <xsl:with-param name="type" select="@name"/>
    </xsl:apply-templates>

    <xsl:text> is
   begin
      return </xsl:text>
    <xsl:call-template name="real-kind-name"/>
    <xsl:text>;
   end;
</xsl:text>
  </xsl:if>

  <xsl:if test="attr/@child">
   function Children (Element : access <xsl:value-of select="@name"/>
    <xsl:text>)
     return Traverse_List is
   begin</xsl:text>
    <xsl:if test="attr/@n_child">
      <xsl:text>
      if Element.Is_Normalized then
         return ((False, Element.</xsl:text>
      <xsl:value-of select="attr[@n_child]/@name"/>'Access),
           (False, Element.<xsl:value-of
                            select="attr[@child=2]/@name"/>'Access));
      <xsl:text>
      end if;</xsl:text>
    </xsl:if>
    <xsl:text>
      return (</xsl:text>

    <xsl:variable name="child-list">
      <xsl:for-each select="ancestor-or-self::node/attr[@child]">
        <xsl:sort select="@child"/>
        <xsl:value-of select="@child"/>,
      </xsl:for-each>
    </xsl:variable>

    <xsl:variable name="first-child">
      <xsl:value-of select="substring-before($child-list, ',')"/>
    </xsl:variable>

    <xsl:if test="count(ancestor-or-self::node/attr/@child) = 1">
      <xsl:text>1 => </xsl:text>
    </xsl:if>

    <xsl:for-each select="ancestor-or-self::node/attr[@child]">
      <xsl:sort select="@child"/>

      <xsl:if test="@child != $first-child">,
        </xsl:if>

      <xsl:choose>
        <xsl:when test="starts-with(@type, 'Primary_')">
          <xsl:text>(True, Asis.Element (Element.</xsl:text>
          <xsl:value-of select="@name"/>
          <xsl:text>))</xsl:text>
        </xsl:when>

        <xsl:otherwise>
          <xsl:text>(False, Element.</xsl:text>
          <xsl:value-of select="@name"/>
          <xsl:text>'Access)</xsl:text>
        </xsl:otherwise>
      </xsl:choose>

    </xsl:for-each>

    <xsl:text>);
   end Children;
</xsl:text>
</xsl:if>

  <xsl:if test="not(@abstract)">
   function Clone
     (Element : <xsl:value-of select="@name"/>;
      Parent  : Asis.Element)
     return Asis.Element
   is
      Result : constant <xsl:value-of select="substring-before(@name,'_Node')"
         />_Ptr := new <xsl:value-of select="@name"/>
   <xsl:text>;
   begin</xsl:text>
  <xsl:for-each select="ancestor-or-self::node">
    <xsl:for-each 
      select="attr[not(@child) 
                   and @name != 'Next_Element'
                   and not (starts-with(@type, 'Primary_'))]">
      <xsl:choose>

        <xsl:when test="@name = 'Enclosing_Element'">
      Result.Enclosing_Element := Parent<xsl:text/>
        </xsl:when>

        <xsl:when test="@name = 'Enclosing_Compilation_Unit'">
      Result.Enclosing_Compilation_Unit :=
        Enclosing_Compilation_Unit (Parent.all)<xsl:text/>
        </xsl:when>

        <xsl:when test="contains (@type,'.List')">
          <xsl:text>
      </xsl:text>
          <xsl:value-of select="substring-before(@type,'.List')"/>
          <xsl:text>.Set
       (Result.</xsl:text>
          <xsl:value-of select="@name"/>
          <xsl:text>,
        </xsl:text>
          <xsl:value-of select="substring-before(@type,'.List')"/>
          <xsl:text>.To_Element_List
         (Element.</xsl:text>
          <xsl:value-of select="@name"/>
          <xsl:text>))</xsl:text>
        </xsl:when>

        <xsl:otherwise>
      Result.<xsl:value-of select="@name"
              /> := Element.<xsl:value-of select="@name"/>
        </xsl:otherwise>
      </xsl:choose>
      <xsl:text>;</xsl:text>
    </xsl:for-each>
</xsl:for-each>
      return Asis.Element (Result);
   end Clone;
<xsl:if test="ancestor-or-self::node/attr[@child]">
   procedure Copy
     (Source : in     Asis.Element;
      Target : access <xsl:value-of select="@name"/>;
      Cloner : in     Cloner_Class;
      Parent : in     Asis.Element)
   is
   begin<xsl:text/>
  <xsl:for-each select="ancestor-or-self::node/attr[@child]">
    <xsl:sort select="@child"/>

    <xsl:choose>
      <xsl:when test="starts-with(@type,'Primary_')">
      Set_<xsl:value-of select="@name"/>
        (Target.all,
         <xsl:value-of select="substring-before(@type, '.List')"
         />.Deep_Copy 
           (<xsl:text/>
        <xsl:call-template name="attr-name"
         /> (Source.all), Cloner, Asis.Element (Target)));<xsl:text/>
      </xsl:when>
      <xsl:otherwise>
      Target.<xsl:value-of select="@name"/> :=
        Copy (Cloner, <xsl:call-template name="attr-name"
              /> (Source.all), Asis.Element (Target));<xsl:text/>
      </xsl:otherwise>
    </xsl:choose>
  </xsl:for-each>
   end Copy;
</xsl:if>
</xsl:if>

  <xsl:if test="(not(@abstract) or @helper) and @name!='Fake_Element_Node'">
    <xsl:apply-templates select="node" mode="body"/>
  </xsl:if>

</xsl:template>



<xsl:template match="attr" mode="body">

  <xsl:apply-templates select="." mode="spec">
    <xsl:with-param name="type" select="../@name"/>
  </xsl:apply-templates>

  <xsl:text> is
   begin
      return </xsl:text>

  <xsl:choose>
    <xsl:when test="@type = 'Unbounded_Wide_String'">
      <xsl:text>W.To_Wide_String (Element.</xsl:text>
      <xsl:call-template name="attr-name"/>
      <xsl:text>)</xsl:text>
    </xsl:when>

    <xsl:when test="@type = 'Secondary_Unit_Lists.List_Node'">
      <xsl:text>Secondary_Unit_Lists.To_Compilation_Unit_List
        (Element.</xsl:text>
      <xsl:call-template name="attr-name"/>
      <xsl:text>)</xsl:text>
    </xsl:when>

    <xsl:when test="starts-with(@type,'Primary_')">
      <xsl:value-of select="substring-before(@type,'.List')"/>
      <xsl:text>.To_Element_List
        (Element.</xsl:text>
      <xsl:call-template name="attr-name"/>
      <xsl:text>, Include_Pragmas)</xsl:text>
    </xsl:when>

    <xsl:when test="starts-with(@type,'Secondary_')">
      <xsl:value-of select="substring-before(@type,'.List')"/>
      <xsl:text>.To_Element_List
        (Element.</xsl:text>
      <xsl:call-template name="attr-name"/>
      <xsl:text>, Include_Pragmas)</xsl:text>
    </xsl:when>

    <xsl:otherwise>
      <xsl:text>Element.</xsl:text>
      <xsl:value-of select="@name"/>   
    </xsl:otherwise>
  </xsl:choose>


  <xsl:text>;
   end </xsl:text>
  <xsl:call-template name="attr-name"/>

  <xsl:text>;
</xsl:text>

  <xsl:if test="not (starts-with(@type,'Secondary_'))">

    <xsl:apply-templates select="." mode="set-spec">
       <xsl:with-param name="type" select="../@name"/>
    </xsl:apply-templates>

    <xsl:text> is
   begin
      Element.</xsl:text>

    <xsl:value-of select="@name"/>   

    <xsl:text> := </xsl:text>

  <xsl:choose>
    <xsl:when test="@type = 'Unbounded_Wide_String'">
      <xsl:text>W.To_Unbounded_Wide_String (Value)</xsl:text>
    </xsl:when>

    <xsl:when test="starts-with(@type,'Primary_')">
      <xsl:value-of select="@type"/>
      <xsl:text> (Value)</xsl:text>
    </xsl:when>

    <xsl:otherwise>
      <xsl:text>Value</xsl:text>
    </xsl:otherwise>
  </xsl:choose>

    <xsl:text>;
   end Set_</xsl:text>

    <xsl:value-of select="@name"/>

     <xsl:text>;
</xsl:text>

  </xsl:if>

  <xsl:if test="starts-with(@type,'Secondary_')">

    <xsl:call-template name="add-to-spec"/>
    <xsl:text> is
   begin
      </xsl:text>
    <xsl:value-of select="substring-before(@type,'.')"/>
    <xsl:text>.Add (Element.</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>, </xsl:text>
    <xsl:if test="@type='Secondary_Unit_Lists.List_Node'"
       >Asis.Element (</xsl:if>
    <xsl:text>Item</xsl:text>
    <xsl:if test="@type='Secondary_Unit_Lists.List_Node'">)</xsl:if>
    <xsl:text>);
   end Add_To_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>;
</xsl:text>

  </xsl:if>

  <xsl:if test="starts-with(@type,'Primary_')">

    <xsl:call-template name="get-list-spec"/>
    <xsl:text> is
   begin
      return Asis.Element (Element.</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>);
   end </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>_List;
</xsl:text>
  </xsl:if>

</xsl:template>



<xsl:template name="add-to-spec">
    <xsl:text>
   procedure Add_To_</xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>
     (Element : in out </xsl:text>
    <xsl:value-of select="../@name"/>
    <xsl:text>;
      Item    : in     Asis.</xsl:text>
    <xsl:if test="@type='Secondary_Unit_Lists.List_Node'">Compilation_Unit</xsl:if>
    <xsl:if test="@type!='Secondary_Unit_Lists.List_Node'">Element</xsl:if>
    <xsl:text>)</xsl:text>
</xsl:template>



<xsl:template name="get-list-spec">
    <xsl:text>
   function </xsl:text>
    <xsl:value-of select="@name"/>
    <xsl:text>_List
     (Element : </xsl:text>
    <xsl:value-of select="../@name"/>
    <xsl:text>) return Asis.Element</xsl:text>
</xsl:template>



</xsl:stylesheet>

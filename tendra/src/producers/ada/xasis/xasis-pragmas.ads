with Asis;

package XASIS.Pragmas is

   type Pragma_Kinds_Array is
     array (Asis.List_Index range <>) of Asis.Pragma_Kinds;

   function Find_Pragmas
     (Name    : Asis.Defining_Name;
      Request : Pragma_Kinds_Array)
     return Asis.Pragma_Element_List;

   type Argument_Kinds is
     (Convention, Entity, On, External_Name, Link_Name);

   function Parameter
     (Element : Asis.Pragma_Element;
      Kind    : Argument_Kinds) return Asis.Expression;

end XASIS.Pragmas;

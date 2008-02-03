with A0025.A;

package body A0025 is

   --  Dummy subprogram completions

   function Library_Unit_Declaration
     (Name : String) return Compilation_Unit_List is
   begin
      return Dummy;
   end Library_Unit_Declaration;

   function Compilation_Unit_Body
     (Name : String) return Compilation_Unit_List is
   begin
      return Dummy;
   end Compilation_Unit_Body;

   function "+"
     (Left, Right : Compilation_Unit_List)
     return Compilation_Unit_List is
   begin
      return Dummy;
   end "+";

   procedure Semantic_Dependence_Order
     (Compilation_Units : in Compilation_Unit_List;
      Dependent_Units   : in Compilation_Unit_List;
      Relation          : in Relation_Kinds) is
   begin
      null;
   end Semantic_Dependence_Order;

   procedure Elaboration_Order
     (Compilation_Units : in Compilation_Unit_List) is
   begin
      null;
   end Elaboration_Order;

begin
   --  Actualy, test starts here:

   --  Test Ancestors relation:
   Semantic_Dependence_Order
     (Library_Unit_Declaration ("A0025.A"),
      Nil_Compilation_Unit_List,
      Ancestors);

   --  Test Descendants relation:
   Semantic_Dependence_Order
     (Library_Unit_Declaration ("A0025"),
      Library_Unit_Declaration ("A0025")
      + Library_Unit_Declaration ("A0025.A")
      + Compilation_Unit_Body ("A0025"),
      Descendants);

end A0025;

with A0025.A;
with A0025.B;
with A0025c;
with A0025d;

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

   Semantic_Dependence_Order
     (Library_Unit_Declaration ("A0025")
      + Library_Unit_Declaration ("A0025.A"),
      Nil_Compilation_Unit_List,
      Descendants);

   --  Test Supporters relation:
   Semantic_Dependence_Order
     (Library_Unit_Declaration ("A0025.A"),
      Nil_Compilation_Unit_List,
      Supporters);

   Semantic_Dependence_Order
     (Library_Unit_Declaration ("A0025.B"),
      Nil_Compilation_Unit_List,
      Supporters);

   --  Test Dependents relation:
   Semantic_Dependence_Order
     (Library_Unit_Declaration ("A0025"),
      Nil_Compilation_Unit_List,
      Dependents);

   --  Test Family relation:
   Semantic_Dependence_Order
     (Compilation_Unit_Body ("A0025"),
      Nil_Compilation_Unit_List,
      Family);

   --  Test Needed_Units relation:
   Semantic_Dependence_Order
     (Library_Unit_Declaration ("A0025d"),
      Nil_Compilation_Unit_List,
      Needed_Units);

end A0025;

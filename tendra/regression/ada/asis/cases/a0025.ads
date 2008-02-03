------------------------------------------------------------------------------
--             G E L A   A S I S   R E G R E S S I O N   T E S T            --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose: Check Asis.Compilation_Units.Relations.
--           We use fake type Compilation_Unit_List and some functions to
--           construct lists as arguments of call to
--           Semantic_Dependence_Order or Elaboration_Order.
--           These calls just triggers print result of call to
--           corresponding functions from Asis.Compilation_Units.Relations.
--

package A0025 is
   type Compilation_Unit_List is private;

   function Library_Unit_Declaration
     (Name : String) return Compilation_Unit_List;
   --  return list contains single named library unit declaration

   function Compilation_Unit_Body
     (Name : String) return Compilation_Unit_List;
   --  return list contains single named compilation unit body

   function "+"
     (Left, Right : Compilation_Unit_List)
     return Compilation_Unit_List;
   --  Join two lists

   type Relation_Kinds is
     (Ancestors,
      Descendants,
      Supporters,
      Dependents,
      Family,
      Needed_Units);

   procedure Semantic_Dependence_Order
     (Compilation_Units : in Compilation_Unit_List;
      Dependent_Units   : in Compilation_Unit_List;
      Relation          : in Relation_Kinds);

   procedure Elaboration_Order
     (Compilation_Units : in Compilation_Unit_List);

   Nil_Compilation_Unit_List : constant Compilation_Unit_List;

private
   type Compilation_Unit_List is (Dummy);

   Nil_Compilation_Unit_List : constant Compilation_Unit_List := Dummy;
end A0025;

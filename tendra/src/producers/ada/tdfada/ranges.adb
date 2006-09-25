with Expression;
with Asis.Elements;
with Asis.Expressions;
with Asis.Definitions;

package body Ranges is

   use XASIS.Static;

   Kind   : constant array (Bound_Kinds) of Asis.Attribute_Kinds :=
     (Lower => Asis.A_First_Attribute, Upper => Asis.A_Last_Attribute);

   procedure Compile_Range_Attribute
     (State    : access States.State;
      Element  : in     Asis.Range_Constraint;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  : in     Range_Context;
      Bound    : in     XASIS.Static.Bound_Kinds)
   is
      use Asis;
      use Asis.Elements;
      use Asis.Expressions;
      use Asis.Definitions;
      use XASIS.Classes;

      Attr   : constant Asis.Expression := Range_Attribute (Element);
      Prefix : constant Asis.Expression :=
        Asis.Expressions.Prefix (Attr);
      Info   : constant Type_Info := Type_From_Subtype_Mark (Prefix);
      Exps   : constant Asis.Expression_List :=
        Attribute_Designator_Expressions (Attr);
   begin
      if Is_Scalar (Info) then
         Expression.First_Last_Attribute
           (State, Prefix, Kind (Bound), Tipe, Static, B, Unit, Exps);
      else
         raise States.Error;
      end if;
   end Compile_Range_Attribute;

   -------------
   -- Compile --
   -------------

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Range_Constraint;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  : in     Range_Context;
      Bound    : in     XASIS.Static.Bound_Kinds)
   is
      use Asis;
      use Asis.Elements;
      use Asis.Expressions;
      use Asis.Definitions;
      Expr : Asis.Expression;
   begin
      case Constraint_Kind (Element) is
         when A_Range_Attribute_Reference =>
            Compile_Range_Attribute
              (State, Element, Tipe, Static, B, Unit, Context, Bound);

         when A_Simple_Expression_Range =>
            case Bound is
               when XASIS.Static.Upper =>
                  Expr := Upper_Bound (Element);
               when XASIS.Static.Lower =>
                  Expr := Lower_Bound (Element);
            end case;

            Expression.Compile (State, Expr, Tipe, Static, B, Unit);
         when others =>
            raise States.Error;
      end case;
   end Compile;

   ----------------------
   -- Compile_Discrete --
   ----------------------

   procedure Compile_Discrete
     (State    : access States.State;
      Element  : in     Asis.Discrete_Range;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  : in     Range_Context;
      Bound    : in     XASIS.Static.Bound_Kinds)
   is
      use Asis;
      use Asis.Elements;
      use Asis.Expressions;
      use Asis.Definitions;
      Expr : Asis.Expression;
   begin
      case Discrete_Range_Kind (Element) is
         when A_Discrete_Subtype_Indication =>
            declare
               Mark : Asis.Expression :=
                 Asis.Definitions.Subtype_Mark (Element);
               Cons : Asis.Constraint :=
                 Asis.Definitions.Subtype_Constraint (Element);
            begin
               if not Is_Nil (Cons) then
                  Compile
                    (State, Cons, Tipe, Static, B, Unit, Context, Bound);
               elsif Expression_Kind (Mark) = An_Attribute_Reference then
                  Expression.First_Last_Attribute
                    (State, Mark, Kind (Bound), Tipe, Static, B, Unit);
               end if;
            end;

         when A_Discrete_Range_Attribute_Reference =>
            Compile_Range_Attribute
              (State, Element, Tipe, Static, B, Unit, Context, Bound);

         when A_Discrete_Simple_Expression_Range =>
            case Bound is
               when XASIS.Static.Upper =>
                  Expr := Upper_Bound (Element);
               when XASIS.Static.Lower =>
                  Expr := Lower_Bound (Element);
            end case;

            Expression.Compile (State, Expr, Tipe, Static, B, Unit);

         when others =>
            raise States.Error;
      end case;
   end Compile_Discrete;

   -----------------
   -- New_Context --
   -----------------

   procedure New_Context
     (State    : access States.State;
      Element  : in     Asis.Range_Constraint;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  :    out Range_Context) is
   begin
      null;
   end New_Context;

   --------------------------
   -- New_Context_Discrete --
   --------------------------

   procedure New_Context_Discrete
     (State    : access States.State;
      Element  : in     Asis.Discrete_Range;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  :    out Range_Context) is
   begin
      null;
   end New_Context_Discrete;

end Ranges;

with Asis;
with XASIS.Classes;

generic
   type Value is private;

   type Static_Range is array (Bound_Kinds) of Value;

   type Calculator is limited private;

   with function Literal
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value is <>;

   with function Operator
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Operator_Kinds;
      Args    : in     Asis.Association_List) return Value is <>;

   with function Attribute
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Attribute_Kinds;
      Element : in     Asis.Expression) return Value is <>;

   with function Attribute_Call
     (Object  : access Calculator;
      Tipe    : in     Classes.Type_Info;
      Kind    : in     Asis.Attribute_Kinds;
      Args    : in     Asis.Association_List) return Value is <>;

   with function Check_Range
     (Object   : access Calculator;
      Expr     : in     Asis.Expression;
      Bounds   : in     Static_Range;
      Invert   : in     Boolean) return Value is <>;

   with function Undefined
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value is <>;

   with function Range_Of_Array
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration;
      Attr    : in     Asis.Expression) return Static_Range is <>;

   with function Range_Of_Type
     (Object   : access Calculator;
      Type_Def : in     Asis.Definition) return Static_Range is <>;

   with function String_Constant_Range
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration) return Static_Range is <>;

package XASIS.Static.Iter is

   function Evaluate
     (Object  : access Calculator;
      Element : in     Asis.Expression) return Value;

   --  Implimentation related functions

   function Constrained_Array_Range
     (Object  : access Calculator;
      Decl    : in     Asis.Declaration;
      Index   : in     Asis.ASIS_Positive)
     return Static_Range;

   function Evaluate_Static_Constant
     (Object  : access Calculator;
      Element : in     Asis.Declaration)
     return Value;

   function Get_Discrete_Range
     (Object  : access Calculator;
      Element : in     Asis.Definition) return Static_Range;

   function Static_Range_Attribute   --  like Is_Static_Bound
     (Object : access Calculator;
      Attr   : in     Asis.Expression) return Static_Range;

end XASIS.Static.Iter;

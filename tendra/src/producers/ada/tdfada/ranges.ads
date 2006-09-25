with Asis;
with States;
with XASIS.Classes;
with XASIS.Static;
with TenDRA.Streams;

package Ranges is
   use TenDRA.Streams;

   type Range_Context is private;

   procedure New_Context
     (State    : access States.State;
      Element  : in     Asis.Range_Constraint;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  :    out Range_Context);

   procedure Compile
     (State    : access States.State;
      Element  : in     Asis.Range_Constraint;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  : in     Range_Context;
      Bound    : in     XASIS.Static.Bound_Kinds);

   procedure New_Context_Discrete
     (State    : access States.State;
      Element  : in     Asis.Discrete_Range;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  :    out Range_Context);

   procedure Compile_Discrete
     (State    : access States.State;
      Element  : in     Asis.Discrete_Range;
      Tipe     : in     XASIS.Classes.Type_Info;
      Static   : in     Boolean;
      B        : in out Stream'Class;
      Unit     : in     States.Unit_Kinds;
      Context  : in     Range_Context;
      Bound    : in     XASIS.Static.Bound_Kinds);

private
   type Range_Context is null record;
end Ranges;

with Ada.Strings.Unbounded;

package Automatons.Output is

   type Start_Names is array (Positive range <>)
     of Ada.Strings.Unbounded.Unbounded_String;

   procedure Generate
     (A     : in DFA;
      Pkg   : in String;
      Start : in Start_Names);

end Automatons.Output;

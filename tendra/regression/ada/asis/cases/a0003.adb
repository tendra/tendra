package body A0003 is

   procedure Test is
      type Local_Derived_Type is new Base_Type;

      -- Doesnt work yet: function T1 return Local_Derived_Type renames False;
      procedure T2 (Item : Base_Type)          renames Used_Defined;
      procedure T3 (Item : Derived_Type)       renames Used_Defined;
      procedure T4 (Item : Local_Derived_Type) renames Used_Defined;

   begin
      null;
   end Test;


   procedure Used_Defined (Item : Base_Type) is
   begin
      null;
   end;
end;


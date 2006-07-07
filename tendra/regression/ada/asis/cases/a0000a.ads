package A0000A is

   type Private_Type_Declaration (<>) is private;

   type Type_1 is tagged null record;

   type Private_Extension_Declaration is new Type_1 with private;

   Deferred_Constant_Declaration : constant Private_Type_Declaration;

   -----------------
   -- Trait_Kinds --
   -----------------

   type Private_Trait is private;

   type Limited_Trait is limited null record;

   type Limited_Private_Trait is limited private;

   type Abstract_Trait is abstract tagged null record;

   type Abstract_Private_Trait is abstract tagged private;

   type Abstract_Limited_Trait is abstract tagged limited null record;

   type Abstract_Limited_Private_Trait is abstract tagged limited private;

private

   type Private_Type_Declaration is new Integer;

   Deferred_Constant_Declaration : constant Private_Type_Declaration := 1;

   type Private_Extension_Declaration is new Type_1 with null record;

   type Private_Trait is null record;

   type Limited_Private_Trait is limited null record;

   type Abstract_Private_Trait is abstract tagged null record;

   type Abstract_Limited_Private_Trait is abstract tagged limited null record;

end A0000A;

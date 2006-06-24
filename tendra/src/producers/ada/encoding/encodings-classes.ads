--  This package is intended for fast calculation equivalence classes
--  for decoded characters.
--  It use map table for 8-bit encodings and cache for UTF-8.
--  User provides Get_Class function to determine
--  equivalence classes of a wide character.
--  If supplied character is begin of surrogate character
--  function should return Unknown.
--  Next time pair of characters would be supplied to
--  determine equivalence class and so on.

generic
   type Character_Class is mod <>;
   with function Get_Class (C : Wide_String) return Character_Class;
package Encodings.Classes is

   Unknown : constant Character_Class := Character_Class'Last;

   type Character_Classes is array (Positive range <>) of Character_Class;
   pragma Pack (Character_Classes);

   type Coder (Map : Encoding := Encodings.UTF_8) is private;

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Classes     :    out Character_Classes;
      Object      : in out Coder);

private

   Cache_Size  : constant := 257;

   subtype Cache_Index is Positive range 1 .. Cache_Size;
   subtype Class_Cache is Character_Classes (Cache_Index);
   type Class_Map      is array (Character) of Character_Class;

   type Coder (Map : Encoding := Encodings.UTF_8) is record
      Prefix        : Wide_Character := ' ';
      case Map is
         when Encodings.Unknown =>
            null;
         when UTF_8 =>
            Cache   : Class_Cache := (others => Unknown);
            Wide    : Wide_String (Cache_Index);
         when others =>  --  8 bit encoding
            Classes : Class_Map   := (others => Unknown);
      end case;
   end record;

end Encodings.Classes;

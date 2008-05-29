------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Characters.Conversions;

package Ada.Characters.Handling is
   pragma Pure (Handling);

   --  Character classification functions

   function Is_Control           (Item : in Character) return Boolean;
   function Is_Graphic           (Item : in Character) return Boolean;
   function Is_Letter            (Item : in Character) return Boolean;
   function Is_Lower             (Item : in Character) return Boolean;
   function Is_Upper             (Item : in Character) return Boolean;
   function Is_Basic             (Item : in Character) return Boolean;
   function Is_Digit             (Item : in Character) return Boolean;
   function Is_Decimal_Digit     (Item : in Character) return Boolean
     renames Is_Digit;
   function Is_Hexadecimal_Digit (Item : in Character) return Boolean;
   function Is_Alphanumeric      (Item : in Character) return Boolean;
   function Is_Special           (Item : in Character) return Boolean;

   --  Conversion functions for Character and String

   function To_Lower (Item : in Character) return Character;
   function To_Upper (Item : in Character) return Character;
   function To_Basic (Item : in Character) return Character;

   function To_Lower (Item : in String) return String;
   function To_Upper (Item : in String) return String;
   function To_Basic (Item : in String) return String;

   --  Classifications of and conversions between Character and ISO 646

   subtype ISO_646 is
     Character range Character'Val(0) .. Character'Val(127);

   function Is_ISO_646 (Item : in Character) return Boolean;
   function Is_ISO_646 (Item : in String)    return Boolean;

   function To_ISO_646 (Item       : in Character;
                        Substitute : in ISO_646 := ' ')
                       return ISO_646;

   function To_ISO_646 (Item       : in String;
                        Substitute : in ISO_646 := ' ')
                       return String;

   --  The functions Is_Character, Is_String, To_Character, To_String,
   --  To_Wide_Character  and To_Wide_String are obsolescent; see J.14.

   function Is_Character (Item : in Wide_Character) return Boolean
     renames Conversions.Is_Character;
   function Is_String    (Item : in Wide_String)    return Boolean
     renames Conversions.Is_String;

   function To_Character (Item       : in Wide_Character;
                          Substitute : in Character := ' ')
                         return Character
     renames Conversions.To_Character;

   function To_String    (Item       : in Wide_String;
                          Substitute : in Character := ' ')
                         return String
     renames Conversions.To_String;

   function To_Wide_Character (Item : in Character) return Wide_Character
     renames Conversions.To_Wide_Character;

   function To_Wide_String    (Item : in String)    return Wide_String
     renames Conversions.To_Wide_String;

end Ada.Characters.Handling;




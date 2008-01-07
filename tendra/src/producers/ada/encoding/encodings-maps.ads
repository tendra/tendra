package Encodings.Maps is

   type Range_Count is range 0 .. 1024;
   subtype Range_Index is Range_Count range 1 .. Range_Count'Last;

   type Backward_Index is range 1 .. 1024;

   type Forward_Map  is array (Character range <>) of Wide_Character;
   pragma Pack (Forward_Map);

   type Backward_Map is array (Backward_Index range <>) of Character;
   pragma Pack (Backward_Map);

   type Wide_Range is record
      Lower : Wide_Character;
      Upper : Wide_Character;
      Index : Backward_Index;
   end record;
   pragma Pack (Wide_Range);

   type Wide_Ranges is array (Range_Index range <>) of Wide_Range;
   pragma Pack (Wide_Ranges);

   function Decode
     (Char     : Character;
      Forward  : Forward_Map) return Wide_Character;

   function Encode
     (Char     : Wide_Character;
      Ranges   : Wide_Ranges;
      Backward : Backward_Map) return Character;

   pragma Inline (Decode);
   pragma Inline (Encode);

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Forward     : in     Forward_Map);

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Ranges      : in     Wide_Ranges;
      Backward    : in     Backward_Map);

end Encodings.Maps;

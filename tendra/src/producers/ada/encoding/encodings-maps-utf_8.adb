package body Encodings.Maps.UTF_8 is

   ------------
   -- Decode --
   ------------

   procedure Decode
     (Text        : in     Raw_String;
      Text_Last   :    out Natural;
      Result      :    out Wide_String;
      Result_Last :    out Natural;
      Map         : in     Encoding := Encodings.UTF_8)
   is
      Index  : Positive := Text'First;
      Value  : Natural;
      T_Last : Natural := Text'First - 1;
      R_Last : Natural := Result'First - 1;
   begin
      for I in Result'Range loop
         exit when Index > Text'Last;

         Value := Character'Pos (Text (Index));

         case Value is
            when 16#E0# .. 16#ff# =>
               exit when Index > Text'Last - 2;
               Value := (Value - 16#E0#) * 2 ** 6;
               Index := Index + 1;
               Value := Value + Character'Pos (Text (Index)) - 16#80#;
               Value := Value * 2 ** 6;
               Index := Index + 1;
               Value := Value + Character'Pos (Text (Index)) - 16#80#;

            when 16#C0# .. 16#DF# =>
               exit when Index > Text'Last - 1;
               Value := (Value - 16#C0#) * 2 ** 6;
               Index := Index + 1;
               Value := Value + Character'Pos (Text (Index)) - 16#80#;

            when others =>
               null;
         end case;

         Result (I) := Wide_Character'Val (Value);
         T_Last := Index;
         R_Last := I;
         Index := Index + 1;
      end loop;

      Text_Last := T_Last;
      Result_Last := R_Last;
   end Decode;

   ------------
   -- Encode --
   ------------

   procedure Encode
     (Text        : in     Wide_String;
      Text_Last   :    out Natural;
      Result      :    out Raw_String;
      Result_Last :    out Natural;
      Map         : in     Encoding := Encodings.UTF_8)
   is
      Index  : Positive := Result'First;
      Value  : Natural;
      T_Last : Natural := Text'First - 1;
      R_Last : Natural := Result'First - 1;
   begin
      for I in Text'Range loop
         exit when Index > Result'Last;

         Value := Wide_Character'Pos (Text (I));

         case Value is
            when 16#0000# .. 16#007f# =>
               Result (Index) := Character'Val (Value);

            when 16#0080# .. 16#07ff# =>
               exit when Index > Result'Last - 1;

               Result (Index) := Character'Val (16#C0# + Value / 2 ** 6);
               Index := Index + 1;
               Result (Index) := Character'Val (16#80# + Value mod 2 ** 6);

            when others =>
               exit when Index > Result'Last - 2;

               Result (Index) := Character'Val (16#E0# + Value / 2 ** 12);
               Index := Index + 1;
               Result (Index) :=
                 Character'Val (16#80# + Value mod 2 ** 12 / 2 ** 6);
               Index := Index + 1;
               Result (Index) := Character'Val (16#80# + Value mod 2 ** 6);
         end case;

         T_Last := I;
         R_Last := Index;
         Index  := Index + 1;
      end loop;

      Text_Last := T_Last;
      Result_Last := R_Last;
   end Encode;

begin
   Encoder_List (Encodings.UTF_8) := Encode'Access;
   Decoder_List (Encodings.UTF_8) := Decode'Access;
end Encodings.Maps.UTF_8;

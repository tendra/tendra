with XASIS.Types;
with Asis.Gela.Classes;

package body Asis.Gela.Overloads.Attr is

   -----------------
   -- Get_Profile --
   -----------------

   function Get_Profile
     (Tipe : Asis.Declaration;
      Kind : Asis.Attribute_Kinds) return Asis.Element_List is
   begin
      case Kind is
         when A_Val_Attribute =>
            return (1 => XASIS.Types.Universal_Integer);
         when A_Value_Attribute =>
            return (1 => XASIS.Types.String);
         when An_Adjacent_Attribute
           | A_Copy_Sign_Attribute
           | A_Max_Attribute
           | A_Min_Attribute
           | A_Remainder_Attribute
           =>
            return (1 | 2 => Tipe);
         when A_Ceiling_Attribute
           | An_Exponent_Attribute
           | A_Floor_Attribute
           | A_Fraction_Attribute
           | An_Image_Attribute
           | A_Machine_Attribute
           | A_Model_Attribute
           | A_Pos_Attribute
           | A_Pred_Attribute
           | A_Rounding_Attribute
           | A_Succ_Attribute
           | A_Truncation_Attribute
           | An_Unbiased_Rounding_Attribute
           | A_Wide_Image_Attribute
           =>
            return (1 => Tipe);
         when A_Compose_Attribute
           | A_Leading_Part_Attribute
           | A_Scaling_Attribute
           =>
            return (1 => Tipe, 2 => XASIS.Types.Universal_Integer);
         when A_Round_Attribute =>
            return (1 => XASIS.Types.Universal_Real);
         when A_Wide_Value_Attribute =>
            return (1 => XASIS.Types.Wide_String);
         when An_Input_Attribute =>
            return (1 => XASIS.Types.Root_Stream_Type);
         when A_Read_Attribute
           | A_Write_Attribute
           | An_Output_Attribute =>
            return (1 => XASIS.Types.Root_Stream_Type,
                    2 => Tipe);
         when others =>
            raise Internal_Error;
      end case;
   end Get_Profile;

   ------------------------
   -- Get_Result_Profile --
   ------------------------

   function Get_Result_Profile
     (Tipe       : Asis.Declaration;
      Kind       : Asis.Attribute_Kinds;
      Class_Wide : Boolean;
      Place      : Asis.Element) return Types.Up_Interpretation is
   begin
      case Kind is
         when A_Val_Attribute
           | A_Value_Attribute
           | An_Adjacent_Attribute
           | A_Ceiling_Attribute
           | A_Compose_Attribute
           | A_Copy_Sign_Attribute
           | A_Floor_Attribute
           | A_Fraction_Attribute
           | A_Leading_Part_Attribute
           | A_Machine_Attribute
           | A_Max_Attribute
           | A_Min_Attribute
           | A_Model_Attribute
           | A_Pred_Attribute
           | A_Remainder_Attribute
           | A_Round_Attribute
           | A_Rounding_Attribute
           | A_Scaling_Attribute
           | A_Succ_Attribute
           | A_Truncation_Attribute
           | An_Unbiased_Rounding_Attribute
           | A_Wide_Value_Attribute
           =>
            return Types.Up_Expression (Tipe, Place);
         when An_Exponent_Attribute
           | A_Pos_Attribute =>
            return Types.Up_Expression (XASIS.Types.Universal_Integer, Place);
         when An_Image_Attribute =>
            return Types.Up_Expression (XASIS.Types.String, Place);
         when A_Wide_Image_Attribute =>
            return Types.Up_Expression (XASIS.Types.Wide_String, Place);
         when An_Input_Attribute =>
            declare
               use Asis.Gela.Classes;
               Result : Type_Info := Type_From_Declaration (Tipe, Place);
            begin
               if Class_Wide then
                  Set_Class_Wide (Result);
               end if;

               return Types.Up_Expression (Result);
            end;
         when A_Read_Attribute
           | A_Write_Attribute
           | An_Output_Attribute =>
            return (Kind => Types.A_Procedure_Call);
         when others =>
            raise Internal_Error;
      end case;
   end Get_Result_Profile;

end Asis.Gela.Overloads.Attr;



------------------------------------------------------------------------------
--  Copyright (c) 2006, Maxim Reznik
--  All rights reserved.
--
--  Redistribution and use in source and binary forms, with or without
--  modification, are permitted provided that the following conditions are met:
--
--     * Redistributions of source code must retain the above copyright notice,
--     * this list of conditions and the following disclaimer.
--     * Redistributions in binary form must reproduce the above copyright
--     * notice, this list of conditions and the following disclaimer in the
--     * documentation and/or other materials provided with the distribution.
--
--  THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
--  AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
--  IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
--  ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT OWNER OR CONTRIBUTORS BE
--  LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
--  CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
--  SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
--  INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
--  CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
--  ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
--  POSSIBILITY OF SUCH DAMAGE.
------------------------------------------------------------------------------

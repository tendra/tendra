with Interfaces.C.Pointers;
with System.Address_To_Access_Conversions;

package body Gela.Source_Buffers is
   use Interfaces;

   type Code_Unit_8_Array is
     array (Count range <>) of aliased Code_Unit_8;

   type Code_Unit_16_Array is
     array (Count range <>) of aliased Code_Unit_16;

   type Code_Unit_32_Array is
     array (Count range <>) of aliased Code_Unit_32;

   package P8 is new C.Pointers  (Count, Code_Unit_8,  Code_Unit_8_Array, 0);
   package P16 is new C.Pointers (Count, Code_Unit_16, Code_Unit_16_Array, 0);
   package P32 is new C.Pointers (Count, Code_Unit_32, Code_Unit_32_Array, 0);

   package Conv_8  is new System.Address_To_Access_Conversions (Code_Unit_8);
   package Conv_16 is new System.Address_To_Access_Conversions (Code_Unit_16);
   package Conv_32 is new System.Address_To_Access_Conversions (Code_Unit_32);

   subtype Source_Buffer_Class is Abstract_Source_Buffer'Class;

   ---------
   -- "+" --
   ---------

   function "+"
     (Left  : in Code_Unit_8_Access;
      Right : in Offset)
      return Code_Unit_8_Access
   is
      use P8;
   begin
      return Code_Unit_8_Access (Pointer (Left) + C.ptrdiff_t (Right));
   end "+";

   ---------
   -- "+" --
   ---------

   function "+"
     (Left  : in Code_Unit_16_Access;
      Right : in Offset)
      return Code_Unit_16_Access
   is
      use P16;
   begin
      return Code_Unit_16_Access (Pointer (Left) + C.ptrdiff_t (Right));
   end "+";

   ---------
   -- "+" --
   ---------

   function "+"
     (Left  : in Code_Unit_32_Access;
      Right : in Offset)
      return Code_Unit_32_Access
   is
      use P32;
   begin
      return Code_Unit_32_Access (Pointer (Left) + C.ptrdiff_t (Right));
   end "+";

   ----------
   -- Data --
   ----------

   function Data
     (This : in Abstract_Source_Buffer)
     return Code_Unit_8_Access
   is
   begin
      if not Is_Open (Source_Buffer_Class (This)) then
         raise Use_Error;
      else
         return Code_Unit_8_Access (Conv_8.To_Pointer (This.Internal_Data));
      end if;
   end Data;

   ----------
   -- Data --
   ----------

   function Data
     (This : in Abstract_Source_Buffer)
      return Code_Unit_16_Access
   is
      package Conv is
        new System.Address_To_Access_Conversions (Code_Unit_16);
   begin
      if not Is_Open (Source_Buffer_Class (This)) then
         raise Use_Error;
      else
         return Code_Unit_16_Access (Conv_16.To_Pointer (This.Internal_Data));
      end if;
   end Data;

   ----------
   -- Data --
   ----------

   function Data
     (This : in Abstract_Source_Buffer)
      return Code_Unit_32_Access
   is
      package Conv is
        new System.Address_To_Access_Conversions (Code_Unit_32);
   begin
      if not Is_Open (Source_Buffer_Class (This)) then
         raise Use_Error;
      else
         return Code_Unit_32_Access (Conv_32.To_Pointer (This.Internal_Data));
      end if;
   end Data;

   ----------
   -- Size --
   ----------

   function Size
     (This      : in Abstract_Source_Buffer;
      Unit_Size : in Code_Unit_Size)
     return Offset
   is
   begin
      case Unit_Size is
         when Unit_8 =>
            return This.Internal_Size;
         when Unit_16 =>
            return This.Internal_Size / 2;
         when Unit_32 =>
            return This.Internal_Size / 4;
      end case;
   end Size;

   -------------
   -- Is_Open --
   -------------

   function Is_Open (This : in Abstract_Source_Buffer) return Boolean is
      use type System.Address;
   begin
      return This.Internal_Data /= System.Null_Address;
   end Is_Open;

   --------------
   -- Finalize --
   --------------

   procedure Finalize (This : in out Abstract_Source_Buffer) is
   begin
      if Is_Open (Source_Buffer_Class (This)) then
         Close (Source_Buffer_Class (This));
      end if;
   end Finalize;

end Gela.Source_Buffers;

------------------------------------------------------------------------------
--  Copyright (c) 2008, Maxim Reznik
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
--
--  Authors:
--    Andry Ogorodnik
--    Maxim Reznik
--    Vadim Godunko
------------------------------------------------------------------------------

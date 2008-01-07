------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

package Interfaces.COBOL is
   pragma Preelaborate(COBOL);

   -- Types and operations for internal data representations

   type Floating      is digits implementation-defined;
   type Long_Floating is digits implementation-defined;

   type Binary      is range implementation-defined .. implementation-defined;
   type Long_Binary is range implementation-defined .. implementation-defined;

   Max_Digits_Binary      : constant := implementation-defined;
   Max_Digits_Long_Binary : constant := implementation-defined;

   type Decimal_Element  is mod implementation-defined;
   type Packed_Decimal is array (Positive range <>) of Decimal_Element;
   pragma Pack(Packed_Decimal);

   type COBOL_Character is new Character; 
   --  implementation-defined character type;

   Ada_To_COBOL
     : array (Character) of COBOL_Character := implementation-defined;

   COBOL_To_Ada
     : array (COBOL_Character) of Character := implementation-defined;

   type Alphanumeric is array (Positive range <>) of COBOL_Character;
   pragma Pack(Alphanumeric);

   function To_COBOL (Item : in String) return Alphanumeric;
   function To_Ada   (Item : in Alphanumeric) return String;

   procedure To_COBOL (Item       : in String;
                       Target     : out Alphanumeric;
                       Last       : out Natural);

   procedure To_Ada (Item     : in Alphanumeric;
                     Target   : out String;
                     Last     : out Natural);

   type Numeric is array (Positive range <>) of COBOL_Character;
   pragma Pack(Numeric);

   -- Formats for COBOL data representations

   type Display_Format is private;

   Unsigned             : constant Display_Format;
   Leading_Separate     : constant Display_Format;
   Trailing_Separate    : constant Display_Format;
   Leading_Nonseparate  : constant Display_Format;
   Trailing_Nonseparate : constant Display_Format;

   type Binary_Format is private;

   High_Order_First  : constant Binary_Format;
   Low_Order_First   : constant Binary_Format;
   Native_Binary     : constant Binary_Format;

   type Packed_Format is private;

   Packed_Unsigned   : constant Packed_Format;
   Packed_Signed     : constant Packed_Format;

   -- Types for external representation of COBOL binary data

   type Byte is mod 2**COBOL_Character'Size;
   type Byte_Array is array (Positive range <>) of Byte;
   pragma Pack (Byte_Array);

   Conversion_Error : exception;

   generic
      type Num is delta <> digits <>;
   package Decimal_Conversions is

      -- Display Formats: data values are represented as Numeric

      function Valid (Item   : in Numeric;
                      Format : in Display_Format) return Boolean;

      function Length (Format : in Display_Format) return Natural;

      function To_Decimal (Item   : in Numeric;
                           Format : in Display_Format) return Num;

      function To_Display (Item   : in Num;
                           Format : in Display_Format) return Numeric;

      -- Packed Formats: data values are represented as Packed_Decimal

      function Valid (Item   : in Packed_Decimal;
                      Format : in Packed_Format) return Boolean;

      function Length (Format : in Packed_Format) return Natural;

      function To_Decimal (Item   : in Packed_Decimal;
                           Format : in Packed_Format) return Num;

      function To_Packed (Item   : in Num;
                          Format : in Packed_Format) return Packed_Decimal;

      -- Binary Formats: external data values are represented as Byte_Array

      function Valid (Item   : in Byte_Array;
                      Format : in Binary_Format) return Boolean;

      function Length (Format : in Binary_Format) return Natural;
      function To_Decimal (Item   : in Byte_Array;
                           Format : in Binary_Format) return Num;

      function To_Binary (Item   : in Num;
                          Format : in Binary_Format) return Byte_Array;

      -- Internal Binary formats: data values are of type Binary or Long_Binary

      function To_Decimal (Item : in Binary)      return Num;
      function To_Decimal (Item : in Long_Binary) return Num;

      function To_Binary      (Item : in Num)  return Binary;
      function To_Long_Binary (Item : in Num)  return Long_Binary;

   end Decimal_Conversions;

private
   -- not specified by the language
end Interfaces.COBOL;


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

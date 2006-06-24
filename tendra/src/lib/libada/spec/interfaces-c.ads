------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

package Interfaces.C is
   pragma Pure(C);

   -- Declarations based on C's <limits.h>

   CHAR_BIT  : constant := implementation-defined;  -- typically 8
   SCHAR_MIN : constant := implementation-defined;  -- typically -128
   SCHAR_MAX : constant := implementation-defined;  -- typically 127
   UCHAR_MAX : constant := implementation-defined;  -- typically 255

   -- Signed and Unsigned Integers
   type int   is range implementation-defined .. implementation-defined;
   type short is range implementation-defined .. implementation-defined;
   type long  is range implementation-defined .. implementation-defined;

   type signed_char is range SCHAR_MIN .. SCHAR_MAX;
   for signed_char'Size use CHAR_BIT;

   type unsigned       is mod implementation-defined;
   type unsigned_short is mod implementation-defined;
   type unsigned_long  is mod implementation-defined;

   type unsigned_char is mod (UCHAR_MAX+1);
   for unsigned_char'Size use CHAR_BIT;

   subtype plain_char is unsigned_char; --  implementation-defined;

   type ptrdiff_t is range implementation-defined .. implementation-defined;

   type size_t is mod implementation-defined;

   -- Floating Point

   type C_float     is digits implementation-defined;

   type double      is digits implementation-defined;

   type long_double is digits implementation-defined;

   -- Characters and Strings

   type char is new Character; --  implementation-defined character type;

   nul : constant char := char'Val (0); --  implementation-defined;

   function To_C   (Item : in Character) return char;

   function To_Ada (Item : in char) return Character;

   type char_array is array (size_t range <>) of aliased char;
   pragma Pack (char_array);
   for char_array'Component_Size use CHAR_BIT;

   function Is_Nul_Terminated (Item : in char_array) return Boolean;

   function To_C   (Item       : in String;
                    Append_Nul : in Boolean := True)
                   return char_array;

   function To_Ada (Item     : in char_array;
                    Trim_Nul : in Boolean := True)
                   return String;

   procedure To_C (Item       : in String;
                   Target     : out char_array;
                   Count      : out size_t;
                   Append_Nul : in Boolean := True);

   procedure To_Ada (Item     : in char_array;
                     Target   : out String;
                     Count    : out Natural;
                     Trim_Nul : in Boolean := True);

   -- Wide Character and Wide String

   type wchar_t is (' ');  --  implementation-defined char type;

   Wide_Nul : constant wchar_t := Wchar_T'Val (0); --  implementation-defined;

   function To_C   (Item : in Wide_Character) return wchar_t;
   function To_Ada (Item : in wchar_t       ) return Wide_Character;

   type wchar_array is array (size_t range <>) of aliased wchar_t;

   pragma Pack (wchar_array);

   function Is_Nul_Terminated (Item : in wchar_array) return Boolean;

   function To_C   (Item       : in Wide_String;
                    Append_Nul : in Boolean := True)
                   return wchar_array;

   function To_Ada (Item     : in wchar_array;
                    Trim_Nul : in Boolean := True)
                   return Wide_String;

   procedure To_C (Item       : in  Wide_String;
                   Target     : out wchar_array;
                   Count      : out size_t;
                   Append_Nul : in  Boolean := True);

   procedure To_Ada (Item     : in  wchar_array;
                     Target   : out Wide_String;
                     Count    : out Natural;
                     Trim_Nul : in  Boolean := True);

   Terminator_Error : exception;

end Interfaces.C;


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

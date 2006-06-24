------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Characters.Handling is
   pragma Preelaborate(Handling);

   --Character classification functions

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

   --Conversion functions for Character and String

   function To_Lower (Item : in Character) return Character;
   function To_Upper (Item : in Character) return Character;
   function To_Basic (Item : in Character) return Character;

   function To_Lower (Item : in String) return String;
   function To_Upper (Item : in String) return String;
   function To_Basic (Item : in String) return String;

   --Classifications of and conversions between Character and ISO 646

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

   --Classifications of and conversions between Wide_Character and Character.

   function Is_Character (Item : in Wide_Character) return Boolean;
   function Is_String    (Item : in Wide_String)    return Boolean;

   function To_Character (Item       : in Wide_Character;
                          Substitute : in Character := ' ')
                         return Character;

   function To_String    (Item       : in Wide_String;
                          Substitute : in Character := ' ')
                         return String;

   function To_Wide_Character
     (Item : in Character) return Wide_Character;

   function To_Wide_String (Item : in String) return Wide_String;

end Ada.Characters.Handling;


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

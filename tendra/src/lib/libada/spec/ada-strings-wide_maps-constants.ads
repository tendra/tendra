------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Strings.Wide_Maps.Constants is
   pragma Preelaborate(Constants);

   Control_Set           : constant Wide_Character_Set;
   Graphic_Set           : constant Wide_Character_Set;
   Letter_Set            : constant Wide_Character_Set;
   Lower_Set             : constant Wide_Character_Set;
   Upper_Set             : constant Wide_Character_Set;
   Basic_Set             : constant Wide_Character_Set;
   Decimal_Digit_Set     : constant Wide_Character_Set;
   Hexadecimal_Digit_Set : constant Wide_Character_Set;
   Alphanumeric_Set      : constant Wide_Character_Set;
   Special_Set           : constant Wide_Character_Set;
   ISO_646_Set           : constant Wide_Character_Set;
   Character_Set         : constant Wide_Maps.Wide_Character_Set;
   --  Contains each Wide_Character value WC such that
   --  Characters.Is_Character(WC) is True


   Lower_Case_Map        : constant Wide_Character_Mapping;
   --  Wide_Maps to lower case for letters, else identity
   Upper_Case_Map        : constant Wide_Character_Mapping;
   --  Wide_Maps to upper case for letters, else identity
   Basic_Map             : constant Wide_Character_Mapping;
   --  Wide_Maps to basic letter for letters, else identity

private

   pragma Import (Ada, Control_Set);
   pragma Import (Ada, Graphic_Set);
   pragma Import (Ada, Letter_Set);
   pragma Import (Ada, Lower_Set);
   pragma Import (Ada, Upper_Set);
   pragma Import (Ada, Basic_Set);
   pragma Import (Ada, Decimal_Digit_Set);
   pragma Import (Ada, Hexadecimal_Digit_Set);
   pragma Import (Ada, Alphanumeric_Set);
   pragma Import (Ada, Special_Set);
   pragma Import (Ada, ISO_646_Set);
   pragma Import (Ada, Character_Set);

   pragma Import (Ada, Lower_Case_Map);
   pragma Import (Ada, Upper_Case_Map);
   pragma Import (Ada, Basic_Map);

end Ada.Strings.Wide_Maps.Constants;


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

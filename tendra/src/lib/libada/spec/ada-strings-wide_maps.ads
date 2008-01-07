------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Strings.Wide_Maps is
   pragma Preelaborate (Wide_Maps);

   -- Representation for a set of Wide_Character values:
   type Wide_Character_Set is private;

   Null_Set : constant Wide_Character_Set;

   type Wide_Character_Range is
      record
         Low  : Wide_Character;
         High : Wide_Character;
      end record;
   -- Represents Wide_Character range Low..High

   type Wide_Character_Ranges is array (Positive range <>)
     of Wide_Character_Range;

   function To_Set    (Ranges : in Wide_Character_Ranges)
                      return Wide_Character_Set;

   function To_Set    (Span   : in Wide_Character_Range)
                      return Wide_Character_Set;

   function To_Ranges (Set    : in Wide_Character_Set)
                      return Wide_Character_Ranges;

   function "="   (Left, Right : in Wide_Character_Set) return Boolean;

   function "not" (Right : in Wide_Character_Set)
                  return Wide_Character_Set;
   function "and" (Left, Right : in Wide_Character_Set)
                  return Wide_Character_Set;
   function "or"  (Left, Right : in Wide_Character_Set)
                  return Wide_Character_Set;
   function "xor" (Left, Right : in Wide_Character_Set)
                  return Wide_Character_Set;
   function "-"   (Left, Right : in Wide_Character_Set)
                  return Wide_Character_Set;

   function Is_In (Element : in Wide_Character;
                   Set     : in Wide_Character_Set)
                  return Boolean;

   function Is_Subset (Elements : in Wide_Character_Set;
                       Set      : in Wide_Character_Set)
                      return Boolean;

   function "<=" (Left  : in Wide_Character_Set;
                  Right : in Wide_Character_Set)
                 return Boolean renames Is_Subset;

   -- Alternative representation for a set of Wide_Character values:
   subtype Wide_Character_Sequence is Wide_String;

   function To_Set (Sequence  : in Wide_Character_Sequence)
                   return Wide_Character_Set;

   function To_Set (Singleton : in Wide_Character)
                   return Wide_Character_Set;

   function To_Sequence (Set  : in Wide_Character_Set)
                        return Wide_Character_Sequence;

   -- Representation for a Wide_Character to Wide_Character mapping:
   type Wide_Character_Mapping is private;

   function Value (Map     : in Wide_Character_Mapping;
                   Element : in Wide_Character)
                  return Wide_Character;

   Identity : constant Wide_Character_Mapping;

   function To_Mapping (From, To : in Wide_Character_Sequence)
                       return Wide_Character_Mapping;

   function To_Domain (Map : in Wide_Character_Mapping)
                      return Wide_Character_Sequence;

   function To_Range  (Map : in Wide_Character_Mapping)
                      return Wide_Character_Sequence;

   type Wide_Character_Mapping_Function is
     access function (From : in Wide_Character) return Wide_Character;

private

   pragma Import (Ada, Wide_Character_Set);
   pragma Import (Ada, Null_Set);
   pragma Import (Ada, Wide_Character_Mapping);
   pragma Import (Ada, Identity);

end Ada.Strings.Wide_Maps;


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

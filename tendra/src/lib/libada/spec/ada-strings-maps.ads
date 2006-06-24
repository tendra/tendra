------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

package Ada.Strings.Maps is
   pragma Preelaborate (Maps);

   -- Representation for a set of character values:
   type Character_Set is private;

   Null_Set : constant Character_Set;

   type Character_Range is
      record
         Low  : Character;
         High : Character;
      end record;
   -- Represents Character range Low..High

   type Character_Ranges is
     array (Positive range <>) of Character_Range;

   function To_Set
     (Ranges : in Character_Ranges) return Character_Set;

   function To_Set    (Span   : in Character_Range) return Character_Set;

   function To_Ranges
     (Set    : in Character_Set) return Character_Ranges;

   function "="   (Left, Right : in Character_Set) return Boolean;

   function "not" (Right : in Character_Set)       return Character_Set;
   function "and" (Left, Right : in Character_Set) return Character_Set;
   function "or"  (Left, Right : in Character_Set) return Character_Set;
   function "xor" (Left, Right : in Character_Set) return Character_Set;
   function "-"   (Left, Right : in Character_Set) return Character_Set;

   function Is_In (Element : in Character;
                   Set     : in Character_Set)
                  return Boolean;

   function Is_Subset (Elements : in Character_Set;
                       Set      : in Character_Set)
                      return Boolean;

   function "<=" (Left  : in Character_Set;
                  Right : in Character_Set)
                 return Boolean renames Is_Subset;

   -- Alternative representation for a set of character values:
   subtype Character_Sequence is String;

   function To_Set
     (Sequence  : in Character_Sequence)return Character_Set;

   function To_Set (Singleton : in Character)     return Character_Set;

   function To_Sequence
     (Set  : in Character_Set) return Character_Sequence;

   -- Representation for a character to character mapping:
   type Character_Mapping is private;

   function Value (Map     : in Character_Mapping;
                   Element : in Character)
                  return Character;

   Identity : constant Character_Mapping;

   function To_Mapping (From, To : in Character_Sequence)
                       return Character_Mapping;

   function To_Domain (Map : in Character_Mapping)
                      return Character_Sequence;
   function To_Range  (Map : in Character_Mapping)
                      return Character_Sequence;

   type Character_Mapping_Function is
     access function (From : in Character) return Character;

private

   pragma Import (Ada, Character_Set);
   pragma Import (Ada, Null_Set);
   pragma Import (Ada, Character_Mapping);
   pragma Import (Ada, Identity);

end Ada.Strings.Maps;


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

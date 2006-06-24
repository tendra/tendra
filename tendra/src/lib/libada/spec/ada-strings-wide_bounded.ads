------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Strings.Wide_Maps;

package Ada.Strings.Bounded_Wide is
   pragma Preelaborate (Bounded_Wide);

   generic
      Max   : Positive;    -- Maximum length of a Bounded_Wide_Wide_String
   package Generic_Bounded_Length is

      Max_Length : constant Positive := Max;

      type Bounded_Wide_String is private;

      Null_Bounded_Wide_String : constant Bounded_Wide_String;

      subtype Length_Range is Natural range 0 .. Max_Length;

      function Length (Source : in Bounded_Wide_String) return Length_Range;

      -- Conversion, Concatenation, and Selection functions

      function To_Bounded_Wide_String (Source : in Wide_String;
                                       Drop   : in Truncation := Error)
                                      return Bounded_Wide_String;

      function To_Wide_String (Source : in Bounded_Wide_String)
                              return Wide_String;

      function Append (Left, Right : in Bounded_Wide_String;
                       Drop        : in Truncation  := Error)
                      return Bounded_Wide_String;

      function Append (Left  : in Bounded_Wide_String;
                       Right : in Wide_String;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_String;

      function Append (Left  : in Wide_String;
                       Right : in Bounded_Wide_String;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_String;

      function Append (Left  : in Bounded_Wide_String;
                       Right : in Wide_Character;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_String;

      function Append (Left  : in Wide_Character;
                       Right : in Bounded_Wide_String;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_String;

      procedure Append (Source   : in out Bounded_Wide_String;
                        New_Item : in Bounded_Wide_String;
                        Drop     : in Truncation  := Error);

      procedure Append (Source   : in out Bounded_Wide_String;
                        New_Item : in Wide_String;
                        Drop     : in Truncation  := Error);

      procedure Append (Source   : in out Bounded_Wide_String;
                        New_Item : in Wide_Character;
                        Drop     : in Truncation  := Error);

      function "&" (Left, Right : in Bounded_Wide_String)
                   return Bounded_Wide_String;

      function "&" (Left : in Bounded_Wide_String; Right : in Wide_String)
                   return Bounded_Wide_String;

      function "&" (Left : in Wide_String; Right : in Bounded_Wide_String)
                   return Bounded_Wide_String;

      function "&" (Left : in Bounded_Wide_String; Right : in Wide_Character)
                   return Bounded_Wide_String;

      function "&" (Left : in Wide_Character; Right : in Bounded_Wide_String)
                   return Bounded_Wide_String;

      function Element (Source : in Bounded_Wide_String;
                        Index  : in Positive)
                       return Wide_Character;

      procedure Replace_Element (Source : in out Bounded_Wide_String;
                                 Index  : in Positive;
                                 By     : in Wide_Character);

      function Slice (Source : in Bounded_Wide_String;
                      Low    : in Positive;
                      High   : in Natural)
                     return Wide_String;

      function "="  (Left, Right : in Bounded_Wide_String) return Boolean;
      function "="  (Left : in Bounded_Wide_String; Right : in Wide_String)
                    return Boolean;

      function "="  (Left : in Wide_String; Right : in Bounded_Wide_String)
                    return Boolean;

      function "<"  (Left, Right : in Bounded_Wide_String) return Boolean;

      function "<"  (Left : in Bounded_Wide_String; Right : in Wide_String)
                    return Boolean;

      function "<"  (Left : in Wide_String; Right : in Bounded_Wide_String)
                    return Boolean;

      function "<=" (Left, Right : in Bounded_Wide_String) return Boolean;

      function "<="  (Left : in Bounded_Wide_String; Right : in Wide_String)
                     return Boolean;

      function "<="  (Left : in Wide_String; Right : in Bounded_Wide_String)
                     return Boolean;

      function ">"  (Left, Right : in Bounded_Wide_String) return Boolean;

      function ">"  (Left : in Bounded_Wide_String; Right : in Wide_String)
                    return Boolean;

      function ">"  (Left : in Wide_String; Right : in Bounded_Wide_String)
                    return Boolean;

      function ">=" (Left, Right : in Bounded_Wide_String) return Boolean;

      function ">="  (Left : in Bounded_Wide_String; Right : in Wide_String)
                     return Boolean;

      function ">="  (Left : in Wide_String; Right : in Bounded_Wide_String)
                     return Boolean;

      -- Search functions

      function Index (Source   : in Bounded_Wide_String;
                      Pattern  : in Wide_String;
                      Going    : in Direction := Forward;
                      Mapping  : in Wide_Maps.Wide_Character_Mapping
                        := Wide_Maps.Identity)
                     return Natural;

      function Index (Source   : in Bounded_Wide_String;
                      Pattern  : in Wide_String;
                      Going    : in Direction := Forward;
                      Mapping  : in Wide_Maps.Wide_Character_Mapping_Function)
                     return Natural;

      function Index (Source : in Bounded_Wide_String;
                      Set    : in Wide_Maps.Wide_Character_Set;
                      Test   : in Membership := Inside;
                      Going  : in Direction  := Forward)
                     return Natural;

      function Index_Non_Blank (Source : in Bounded_Wide_String;
                                Going  : in Direction := Forward)
                               return Natural;

      function Count (Source   : in Bounded_Wide_String;
                      Pattern  : in Wide_String;
                      Mapping  : in Wide_Maps.Wide_Character_Mapping
                        := Wide_Maps.Identity)
                     return Natural;

      function Count (Source   : in Bounded_Wide_String;
                      Pattern  : in Wide_String;
                      Mapping  : in Wide_Maps.Wide_Character_Mapping_Function)
                     return Natural;

      function Count (Source   : in Bounded_Wide_String;
                      Set      : in Wide_Maps.Wide_Character_Set)
                     return Natural;

      procedure Find_Token (Source : in Bounded_Wide_String;
                            Set    : in Wide_Maps.Wide_Character_Set;
                            Test   : in Membership;
                            First  : out Positive;
                            Last   : out Natural);

      -- Wide_String translation subprograms

      function Translate (Source  : in Bounded_Wide_String;
                          Mapping : in Wide_Maps.Wide_Character_Mapping)
                         return Bounded_Wide_String;

      procedure Translate (Source  : in out Bounded_Wide_String;
                           Mapping : in Wide_Maps.Wide_Character_Mapping);

      function Translate
        (Source  : in Bounded_Wide_String;
         Mapping : in Wide_Maps.Wide_Character_Mapping_Function)
        return Bounded_Wide_String;

      procedure Translate
        (Source  : in out Bounded_Wide_String;
         Mapping : in Wide_Maps.Wide_Character_Mapping_Function);

      -- Wide_String transformation subprograms

      function Replace_Slice (Source   : in Bounded_Wide_String;
                              Low      : in Positive;
                              High     : in Natural;
                              By       : in Wide_String;
                              Drop     : in Truncation := Error)
                             return Bounded_Wide_String;

      procedure Replace_Slice (Source   : in out Bounded_Wide_String;
                               Low      : in Positive;
                               High     : in Natural;
                               By       : in Wide_String;
                               Drop     : in Truncation := Error);

      function Insert (Source   : in Bounded_Wide_String;
                       Before   : in Positive;
                       New_Item : in Wide_String;
                       Drop     : in Truncation := Error)
                      return Bounded_Wide_String;

      procedure Insert (Source   : in out Bounded_Wide_String;
                        Before   : in Positive;
                        New_Item : in Wide_String;
                        Drop     : in Truncation := Error);

      function Overwrite (Source    : in Bounded_Wide_String;
                          Position  : in Positive;
                          New_Item  : in Wide_String;
                          Drop      : in Truncation := Error)
                         return Bounded_Wide_String;

      procedure Overwrite (Source    : in out Bounded_Wide_String;
                           Position  : in Positive;
                           New_Item  : in Wide_String;
                           Drop      : in Truncation := Error);

      function Delete (Source  : in Bounded_Wide_String;
                       From    : in Positive;
                       Through : in Natural)
                      return Bounded_Wide_String;

      procedure Delete (Source  : in out Bounded_Wide_String;
                        From    : in Positive;
                        Through : in Natural);

      --Wide_String selector subprograms

      function Trim (Source : in Bounded_Wide_String;
                     Side   : in Trim_End)
                    return Bounded_Wide_String;
      procedure Trim (Source : in out Bounded_Wide_String;
                      Side   : in Trim_End);

      function Trim (Source : in Bounded_Wide_String;
                     Left   : in Wide_Maps.Wide_Character_Set;
                     Right  : in Wide_Maps.Wide_Character_Set)
                    return Bounded_Wide_String;

      procedure Trim (Source : in out Bounded_Wide_String;
                      Left   : in Wide_Maps.Wide_Character_Set;
                      Right  : in Wide_Maps.Wide_Character_Set);

      function Head (Source : in Bounded_Wide_String;
                     Count  : in Natural;
                     Pad    : in Wide_Character  := Wide_Space;
                     Drop   : in Truncation := Error)
                    return Bounded_Wide_String;

      procedure Head (Source : in out Bounded_Wide_String;
                      Count  : in Natural;
                      Pad    : in Wide_Character  := Wide_Space;
                      Drop   : in Truncation := Error);

      function Tail (Source : in Bounded_Wide_String;
                     Count  : in Natural;
                     Pad    : in Wide_Character  := Wide_Space;
                     Drop   : in Truncation := Error)
                    return Bounded_Wide_String;

      procedure Tail (Source : in out Bounded_Wide_String;
                      Count  : in Natural;
                      Pad    : in Wide_Character  := Wide_Space;
                      Drop   : in Truncation := Error);

      --Wide_String constructor subprograms

      function "*" (Left  : in Natural;
                    Right : in Wide_Character)
                   return Bounded_Wide_String;

      function "*" (Left  : in Natural;
                    Right : in Wide_String)
                   return Bounded_Wide_String;

      function "*" (Left  : in Natural;
                    Right : in Bounded_Wide_String)
                   return Bounded_Wide_String;

      function Replicate (Count : in Natural;
                          Item  : in Wide_Character;
                          Drop  : in Truncation := Error)
                         return Bounded_Wide_String;

      function Replicate (Count : in Natural;
                          Item  : in Wide_String;
                          Drop  : in Truncation := Error)
                         return Bounded_Wide_String;

      function Replicate (Count : in Natural;
                          Item  : in Bounded_Wide_String;
                          Drop  : in Truncation := Error)
                         return Bounded_Wide_String;

   private

      pragma Import (Ada, Bounded_Wide_String);
      pragma Import (Ada, Null_Bounded_Wide_String);


   end Generic_Bounded_Length;

end Ada.Strings.Bounded_Wide;


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

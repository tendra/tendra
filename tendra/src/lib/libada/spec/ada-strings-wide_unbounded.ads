------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

with Ada.Strings.Wide_Maps;

package Ada.Strings.Unbounded_Wide is
   pragma Preelaborate (Unbounded_Wide);

   type Unbounded_Wide_String is private;

   Null_Unbounded_Wide_String : constant Unbounded_Wide_String;

   function Length (Source : in Unbounded_Wide_String) return Natural;

   type Wide_String_Access is access all Wide_String;
   procedure Free (X : in out Wide_String_Access);

   -- Conversion, Concatenation, and Selection functions

   function To_Unbounded_Wide_String (Source : in Wide_String)
                                return Unbounded_Wide_String;

   function To_Unbounded_Wide_String (Length : in Natural)
                                return Unbounded_Wide_String;

   function To_Wide_String (Source : in Unbounded_Wide_String)
                           return Wide_String;

   procedure Append (Source   : in out Unbounded_Wide_String;
                     New_Item : in Unbounded_Wide_String);

   procedure Append (Source   : in out Unbounded_Wide_String;
                     New_Item : in Wide_String);

   procedure Append (Source   : in out Unbounded_Wide_String;
                     New_Item : in Wide_Character);

   function "&" (Left, Right : in Unbounded_Wide_String)
                return Unbounded_Wide_String;

   function "&" (Left : in Unbounded_Wide_String; Right : in Wide_String)
                return Unbounded_Wide_String;

   function "&" (Left : in Wide_String; Right : in Unbounded_Wide_String)
                return Unbounded_Wide_String;

   function "&" (Left : in Unbounded_Wide_String;
                 Right : in Wide_Character)
                return Unbounded_Wide_String;

   function "&" (Left : in Wide_Character;
                 Right : in Unbounded_Wide_String)
                return Unbounded_Wide_String;

   function Element (Source : in Unbounded_Wide_String;
                     Index  : in Positive)
                    return Wide_Character;

   procedure Replace_Element (Source : in out Unbounded_Wide_String;
                              Index  : in Positive;
                              By     : in Wide_Character);

   function Slice (Source : in Unbounded_Wide_String;
                   Low    : in Positive;
                   High   : in Natural)
                  return Wide_String;

   function "="  (Left, Right : in Unbounded_Wide_String) return Boolean;

   function "="  (Left : in Unbounded_Wide_String;
                  Right : in Wide_String)
                 return Boolean;

   function "="  (Left : in Wide_String;
                  Right : in Unbounded_Wide_String)
                 return Boolean;

   function "<"  (Left, Right : in Unbounded_Wide_String) return Boolean;

   function "<"  (Left : in Unbounded_Wide_String;
                  Right : in Wide_String)
                 return Boolean;

   function "<"  (Left : in Wide_String;
                  Right : in Unbounded_Wide_String)
                 return Boolean;

   function "<=" (Left, Right : in Unbounded_Wide_String) return Boolean;

   function "<="  (Left : in Unbounded_Wide_String;
                   Right : in Wide_String)
                  return Boolean;

   function "<="  (Left : in Wide_String;
                   Right : in Unbounded_Wide_String)
                  return Boolean;

   function ">"  (Left, Right : in Unbounded_Wide_String) return Boolean;

   function ">"  (Left : in Unbounded_Wide_String;
                  Right : in Wide_String)
                 return Boolean;

   function ">"  (Left : in Wide_String;
                  Right : in Unbounded_Wide_String)
                 return Boolean;

   function ">=" (Left, Right : in Unbounded_Wide_String) return Boolean;

   function ">="  (Left : in Unbounded_Wide_String;
                   Right : in Wide_String)
                  return Boolean;

   function ">="  (Left : in Wide_String;
                   Right : in Unbounded_Wide_String)
                  return Boolean;

   -- Search subprograms

   function Index (Source   : in Unbounded_Wide_String;
                   Pattern  : in Wide_String;
                   Going    : in Direction := Forward;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping
                     := Wide_Maps.Identity)
                  return Natural;

   function Index (Source   : in Unbounded_Wide_String;
                   Pattern  : in Wide_String;
                   Going    : in Direction := Forward;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping_Function)
                  return Natural;

   function Index (Source : in Unbounded_Wide_String;
                   Set    : in Wide_Maps.Wide_Character_Set;
                   Test   : in Membership := Inside;
                   Going  : in Direction  := Forward) return Natural;

   function Index_Non_Blank (Source : in Unbounded_Wide_String;
                             Going  : in Direction := Forward)
                            return Natural;

   function Count (Source   : in Unbounded_Wide_String;
                   Pattern  : in Wide_String;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping
                     := Wide_Maps.Identity)
                  return Natural;

   function Count (Source   : in Unbounded_Wide_String;
                   Pattern  : in Wide_String;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping_Function)
                  return Natural;

   function Count (Source   : in Unbounded_Wide_String;
                   Set      : in Wide_Maps.Wide_Character_Set)
                  return Natural;

   procedure Find_Token (Source : in Unbounded_Wide_String;
                         Set    : in Wide_Maps.Wide_Character_Set;
                         Test   : in Membership;
                         First  : out Positive;
                         Last   : out Natural);

   -- Wide_String translation subprograms

   function Translate (Source  : in Unbounded_Wide_String;
                       Mapping : in Wide_Maps.Wide_Character_Mapping)
                      return Unbounded_Wide_String;

   procedure Translate (Source  : in out Unbounded_Wide_String;
                        Mapping : in Wide_Maps.Wide_Character_Mapping);

   function Translate (Source  : in Unbounded_Wide_String;
                       Mapping : in Wide_Maps.Wide_Character_Mapping_Function)
                      return Unbounded_Wide_String;

   procedure Translate
     (Source  : in out Unbounded_Wide_String;
      Mapping : in Wide_Maps.Wide_Character_Mapping_Function);

   -- Wide_String transformation subprograms

   function Replace_Slice (Source   : in Unbounded_Wide_String;
                           Low      : in Positive;
                           High     : in Natural;
                           By       : in Wide_String)
                          return Unbounded_Wide_String;

   procedure Replace_Slice (Source   : in out Unbounded_Wide_String;
                            Low      : in Positive;
                            High     : in Natural;
                            By       : in Wide_String);

   function Insert (Source   : in Unbounded_Wide_String;
                    Before   : in Positive;
                    New_Item : in Wide_String)
                   return Unbounded_Wide_String;

   procedure Insert (Source   : in out Unbounded_Wide_String;
                     Before   : in Positive;
                     New_Item : in Wide_String);

   function Overwrite (Source    : in Unbounded_Wide_String;
                       Position  : in Positive;
                       New_Item  : in Wide_String)
                      return Unbounded_Wide_String;

   procedure Overwrite (Source    : in out Unbounded_Wide_String;
                        Position  : in Positive;
                        New_Item  : in Wide_String);

   function Delete (Source  : in Unbounded_Wide_String;
                    From    : in Positive;
                    Through : in Natural)
                   return Unbounded_Wide_String;

   procedure Delete (Source  : in out Unbounded_Wide_String;
                     From    : in Positive;
                     Through : in Natural);

   function Trim (Source : in Unbounded_Wide_String;
                  Side   : in Trim_End)
                 return Unbounded_Wide_String;

   procedure Trim (Source : in out Unbounded_Wide_String;
                   Side   : in Trim_End);

   function Trim (Source : in Unbounded_Wide_String;
                  Left   : in Wide_Maps.Wide_Character_Set;
                  Right  : in Wide_Maps.Wide_Character_Set)
                 return Unbounded_Wide_String;

   procedure Trim (Source : in out Unbounded_Wide_String;
                   Left   : in Wide_Maps.Wide_Character_Set;
                   Right  : in Wide_Maps.Wide_Character_Set);

   function Head (Source : in Unbounded_Wide_String;
                  Count  : in Natural;
                  Pad    : in Wide_Character := Wide_Space)
                 return Unbounded_Wide_String;

   procedure Head (Source : in out Unbounded_Wide_String;
                   Count  : in Natural;
                   Pad    : in Wide_Character := Wide_Space);

   function Tail (Source : in Unbounded_Wide_String;
                  Count  : in Natural;
                  Pad    : in Wide_Character := Wide_Space)
                 return Unbounded_Wide_String;

   procedure Tail (Source : in out Unbounded_Wide_String;
                   Count  : in Natural;
                   Pad    : in Wide_Character := Wide_Space);

   function "*" (Left  : in Natural;
                 Right : in Wide_Character)
                return Unbounded_Wide_String;

   function "*" (Left  : in Natural;
                 Right : in Wide_String)
                return Unbounded_Wide_String;

   function "*" (Left  : in Natural;
                 Right : in Unbounded_Wide_String)
                return Unbounded_Wide_String;

private

   pragma Import (Ada, Unbounded_Wide_String);
   pragma Import (Ada, Null_Unbounded_Wide_String);

end Ada.Strings.Unbounded_Wide;


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

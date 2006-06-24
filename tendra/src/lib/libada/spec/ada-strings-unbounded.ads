------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

with Ada.Strings.Maps;
package Ada.Strings.Unbounded is
   pragma Preelaborate (Unbounded);

   type Unbounded_String is private;

   Null_Unbounded_String : constant Unbounded_String;

   function Length (Source : in Unbounded_String) return Natural;

   type String_Access is access all String;
   procedure Free (X : in out String_Access);

   -- Conversion, Concatenation, and Selection functions

   function To_Unbounded_String (Source : in String)
                                return Unbounded_String;

   function To_Unbounded_String (Length : in Natural)
                                return Unbounded_String;

   function To_String (Source : in Unbounded_String) return String;

   procedure Append (Source   : in out Unbounded_String;
                     New_Item : in Unbounded_String);

   procedure Append (Source   : in out Unbounded_String;
                     New_Item : in String);

   procedure Append (Source   : in out Unbounded_String;
                     New_Item : in Character);

   function "&" (Left, Right : in Unbounded_String)
                return Unbounded_String;

   function "&" (Left : in Unbounded_String; Right : in String)
                return Unbounded_String;

   function "&" (Left : in String; Right : in Unbounded_String)
                return Unbounded_String;

   function "&" (Left : in Unbounded_String; Right : in Character)
                return Unbounded_String;

   function "&" (Left : in Character; Right : in Unbounded_String)
                return Unbounded_String;

   function Element (Source : in Unbounded_String;
                     Index  : in Positive)
                    return Character;

   procedure Replace_Element (Source : in out Unbounded_String;
                              Index  : in Positive;
                              By     : in Character);

   function Slice (Source : in Unbounded_String;
                   Low    : in Positive;
                   High   : in Natural)
                  return String;

   function "="  (Left, Right : in Unbounded_String) return Boolean;

   function "="  (Left : in Unbounded_String; Right : in String)
                 return Boolean;

   function "="  (Left : in String; Right : in Unbounded_String)
                 return Boolean;

   function "<"  (Left, Right : in Unbounded_String) return Boolean;

   function "<"  (Left : in Unbounded_String; Right : in String)
                 return Boolean;

   function "<"  (Left : in String; Right : in Unbounded_String)
                 return Boolean;

   function "<=" (Left, Right : in Unbounded_String) return Boolean;

   function "<="  (Left : in Unbounded_String; Right : in String)
                  return Boolean;

   function "<="  (Left : in String; Right : in Unbounded_String)
                  return Boolean;

   function ">"  (Left, Right : in Unbounded_String) return Boolean;

   function ">"  (Left : in Unbounded_String; Right : in String)
                 return Boolean;

   function ">"  (Left : in String; Right : in Unbounded_String)
                 return Boolean;

   function ">=" (Left, Right : in Unbounded_String) return Boolean;

   function ">="  (Left : in Unbounded_String; Right : in String)
                  return Boolean;

   function ">="  (Left : in String; Right : in Unbounded_String)
                  return Boolean;

   -- Search subprograms

   function Index (Source   : in Unbounded_String;
                   Pattern  : in String;
                   Going    : in Direction := Forward;
                   Mapping  : in Maps.Character_Mapping
                     := Maps.Identity)
                  return Natural;

   function Index (Source   : in Unbounded_String;
                   Pattern  : in String;
                   Going    : in Direction := Forward;
                   Mapping  : in Maps.Character_Mapping_Function)
                  return Natural;

   function Index (Source : in Unbounded_String;
                   Set    : in Maps.Character_Set;
                   Test   : in Membership := Inside;
                   Going  : in Direction  := Forward) return Natural;

   function Index_Non_Blank (Source : in Unbounded_String;
                             Going  : in Direction := Forward)
                            return Natural;

   function Count (Source   : in Unbounded_String;
                   Pattern  : in String;
                   Mapping  : in Maps.Character_Mapping
                     := Maps.Identity)
                  return Natural;

   function Count (Source   : in Unbounded_String;
                   Pattern  : in String;
                   Mapping  : in Maps.Character_Mapping_Function)
                  return Natural;

   function Count (Source   : in Unbounded_String;
                   Set      : in Maps.Character_Set)
                  return Natural;

   procedure Find_Token (Source : in Unbounded_String;
                         Set    : in Maps.Character_Set;
                         Test   : in Membership;
                         First  : out Positive;
                         Last   : out Natural);

   -- String translation subprograms

   function Translate (Source  : in Unbounded_String;
                       Mapping : in Maps.Character_Mapping)
                      return Unbounded_String;

   procedure Translate (Source  : in out Unbounded_String;
                        Mapping : in Maps.Character_Mapping);

   function Translate (Source  : in Unbounded_String;
                       Mapping : in Maps.Character_Mapping_Function)
                      return Unbounded_String;

   procedure Translate (Source  : in out Unbounded_String;
                        Mapping : in Maps.Character_Mapping_Function);

   -- String transformation subprograms

   function Replace_Slice (Source   : in Unbounded_String;
                           Low      : in Positive;
                           High     : in Natural;
                           By       : in String)
                          return Unbounded_String;

   procedure Replace_Slice (Source   : in out Unbounded_String;
                            Low      : in Positive;
                            High     : in Natural;
                            By       : in String);

   function Insert (Source   : in Unbounded_String;
                    Before   : in Positive;
                    New_Item : in String)
                   return Unbounded_String;

   procedure Insert (Source   : in out Unbounded_String;
                     Before   : in Positive;
                     New_Item : in String);

   function Overwrite (Source    : in Unbounded_String;
                       Position  : in Positive;
                       New_Item  : in String)
                      return Unbounded_String;

   procedure Overwrite (Source    : in out Unbounded_String;
                        Position  : in Positive;
                        New_Item  : in String);

   function Delete (Source  : in Unbounded_String;
                    From    : in Positive;
                    Through : in Natural)
                   return Unbounded_String;

   procedure Delete (Source  : in out Unbounded_String;
                     From    : in Positive;
                     Through : in Natural);

   function Trim (Source : in Unbounded_String;
                  Side   : in Trim_End)
                 return Unbounded_String;

   procedure Trim (Source : in out Unbounded_String;
                   Side   : in Trim_End);

   function Trim (Source : in Unbounded_String;
                  Left   : in Maps.Character_Set;
                  Right  : in Maps.Character_Set)
                 return Unbounded_String;

   procedure Trim (Source : in out Unbounded_String;
                   Left   : in Maps.Character_Set;
                   Right  : in Maps.Character_Set);

   function Head (Source : in Unbounded_String;
                  Count  : in Natural;
                  Pad    : in Character := Space)
                 return Unbounded_String;

   procedure Head (Source : in out Unbounded_String;
                   Count  : in Natural;
                   Pad    : in Character := Space);

   function Tail (Source : in Unbounded_String;
                  Count  : in Natural;
                  Pad    : in Character := Space)
                 return Unbounded_String;

   procedure Tail (Source : in out Unbounded_String;
                   Count  : in Natural;
                   Pad    : in Character := Space);

   function "*" (Left  : in Natural;
                 Right : in Character)
                return Unbounded_String;

   function "*" (Left  : in Natural;
                 Right : in String)
                return Unbounded_String;

   function "*" (Left  : in Natural;
                 Right : in Unbounded_String)
                return Unbounded_String;

private

   pragma Import (Ada, Unbounded_String);
   pragma Import (Ada, Null_Unbounded_String);

end Ada.Strings.Unbounded;


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

------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $

with Ada.Strings.Wide_Maps;

package Ada.Strings.Fixed is
   pragma Preelaborate (Fixed);

   --  "Copy" procedure for strings of possibly different lengths

   procedure Move (Source  : in  Wide_String;
                   Target  : out Wide_String;
                   Drop    : in  Truncation := Error;
                   Justify : in  Alignment  := Left;
                   Pad     : in  Wide_Character  := Wide_Space);

   --  Search subprograms

   function Index (Source   : in Wide_String;
                   Pattern  : in Wide_String;
                   Going    : in Direction := Forward;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping
                     := Wide_Maps.Identity)
                  return Natural;

   function Index (Source   : in Wide_String;
                   Pattern  : in Wide_String;
                   Going    : in Direction := Forward;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping_Function)
                  return Natural;

   function Index (Source : in Wide_String;
                   Set    : in Wide_Maps.Wide_Character_Set;
                   Test   : in Membership := Inside;
                   Going  : in Direction  := Forward)
                  return Natural;

   function Index_Non_Blank (Source : in Wide_String;
                             Going  : in Direction := Forward)
                            return Natural;

   function Count (Source   : in Wide_String;
                   Pattern  : in Wide_String;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping
                     := Wide_Maps.Identity)
                  return Natural;

   function Count (Source   : in Wide_String;
                   Pattern  : in Wide_String;
                   Mapping  : in Wide_Maps.Wide_Character_Mapping_Function)
                  return Natural;

   function Count (Source   : in Wide_String;
                   Set      : in Wide_Maps.Wide_Character_Set)
                  return Natural;

   procedure Find_Token (Source : in Wide_String;
                         Set    : in Wide_Maps.Wide_Character_Set;
                         Test   : in Membership;
                         First  : out Positive;
                         Last   : out Natural);

   --  Wide_String translation subprograms

   function Translate (Source  : in Wide_String;
                       Mapping : in Wide_Maps.Wide_Character_Mapping)
                      return Wide_String;

   procedure Translate (Source  : in out Wide_String;
                        Mapping : in Wide_Maps.Wide_Character_Mapping);

   function Translate (Source  : in Wide_String;
                       Mapping : in Wide_Maps.Wide_Character_Mapping_Function)
                      return Wide_String;

   procedure Translate
     (Source  : in out Wide_String;
      Mapping : in Wide_Maps.Wide_Character_Mapping_Function);

   --  Wide_String transformation subprograms

   function Replace_Slice (Source   : in Wide_String;
                           Low      : in Positive;
                           High     : in Natural;
                           By       : in Wide_String)
                          return Wide_String;

   procedure Replace_Slice (Source   : in out Wide_String;
                            Low      : in Positive;
                            High     : in Natural;
                            By       : in Wide_String;
                            Drop     : in Truncation := Error;
                            Justify  : in Alignment  := Left;
                            Pad      : in Wide_Character  := Wide_Space);

   function Insert (Source   : in Wide_String;
                    Before   : in Positive;
                    New_Item : in Wide_String)
                   return Wide_String;

   procedure Insert (Source   : in out Wide_String;
                     Before   : in Positive;
                     New_Item : in Wide_String;
                     Drop     : in Truncation := Error);

   function Overwrite (Source   : in Wide_String;
                       Position : in Positive;
                       New_Item : in Wide_String)
                      return Wide_String;

   procedure Overwrite (Source   : in out Wide_String;
                        Position : in Positive;
                        New_Item : in Wide_String;
                        Drop     : in Truncation := Right);

   function Delete (Source  : in Wide_String;
                    From    : in Positive;
                    Through : in Natural)
                   return Wide_String;

   procedure Delete (Source  : in out Wide_String;
                     From    : in Positive;
                     Through : in Natural;
                     Justify : in Alignment := Left;
                     Pad     : in Wide_Character := Wide_Space);

   --  Wide_String selector subprograms
   function Trim (Source : in Wide_String;
                  Side   : in Trim_End)
                 return Wide_String;

   procedure Trim (Source  : in out Wide_String;
                   Side    : in Trim_End;
                   Justify : in Alignment := Left;
                   Pad     : in Wide_Character := Wide_Space);

   function Trim (Source : in Wide_String;
                  Left   : in Wide_Maps.Wide_Character_Set;
                  Right  : in Wide_Maps.Wide_Character_Set)
                 return Wide_String;

   procedure Trim (Source  : in out Wide_String;
                   Left    : in Wide_Maps.Wide_Character_Set;
                   Right   : in Wide_Maps.Wide_Character_Set;
                   Justify : in Alignment := Strings.Left;
                   Pad     : in Wide_Character := Wide_Space);

   function Head (Source : in Wide_String;
                  Count  : in Natural;
                  Pad    : in Wide_Character := Wide_Space)
                 return Wide_String;

   procedure Head (Source  : in out Wide_String;
                   Count   : in Natural;
                   Justify : in Alignment := Left;
                   Pad     : in Wide_Character := Wide_Space);

   function Tail (Source : in Wide_String;
                  Count  : in Natural;
                  Pad    : in Wide_Character := Wide_Space)
                 return Wide_String;

   procedure Tail (Source  : in out Wide_String;
                   Count   : in Natural;
                   Justify : in Alignment := Left;
                   Pad     : in Wide_Character := Wide_Space);

   --  Wide_String constructor functions

   function "*" (Left  : in Natural;
                 Right : in Wide_Character) return Wide_String;

   function "*" (Left  : in Natural;
                 Right : in Wide_String) return Wide_String;

end Ada.Strings.Fixed;


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

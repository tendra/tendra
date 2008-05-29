------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Strings.Wide_Maps;

package Ada.Strings.Wide_Fixed is
   pragma Preelaborate (Wide_Fixed);

   --  "Copy" procedure for strings of possibly different lengths

   procedure Move (Source  : in  Wide_String;
                   Target  : out Wide_String;
                   Drop    : in  Truncation := Error;
                   Justify : in  Alignment  := Left;
                   Pad     : in  Wide_Character  := Wide_Space);

   --  Search subprograms

   function Index (Source  : in Wide_String;
                   Pattern : in Wide_String;
                   From    : in Positive;
                   Going   : in Direction := Forward;
                   Mapping : in Wide_Maps.Wide_Character_Mapping
                     := Wide_Maps.Identity)
                  return Natural;

   function Index (Source  : in Wide_String;
                   Pattern : in Wide_String;
                   From    : in Positive;
                   Going   : in Direction := Forward;
                   Mapping : in Wide_Maps.Wide_Character_Mapping_Function)
                  return Natural;

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

   function Index (Source  : in Wide_String;
                   Set     : in Wide_Maps.Wide_Character_Set;
                   From    : in Positive;
                   Test    : in Membership := Inside;
                   Going   : in Direction := Forward)
                  return Natural;

   function Index (Source : in Wide_String;
                   Set    : in Wide_Maps.Wide_Character_Set;
                   Test   : in Membership := Inside;
                   Going  : in Direction  := Forward)
                  return Natural;

   function Index_Non_Blank (Source : in Wide_String;
                             From   : in Positive;
                             Going  : in Direction := Forward)
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

end Ada.Strings.Wide_Fixed;




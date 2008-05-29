------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Strings.Maps;
package Ada.Strings.Bounded is
   pragma Preelaborate (Bounded);

   generic
      Max   : Positive;    -- Maximum length of a Bounded_String
   package Generic_Bounded_Length is

      Max_Length : constant Positive := Max;

      type Bounded_String is private;

      Null_Bounded_String : constant Bounded_String;

      subtype Length_Range is Natural range 0 .. Max_Length;

      function Length (Source : in Bounded_String) return Length_Range;

      -- Conversion, Concatenation, and Selection functions

      function To_Bounded_String (Source : in String;
                                  Drop   : in Truncation := Error)
                                 return Bounded_String;

      function To_String (Source : in Bounded_String) return String;

      procedure Set_Bounded_String
        (Target :    out Bounded_String;
         Source : in     String;
         Drop   : in     Truncation := Error);

      function Append (Left, Right : in Bounded_String;
                       Drop        : in Truncation  := Error)
                      return Bounded_String;

      function Append (Left  : in Bounded_String;
                       Right : in String;
                       Drop  : in Truncation := Error)
                      return Bounded_String;

      function Append (Left  : in String;
                       Right : in Bounded_String;
                       Drop  : in Truncation := Error)
                      return Bounded_String;

      function Append (Left  : in Bounded_String;
                       Right : in Character;
                       Drop  : in Truncation := Error)
                      return Bounded_String;

      function Append (Left  : in Character;
                       Right : in Bounded_String;
                       Drop  : in Truncation := Error)
                      return Bounded_String;

      procedure Append (Source   : in out Bounded_String;
                        New_Item : in Bounded_String;
                        Drop     : in Truncation  := Error);

      procedure Append (Source   : in out Bounded_String;
                        New_Item : in String;
                        Drop     : in Truncation  := Error);

      procedure Append (Source   : in out Bounded_String;
                        New_Item : in Character;
                        Drop     : in Truncation  := Error);

      function "&" (Left, Right : in Bounded_String)
                   return Bounded_String;

      function "&" (Left : in Bounded_String; Right : in String)
                   return Bounded_String;

      function "&" (Left : in String; Right : in Bounded_String)
                   return Bounded_String;

      function "&" (Left : in Bounded_String; Right : in Character)
                   return Bounded_String;

      function "&" (Left : in Character; Right : in Bounded_String)
                   return Bounded_String;

      function Element (Source : in Bounded_String;
                        Index  : in Positive)
                       return Character;

      procedure Replace_Element (Source : in out Bounded_String;
                                 Index  : in Positive;
                                 By     : in Character);

      function Slice (Source : in Bounded_String;
                      Low    : in Positive;
                      High   : in Natural)
                     return String;

      function Bounded_Slice
        (Source : in Bounded_String;
         Low    : in Positive;
         High   : in Natural)
        return Bounded_String;

      procedure Bounded_Slice
        (Source : in     Bounded_String;
         Target :    out Bounded_String;
         Low    : in     Positive;
         High   : in     Natural);

      function "="  (Left, Right : in Bounded_String) return Boolean;
      function "="  (Left : in Bounded_String; Right : in String)
                    return Boolean;

      function "="  (Left : in String; Right : in Bounded_String)
                    return Boolean;

      function "<"  (Left, Right : in Bounded_String) return Boolean;

      function "<"  (Left : in Bounded_String; Right : in String)
                    return Boolean;

      function "<"  (Left : in String; Right : in Bounded_String)
                    return Boolean;

      function "<=" (Left, Right : in Bounded_String) return Boolean;

      function "<="  (Left : in Bounded_String; Right : in String)
                     return Boolean;

      function "<="  (Left : in String; Right : in Bounded_String)
                     return Boolean;

      function ">"  (Left, Right : in Bounded_String) return Boolean;

      function ">"  (Left : in Bounded_String; Right : in String)
                    return Boolean;

      function ">"  (Left : in String; Right : in Bounded_String)
                    return Boolean;

      function ">=" (Left, Right : in Bounded_String) return Boolean;

      function ">="  (Left : in Bounded_String; Right : in String)
                     return Boolean;

      function ">="  (Left : in String; Right : in Bounded_String)
                     return Boolean;

      -- Search subprograms

      function Index (Source  : in Bounded_String;
                      Pattern : in String;
                      From    : in Positive;
                      Going   : in Direction := Forward;
                      Mapping : in Maps.Character_Mapping := Maps.Identity)
                     return Natural;

      function Index (Source  : in Bounded_String;
                      Pattern : in String;
                      From    : in Positive;
                      Going   : in Direction := Forward;
                      Mapping : in Maps.Character_Mapping_Function)
                     return Natural;

      function Index (Source   : in Bounded_String;
                      Pattern  : in String;
                      Going    : in Direction := Forward;
                      Mapping  : in Maps.Character_Mapping
                        := Maps.Identity)
                     return Natural;

      function Index (Source   : in Bounded_String;
                      Pattern  : in String;
                      Going    : in Direction := Forward;
                      Mapping  : in Maps.Character_Mapping_Function)
                     return Natural;

      function Index (Source  : in Bounded_String;
                      Set     : in Maps.Character_Set;
                      From    : in Positive;
                      Test    : in Membership := Inside;
                      Going   : in Direction := Forward)
                     return Natural;

      function Index (Source : in Bounded_String;
                      Set    : in Maps.Character_Set;
                      Test   : in Membership := Inside;
                      Going  : in Direction  := Forward)
                     return Natural;

      function Index_Non_Blank (Source : in Bounded_String;
                                From   : in Positive;
                                Going  : in Direction := Forward)
                               return Natural;

      function Index_Non_Blank (Source : in Bounded_String;
                                Going  : in Direction := Forward)
                               return Natural;

      function Count (Source   : in Bounded_String;
                      Pattern  : in String;
                      Mapping  : in Maps.Character_Mapping
                        := Maps.Identity)
                     return Natural;

      function Count (Source   : in Bounded_String;
                      Pattern  : in String;
                      Mapping  : in Maps.Character_Mapping_Function)
                     return Natural;

      function Count (Source   : in Bounded_String;
                      Set      : in Maps.Character_Set)
                     return Natural;

      procedure Find_Token (Source : in Bounded_String;
                            Set    : in Maps.Character_Set;
                            Test   : in Membership;
                            First  : out Positive;
                            Last   : out Natural);

      -- String translation subprograms

      function Translate (Source  : in Bounded_String;
                          Mapping : in Maps.Character_Mapping)
                         return Bounded_String;

      procedure Translate (Source  : in out Bounded_String;
                           Mapping : in Maps.Character_Mapping);

      function Translate (Source  : in Bounded_String;
                          Mapping : in Maps.Character_Mapping_Function)
                         return Bounded_String;

      procedure Translate (Source  : in out Bounded_String;
                           Mapping : in Maps.Character_Mapping_Function);

      -- String transformation subprograms

      function Replace_Slice (Source   : in Bounded_String;
                              Low      : in Positive;
                              High     : in Natural;
                              By       : in String;
                              Drop     : in Truncation := Error)
                             return Bounded_String;

      procedure Replace_Slice (Source   : in out Bounded_String;
                               Low      : in Positive;
                               High     : in Natural;
                               By       : in String;
                               Drop     : in Truncation := Error);

      function Insert (Source   : in Bounded_String;
                       Before   : in Positive;
                       New_Item : in String;
                       Drop     : in Truncation := Error)
                      return Bounded_String;

      procedure Insert (Source   : in out Bounded_String;
                        Before   : in Positive;
                        New_Item : in String;
                        Drop     : in Truncation := Error);

      function Overwrite (Source    : in Bounded_String;
                          Position  : in Positive;
                          New_Item  : in String;
                          Drop      : in Truncation := Error)
                         return Bounded_String;

      procedure Overwrite (Source    : in out Bounded_String;
                           Position  : in Positive;
                           New_Item  : in String;
                           Drop      : in Truncation := Error);

      function Delete (Source  : in Bounded_String;
                       From    : in Positive;
                       Through : in Natural)
                      return Bounded_String;

      procedure Delete (Source  : in out Bounded_String;
                        From    : in Positive;
                        Through : in Natural);

      --String selector subprograms

      function Trim (Source : in Bounded_String;
                     Side   : in Trim_End)
                    return Bounded_String;
      procedure Trim (Source : in out Bounded_String;
                      Side   : in Trim_End);

      function Trim (Source : in Bounded_String;
                     Left   : in Maps.Character_Set;
                     Right  : in Maps.Character_Set)
                    return Bounded_String;

      procedure Trim (Source : in out Bounded_String;
                      Left   : in Maps.Character_Set;
                      Right  : in Maps.Character_Set);

      function Head (Source : in Bounded_String;
                     Count  : in Natural;
                     Pad    : in Character  := Space;
                     Drop   : in Truncation := Error)
                    return Bounded_String;

      procedure Head (Source : in out Bounded_String;
                      Count  : in Natural;
                      Pad    : in Character  := Space;
                      Drop   : in Truncation := Error);

      function Tail (Source : in Bounded_String;
                     Count  : in Natural;
                     Pad    : in Character  := Space;
                     Drop   : in Truncation := Error)
                    return Bounded_String;

      procedure Tail (Source : in out Bounded_String;
                      Count  : in Natural;
                      Pad    : in Character  := Space;
                      Drop   : in Truncation := Error);

      --String constructor subprograms

      function "*" (Left  : in Natural;
                    Right : in Character)
                   return Bounded_String;

      function "*" (Left  : in Natural;
                    Right : in String)
                   return Bounded_String;

      function "*" (Left  : in Natural;
                    Right : in Bounded_String)
                   return Bounded_String;

      function Replicate (Count : in Natural;
                          Item  : in Character;
                          Drop  : in Truncation := Error)
                         return Bounded_String;

      function Replicate (Count : in Natural;
                          Item  : in String;
                          Drop  : in Truncation := Error)
                         return Bounded_String;

      function Replicate (Count : in Natural;
                          Item  : in Bounded_String;
                          Drop  : in Truncation := Error)
                         return Bounded_String;

   private

      type Bounded_String is null record;
      Null_Bounded_String : constant Bounded_String := (null record);

   end Generic_Bounded_Length;

end Ada.Strings.Bounded;




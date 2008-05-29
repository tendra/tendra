------------------------------------------------------------------------------
--              A d a   r u n - t i m e   s p e c i f i c a t i o n         --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--          Read copyright and license at the end of ada.ads file           --
------------------------------------------------------------------------------
--  $TenDRA$

with Ada.Strings.Wide_Wide_Maps;
package Ada.Strings.Wide_Wide_Bounded is
   pragma Preelaborate (Wide_Wide_Bounded);

   generic
      Max   : Positive;    --  Maximum length of a Bounded_Wide_Wide_String
   package Generic_Bounded_Length is

      Max_Length : constant Positive := Max;

      type Bounded_Wide_Wide_String is private;

      Null_Bounded_Wide_Wide_String : constant Bounded_Wide_Wide_String;

      subtype Length_Range is Natural range 0 .. Max_Length;

      function Length (Source : in Bounded_Wide_Wide_String)
                      return Length_Range;

      --  Conversion, Concatenation, and Selection functions

      function To_Bounded_Wide_Wide_String (Source : in Wide_Wide_String;
                                            Drop   : in Truncation := Error)
                                           return Bounded_Wide_Wide_String;

      function To_Wide_Wide_String (Source : in Bounded_Wide_Wide_String)
                                   return Wide_Wide_String;

      procedure Set_Bounded_Wide_Wide_String
        (Target :    out Bounded_Wide_Wide_String;
         Source : in     Wide_Wide_String;
         Drop   : in     Truncation := Error);

      function Append (Left, Right : in Bounded_Wide_Wide_String;
                       Drop        : in Truncation  := Error)
                      return Bounded_Wide_Wide_String;

      function Append (Left  : in Bounded_Wide_Wide_String;
                       Right : in Wide_Wide_String;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_Wide_String;

      function Append (Left  : in Wide_Wide_String;
                       Right : in Bounded_Wide_Wide_String;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_Wide_String;

      function Append (Left  : in Bounded_Wide_Wide_String;
                       Right : in Wide_Wide_Character;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_Wide_String;

      function Append (Left  : in Wide_Wide_Character;
                       Right : in Bounded_Wide_Wide_String;
                       Drop  : in Truncation := Error)
                      return Bounded_Wide_Wide_String;

      procedure Append (Source   : in out Bounded_Wide_Wide_String;
                        New_Item : in Bounded_Wide_Wide_String;
                        Drop     : in Truncation  := Error);

      procedure Append (Source   : in out Bounded_Wide_Wide_String;
                        New_Item : in Wide_Wide_String;
                        Drop     : in Truncation  := Error);

      procedure Append (Source   : in out Bounded_Wide_Wide_String;
                        New_Item : in Wide_Wide_Character;
                        Drop     : in Truncation  := Error);

      function "&" (Left, Right : in Bounded_Wide_Wide_String)
                   return Bounded_Wide_Wide_String;

      function "&" (Left  : in Bounded_Wide_Wide_String;
                    Right : in Wide_Wide_String)
                   return Bounded_Wide_Wide_String;

      function "&" (Left  : in Wide_Wide_String;
                    Right : in Bounded_Wide_Wide_String)
                   return Bounded_Wide_Wide_String;

      function "&" (Left  : in Bounded_Wide_Wide_String;
                    Right : in Wide_Wide_Character)
                   return Bounded_Wide_Wide_String;

      function "&" (Left  : in Wide_Wide_Character;
                    Right : in Bounded_Wide_Wide_String)
                   return Bounded_Wide_Wide_String;

      function Element (Source : in Bounded_Wide_Wide_String;
                        Index  : in Positive)
                       return Wide_Wide_Character;

      procedure Replace_Element (Source : in out Bounded_Wide_Wide_String;
                                 Index  : in Positive;
                                 By     : in Wide_Wide_Character);

      function Slice (Source : in Bounded_Wide_Wide_String;
                      Low    : in Positive;
                      High   : in Natural)
                     return Wide_Wide_String;

      function Bounded_Slice
        (Source : in Bounded_Wide_Wide_String;
         Low    : in Positive;
         High   : in Natural)
        return Bounded_Wide_Wide_String;

      procedure Bounded_Slice
        (Source : in     Bounded_Wide_Wide_String;
         Target :    out Bounded_Wide_Wide_String;
         Low    : in     Positive;
         High   : in     Natural);

      function "="  (Left, Right : in Bounded_Wide_Wide_String) return Boolean;

      function "="  (Left  : in Bounded_Wide_Wide_String;
                     Right : in Wide_Wide_String)
                    return Boolean;

      function "="  (Left  : in Wide_Wide_String;
                     Right : in Bounded_Wide_Wide_String)
                    return Boolean;

      function "<"  (Left, Right : in Bounded_Wide_Wide_String) return Boolean;

      function "<"  (Left  : in Bounded_Wide_Wide_String;
                     Right : in Wide_Wide_String)
                    return Boolean;

      function "<"  (Left  : in Wide_Wide_String;
                     Right : in Bounded_Wide_Wide_String)
                    return Boolean;

      function "<=" (Left, Right : in Bounded_Wide_Wide_String) return Boolean;

      function "<="  (Left  : in Bounded_Wide_Wide_String;
                      Right : in Wide_Wide_String)
                     return Boolean;

      function "<="  (Left  : in Wide_Wide_String;
                      Right : in Bounded_Wide_Wide_String)
                     return Boolean;

      function ">"  (Left, Right : in Bounded_Wide_Wide_String) return Boolean;

      function ">"  (Left  : in Bounded_Wide_Wide_String;
                     Right : in Wide_Wide_String)
                    return Boolean;

      function ">"  (Left  : in Wide_Wide_String;
                     Right : in Bounded_Wide_Wide_String)
                    return Boolean;

      function ">=" (Left, Right : in Bounded_Wide_Wide_String) return Boolean;

      function ">="  (Left  : in Bounded_Wide_Wide_String;
                      Right : in Wide_Wide_String)
                     return Boolean;

      function ">="  (Left  : in Wide_Wide_String;
                      Right : in Bounded_Wide_Wide_String)
                     return Boolean;

      --  Search subprograms

      function Index (Source  : in Bounded_Wide_Wide_String;
                      Pattern : in Wide_Wide_String;
                      From    : in Positive;
                      Going   : in Direction := Forward;
                      Mapping : in Wide_Wide_Maps.Wide_Wide_Character_Mapping
                        := Wide_Wide_Maps.Identity)
                     return Natural;

      function Index
        (Source  : in Bounded_Wide_Wide_String;
         Pattern : in Wide_Wide_String;
         From    : in Positive;
         Going   : in Direction := Forward;
         Mapping : in Wide_Wide_Maps.Wide_Wide_Character_Mapping_Function)
        return Natural;

      function Index (Source   : in Bounded_Wide_Wide_String;
                      Pattern  : in Wide_Wide_String;
                      Going    : in Direction := Forward;
                      Mapping  : in Wide_Wide_Maps.Wide_Wide_Character_Mapping
                        := Wide_Wide_Maps.Identity)
                     return Natural;

      function Index
        (Source   : in Bounded_Wide_Wide_String;
         Pattern  : in Wide_Wide_String;
         Going    : in Direction := Forward;
         Mapping  : in Wide_Wide_Maps.Wide_Wide_Character_Mapping_Function)
        return Natural;

      function Index (Source  : in Bounded_Wide_Wide_String;
                      Set     : in Wide_Wide_Maps.Wide_Wide_Character_Set;
                      From    : in Positive;
                      Test    : in Membership := Inside;
                      Going   : in Direction := Forward)
                     return Natural;

      function Index (Source : in Bounded_Wide_Wide_String;
                      Set    : in Wide_Wide_Maps.Wide_Wide_Character_Set;
                      Test   : in Membership := Inside;
                      Going  : in Direction  := Forward)
                     return Natural;

      function Index_Non_Blank (Source : in Bounded_Wide_Wide_String;
                                From   : in Positive;
                                Going  : in Direction := Forward)
                               return Natural;

      function Index_Non_Blank (Source : in Bounded_Wide_Wide_String;
                                Going  : in Direction := Forward)
                               return Natural;

      function Count (Source   : in Bounded_Wide_Wide_String;
                      Pattern  : in Wide_Wide_String;
                      Mapping  : in Wide_Wide_Maps.Wide_Wide_Character_Mapping
                        := Wide_Wide_Maps.Identity)
                     return Natural;

      function Count
        (Source   : in Bounded_Wide_Wide_String;
         Pattern  : in Wide_Wide_String;
         Mapping  : in Wide_Wide_Maps.Wide_Wide_Character_Mapping_Function)
        return Natural;

      function Count (Source   : in Bounded_Wide_Wide_String;
                      Set      : in Wide_Wide_Maps.Wide_Wide_Character_Set)
                     return Natural;

      procedure Find_Token (Source : in Bounded_Wide_Wide_String;
                            Set    : in Wide_Wide_Maps.Wide_Wide_Character_Set;
                            Test   : in Membership;
                            First  : out Positive;
                            Last   : out Natural);

      --  Wide_Wide_String translation subprograms

      function Translate
        (Source  : in Bounded_Wide_Wide_String;
         Mapping : in Wide_Wide_Maps.Wide_Wide_Character_Mapping)
        return Bounded_Wide_Wide_String;

      procedure Translate
        (Source  : in out Bounded_Wide_Wide_String;
         Mapping : in Wide_Wide_Maps.Wide_Wide_Character_Mapping);

      function Translate
        (Source  : in Bounded_Wide_Wide_String;
         Mapping : in Wide_Wide_Maps.Wide_Wide_Character_Mapping_Function)
        return Bounded_Wide_Wide_String;

      procedure Translate
        (Source  : in out Bounded_Wide_Wide_String;
         Mapping : in Wide_Wide_Maps.Wide_Wide_Character_Mapping_Function);

      --  Wide_Wide_String transformation subprograms

      function Replace_Slice (Source   : in Bounded_Wide_Wide_String;
                              Low      : in Positive;
                              High     : in Natural;
                              By       : in Wide_Wide_String;
                              Drop     : in Truncation := Error)
                             return Bounded_Wide_Wide_String;

      procedure Replace_Slice (Source   : in out Bounded_Wide_Wide_String;
                               Low      : in Positive;
                               High     : in Natural;
                               By       : in Wide_Wide_String;
                               Drop     : in Truncation := Error);

      function Insert (Source   : in Bounded_Wide_Wide_String;
                       Before   : in Positive;
                       New_Item : in Wide_Wide_String;
                       Drop     : in Truncation := Error)
                      return Bounded_Wide_Wide_String;

      procedure Insert (Source   : in out Bounded_Wide_Wide_String;
                        Before   : in Positive;
                        New_Item : in Wide_Wide_String;
                        Drop     : in Truncation := Error);

      function Overwrite (Source    : in Bounded_Wide_Wide_String;
                          Position  : in Positive;
                          New_Item  : in Wide_Wide_String;
                          Drop      : in Truncation := Error)
                         return Bounded_Wide_Wide_String;

      procedure Overwrite (Source    : in out Bounded_Wide_Wide_String;
                           Position  : in Positive;
                           New_Item  : in Wide_Wide_String;
                           Drop      : in Truncation := Error);

      function Delete (Source  : in Bounded_Wide_Wide_String;
                       From    : in Positive;
                       Through : in Natural)
                      return Bounded_Wide_Wide_String;

      procedure Delete (Source  : in out Bounded_Wide_Wide_String;
                        From    : in Positive;
                        Through : in Natural);

      --  Wide_Wide_String selector subprograms

      function Trim (Source : in Bounded_Wide_Wide_String;
                     Side   : in Trim_End)
                    return Bounded_Wide_Wide_String;
      procedure Trim (Source : in out Bounded_Wide_Wide_String;
                      Side   : in Trim_End);

      function Trim (Source : in Bounded_Wide_Wide_String;
                     Left   : in Wide_Wide_Maps.Wide_Wide_Character_Set;
                     Right  : in Wide_Wide_Maps.Wide_Wide_Character_Set)
                    return Bounded_Wide_Wide_String;

      procedure Trim (Source : in out Bounded_Wide_Wide_String;
                      Left   : in Wide_Wide_Maps.Wide_Wide_Character_Set;
                      Right  : in Wide_Wide_Maps.Wide_Wide_Character_Set);

      function Head (Source : in Bounded_Wide_Wide_String;
                     Count  : in Natural;
                     Pad    : in Wide_Wide_Character  := Wide_Wide_Space;
                     Drop   : in Truncation := Error)
                    return Bounded_Wide_Wide_String;

      procedure Head (Source : in out Bounded_Wide_Wide_String;
                      Count  : in Natural;
                      Pad    : in Wide_Wide_Character  := Wide_Wide_Space;
                      Drop   : in Truncation := Error);

      function Tail (Source : in Bounded_Wide_Wide_String;
                     Count  : in Natural;
                     Pad    : in Wide_Wide_Character  := Wide_Wide_Space;
                     Drop   : in Truncation := Error)
                    return Bounded_Wide_Wide_String;

      procedure Tail (Source : in out Bounded_Wide_Wide_String;
                      Count  : in Natural;
                      Pad    : in Wide_Wide_Character  := Wide_Wide_Space;
                      Drop   : in Truncation := Error);

      --  Wide_Wide_String constructor subprograms

      function "*" (Left  : in Natural;
                    Right : in Wide_Wide_Character)
                   return Bounded_Wide_Wide_String;

      function "*" (Left  : in Natural;
                    Right : in Wide_Wide_String)
                   return Bounded_Wide_Wide_String;

      function "*" (Left  : in Natural;
                    Right : in Bounded_Wide_Wide_String)
                   return Bounded_Wide_Wide_String;

      function Replicate (Count : in Natural;
                          Item  : in Wide_Wide_Character;
                          Drop  : in Truncation := Error)
                         return Bounded_Wide_Wide_String;

      function Replicate (Count : in Natural;
                          Item  : in Wide_Wide_String;
                          Drop  : in Truncation := Error)
                         return Bounded_Wide_Wide_String;

      function Replicate (Count : in Natural;
                          Item  : in Bounded_Wide_Wide_String;
                          Drop  : in Truncation := Error)
                         return Bounded_Wide_Wide_String;

   private

      type Bounded_Wide_Wide_String is null record;
      Null_Bounded_Wide_Wide_String : constant Bounded_Wide_Wide_String
        := (null record);

   end Generic_Bounded_Length;

end Ada.Strings.Wide_Wide_Bounded;




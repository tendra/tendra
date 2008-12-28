------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Resolve names and fill Corresponding_Defining_Name_List with
--  possible defining names
--  This package stores symbol table as hierarchy of declarative regions
--  starting from parent of Standard and includes regions of all unit
--  of context.

with Asis;
with Asis.Gela.Classes;

package Asis.Gela.Visibility is

   type Point is private;
   --  Represent point in source. Used to lookup names and to point to
   --  place in declarative region.

   Null_Point : constant Point;

   function Enter_Unit (Unit : Asis.Compilation_Unit) return Point;
   --  For given unit find corresponding declarative region.
   --  Result used as initial value to traverse AST and construct
   --  nested regions.

   procedure Enter_Construction
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point);
   --  Create declarative region for given construct if it need it.
   --  Jump to correspondong region if Element is completion.

   procedure Leave_Construction
     (Element : in     Asis.Element;
      Point   : in out Visibility.Point);
   --  Leave declarative region if construction has it.

   function Lookup
     (Item  : Asis.Element;
      Point : Visibility.Point) return Asis.Defining_Name_List;
   --  Return defining names for given name or operator symbol.
   --  Search starts from given point.

   function Lookup_Direct
     (Item  : Asis.Element;
      Point : Visibility.Point) return Asis.Defining_Name_List;
   --  Return direct names for given name or operator symbol.

   function Lookup_In_Region
     (Item  : Asis.Element;
      Reg   : Visibility.Point;
      Point : Visibility.Point) return Asis.Defining_Name_List;
   --  Return names from given region only.

   function Lookup_In_Region
     (Item    : Asis.Element;
      Element : Asis.Element;
      Point   : Visibility.Point)
     return Asis.Defining_Name_List;

   function Lookup_In_Parent_Region
     (Item    : Asis.Element;
      Element : Asis.Element) return Asis.Defining_Name_List;

   function Lookup_Use
     (Item   : Asis.Element;
      Direct : Asis.Defining_Name_List;
      Point  : Visibility.Point) return Asis.Defining_Name_List;
   --  Return names visible through use clauses.

   procedure Print_Region
     (Point  : Visibility.Point;
      Prefix : Wide_String := "");
   --  Dump given region to stdout

   procedure Print_Standard_Region;

   procedure Try_To_Resolve
     (Element : Asis.Expression;
      Point   : Visibility.Point);
   --  Resolve name and collect in corresponfing_defining_name_list

   procedure Try_To_Resolve_Goto
     (Element : Asis.Expression;
      Stmt    : Asis.Statement);

   procedure New_Implicit_Declaration
     (Element    : in     Asis.Declaration;
      Point      : in out Visibility.Point;
      Tipe       : in     Asis.Declaration;
      Overridden :    out Boolean);
   --  Declare implicit declaration to given declarative region.

   function Visible_From
     (Name  : in Asis.Defining_Name;
      Point : in Asis.Element) return Boolean;
   --  Check if name is visible from given point

   function End_Of_Package
     (The_Package : Asis.Declaration)
     return Asis.Element;
   --  Return special element used to mark end of package declaration
   --  view point in call to Visible_From function.
   --  For now defining_name of the package is chosen as such element.

   function Is_Declared (Name : in Asis.Defining_Name) return Boolean;
   --  Check if name was declared

   procedure Set_Not_Declared (Name : in Asis.Defining_Name);
   --  Mark name as not declared

   type Region_Item_Access is private;

   function Unique_Name (Name  : in Asis.Defining_Name) return Wide_String;
   --  Return unique name of region where Name declared and unique name of
   --  defining name in this region

private

   type Region_Node;
   type Part_Node;
   type Region_Item;

   type Region_Access is access all Region_Node;
   type Part_Access is access all Part_Node;
   type Region_Item_Access is access all Region_Item;

   type Item_Kinds is
     (Definition,
      Char, Wide_Char, Wide_Wide_Char,
      Use_Package, Use_Type, Dummy);

   type Region_Item (Kind : Item_Kinds := Definition) is record
      Part          : Part_Access;
      Next          : Region_Item_Access;

      case Kind is
         when Definition | Char | Wide_Char | Wide_Wide_Char =>
            Defining_Name : Asis.Defining_Name;
            --  List of equal names in the same region:
            Prev          : Region_Item_Access;
            --  List of equal names in the upper regions:
            Up            : Region_Item_Access;
            --  Count of equal names in this and upper regions (plus one):
            Count         : Asis.ASIS_Natural;

            case Kind is
               when Definition =>
                  Still_Hidden  : Boolean;
                  Library_Unit  : Boolean;
               when others =>
                  null;
            end case;
         when Use_Package =>
           Declaration : Asis.Declaration;
         when Use_Type =>
            Tipe : Asis.Gela.Classes.Type_Info;
         when Dummy =>
            null;
      end case;
   end record;

   type Part_Kinds is
     (A_Public_Limited_View_Part,
      A_Private_Limited_View_Part,  --  where names of private children go
      A_Visible_Part,
      A_Private_Part,
      A_Public_Children_Part,
      A_Private_Children_Part,
      A_Body_Part);

   subtype A_Children_Part is Part_Kinds range
     A_Public_Children_Part .. A_Private_Children_Part;

   subtype A_Limited_View_Part is Part_Kinds range
     A_Public_Limited_View_Part .. A_Private_Limited_View_Part;

   Is_Visible : constant array (Part_Kinds) of Boolean :=
     (A_Public_Limited_View_Part |
      A_Visible_Part |
      A_Public_Children_Part => True,
      others => False);

   type Part_Node is record
      Dummy_Item    : aliased Region_Item (Dummy);
      Kind          : Part_Kinds;
      Region        : Region_Access;
      Next          : Part_Access;
      Parent_Item   : Region_Item_Access;
      Last_Item     : Region_Item_Access;
      Element       : Asis.Element;
   end record;

   type Region_Node is record
      First_Part      : aliased Part_Node;
      Last_Part       : Part_Access;
      Next            : Region_Access;
      First_Child     : Region_Access;
      Library_Unit    : Boolean := False;
      Public_Child    : Boolean := True;
      Depth           : Positive := 1;
   end record;

   --  function Parent (Object : Region) return Region;

   type Point is record
      Item : Region_Item_Access;
   end record;

   Null_Point : constant Point := (Item => null);

end Asis.Gela.Visibility;


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

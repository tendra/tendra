with Asis.Errors;
with Asis.Elements;
with Asis.Exceptions;
with Asis.Declarations;              use Asis.Declarations;
with Asis.Implementation;
with Asis.Compilation_Units;         use Asis.Compilation_Units;

with Asis.Gela.Units;
with XASIS.Utils;
with Asis.Gela.Contexts.Utils;

with Ada.Wide_Text_IO;

package body Asis.Gela.Contexts is

   procedure Check_Same_Context
     (Unit        : Asis.Compilation_Unit;
      The_Context : Concrete_Context_Node;
      Raiser      : Wide_String);

   procedure Check_Same_Context
     (Decl        : Asis.Declaration;
      The_Context : Concrete_Context_Node;
      Raiser      : Wide_String);

   ---------------
   -- Associate --
   ---------------

   procedure Associate
     (The_Context : access Concrete_Context_Node;
      Name        : in     Wide_String;
      Parameters  : in     Wide_String)
   is
   begin
      The_Context.This         := Asis.Context (The_Context);
      The_Context.Context_Name := U.To_Unbounded_Wide_String (Name);
      The_Context.Parameters   := U.To_Unbounded_Wide_String (Parameters);
      The_Context.Has_Associations := True;
      The_Context.Error            := Success;
      The_Context.Current_File     := The_Context.Parameters;
      Compilations.Initialize (The_Context.Compilation_List);
   end Associate;

   -----------------------
   -- Check_Appropriate --
   -----------------------

   function Check_Appropriate
     (The_Context : in Concrete_Context_Node)
     return Boolean is
   begin
      return The_Context.Check_Appropriate;
   end Check_Appropriate;

   ------------------------
   -- Check_Same_Context --
   ------------------------

   procedure Check_Same_Context
     (Unit        : Asis.Compilation_Unit;
      The_Context : Concrete_Context_Node;
      Raiser      : Wide_String)
   is
      Decl : constant Asis.Declaration :=
        Asis.Elements.Unit_Declaration (Unit);
   begin
      Check_Same_Context (Decl, The_Context, Raiser);
   end Check_Same_Context;

   ------------------------
   -- Check_Same_Context --
   ------------------------

   procedure Check_Same_Context
     (Decl        : Asis.Declaration;
      The_Context : Concrete_Context_Node;
      Raiser      : Wide_String)
   is
      use Asis.Elements;
      Unit         : constant Asis.Compilation_Unit :=
        Asis.Elements.Enclosing_Compilation_Unit (Decl);
      Unit_Context : constant Asis.Context := Enclosing_Context (Unit);
   begin
      if not Assigned (Unit_Context)
        or else Unit_Context.all not in Concrete_Context_Node'Class
        or else not Is_Equal (The_Context,
                              Concrete_Context_Node (Unit_Context.all))
      then
         Implementation.Set_Status
           (Asis.Errors.Not_Implemented_Error,
            "Multiple context in : " & Raiser);

         raise Asis.Exceptions.ASIS_Failed;
      end if;
   end Check_Same_Context;

   -----------
   -- Close --
   -----------

   procedure Close (The_Context : in out Concrete_Context_Node) is
   begin
      The_Context.Is_Open := False;
   end Close;

   -----------------------------
   -- Compilation_Unit_Bodies --
   -----------------------------

   function Compilation_Unit_Bodies
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List
   is
   begin
      return Secondary_Unit_Lists.To_Compilation_Unit_List
        (The_Context.Compilation_Unit_Bodies);
   end Compilation_Unit_Bodies;

   ---------------------------
   -- Compilation_Unit_Body --
   ---------------------------

   function Compilation_Unit_Body
     (Name        : in Wide_String;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit
   is
--      use Asis.Gela.Elements.Utils;
      use Secondary_Unit_Lists;
      use type U.Unbounded_Wide_String;

      Bodies : List_Node renames The_Context.Compilation_Unit_Bodies;
      Unit   : Compilation_Unit;
   begin
      for I in 1 .. Length (Bodies) loop
         Unit := Compilation_Unit (Get (Bodies, I));
         if XASIS.Utils.Are_Equal_Identifiers (Unit_Full_Name (Unit), Name)
         then
            return Unit;
         end if;
      end loop;
      return Nil_Compilation_Unit;
   end Compilation_Unit_Body;

   ---------------------------
   -- Configuration_Pragmas --
   ---------------------------

   function Configuration_Pragmas
     (The_Context : in Concrete_Context_Node)
      return Asis.Pragma_Element_List
   is
   begin
      return Secondary_Pragma_Lists.To_Pragma_List
         (The_Context.Configuration_Pragmas);
   end Configuration_Pragmas;

   -----------------------------
   -- Make_Configuration_Unit --
   -----------------------------

   procedure Make_Configuration_Unit
     (The_Context : in out Concrete_Context_Node)
   is
      use Asis.Gela.Units;
      New_Unit : Any_Compilation_Unit_Ptr;
   begin
      if not Assigned (The_Context.Configuration_Unit) then
         New_Unit := new Any_Compilation_Unit_Node;
         Set_Enclosing_Context (New_Unit.all, The_Context.This);
         Set_Unit_Kind (New_Unit.all, A_Configuration_Compilation);
         Set_Unit_Class (New_Unit.all, Not_A_Class);
         Set_Unit_Origin (New_Unit.all, An_Application_Unit);
         The_Context.Configuration_Unit :=
           Asis.Compilation_Unit (New_Unit);
      end if;
   end Make_Configuration_Unit;

   -------------------------------
   -- Context_Compilation_Units --
   -------------------------------

   function Context_Compilation_Units
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List
   is
   begin
      return Compilation_Unit_Bodies (The_Context) &
        Library_Unit_Declarations (The_Context);
   end Context_Compilation_Units;

   ------------------
   -- Context_Name --
   ------------------

   function Context_Name
     (The_Context : Concrete_Context_Node)
      return Wide_String
   is
   begin
      return U.To_Wide_String (The_Context.Context_Name);
   end Context_Name;

   ------------------------
   -- Corresponding_Body --
   ------------------------

   function Corresponding_Body
     (Library_Item : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit
   is
   begin
      Check_Same_Context (Library_Item, The_Context, "Corresponding_Body");
      return Corresponding_Body (Library_Item);
   end Corresponding_Body;

   ------------------------
   -- Corresponding_Body --
   ------------------------

   function Corresponding_Body
     (Declaration : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration
   is
   begin
      Check_Same_Context (Declaration, The_Context, "Corresponding_Body");
      return Corresponding_Body (Declaration);
   end Corresponding_Body;

   -----------------------------
   -- Corresponding_Body_Stub --
   -----------------------------

   function Corresponding_Body_Stub
     (Subunit     : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration
   is
   begin
      Check_Same_Context (Subunit, The_Context, "Corresponding_Body_Stub");
      return Corresponding_Body_Stub (Subunit);
   end Corresponding_Body_Stub;

   ----------------------------
   -- Corresponding_Children --
   ----------------------------

   function Corresponding_Children
     (Library_Unit : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List
   is
   begin
      Check_Same_Context (Library_Unit, The_Context, "Corresponding_Children");
      return Corresponding_Children (Library_Unit);
   end Corresponding_Children;

   -------------------------------
   -- Corresponding_Declaration --
   -------------------------------

   function Corresponding_Declaration
     (Library_Item : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit
   is
   begin
      Check_Same_Context
        (Library_Item, The_Context, "Corresponding_Declaration");
      return Corresponding_Declaration (Library_Item);
   end Corresponding_Declaration;

   -------------------------------
   -- Corresponding_Declaration --
   -------------------------------

   function Corresponding_Declaration
     (Declaration : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration
   is
   begin
      Check_Same_Context
        (Declaration, The_Context, "Corresponding_Declaration");
      return Corresponding_Declaration (Declaration);
   end Corresponding_Declaration;

   --------------------------------------
   -- Corresponding_Parent_Declaration --
   --------------------------------------

   function Corresponding_Parent_Declaration
     (Library_Unit : in Asis.Compilation_Unit;
      The_Context  : in Concrete_Context_Node)
      return Asis.Compilation_Unit
   is
   begin
      Check_Same_Context
        (Library_Unit, The_Context, "Corresponding_Parent_Declaration");
      return Corresponding_Parent_Declaration (Library_Unit);
   end Corresponding_Parent_Declaration;

   ---------------------------
   -- Corresponding_Subunit --
   ---------------------------

   function Corresponding_Subunit
     (Body_Stub   : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration
   is
   begin
      Check_Same_Context
        (Body_Stub, The_Context, "Corresponding_Subunit");
      return Corresponding_Subunit (Body_Stub);
   end Corresponding_Subunit;

   ---------------------------------------
   -- Corresponding_Subunit_Parent_Body --
   ---------------------------------------

   function Corresponding_Subunit_Parent_Body
     (Subunit     : in Asis.Compilation_Unit;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit
   is
   begin
      Check_Same_Context
        (Subunit, The_Context, "Corresponding_Subunit_Parent_Body");
      return Corresponding_Subunit_Parent_Body (Subunit);
   end Corresponding_Subunit_Parent_Body;

   ------------------------------------
   -- Corresponding_Type_Declaration --
   ------------------------------------

   function Corresponding_Type_Declaration
     (Declaration : in Asis.Declaration;
      The_Context : in Concrete_Context_Node)
      return Asis.Declaration
   is
   begin
      Check_Same_Context
        (Declaration, The_Context, "Corresponding_Type_Declaration");
      return Corresponding_Type_Declaration (Declaration);
   end Corresponding_Type_Declaration;

   ------------------
   -- Current_File --
   ------------------

   function Current_File
     (The_Context : Concrete_Context_Node)
      return Wide_String
   is
   begin
      return U.To_Wide_String (The_Context.Current_File);
   end Current_File;

   ------------------
   -- Current_Unit --
   ------------------

   function Current_Unit
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit
   is
   begin
      return The_Context.Current_Unit;
   end Current_Unit;

   -----------------
   -- Debug_Image --
   -----------------

   function Debug_Image
     (The_Context : Concrete_Context_Node)
      return Wide_String
   is
   begin
      return "Debug_Image";
   end Debug_Image;

   ----------------
   -- Dissociate --
   ----------------

   procedure Dissociate (The_Context : in out Concrete_Context_Node) is
   begin
      The_Context.Has_Associations := False;
      Compilations.Finalize (The_Context.Compilation_List);
   end Dissociate;

   ----------------------
   -- Has_Associations --
   ----------------------

   function Has_Associations
     (The_Context : Concrete_Context_Node)
      return Boolean
   is
   begin
      return The_Context.Has_Associations;
   end Has_Associations;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal
     (Left  : in Concrete_Context_Node;
      Right : in Concrete_Context_Node)
      return Boolean
   is
      use type U.Unbounded_Wide_String;
   begin
      return Left.Context_Name = Right.Context_Name;
   end Is_Equal;

   -------------
   -- Is_Open --
   -------------

   function Is_Open (The_Context : Concrete_Context_Node) return Boolean is
   begin
      return The_Context.Is_Open;
   end Is_Open;

   --------------------------
   -- New_Compilation_Unit --
   --------------------------

   function New_Compilation_Unit
     (The_Context : access Concrete_Context_Node)
     return Asis.Compilation_Unit
   is
      use Asis.Gela.Units;

      New_Unit : constant Any_Compilation_Unit_Ptr :=
        new Any_Compilation_Unit_Node;
   begin
      Set_Enclosing_Context (New_Unit.all, The_Context.This);
      Set_Text_Name (New_Unit.all, Current_File (The_Context.all));
      The_Context.Current_Unit := Compilation_Unit (New_Unit);

      return Asis.Compilation_Unit (New_Unit);
   end New_Compilation_Unit;

   ------------------------------
   -- Library_Unit_Declaration --
   ------------------------------

   function Library_Unit_Declaration
     (Name        : in Wide_String;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit
   is
      use Secondary_Unit_Lists;
      use type U.Unbounded_Wide_String;

      Decls  : List_Node renames The_Context.Library_Unit_Declarations;
      Unit   : Compilation_Unit;
   begin
      for I in 1 .. Length (Decls) loop
         Unit := Compilation_Unit (Get (Decls, I));
         if XASIS.Utils.Are_Equal_Identifiers (Unit_Full_Name (Unit), Name)
         then
            return Unit;
         end if;
      end loop;
      return Nil_Compilation_Unit;
   end Library_Unit_Declaration;

   -------------------------------
   -- Library_Unit_Declarations --
   -------------------------------

   function Library_Unit_Declarations
     (The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List
   is
   begin
      return Secondary_Unit_Lists.To_Compilation_Unit_List
        (The_Context.Library_Unit_Declarations);
   end Library_Unit_Declarations;

   ----------
   -- Open --
   ----------

   procedure Open (The_Context : in out Concrete_Context_Node) is
   begin
      Utils.Read_File_And_Supporters (The_Context);

      if The_Context.Error /= Success then
         Implementation.Set_Status
           (Asis.Errors.Environment_Error,
            "There are compilation errors");

         raise Asis.Exceptions.ASIS_Failed;
      end if;

      The_Context.Is_Open := True;
   end Open;

   ----------------
   -- Parameters --
   ----------------

   function Parameters
     (The_Context : Concrete_Context_Node)
      return Wide_String
   is
   begin
      return U.To_Wide_String (The_Context.Parameters);
   end Parameters;

   ------------------
   -- Report_Error --
   ------------------

   procedure Report_Error
     (The_Context : in out Concrete_Context_Node;
      The_Unit    : in     Compilation_Unit;
      Where       : in     Text_Position;
      Text        : in     Wide_String;
      Level       : in     Error_Level)
   is
      function Get_File_Name return Wide_String is
      begin
         if Is_Nil (The_Unit) then
            return Current_File (The_Context);
         else
            return Text_Name (The_Unit.all);
         end if;
      end Get_File_Name;

      File_Name : constant Wide_String :=  Get_File_Name;
      Where_Img : constant Wide_String := To_Wide_String (Where);
      Message   : constant Wide_String :=
        File_Name & ":" & Where_Img & ": " & Text;
   begin
      Ada.Wide_Text_IO.Put_Line (Message);
      if The_Context.Error < Level then
         The_Context.Error := Level;
         if Level = Fatal then
            Implementation.Set_Status
              (Asis.Errors.Environment_Error, Message);

            raise Asis.Exceptions.ASIS_Failed;
         end if;
      end if;
   end Report_Error;

   ---------------------------
   -- Set_Check_Appropriate --
   ---------------------------

   procedure Set_Check_Appropriate
     (The_Context : in out Concrete_Context_Node;
      Value       : in     Boolean) is
   begin
      The_Context.Check_Appropriate := Value;
   end Set_Check_Appropriate;

   --------------
   -- Subunits --
   --------------

   function Subunits
     (Parent_Body : in Asis.Compilation_Unit;
      The_Context : in Concrete_Context_Node)
      return Asis.Compilation_Unit_List
   is
   begin
      Check_Same_Context (Parent_Body, The_Context, "Subunits");
      return Subunits (Parent_Body);
   end Subunits;

end Asis.Gela.Contexts;



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

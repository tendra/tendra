------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with XASIS.Utils;
with Asis.Gela.Debug;
with Asis.Gela.Units;
with Asis.Gela.Pools;
with Asis.Gela.Parser;
with Asis.Gela.Errors;
with Asis.Gela.Library;
with Asis.Gela.Implicit;
with Asis.Gela.Implicit.Limited_View;
with Asis.Gela.Resolver;
with Asis.Gela.Normalizer;
with Asis.Gela.Text_Utils;
with Asis.Gela.Unit_Utils;
with Asis.Gela.Compilations;
with Asis.Gela.Element_Utils;

with Ada.Strings.Wide_Maps;

with Gela.Decoders.Create;

package body Asis.Gela.Contexts.Utils is

   procedure Normalize
     (The_Context  : in out Concrete_Context_Node;
      Limited_View : in     Boolean);

   procedure Read_Parent
     (The_Context  : in out Concrete_Context_Node;
      An_Unit      : in     Compilation_Unit;
      Limited_View : in     Boolean);

   function Parent_Name (An_Unit : Compilation_Unit) return Wide_String;

   procedure Read_Unit_Body
     (The_Context    : in out Concrete_Context_Node;
      Full_Unit_Name : in     Wide_String;
      Place          : in     Element;
      Result         :    out Compilation_Unit);

   procedure Read_Unit_Declaration
     (The_Context    : in out Concrete_Context_Node;
      Full_Unit_Name : in     Wide_String;
      Place          : in     Element;
      Limited_View   : in     Boolean;
      Result         :    out Compilation_Unit);

   procedure Read_Declaration
     (The_Context : in out Concrete_Context_Node;
      An_Unit     : in     Compilation_Unit);

   procedure Read_Withed
     (The_Context : in out Concrete_Context_Node;
      An_Unit     : in     Compilation_Unit);

   procedure Move_First_Pragmas (The_Context : in out Concrete_Context_Node);
   procedure Move_Last_Pragmas (The_Context : in out Concrete_Context_Node);

   procedure Split_Compilation
     (The_Context  : in out Concrete_Context_Node;
      Limited_View : in     Boolean);

   procedure Set_Encoding
     (The_Context   : in out Concrete_Context_Node;
      Encoding_Name : in     Wide_String);

   ------------------------
   -- Move_First_Pragmas --
   ------------------------

   procedure Move_First_Pragmas (The_Context : in out Concrete_Context_Node) is
      use Primary_Unit_Lists;
      use Secondary_Pragma_Lists;
      use Asis.Gela.Unit_Utils;

      function Find_Unit return Asis.Compilation_Unit is
         Next : Asis.Element;
      begin
         for J in 1 .. Length (The_Context.Compilation.all) loop
            Next := Get_Item (The_Context.Compilation, J);
            if Next.all in Compilation_Unit_Node'Class then
               return Asis.Compilation_Unit (Next);
            end if;
         end loop;

         return Asis.Nil_Compilation_Unit;
      end Find_Unit;

      Index     : Natural;
      Next      : Asis.Element;
      Last_Unit : Asis.Element;
   begin

      Index := Length (The_Context.Compilation.all);

      while Index > 0 loop
         Next := Get_Item (The_Context.Compilation, Index);

         if Next.all in Compilation_Unit_Node'Class then
            Last_Unit := Next;
         elsif Element_Kind (Next.all) = A_Pragma then
            Remove (The_Context.Compilation.all, Next);
            Asis.Gela.Element_Utils.Set_Pragma_Kind (Next);

            if Is_Program_Unit_Pragma (Pragma_Kind (Next.all))
              and Assigned (Last_Unit)
            then
               Add_Pragma (Last_Unit, Next);
            elsif not Is_Configuration_Pragma (Pragma_Kind (Next.all))
              and Assigned (Last_Unit)
            then
               Add_Pragma (Last_Unit, Next, True);
            elsif Is_Configuration_Pragma (Pragma_Kind (Next.all)) then
                  Make_Configuration_Unit (The_Context);
                  Add_Pragma
                    (Asis.Element (The_Context.Configuration_Unit), Next);
            elsif Is_Program_Unit_Pragma (Pragma_Kind (Next.all)) then
               Element_Utils.Set_Enclosing_Compilation_Unit (Next, Find_Unit);
               Errors.Report (Item => Next,
                              What => Errors.Error_Syntax_Misplaced_Pragma,
                              Argument1 => Pragma_Name_Image (Next.all));
            else
               Element_Utils.Set_Enclosing_Compilation_Unit (Next, Find_Unit);
               Errors.Report (Item => Next,
                              What => Errors.Warning_Syntax_Ignored_Pragma,
                              Argument1 => Pragma_Name_Image (Next.all));
            end if;
         end if;

         Index := Index - 1;
      end loop;
   end Move_First_Pragmas;

   -----------------------
   -- Move_Last_Pragmas --
   -----------------------

   procedure Move_Last_Pragmas (The_Context : in out Concrete_Context_Node) is
      use Primary_Unit_Lists;

      -------------
      -- Is_Spec --
      -------------

      function Is_Spec (Next : Asis.Element) return Boolean is
         Kind : Unit_Kinds := Not_A_Unit;
      begin
         if Next.all in Compilation_Unit_Node'Class then
            Kind := Unit_Kind (Compilation_Unit (Next).all);
         end if;

         if Kind in A_Subprogram_Declaration
           or Kind in A_Generic_Procedure .. A_Generic_Function
           or Kind in A_Generic_Unit_Instance
         then
            return True;
         else
            return False;
         end if;
      end Is_Spec;

      ---------------------
      -- Is_Right_Pragma --
      ---------------------

      function Is_Right_Pragma (Next, Spec : Asis.Element) return Boolean is

         function Direct_Name (Spec : Asis.Element) return Wide_String is
            use Asis.Gela.Units;
            Name  : constant Wide_String :=
              Unit_Full_Name (Any_Compilation_Unit_Node (Spec.all));
         begin
            return Name;

--              for I in reverse Name'Range loop
--                 if Name (I) = '.' then
--                    Index := I + 1;
--                    exit;
--                 end if;
--              end loop;

--              return Name (Index .. Name'Last);
         end Direct_Name;

         Name : constant Wide_String := Direct_Name (Spec);
         Args : constant Asis.Association_List :=
           Pragma_Argument_Associations (Next.all);
      begin
         for I in Args'Range loop
            declare
               use XASIS.Utils;
               Param : constant Asis.Element :=
                 Actual_Parameter (Args (I).all);
               Kind  : constant Asis.Expression_Kinds :=
                 Expression_Kind (Param.all);
            begin
               if (Kind = An_Identifier or Kind = A_Selected_Component)
                 and then Are_Equal_Identifiers
                            (Element_Utils.Compound_Name_Image (Param), Name)
               then
                  return True;
               end if;
            end;
         end loop;

         return False;
      end Is_Right_Pragma;

      Index : Positive := 1;
      Found : Boolean  := False;
      Spec  : Asis.Element;
      Next  : Asis.Element;
   begin
      while Index <= Length (The_Context.Compilation.all) loop
         Next := Get_Item (The_Context.Compilation, Index);

         if Is_Spec (Next) then
            Spec  := Next;
            Found := True;
            Index := Index + 1;
         elsif Element_Kind (Next.all) = A_Pragma then
            if Found and then Is_Right_Pragma (Next, Spec) then
               Remove (The_Context.Compilation.all, Next);
               Unit_Utils.Add_Pragma (Spec, Next);
            else
               Index := Index + 1;
            end if;
         else
            Found := False;
            Index := Index + 1;
         end if;
      end loop;
   end Move_Last_Pragmas;

   ---------------
   -- Normalize --
   ---------------

   procedure Normalize
     (The_Context  : in out Concrete_Context_Node;
      Limited_View : in     Boolean) is
   begin
      Move_Last_Pragmas (The_Context);
      Move_First_Pragmas (The_Context);
      Split_Compilation (The_Context, Limited_View);
   end Normalize;

   -----------------
   -- Parent_Name --
   -----------------

   function Parent_Name (An_Unit : Compilation_Unit) return Wide_String is
      Full_Name : constant Wide_String := Unit_Full_Name (An_Unit.all);
      Kind      : constant Unit_Kinds  := Unit_Kind (An_Unit.all);
   begin
      if Kind in A_Subunit then
         return Separate_Name_Image (An_Unit.all);
      elsif XASIS.Utils.Are_Equal_Identifiers (Full_Name, "Standard") then
         return "";
      else
         for I in reverse Full_Name'Range loop
            if Full_Name (I) = '.' then
               return Full_Name (1 .. I - 1);
            end if;
         end loop;
         return "Standard";
      end if;
   end Parent_Name;

   ----------------------
   -- Parse_Parameters --
   ----------------------

   procedure Parse_Parameters (The_Context : in out Concrete_Context_Node) is
      use Asis.Gela.Library;
      use Ada.Strings.Wide_Maps;
      Space  : constant Wide_Character_Set := To_Set (' ');
      Params : U.Unbounded_Wide_String := The_Context.Parameters;
      From   : Positive;
      To     : Natural;
   begin
      Clear_Search_Path;
      U.Find_Token (Params, Space, Ada.Strings.Outside, From, To);

      while To > 0 loop
         declare
            Slice : constant Wide_String := U.Slice (Params, From, To);
            Word  : constant Wide_String (1 .. Slice'Length) := Slice;
         begin
            U.Delete (Params, 1, To);
            U.Find_Token (Params, Space, Ada.Strings.Outside, From, To);

            if Word'Length >= 2 and then Word (1) = '-' then
               case Word (2) is
                  when 'I' =>
                     Add_To_Search_Path (Word (3 .. Word'Last));

                  when 'A' =>
                     pragma Assert (Debug.Set (Word (3 .. Word'Last)));
                     null;

                  when 'E' =>
                     Set_Encoding (The_Context, Word (3 .. Word'Last));

                  when others =>
                     null;
               end case;
            else
               The_Context.Current_File := U.To_Unbounded_Wide_String (Word);
            end if;
         end;
      end loop;

   end Parse_Parameters;

   ----------------------
   -- Read_Declaration --
   ----------------------

   procedure Read_Declaration
     (The_Context : in out Concrete_Context_Node;
      An_Unit     : in     Compilation_Unit)
   is
      use Asis.Gela.Unit_Utils;

      Full_Name : constant Wide_String  := Unit_Full_Name (An_Unit.all);
      Kind      : constant Unit_Kinds   := Unit_Kind (An_Unit.all);
      Class     : constant Unit_Classes := Unit_Class (An_Unit.all);
      Place     : constant Element      := Unit_Declaration (An_Unit.all);
      Result    : Asis.Compilation_Unit;
   begin
      if Kind in A_Library_Unit_Body
        and Class /= A_Public_Declaration_And_Body
      then
         Read_Unit_Declaration (The_Context, Full_Name, Place, False, Result);

         if Unit_Class (Result.all) /= A_Public_Declaration
           and Unit_Class (Result.all) /= A_Private_Declaration
         then
            Errors.Report (Item => Place,
                           What => Errors.Error_Cant_Read_Unit_Decl,
                           Argument1 => Full_Name);

            Result := Make_Nonexistent_Unit
              (The_Context.This, Full_Name, A_Nonexistent_Declaration);
         end if;

         Set_Body (Result, An_Unit);
      end if;
   end Read_Declaration;

   ------------------------------
   -- Read_File_And_Supporters --
   ------------------------------

   procedure Read_File_And_Supporters
     (The_Context  : in out Concrete_Context_Node;
      Limited_View : in     Boolean := False)
   is
      use Primary_Unit_Lists;
      State : constant Pools.Pool_State := Pools.State (Pool);

      use Asis.Gela.Compilations;

      File        : constant Wide_String := Current_File (The_Context);
      Encoding    : Encodings.Encoding := The_Context.User_Encoding;
      Buffer      : Text_Utils.Source_Buffer_Access;
      Decoder     : Text_Utils.Decoder_Access;
      Root        : Asis.Element;
      Implicit    : Asis.Compilation_Unit;
      New_Version : Compilation;
      Old_Version : constant Compilation :=
        Get_Compilation (The_Context.Compilation_List, File);
   begin
      if Library.Is_Predefined_Unit (File) then
         Encoding := Encodings.UTF_8;
      end if;

      Decoder := Decoders.Create (Encoding);
      Buffer  := Text_Utils.New_Buffer (File);

      Lines.Vectors.Clear (The_Context.Line_List);

      New_Compilation
        (The_Context.Compilation_List, File, Buffer, Decoder, New_Version);

      Parser.Run (The_Context.This,
                  Buffer.all,
                  Encoding,
                  Decoder.all,
                  The_Context.Line_List,
                  Root);

      Set_Line_List (The_Context.Compilation_List,
                     New_Version,
                     The_Context.Line_List);

      The_Context.Compilation := List (Root);

      declare
         Units : constant Compilation_Unit_List :=
           To_Compilation_Unit_List (The_Context.Compilation.all);
      begin
         for I in Units'Range loop
            Unit_Utils.Set_Compilation (Units (I), New_Version);
            Normalizer.Run (Units (I));
         end loop;

         Normalize (The_Context, Limited_View);

         for I in Units'Range loop
            Asis.Gela.Implicit.Process_Unit (Units (I));

            if Unit_Kind (Units (I).all) = A_Package then
               Implicit := Unit_Utils.Make_Limited_View_Unit
                 (The_Context.This, Units (I));

               Gela.Implicit.Limited_View.Populate
                 (Implicit, Unit_Declaration (Units (I).all));

               Secondary_Unit_Lists.Add
                 (The_Context.Limited_Views, Asis.Element (Implicit));

               Read_Parent (The_Context, Implicit, Limited_View => True);

               Resolver.Run (Implicit);
            end if;

            if not Limited_View then
               Read_Parent (The_Context, Units (I), Limited_View);
               Read_Declaration (The_Context, Units (I));
               Read_Withed (The_Context, Units (I));
               Resolver.Run (Units (I));
            end if;
         end loop;
      end;

      Drop_Compilation
        (The_Context.Compilation_List,
         Old_Version);

      Pools.Set_State (Pool, State);
   end Read_File_And_Supporters;

   -----------------
   -- Read_Parent --
   -----------------

   procedure Read_Parent
     (The_Context  : in out Concrete_Context_Node;
      An_Unit      : in     Compilation_Unit;
      Limited_View : in     Boolean)
   is
      Parent : constant Wide_String := Parent_Name (An_Unit);
      Kind   : constant Unit_Kinds  := Unit_Kind (An_Unit.all);
      Place  : constant Element     := Unit_Declaration (An_Unit.all);
      Result : Compilation_Unit;
   begin
      if Parent = "" then
         return;
      elsif Kind in A_Subunit then
         Read_Unit_Body (The_Context, Parent, Place, Result);
         Unit_Utils.Add_Subunit (Result, An_Unit);
      else
         Read_Unit_Declaration (The_Context, Parent, Place, Limited_View,
                                Result);

         Unit_Utils.Add_Child (Result, An_Unit);
      end if;
   end Read_Parent;

   --------------------
   -- Read_Unit_Body --
   --------------------

   procedure Read_Unit_Body
     (The_Context    : in out Concrete_Context_Node;
      Full_Unit_Name : in     Wide_String;
      Place          : in     Element;
      Result         :    out Compilation_Unit)
   is
      Body_Name : constant Wide_String := Library.Body_File (Full_Unit_Name);
   begin
      Result := Compilation_Unit_Body (Full_Unit_Name, The_Context);
      if Assigned (Result) then
         return;
      end if;

      if Library.File_Exists (Body_Name) then
         The_Context.Current_File := W.To_Unbounded_Wide_String (Body_Name);
      else
         Errors.Report (Item => Place,
                        What => Errors.Error_Cant_Read_Unit,
                        Argument1 => Full_Unit_Name);
         return;
      end if;

      --  recursive call --------------------------------
      Read_File_And_Supporters (The_Context);      --  <-
      --  recursive call --------------------------------

      Result := Compilation_Unit_Body (Full_Unit_Name, The_Context);

      if not Assigned (Result) then
         Result := Unit_Utils.Make_Nonexistent_Unit
           (The_Context.This, Full_Unit_Name, A_Nonexistent_Body);
      end if;

   end Read_Unit_Body;

   ---------------------------
   -- Read_Unit_Declaration --
   ---------------------------

   procedure Read_Unit_Declaration
     (The_Context    : in out Concrete_Context_Node;
      Full_Unit_Name : in     Wide_String;
      Place          : in     Element;
      Limited_View   : in     Boolean;
      Result         :    out Compilation_Unit)
   is
      Decl_Name : constant Wide_String :=
        Library.Declaration_File (Full_Unit_Name);
   begin
      if not Limited_View then
         Result := Library_Unit_Declaration (Full_Unit_Name, The_Context);
         if Assigned (Result) then
            return;
         end if;
      end if;

      Result := Contexts.Limited_View (Full_Unit_Name, The_Context);

      if Assigned (Result) then
         if not Limited_View then
            --  Turn limited view into ordinary
            Result := Corresponding_Declaration (Result.all);

            Secondary_Unit_Lists.Add
              (The_Context.Library_Unit_Declarations, Asis.Element (Result));

            Read_Parent (The_Context, Result, Limited_View => False);
            Read_Declaration (The_Context, Result);
            Read_Withed (The_Context, Result);
            Resolver.Run (Result);
         end if;

         return;
      end if;

      if Library.Has_Declaration (Full_Unit_Name) then
         The_Context.Current_File := W.To_Unbounded_Wide_String (Decl_Name);
      else
         Read_Unit_Body (The_Context, Full_Unit_Name, Place, Result);
         return;
      end if;

      --  recursive call ----------------------------------------------
      Read_File_And_Supporters (The_Context, Limited_View);      --  <-
      --  recursive call ----------------------------------------------

      if Limited_View then
         Result := Contexts.Limited_View (Full_Unit_Name, The_Context);
      else
         Result := Library_Unit_Declaration (Full_Unit_Name, The_Context);
      end if;

      if not Assigned (Result) then
         Result := Unit_Utils.Make_Nonexistent_Unit
           (The_Context.This, Full_Unit_Name, A_Nonexistent_Declaration);
      end if;
   end Read_Unit_Declaration;

   -----------------
   -- Read_Withed --
   -----------------

   procedure Read_Withed
     (The_Context : in out Concrete_Context_Node;
      An_Unit     : in     Compilation_Unit)
   is
      Clauses : constant Asis.Context_Clause_List :=
        Context_Clause_Elements (An_Unit.all);
      Result  : Asis.Compilation_Unit;
   begin
      for I in Clauses'Range loop
         if Clause_Kind (Clauses (I).all) = A_With_Clause then
            declare
               Names : constant Name_List := Clause_Names (Clauses (I).all);

               Limited_View : constant Boolean :=
                 Has_Limited (Clauses (I).all);
            begin
               for J in Names'Range loop
                  declare
                     Full_Name : constant Program_Text :=
                       XASIS.Utils.Name_Image (Names (J));
                  begin
                     Result := Nil_Compilation_Unit;
                     Read_Unit_Declaration
                       (The_Context, Full_Name, Names (J), Limited_View,
                        Result);
                  end;
               end loop;
            end;
         end if;
      end loop;
   end Read_Withed;

   ------------------
   -- Set_Encoding --
   ------------------

   procedure Set_Encoding
     (The_Context   : in out Concrete_Context_Node;
      Encoding_Name : in     Wide_String) is
   begin
      The_Context.User_Encoding :=
        Encodings.Encoding'Wide_Value (Encoding_Name);
   exception when Constraint_Error =>
      Report_Error (The_Context, Text => "Unknown encoding: " & Encoding_Name);
   end Set_Encoding;

   -----------------------
   -- Split_Compilation --
   -----------------------

   procedure Split_Compilation
     (The_Context  : in out Concrete_Context_Node;
      Limited_View : in     Boolean)
   is
      use Primary_Unit_Lists;
      use Secondary_Unit_Lists;
      use Asis.Gela.Unit_Utils;

      Index     : Natural;
      Next      : Asis.Element;
   begin
      Index := Length (The_Context.Compilation.all);

      while Index > 0 loop
         Next := Get_Item (The_Context.Compilation, Index);
         Remove (The_Context.Compilation.all, Next);

         if Limited_View then
            --  Partially processed units shouldn't be available
            null;
         elsif Next.all in Compilation_Unit_Node'Class then
            if Is_Compilation_Unit_Body (Compilation_Unit (Next)) then
               Add (The_Context.Compilation_Unit_Bodies, Next);
            else
               Add (The_Context.Library_Unit_Declarations, Next);
            end if;
         end if;

         Index := Index - 1;
      end loop;
   end Split_Compilation;

   ----------------------
   -- Compilation_List --
   ----------------------

   function Compilation_List
     (The_Context : in Asis.Context)
     return Gela.Compilations.Compilation_List
   is
      Node : Concrete_Context_Node renames
        Concrete_Context_Node (The_Context.all);
   begin
      return Node.Compilation_List;
   end Compilation_List;

end Asis.Gela.Contexts.Utils;



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

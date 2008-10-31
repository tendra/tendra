with Ada.Wide_Text_IO;
with Ada.Strings.Maps;
with Ada.Strings.Fixed;
with Ada.Strings.Wide_Fixed;
with Ada.Characters.Handling;
with Ada.Command_Line;

package body Asis.Gela.Library is

   function To_File_Name
     (Full_Name : Wide_String;
      Suffix    : String) return Wide_String;

   function Gela_Lib_Path return String;
   function Env return String is separate;

   Search_Path    : Unbounded_Wide_String;
   Path_Separator : constant Wide_String := (1 => Wide_Character'Val (10));
   File_Separator : constant Wide_Character := '/';

   ------------------------
   -- Add_To_Search_Path --
   ------------------------

   procedure Add_To_Search_Path (Path : Wide_String) is
      use Ada.Strings.Wide_Unbounded;
   begin
      if Path'Length > 0 and then Path (Path'Last) /= File_Separator then
         Search_Path := Search_Path & Path & File_Separator & Path_Separator;
      else
         Search_Path := Search_Path & Path & Path_Separator;
      end if;
   end Add_To_Search_Path;

   ---------------
   -- Body_File --
   ---------------

   function Body_File
     (Full_Name : Wide_String)
      return Wide_String
   is
   begin
      return To_File_Name (Full_Name, ".adb");
   end Body_File;

   -----------------------
   -- Clear_Search_Path --
   -----------------------

   procedure Clear_Search_Path is
      use Ada.Characters.Handling;
      Lib : constant Wide_String := To_Wide_String (Gela_Lib_Path);
   begin
      Search_Path := W.Null_Unbounded_Wide_String;
      Add_To_Search_Path (Lib);
   end Clear_Search_Path;

   ----------------------
   -- Declaration_File --
   ----------------------

   function Declaration_File
     (Full_Name : Wide_String)
      return Wide_String
   is
   begin
      return To_File_Name (Full_Name, ".ads");
   end Declaration_File;

   -------------------
   -- Gela_Lib_Path --
   -------------------

   function Gela_Lib_Path return String is
   begin
      return Env;
   end Gela_Lib_Path;

   ---------------------
   -- Has_Declaration --
   ---------------------

   function Has_Declaration
     (Full_Name : Wide_String)
      return Boolean
   is
      File_Name : constant Wide_String := Declaration_File (Full_Name);
   begin
      return File_Exists (File_Name);
   end Has_Declaration;

   -----------------
   -- File_Exists --
   -----------------

   function File_Exists (File_Name : Wide_String) return Boolean is
      use Ada.Wide_Text_IO;
      use Ada.Characters.Handling;
      File : File_Type;
   begin
      Open (File, In_File, To_String (File_Name));
      Close (File);
      return True;
   exception
      when others =>
         return False;
   end File_Exists;

   ----------------
   --  Find_File --
   ----------------

   function Find_File (File_Name : Wide_String) return Wide_String is
      use Ada.Characters.Handling;

      Path : Unbounded_Wide_String := Search_Path;
      Pos  : Natural;
   begin
      loop
         Pos := W.Index (Path, Path_Separator);

         exit when Pos = 0;

         declare
            File : constant Wide_String :=
              W.Slice (Path, 1, Pos - 1) & File_Name;
         begin
            W.Delete (Path, 1, Pos);

            if File_Exists (File) then
               return File;
            end if;
         end;
      end loop;

      return File_Name;
   end Find_File;

   ------------------------
   -- Is_Predefined_Unit --
   ------------------------

   function Is_Predefined_Unit (File_Name : Wide_String) return Boolean is
      use Ada.Characters.Handling;
      Lib : constant Wide_String := To_Wide_String (Gela_Lib_Path);
   begin
      return Ada.Strings.Wide_Fixed.Index (File_Name, Lib) > 0;
   end Is_Predefined_Unit;

   ------------------
   -- To_File_Name --
   ------------------

   function To_File_Name
     (Full_Name : Wide_String;
      Suffix    : String) return Wide_String
   is
      use Ada.Strings.Maps;
      use Ada.Strings.Fixed;
      use Ada.Characters.Handling;

      Name : constant String            := To_Lower (To_String (Full_Name));
      Repl : constant Character_Mapping := To_Mapping (".","-");
      File : constant String            := Translate (Name, Repl) & Suffix;
   begin
      return Find_File (To_Wide_String (File));
   end To_File_Name;

end Asis.Gela.Library;



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

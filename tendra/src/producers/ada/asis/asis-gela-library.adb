with Ada.Wide_Text_IO;
with Ada.Strings.Maps;
with Ada.Strings.Fixed;
with Ada.Characters.Handling;
with Ada.Command_Line;

package body Asis.Gela.Library is

   function To_File_Name
     (Full_Name : Wide_String;
      Suffix    : String) return Wide_String;

   function Gela_Lib_Path return String;

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
      use Ada.Strings;
      Cmd   : constant String := Ada.Command_Line.Command_Name;
      Slash : constant Natural :=
        Fixed.Index (Cmd, Maps.To_Set ("/\"), Going => Backward);
   begin
      if Slash = 0 then
         return "lib/";
      else
         return Cmd (Cmd'First .. Slash) & "lib/";
      end if;
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
      Std  : constant String            := Gela_Lib_Path & File;
   begin
      if File_Exists (To_Wide_String (Std)) then
         return To_Wide_String (Std);
      else
         return To_Wide_String (File);
      end if;
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

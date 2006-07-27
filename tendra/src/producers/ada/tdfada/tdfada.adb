------------------------------------------------------------------------------
--                             T D F   A d a                                --
--         Ada compiler for TenDRA distribution format (TDF)                --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Process command line options and initiate tree traversing

with Ada.Exceptions;
with Ada.Wide_Text_IO;
with Ada.Command_Line;
with Ada.Characters.Handling; use Ada.Characters.Handling;


with Asis;
with Asis.Errors;
with Asis.Exceptions;
with Asis.Implementation;
with Asis.Ada_Environments;

with Process_Context;
with TenDRA.Output;

procedure TDFAda is
   function Process_Options return Boolean;

   Input_File : Positive;

   procedure Usage is
   begin
      Ada.Wide_Text_IO.Put ("Usage: tdfada [-d] input-file");
   end Usage;

   function Process_Options return Boolean is
      use Ada.Command_Line;
   begin
      if Argument_Count /= 1 and Argument_Count /= 2 then
         Usage;
         return False;
      end if;

      if Argument_Count = 2 then
         if Argument (1) = "-d" then
            TenDRA.Output.Set_Debug (True);
         else
            Usage;
            return False;
         end if;

         Input_File := 2;
      else
         Input_File := 1;
      end if;

      return True;
   end Process_Options;

   function Input_File_Name return Wide_String is
   begin
      return To_Wide_String (Ada.Command_Line.Argument (Input_File));
   end Input_File_Name;

   My_Context                : Asis.Context;
   My_Context_Name           : Wide_String :=
     Asis.Ada_Environments.Default_Name;
   Initialization_Parameters : Wide_String := "";
   Finalization_Parameters   : Wide_String := "";
begin
   if not Process_Options then
      return;
   end if;

   Asis.Implementation.Initialize     (Initialization_Parameters);

   Asis.Ada_Environments.Associate
     (The_Context => My_Context,
      Name        => My_Context_Name,
      Parameters  => Input_File_Name);

   Asis.Ada_Environments.Open         (My_Context);
   Process_Context (The_Context => My_Context,
                    File_Name   => Input_File_Name);

   Asis.Ada_Environments.Close        (My_Context);
   Asis.Ada_Environments.Dissociate   (My_Context);
   Asis.Implementation.Finalize       (Finalization_Parameters);
exception
   when Ex : Asis.Exceptions.ASIS_Inappropriate_Context          |
             Asis.Exceptions.ASIS_Inappropriate_Container        |
             Asis.Exceptions.ASIS_Inappropriate_Compilation_Unit |
             Asis.Exceptions.ASIS_Inappropriate_Element          |
             Asis.Exceptions.ASIS_Inappropriate_Line             |
             Asis.Exceptions.ASIS_Inappropriate_Line_Number      |
             Asis.Exceptions.ASIS_Failed                         =>

      Ada.Wide_Text_IO.Put ("ASIS exception (");
      Ada.Wide_Text_IO.Put
        (To_Wide_String (Ada.Exceptions.Exception_Name (Ex)));

      Ada.Wide_Text_IO.Put (") is raised");
      Ada.Wide_Text_IO.New_Line;

      Ada.Wide_Text_IO.Put ("ASIS Error Status is ");
      Ada.Wide_Text_IO.Put
        (Asis.Errors.Error_Kinds'Wide_Image (Asis.Implementation.Status));
      Ada.Wide_Text_IO.New_Line;

      Ada.Wide_Text_IO.Put ("ASIS Diagnosis is ");
      Ada.Wide_Text_IO.New_Line;
      Ada.Wide_Text_IO.Put (Asis.Implementation.Diagnosis);
      Ada.Wide_Text_IO.New_Line;

      Ada.Wide_Text_IO.Put_Line ("ASIS exception information:");
      Ada.Wide_Text_IO.Put
        (To_Wide_String (Ada.Exceptions.Exception_Information (Ex)));

      Asis.Implementation.Set_Status;
end;



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

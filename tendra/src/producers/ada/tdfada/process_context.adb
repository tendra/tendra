with Asis;
with Asis.Elements;
with Asis.Compilation_Units;

with Ada.Strings.Fixed;
with Ada.Characters.Handling;

with States;
with Declaration;

procedure Process_Context
  (The_Context : Asis.Context;
   File_Name   : Wide_String)
is
   use Asis.Elements;
   use Asis.Compilation_Units;

   function Capsule_Name return String is
      use Ada.Strings.Fixed;
      use Ada.Characters.Handling;
      Input : String := To_String (File_Name);
      Dot   : Natural := Index (Input, ".", Ada.Strings.Backward);
   begin
      if Dot = 0 then
         return Input & ".j";
      else
         return Input (Input'First .. Dot) & "j";
      end if;
   end Capsule_Name;

   State : aliased States.State;
   List  : Asis.Compilation_Unit_List :=
     Compilation_Units (The_Context);
begin
   States.Initialize (State);

   for J in List'Range loop
      if Text_Name (List (J)) = File_Name then
         State.Unit := List (J);
         Declaration.Compile (State'Access, Unit_Declaration (List (J)));
      end if;
   end loop;

   States.Create_Capsule (State, Capsule_Name);
end Process_Context;


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

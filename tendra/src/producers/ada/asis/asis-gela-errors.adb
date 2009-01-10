------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:

with Asis.Elements;
with Asis.Compilation_Units;

package body Asis.Gela.Errors is

   ------------
   -- Report --
   ------------

   procedure Report
     (Item      : Asis.Element;
      What      : Code;
      Argument1 : Wide_String := "";
      Argument2 : Wide_String := "")
   is
      use Asis.Elements;
      use Asis.Compilation_Units;
      The_Unit    : constant Compilation_Unit :=
        Enclosing_Compilation_Unit (Item);
      The_Context : constant Context          := Enclosing_Context (The_Unit);
      The_Place   : constant Text_Position    := Start_Position (Item.all);
      The_Text    : constant Wide_String      :=
        Code'Wide_Image (What)  & " " & Argument1 & " " & Argument2;
      The_Level   : Error_Level;
   begin
      case What is
         when Success_Code =>
           The_Level := Success;
         when Warning_Code =>
           The_Level := Warning;
         when Error_Code =>
           The_Level := Error;
         when Fatal_Code =>
           The_Level := Fatal;
      end case;
      Report_Error (The_Context.all, The_Unit, The_Place, The_Text, The_Level);
   end Report;

end Asis.Gela.Errors;



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

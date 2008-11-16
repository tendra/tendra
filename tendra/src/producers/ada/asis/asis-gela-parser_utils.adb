with Asis.Gela.Elements.Assoc;
with Asis.Gela.Elements.Helpers;

package body Asis.Gela.Parser_Utils is

   ----------------
   -- Init_Token --
   ----------------

   procedure Init_Token
     (Element : in out Elements.Helpers.Token_Node;
      Line    : in     Positive;
      Column  : in     Positive;
      Length  : in     Positive;
      Image   : in     Gela_String)
   is
      use Asis.Gela.Elements.Helpers;
   begin
      Set_Start_Position (Element, (Line, Column - Length));
      Set_End_Position (Element, (Line, Column - 1));
      Set_Raw_Image (Element, Image);
   end Init_Token;

   -------------------
   -- Push_Argument --
   -------------------

   procedure Push_Argument
     (Call : in out Elements.Expr.Function_Call_Node;
      Arg  : in     Asis.Element)
   is
      use Asis.Gela.Elements.Expr;
      use Asis.Gela.Elements.Assoc;

      Assoc : constant Asis.Association := Function_Call_Parameters (Call) (1);
      Node  : Parameter_Association_Node renames
         Parameter_Association_Node (Assoc.all);
      Left  : constant Asis.Element := Actual_Parameter (Assoc.all);
   begin
      Set_Start_Position (Node, Start_Position (Arg.all));
      Set_Start_Position (Call, Start_Position (Arg.all));
      if Assigned (Left) then
         Push_Argument
           (Call => Function_Call_Node (Left.all),
            Arg  => Arg);
      else
         Set_Actual_Parameter (Node, Arg);
         Set_End_Position (Node, End_Position (Arg.all));
      end if;
   end Push_Argument;

   -------------------
   -- Push_Argument --
   -------------------

   procedure Push_Argument
     (Call : in out Elements.Expr.Base_Short_Circuit_Node'Class;
      Arg  : in     Asis.Element)
   is
      use Asis.Gela.Elements.Expr;
      Left : constant Asis.Element :=
        Short_Circuit_Operation_Left_Expression (Call);
   begin
      if Assigned (Left) then
         Push_Argument
           (Call => Base_Short_Circuit_Node'Class (Left.all),
            Arg  => Arg);
      else
         Set_Short_Circuit_Operation_Left_Expression (Call, Arg);
      end if;
      Set_Start_Position (Call, Start_Position (Arg.all));
   end Push_Argument;

end Asis.Gela.Parser_Utils;



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

------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Helper procedures to replace one AST node with other

package Asis.Gela.Replace is

   function Could_Be_Positional_Array_Aggregate
     (Item : Asis.Element) return Boolean;

   procedure Operator_Symbol_To_String_Literal (Item : in out Asis.Element);
   procedure Record_To_Parameter_Association (Item : in out Asis.Element);
   procedure Identifier_To_Enumeration_Literal (Item : in out Asis.Element);
   procedure Expression_To_Function_Call (Item : in out Asis.Element);
   procedure Function_To_Indexed_Component (Item : in out Asis.Element);
   procedure Function_To_Slice (Item : in out Asis.Element);
   procedure Function_To_Type_Conversion (Item : in out Asis.Element);
   procedure Record_To_Array_Association (Item : in out Asis.Element);
   procedure Function_To_Constraint (Item : in out Asis.Element);
   procedure Procedure_To_Entry_Call (Item : in out Asis.Element);

   procedure Record_To_Array_Aggregate
     (Item       : in out Asis.Element;
      Positional : in     Boolean);

   procedure Integer_Real_Number (Item : in out Asis.Element);

   procedure To_Conditional_Entry_Call (Element : in out Asis.Statement);
   procedure To_Timed_Entry_Call (Element : in out Asis.Statement);

   procedure To_Enumeration_Rep_Clause (Element : in out Asis.Statement);

   procedure Procedure_To_Indexed_Entry_Call (Element : in out Asis.Statement);

end Asis.Gela.Replace;



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

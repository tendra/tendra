------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Collect error kinds and procedure to report errors

package Asis.Gela.Errors is

    type Code is
      (Success_Dummy,
       Warning_Syntax_Ignored_Pragma,
       Error_Syntax_Assoc_In_Attribute,
       Error_Syntax_Too_Many_Constraints,
       Error_Syntax_Bad_Constraints,
       Error_Syntax_Back_Identifier_Exists,
       Error_Syntax_Index_Exists,
       Error_Syntax_Not_Empty_Generic,
       Error_Syntax_Not_Empty_Profile,
       Error_Syntax_Not_Empty_Result,
       Error_Syntax_Operator_In_Accept,
       Error_Syntax_Guard_Exists,
       Error_Syntax_Expected_Direct_Name,
       Error_Syntax_Misplaced_Mod_Clause,
       Error_Syntax_Misplaced_Pragma,
       Error_Syntax_Misplaced_Association,
       Error_Syntax_Misplaced_Private,
       Error_Syntax_Null_Function,
       Error_Syntax_Bad_Back_Identifier,
       Error_No_Interprentation,
       Error_Ambiguous_Interprentation,
       Error_Unknown_Name,
       Error_Unknown_Type,
       Error_Must_Be_Completion,
       Error_Name_Redeclaration,
       Error_Generic_Expected,
       Error_No_Association_Found,
       Error_No_Such_Stub,
       Error_Bad_Pragma_Argument,
       Error_Cant_Read_Unit_Decl,
       Error_Cant_Read_Unit,
       Fatal_Dummy);

    subtype Success_Code is Code range Success_Dummy .. Success_Dummy;
    subtype Warning_Code is Code range
      Warning_Syntax_Ignored_Pragma .. Warning_Syntax_Ignored_Pragma;

    subtype Error_Code   is Code range
      Error_Syntax_Assoc_In_Attribute .. Error_Cant_Read_Unit;

    subtype Fatal_Code   is Code range Fatal_Dummy .. Fatal_Dummy;

    procedure Report
     (Item      : Asis.Element;
      What      : Code;
      Argument1 : Wide_String := "";
      Argument2 : Wide_String := "");

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

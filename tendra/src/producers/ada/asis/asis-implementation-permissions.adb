------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:
--  Purpose:
--  Provide suitable values for permissions

package body Asis.Implementation.Permissions is

   ------------------------------
   -- Attributes_Are_Supported --
   ------------------------------

   function Attributes_Are_Supported return Boolean is
   begin
      return False;
   end Attributes_Are_Supported;

   ------------------------------------------
   -- Call_Statement_Parameters_Normalized --
   ------------------------------------------

   function Call_Statement_Parameters_Normalized return Boolean is
   begin
      return False;
   end Call_Statement_Parameters_Normalized;

   -------------------------------
   -- Default_In_Mode_Supported --
   -------------------------------

   function Default_In_Mode_Supported return Boolean is
   begin
      return True;
   end Default_In_Mode_Supported;

   ------------------------------------------
   -- Discriminant_Associations_Normalized --
   ------------------------------------------

   function Discriminant_Associations_Normalized return Boolean is
   begin
      return False;
   end Discriminant_Associations_Normalized;

   -----------------------------------------
   -- Function_Call_Parameters_Normalized --
   -----------------------------------------

   function Function_Call_Parameters_Normalized return Boolean is
   begin
      return False;
   end Function_Call_Parameters_Normalized;

   ------------------------------------
   -- Generic_Actual_Part_Normalized --
   ------------------------------------

   function Generic_Actual_Part_Normalized return Boolean is
   begin
      return False;
   end Generic_Actual_Part_Normalized;

   ---------------------------------------
   -- Generic_Macro_Expansion_Supported --
   ---------------------------------------

   function Generic_Macro_Expansion_Supported return Boolean is
   begin
      return True;
   end Generic_Macro_Expansion_Supported;

   -----------------------------------
   -- Implicit_Components_Supported --
   -----------------------------------

   function Implicit_Components_Supported return Boolean is
   begin
      return False;
   end Implicit_Components_Supported;

   --------------------------------------
   -- Inherited_Declarations_Supported --
   --------------------------------------

   function Inherited_Declarations_Supported return Boolean is
   begin
      return False;
   end Inherited_Declarations_Supported;

   -------------------------------------
   -- Inherited_Subprograms_Supported --
   -------------------------------------

   function Inherited_Subprograms_Supported return Boolean is
   begin
      return True;
   end Inherited_Subprograms_Supported;

   -----------------------------
   -- Is_Commentary_Supported --
   -----------------------------

   function Is_Commentary_Supported return Boolean is
   begin
      return False;  --  TODO
   end Is_Commentary_Supported;

   --------------------------------------------------
   -- Is_Formal_Parameter_Named_Notation_Supported --
   --------------------------------------------------

   function Is_Formal_Parameter_Named_Notation_Supported return Boolean is
   begin
      return True;
   end Is_Formal_Parameter_Named_Notation_Supported;

   ------------------------------
   -- Is_Line_Number_Supported --
   ------------------------------

   function Is_Line_Number_Supported return Boolean is
   begin
      return True;
   end Is_Line_Number_Supported;

   ------------------------------
   -- Is_Prefix_Call_Supported --
   ------------------------------

   function Is_Prefix_Call_Supported return Boolean is
   begin
      return True;
   end Is_Prefix_Call_Supported;

   ---------------------------------------
   -- Is_Span_Column_Position_Supported --
   ---------------------------------------

   function Is_Span_Column_Position_Supported return Boolean is
   begin
      return True;
   end Is_Span_Column_Position_Supported;

   ------------------------------------
   -- Object_Declarations_Normalized --
   ------------------------------------

   function Object_Declarations_Normalized return Boolean is
   begin
      return False;
   end Object_Declarations_Normalized;

   -------------------------------------
   -- Predefined_Operations_Supported --
   -------------------------------------

   function Predefined_Operations_Supported return Boolean is
   begin
      return True;
   end Predefined_Operations_Supported;

   ----------------------------------------------
   -- Record_Component_Associations_Normalized --
   ----------------------------------------------

   function Record_Component_Associations_Normalized return Boolean is
   begin
      return False;
   end Record_Component_Associations_Normalized;

end Asis.Implementation.Permissions;



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

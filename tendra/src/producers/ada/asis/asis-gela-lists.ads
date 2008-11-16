------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Provide lists to store elements of given kinds

with Asis.Gela.Pools;
with Asis.Gela.Base_Lists; use Asis.Gela.Base_Lists;
with Asis.Gela.Base_Lists.Primary;

package Asis.Gela.Lists is
   generic package Primary_Lists renames Asis.Gela.Base_Lists.Primary;

--   pragma Preelaborate;
   Pool : Asis.Gela.Pools.Storage_Pool renames Base_Lists.Pool;

   -------------------
   -- Primary_Lists --
   -------------------

   package Primary_Association_Lists is
      new Primary_Lists ((1 => An_Association));

   package Primary_Choise_Lists is
      new Primary_Lists ((An_Expression, A_Definition));
   --------------------------
   --      An_Expression
   --  Definition_Kinds:
   --      A_Discrete_Range
   --      An_Others_Choice

   package Primary_Clause_Lists is
      new Primary_Lists ((A_Clause, A_Pragma, Not_An_Element));

   package Primary_Declaration_Lists is
      new Primary_Lists ((A_Declaration, A_Clause, A_Pragma, A_Definition));
   --  Definition_Kinds:
   --      A_Null_Component
   --      A_Variant_Part

   package Primary_Defining_Name_Lists is
      new Primary_Lists ((1 => A_Defining_Name));

   package Primary_Definition_Lists is
      new Primary_Lists ((1 => A_Definition));

   package Primary_Expression_Lists is
      new Primary_Lists ((1 => An_Expression));

   package Primary_Handler_Lists is
      new Primary_Lists ((An_Exception_Handler, A_Pragma));

   package Primary_Identifier_Lists is
      new Primary_Lists ((1 => An_Expression));
   ----------------------------------------------------------
   --  Expression_Kinds:
   --      An_Identifier for Discriminant_Selector_Names
   --      A_Selected_Component for Index_Subtype_Definitions

   package Primary_Parameter_Lists is
      new Primary_Lists ((1 => A_Declaration));
   -------------------------------
   --  Declaration_Kinds:
   --       A_Parameter_Specification

   package Primary_Path_Lists is
      new Primary_Lists ((A_Path, A_Pragma));

   package Primary_Statement_Lists is
      new Primary_Lists ((A_Statement, A_Pragma));

   package Primary_Pragma_Lists renames Primary_Statement_Lists;

   package Primary_Variant_Lists is
      new Primary_Lists ((A_Definition, A_Pragma));
   -------------------------------
   --  Definition_Kinds:
   --      A_Variant

   package Primary_Unit_Lists is
      new Primary_Lists ((Not_An_Element, A_Pragma));

   ---------------------
   -- Secondary_Lists --
   ---------------------

   package Secondary_Association_Lists is
      new Secondary_Lists ((1 => An_Association));

   package Secondary_Clause_Lists is
      new Secondary_Lists ((1 => A_Clause));
   -------------------------------
   --  Clause_Kinds:
   --    A_Representation_Clause

   package Secondary_Declaration_Lists is
      new Secondary_Lists ((1 => A_Declaration));

   package Secondary_Definition_Lists is
      new Secondary_Lists ((1 => A_Defining_Name));

   package Secondary_Pragma_Lists is
      new Secondary_Lists ((1 => A_Pragma));

   package Secondary_Reference_Lists is
      new Secondary_Lists ((1 => An_Expression));
   -------------------------------
   --  Contains Expression_Kinds:
   --      An_Identifier
   --      An_Operator_Symbol
   --      A_Character_Literal
   --      An_Enumeration_Literal

   package Secondary_Unit_Lists is
      new Secondary_Lists ((1 => Not_An_Element));

end Asis.Gela.Lists;


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

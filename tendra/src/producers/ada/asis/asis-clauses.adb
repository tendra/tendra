------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Procedural wrapper over Object-Oriented ASIS implementation

package body Asis.Clauses is

   ------------------
   -- Clause_Names --
   ------------------

   function Clause_Names
     (Clause : in Asis.Element)
      return Asis.Name_List
   is
   begin
      Check_Nil_Element (Clause, "Clause_Names");
      return Clause_Names (Clause.all);
   end Clause_Names;

   -------------------------------
   -- Component_Clause_Position --
   -------------------------------

   function Component_Clause_Position
     (Clause : in Asis.Component_Clause)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Clause, "Component_Clause_Position");
      return Component_Clause_Position (Clause.all);
   end Component_Clause_Position;

   ----------------------------
   -- Component_Clause_Range --
   ----------------------------

   function Component_Clause_Range
     (Clause : in Asis.Component_Clause)
      return Asis.Discrete_Range
   is
   begin
      Check_Nil_Element (Clause, "Component_Clause_Range");
      return Component_Clause_Range (Clause.all);
   end Component_Clause_Range;

   -----------------------
   -- Component_Clauses --
   -----------------------

   function Component_Clauses
     (Clause : in Asis.Representation_Clause;
      Include_Pragmas : in Boolean := False)
      return Asis.Component_Clause_List
   is
   begin
      Check_Nil_Element (Clause, "Component_Clauses");
      return Component_Clauses (Clause.all, Include_Pragmas);
   end Component_Clauses;

   ---------------------------
   -- Mod_Clause_Expression --
   ---------------------------

   function Mod_Clause_Expression
     (Clause : in Asis.Representation_Clause)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Clause, "Mod_Clause_Expression");
      return Mod_Clause_Expression (Clause.all);
   end Mod_Clause_Expression;

   --------------------------------------
   -- Representation_Clause_Expression --
   --------------------------------------

   function Representation_Clause_Expression
     (Clause : in Asis.Representation_Clause)
      return Asis.Expression
   is
   begin
      Check_Nil_Element (Clause, "Representation_Clause_Expression");
      return Representation_Clause_Expression (Clause.all);
   end Representation_Clause_Expression;

   --------------------------------
   -- Representation_Clause_Name --
   --------------------------------

   function Representation_Clause_Name
     (Clause : in Asis.Clause)
      return Asis.Name
   is
   begin
      Check_Nil_Element (Clause, "Representation_Clause_Name");
      return Representation_Clause_Name (Clause.all);
   end Representation_Clause_Name;

end Asis.Clauses;



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

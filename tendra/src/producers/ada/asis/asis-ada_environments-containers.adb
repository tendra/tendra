------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$:
--  Purpose:
--  Trivial implementation of ASIS Ada_Environments.Containers

with Asis.Compilation_Units;

package body Asis.Ada_Environments.Containers is
   package C renames Asis.Compilation_Units;

   -----------------------------
   -- Compilation_Unit_Bodies --
   -----------------------------

   function Compilation_Unit_Bodies
     (The_Container : in Container)
      return Asis.Compilation_Unit_List
   is
   begin
      return C.Compilation_Unit_Bodies (The_Container.The_Context);
   end Compilation_Unit_Bodies;

   -----------------------
   -- Compilation_Units --
   -----------------------

   function Compilation_Units
     (The_Container : in Container)
      return Asis.Compilation_Unit_List
   is
   begin
      return C.Compilation_Units (The_Container.The_Context);
   end Compilation_Units;

   -------------------------
   -- Defining_Containers --
   -------------------------

   function Defining_Containers
     (The_Context : in Asis.Context)
      return Container_List
   is
   begin
      return (1 => (The_Context => The_Context));
   end Defining_Containers;

   -----------------------
   -- Enclosing_Context --
   -----------------------

   function Enclosing_Context
     (The_Container : in Container)
      return Asis.Context
   is
   begin
      return The_Container.The_Context;
   end Enclosing_Context;

   --------------
   -- Is_Equal --
   --------------

   function Is_Equal
     (Left  : in Container;
      Right : in Container)
      return Boolean
   is
   begin
      return Is_Identical (Left, Right);
   end Is_Equal;

   ------------------
   -- Is_Identical --
   ------------------

   function Is_Identical
     (Left  : in Container;
      Right : in Container)
      return Boolean
   is
   begin
      return Is_Equal (Left.The_Context, Right.The_Context);
   end Is_Identical;

   -------------------------------
   -- Library_Unit_Declarations --
   -------------------------------

   function Library_Unit_Declarations
     (The_Container : in Container)
      return Asis.Compilation_Unit_List
   is
   begin
      return C.Library_Unit_Declarations (The_Container.The_Context);
   end Library_Unit_Declarations;

   ----------
   -- Name --
   ----------

   function Name (The_Container : in Container) return Wide_String is
   begin
      return Name (The_Container.The_Context);
   end Name;

end Asis.Ada_Environments.Containers;



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

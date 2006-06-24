------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Asis.Gela starts package hierarhy where implemented Object-Oriented Asis.
--  Standard procedural Asis implemented as set of wrappers over dispatching
--  calls of tagged type methods.
--
--  Root of AST nodes Element_Node is declared in private part of Asis
--  package. Its primitive operations correspond to functions defined
--  in ASIS standard. Their default implementations raise
--  Inappropriate_Element exception. Types in Asis.Gela.Elements
--  extend Element_Node and provide operations correspond to particular
--  Element_Kind.
--
--  When context is openned parser read units and construct AST from
--  children of Element_Node. A few passes over resulting AST
--  fix syntax simplification, apply resolution rules, creates
--  implicit elements and expands generic instantiations.

with Ada.Strings.Wide_Unbounded;

private
package Asis.Gela is
   pragma Preelaborate;

   type Fuzzy_Boolean is (False, True, Unknown);

   function Next_Hash return Asis.ASIS_Integer;

   package W renames Ada.Strings.Wide_Unbounded;
   subtype Unbounded_Wide_String is W.Unbounded_Wide_String;

end Asis.Gela;


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

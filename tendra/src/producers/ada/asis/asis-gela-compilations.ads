------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Implement abstraction of a compilation of a source. Multiple compilation
--  of the same source differ in version. It used to support IDE where
--  source is changed and recompiled frequntly.

with Asis.Gela.Pools;
with Ada.Strings.Wide_Unbounded;

package Asis.Gela.Compilations is

   type Compilation      is private;
   type Compilation_List is private;

   procedure Initialize (List :    out Compilation_List);
   procedure Finalize   (List : in out Compilation_List);

   function Get_Compilation
     (List : in Compilation_List;
      File : in Wide_String) return Compilation;

   procedure New_Compilation
     (List : in out Compilation_List;
      File : in     Wide_String;
      Item :    out Compilation);

   procedure Drop_Compilation
     (List : in out Compilation_List;
      Item : in     Compilation);

   function Enclosing (Object : Asis.Element) return Compilation;
   function Enclosing (Object : Asis.Compilation_Unit) return Compilation;

   function Valid_Version
     (List : Compilation_List;
      Item : Compilation) return Boolean;
   pragma Inline (Valid_Version);

private
   package U renames Ada.Strings.Wide_Unbounded;

   type Version_Count is mod 2 ** 16;

   type Compilation_Node is record
      File_Name : U.Unbounded_Wide_String;
      Version   : Version_Count;
      Pool      : Pools.Pool_State;
   end record;

   type Compilation_Count is range 0 .. 2 ** 15 - 1;

   subtype Compilation_Index is
     Compilation_Count range 1 .. Compilation_Count'Last;

   type Compilation_Array is
     array (Compilation_Index range <>) of Compilation_Node;

   type Compilation_List_Node (Length : Compilation_Index) is record
      Last  : Compilation_Count;
      Nodes : Compilation_Array (1 .. Length);
   end record;

   type Compilation is record
      Index   : Compilation_Index;
      Version : Version_Count;
   end record;

   type Compilation_List is access all Compilation_List_Node;

end Asis.Gela.Compilations;


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

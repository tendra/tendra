------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Two passes to resolve names:
--  First (down to) Up collects possible interpretations of an expression
--  Second (up to) Down fixes AST to correspond chosen interpretation

with Gela.Containers.Stacks;    use Gela;
with Asis.Gela.Overloads.Types; use Asis.Gela.Overloads.Types;

package Asis.Gela.Overloads.Walk is

   type Up_Resolver is limited private;

   procedure Before
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Up_Resolver);

   procedure After
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Up_Resolver);

   function Get_Interpretations
     (Resolver : in     Up_Resolver) return Up_Interpretation_Set;

   function Get_Implicits
     (Resolver : in     Up_Resolver) return Implicit_Set;

   type Down_Resolver is limited private;

   procedure Before
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Down_Resolver);

   procedure After
     (Element  : in out Asis.Element;
      Control  : in out Traverse_Control;
      Resolver : in out Down_Resolver);

   procedure Set_Interpretation
     (Resolver : in out Down_Resolver;
      Item     : in     Down_Interpretation);

   procedure Copy_Store_Set
     (Source  : in     Up_Resolver;
      Target  : in out Down_Resolver);

   procedure Destroy_Store_Set
     (Source  : in out Up_Resolver);

   procedure Set_Declaration
     (Element : in out Asis.Identifier;
      Decl    : in     Asis.Declaration);

   procedure Check_Association (Element : in out Asis.Element);

private

   package U is new Containers.Stacks (Up_Interpretation_Set);

   type Up_Resolver is limited record
      Stack    : U.Stack;
      Store    : Stored_Sets := Create;
      Implicit : Implicit_Set := Create;
   end record;

   package D is new Containers.Stacks (Down_Interpretation);

   type Down_Resolver is limited record
      Stack    : D.Stack;
      Store    : Stored_Sets;
      Implicit : Implicit_Set;
   end record;

   --  Common subroutines for child packages

   function Is_Subprogram (Decl : Asis.Declaration) return Boolean;

   function Is_Expanded_Name (Item : Asis.Element) return Boolean;

   procedure Find_Formal_Index
     (Params       : in     Asis.Association_List;
      Actual_Index : in     List_Index;
      Profile      : in     Asis.Parameter_Specification_List;
      Formal_Index :    out List_Index;
      Found        :    out Boolean);

   function Get_Formal_Parameter
     (Params  : Asis.Association_List;
      Index   : List_Index) return Asis.Identifier;

   function Get_Actual_Parameter
     (Params  : Asis.Association_List;
      Index   : List_Index) return Asis.Expression;

   procedure Drop_One (Resolver : in out Up_Resolver);

   --  function Get_Array_Index_Type
   --  (Tipe  : Type_Info;
   --  Index : Asis.List_Index := 1) return Tipe_Info;

--   function Get_Array_Element_Type
--     (Tipe : Asis.Element) return Asis.Declaration;

   function Could_Be_Positional_Array_Aggregate
     (Item : Asis.Element) return Boolean;

   function Could_Be_Named_Array_Aggregate
     (Item : Asis.Element) return Boolean;

   function Could_Be_Record_Aggregate
     (Item      : Asis.Element;
      Extension : Boolean) return Boolean;

   function Get_Call_Parameters (Element : Asis.Element )
     return Asis.Association_List;

end Asis.Gela.Overloads.Walk;


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

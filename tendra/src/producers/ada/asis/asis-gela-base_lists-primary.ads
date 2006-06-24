------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Provide Primary_Lists generic.
--  Instances of these generic are constrained with permited Element_Kinds.
--
--  Primary_List owns its elements. It is used to implement syntax properties
--  such as Body_Statements. An Element could be only in one Primary_List.
--

generic
   Allowed : in Element_Kind_List;
package Asis.Gela.Base_Lists.Primary is

   type List_Node is new Primary_Base_List_Node with private;

   type List is access all List_Node;
   for List'Storage_Pool use Pool;

   procedure Add
     (Container : in out List_Node;
      Item      : in     Element);

   procedure Add_After
     (Container : in out List_Node;
      Target    : in     Element;
      Item      : in     Element);

   function To_Element_List
     (Item            : List;
      Include_Pragmas : Boolean)
     return Asis.Element_List;

   function To_Compilation_Unit_List (Item : List)
                                     return Asis.Compilation_Unit_List;

   procedure Destroy (Item : in out List);

   function Deep_Copy
     (Items  : in Asis.Element_List;
      Cloner : in Cloner_Class;
      Parent : in Asis.Element) return Asis.Element;

private

   type List_Node is new Primary_Base_List_Node with null record;

end Asis.Gela.Base_Lists.Primary;


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

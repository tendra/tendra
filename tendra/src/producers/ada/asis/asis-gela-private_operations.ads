------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA$
--  Purpose:
--  Private operations implementation.

with Asis.Gela.Classes;
with Asis.Gela.Visibility;

with Gela; use Gela;
with Gela.Containers.Lists;
with Gela.Embeded_Links.Lists;

package Asis.Gela.Private_Operations is

   type Package_Data is private;
   type Package_Data_Stack is limited private;

   function Create (Element : in Asis.Declaration) return Package_Data;

   procedure Check_Type
     (Element : in     Asis.Declaration;
      Data    : in     Package_Data;
      Point   : in out Visibility.Point);

   procedure On_Private_Part
     (Element : in     Asis.Declaration;
      Point   : in out Visibility.Point);

   procedure On_Package_Body
     (Element : in     Asis.Declaration;
      Point   : in out Visibility.Point);

   procedure Push
     (Stack : in out Package_Data_Stack;
      Item  : in     Package_Data);

   procedure Pop (Stack : in out Package_Data_Stack);

   function Top (Stack : Package_Data_Stack) return Package_Data;

private

   package Type_Info_Lists is
      new Containers.Lists (Classes.Type_Info, Classes.Is_Equal);

   type Type_Data;

   type Type_Data_Access is access all Type_Data;

   type Type_Data is record
      Info      : Classes.Type_Info;
      Dependent : Type_Info_Lists.List;
      Next      : Type_Data_Access;
   end record;

   function  Get_Next (Item : Type_Data_Access) return Type_Data_Access;
   procedure Set_Next (Item, Next : Type_Data_Access);

   package Type_Data_List is
      new Embeded_Links.Lists (Type_Data, Type_Data_Access);

   type Package_Data_Node is record
      Element : Asis.Element;
      Types   : Type_Data_List.List;
      Next    : Package_Data;
   end record;

   type Package_Data is access all Package_Data_Node;

   function  Get_Next (Item : Package_Data) return Package_Data;
   procedure Set_Next (Item, Next : Package_Data);

   package Package_Data_List is
      new Embeded_Links.Lists (Package_Data_Node, Package_Data);

   type Package_Data_Stack is new Package_Data_List.List;

end Asis.Gela.Private_Operations;

------------------------------------------------------------------------------
--  Copyright (c) 2008, Maxim Reznik
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

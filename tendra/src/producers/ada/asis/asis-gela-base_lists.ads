------------------------------------------------------------------------------
--                           G E L A   A S I S                              --
--       ASIS implementation for Gela project, a portable Ada compiler      --
--                     http://www.ten15.org/wiki/Ada                        --
--                     - - - - - - - - - - - - - - -                        --
--            Read copyright and license at the end of this file            --
------------------------------------------------------------------------------
--  $TenDRA: asis-ada_environments.adb 2270 2005-11-04 19:51:32Z maxr $
--  Purpose:
--  Provide Primary_Lists and Secondary_Lists generics.
--  Instances of these generics are constrained with permited Element_Kinds.
--
--  Primary_List owns its elements. It is used to implement syntax properties
--  such as Body_Statements. An Element could be only in one Primary_List.
--
--  Secondary_List contains references to Elements. It is used to implement
--  semantic properties such as Corresponding_Representation_Clauses.

with Gela.Containers.Lists;
with Gela.Embeded_Links.Lists; use Gela;

with Asis.Gela.Pools;

package Asis.Gela.Base_Lists is

   Pool : Asis.Gela.Pools.Storage_Pool;

   -----------------------
   -- Element_Kind_List --
   -----------------------

   type Element_Kind_List is array (Positive range <>) of Element_Kinds;

   ----------------------------
   -- Primary_Base_List_Node --
   ----------------------------

   type Primary_Base_List_Node is abstract new Element_Node with private;

   type Primary_Base_List is access all Primary_Base_List_Node'Class;

   procedure Add
     (Container : in out Primary_Base_List_Node;
      Item      : in     Element);

   procedure Add_After
     (Container : in out Primary_Base_List_Node;
      Target    : in     Element;
      Item      : in     Element);

   function To_Element_List
     (Item : Primary_Base_List_Node)
     return Asis.Element_List;

   function To_Element_List
     (Item            : Primary_Base_List_Node;
      Include_Pragmas : Boolean)
     return Asis.Element_List;

   function To_Pragma_List
     (Item : Primary_Base_List_Node)
     return Asis.Element_List;

   function To_Compilation_Unit_List
     (Item : Primary_Base_List_Node)
     return Asis.Compilation_Unit_List;

   function Length
     (Item : Primary_Base_List_Node)
     return Natural;

   function Get_Item
     (Item  : access Primary_Base_List_Node;
      Index : Positive)
     return Element;

   procedure Remove
     (Container : in out Primary_Base_List_Node;
      Item      : in     Element);

   function Start_Position
     (Element : Primary_Base_List_Node)
      return Text_Position;

   function End_Position
     (Element : Primary_Base_List_Node)
      return Text_Position;

   function Element_Kind
     (Element : in Primary_Base_List_Node)
      return Element_Kinds;

   function Get_Next
     (Item : Primary_Base_List_Node)
      return Element;

   procedure Set_Next
     (Item : in out Primary_Base_List_Node;
      Next : in     Element);

   procedure Set_Start_Position
     (Element : in out Primary_Base_List_Node'Class;
      Value   : in     Asis.Text_Position);

   procedure Set_End_Position
     (Element : in out Primary_Base_List_Node'Class;
      Value   : in     Asis.Text_Position);

   function Find
     (Container : Primary_Base_List_Node;
      Item      : Element)
     return Boolean;

   function Is_List (Item : Primary_Base_List_Node) return Boolean;

   function Clone
     (Item   : Primary_Base_List_Node;
      Parent : Asis.Element) return Asis.Element;

   ---------------------
   -- Secondary_Lists --
   ---------------------

   generic

      Allowed : in Element_Kind_List;

   package Secondary_Lists is

      type List_Node is limited private;

      function Length (Item : List_Node) return Natural;

      function Get
        (Item  : List_Node;
         Index : Positive)
        return Asis.Element;

      function To_Element_List
        (Item : List_Node)
        return Asis.Element_List;

      function To_Element_List
        (Item            : List_Node;
         Include_Pragmas : Boolean)
        return Asis.Element_List;

      function To_Pragma_List
        (Item : List_Node)
        return Asis.Element_List;

      function To_Compilation_Unit_List
        (Item : List_Node)
        return Asis.Compilation_Unit_List;

      procedure Add
        (Container : in out List_Node;
         Item      : in     Element);

      procedure Remove
        (Container : in out List_Node;
         Item      : in     Element);

      procedure Set
        (Container : in out List_Node;
         Items     : in     Element_List);

   private
      package Element_Lists is new Containers.Lists (Element, Is_Equal);
      type List_Node is new Element_Lists.List;
   end Secondary_Lists;

private
   function  Get_Next (Item : Element) return Element;
   procedure Set_Next (Item, Next : Element);

   package ER_Element_Lists is
      new Embeded_Links.Lists (Element_Node'Class, Element);

   type Primary_Base_List_Node is abstract new Element_Node with record
      Content        : ER_Element_Lists.List;
      Last_Index     : Natural;
      Last_Item      : Element;
      Length         : Natural := 0;
      Start_Position : aliased Asis.Text_Position;
      End_Position   : aliased Asis.Text_Position;
   end record;

   procedure Check_Item_Kind
      (Item    : in Element;
       Allowed : in Element_Kind_List);

end Asis.Gela.Base_Lists;


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

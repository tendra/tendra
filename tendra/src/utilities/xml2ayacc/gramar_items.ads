with Ada.Strings.Unbounded;

package Gramar_Items is

   -------------
   -- Wrapper --
   -------------

   type Wrapper is private;

   function Node_Name      (Object : Wrapper) return String;
   function Parent         (Object : Wrapper) return Wrapper;
   function Item_Index     (Object : Wrapper) return Natural;
   function Object_Name    (Object : Wrapper) return String;
   function User_Attr_Name (Object : Wrapper) return String;
   function Top            (Object : Wrapper) return Boolean;
   function Position       (Object : Wrapper) return String;
   function Wrapper_Index  (Object : Wrapper) return Natural;

   ----------
   -- Item --
   ----------

   type Item is abstract tagged limited private;
   type Item_Ptr is access all Item'Class;

   function Item_Name (Object : Item) return String is abstract;
   function Node_Name (Object : Item) return String;
   function User_Attr (Object : Item) return String;
   function Choise    (Object : Item) return String;
   function Parent    (Object : Item) return Wrapper;
   function Create_Node (Object : Item) return String;
   function Trait_Name  (Object : Item) return String;
   function Value     (Object : Item) return String;

   --------------
   -- Sequence --
   --------------

   type Sequence is private;

   function Count (Item : Sequence) return Natural;

   function Get_Item
     (Object : Sequence;
      Index  : Positive)
      return Item_Ptr;

   function Pass_Through (Item : Sequence) return Boolean;
   function Node_Name    (Item : Sequence) return String;
   function Infix        (Item : Sequence) return String;
   function True_Node    (Item : Sequence) return String;
   function False_Node   (Item : Sequence) return String;

   function Find_First_Reference (Item : Sequence) return Natural;
   function Find_First_List (Item : Sequence) return Natural;
   function Choise_Item_Index (Item : Sequence) return Natural;

   function Rule_Name (Seq : Sequence) return String;

   function Is_Item_And_List (Seq : Sequence) return Boolean;
   function Item_Of_List_Index (Seq : Sequence) return Natural;
   function List_For_Item_Index (Seq : Sequence) return Natural;

   function Wrap_Count  (Item : Sequence) return Natural;

   function Get_Wrapper
     (Seq   : Sequence;
      Index : Positive) return Wrapper;

   ----------
   -- Rule --
   ----------

   type Rule is private;

   function Name (Item : Rule) return String;

   function Count (Item : Rule) return Natural;

   function Get_Alternative
     (Item  : Rule;
      Index : Positive)
      return Sequence;

   function Node_Name (Item : Rule) return String;

   ---------------
   -- Reference --
   ---------------

   type Reference is new Item with private;

   function Name (Item : Reference) return String;
   function Is_Token (Item : Reference) return Boolean;
   function Item_Name (Object : Reference) return String;
   function Node_Name (Object : Reference) return String;

   ----------
   -- Body --
   ----------

   type Option is new Item with private;

   function Items
     (Item  : Option;
      Index : Positive := 1)   return Sequence;

   function Count           (Item : Option)   return Natural;
   function Separate_Option (Item : Option)   return Boolean;
   function Inline_Option   (Item : Option)   return Boolean;
   function Item_Name       (Object : Option) return String;
   function Node_Name       (Object : Option) return String;

   function Alternative_Node_Name (Item : Option) return String;

   ----------
   -- List --
   ----------

   type List is new Item with private;

   function Items (Item : List) return Sequence;
   function Item_Name (Object : List) return String;
   function Node_Name (Object : List) return String;
   function List_Item_Node_Name (Object : List) return String;

   -------------
   -- Keyword --
   -------------

   type Keyword is new Item with private;

   function Item_Name (Object : Keyword) return String;
   function Text (Item : Keyword) return String;

   ---------------
   -- Delimiter --
   ---------------

   type Delimiter is new Item with private;

   function Item_Name (Object : Delimiter) return String;
   function Text (Item : Delimiter) return String;

   procedure Read_File (Name : String);

   function Rule_Count return Natural;
   function Get_Rule (Index : Positive) return Rule;
   function Get_Rule (Name  : String) return Rule;

   Not_Found : exception;

   function To_String (X : Natural) return String;

private

   use Ada.Strings.Unbounded;

   type Rule_Node;
   type Rule is access all Rule_Node'Class;

   type Sequence_Node;
   type Sequence is access all Sequence_Node'Class;

   type Item is abstract tagged limited record
      Next      : Item_Ptr;
      Parent    : Sequence;
      Instance  : Positive := 1;
   end record;

   procedure Set_Sequence
     (Object : in out Item;
      Child  : in     Sequence);

   type Reference is new Item with record
      Name      : Unbounded_String;
      Is_Token  : Boolean := False;
   end record;

   type Option_Node;
   type Option_Node_Ptr is access all Option_Node;

   type Option is new Item with record
      Node  : Option_Node_Ptr;
   end record;

   procedure Set_Sequence
     (Object : in out Option;
      Child  : in     Sequence);

   type List is new Item with record
      Items : Sequence;
   end record;

   procedure Set_Sequence
     (Object : in out List;
      Child  : in     Sequence);

   type Keyword is new Item with record
      Text : Unbounded_String;
   end record;

   type Delimiter is new Item with record
      Text : Unbounded_String;
   end record;

   type Wrapper is record
      Node_Name    : Unbounded_String;
      Attr_Name    : Unbounded_String;
      Object_Name  : Unbounded_String;
      Position     : Unbounded_String;
      Parent       : Natural;
      Item_Index   : Natural;
      Seq          : Sequence;
      Index        : Natural;
   end record;

end Gramar_Items;


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

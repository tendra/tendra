with Nodes;

with Text_Streams.File;
with XML_IO.Stream_Readers;

with Gela.Embeded_Links.Lists;

package body Gramar_Items.Code is

   ---------------
   -- Item_Info --
   ---------------

   type Item_Info;
   type Item_Info_Ptr is access all Item_Info;

   type Item_Info is record
      Next                : Item_Info_Ptr;
      Item_Name           : Unbounded_String;
      Attr_Name           : Unbounded_String;
      On_Option_Node_Name : Unbounded_String;
      Trait_Name          : Unbounded_String;
      Create              : Unbounded_String;
      Choise              : Unbounded_String;
      Instance            : Positive := 1;
      Wrapper             : Natural;
   end record;

   function "=" (Left, Right : Item_Info) return Boolean;
   function Get_Next (Item : Item_Info_Ptr) return Item_Info_Ptr;
   procedure Set_Next (Item, Next : Item_Info_Ptr);

   package Item_Info_Lists is
      new Gela.Embeded_Links.Lists (Item_Info, Item_Info_Ptr);

   ---------------
   -- Wrap_Info --
   ---------------

   type Wrap_Info;
   type Wrap_Info_Ptr is access all Wrap_Info;

   type Wrap_Info is record
      Next                : Wrap_Info_Ptr;
      Node_Name           : Unbounded_String;
      Item_Name           : Unbounded_String;
      Attr_Name           : Unbounded_String;
      Position            : Unbounded_String;
      Index               : Positive;
      Parent              : Natural;
      Instance            : Positive := 1;
   end record;

   function "=" (Left, Right : Wrap_Info) return Boolean;
   function Get_Next (Item : Wrap_Info_Ptr) return Wrap_Info_Ptr;
   procedure Set_Next (Item, Next : Wrap_Info_Ptr);

   package Wrap_Info_Lists is
      new Gela.Embeded_Links.Lists (Wrap_Info, Wrap_Info_Ptr);

   --------------
   -- Seq_Info --
   --------------

   type Seq_Info;
   type Seq_Info_Ptr is access all Seq_Info;

   type Seq_Info is record
      Next           : Seq_Info_Ptr;
      Rule_Name      : Unbounded_String;
      Containts_Name : Unbounded_String;
      Node_Name      : Unbounded_String;
      True_Node      : Unbounded_String;
      False_Node     : Unbounded_String;
      Infix          : Unbounded_String;
      Pass_Through   : Boolean;
      Items          : Item_Info_Lists.List;
      Wraps          : Wrap_Info_Lists.List;
   end record;

   function "=" (Left, Right : Seq_Info) return Boolean;
   function Get_Next (Item : Seq_Info_Ptr) return Seq_Info_Ptr;
   procedure Set_Next (Item, Next : Seq_Info_Ptr);

   package Seq_Info_Lists is
      new Gela.Embeded_Links.Lists (Seq_Info, Seq_Info_Ptr);

   All_Seq    : Seq_Info_Lists.List;
   Wrap_Stack : Wrap_Info_Lists.List;
   Last_Wrap  : Positive;

   function Get_Parent_Wrap return Natural;

   function Find_Seq
     (Rule_Name : String;
      Seq       : Sequence) return Seq_Info_Ptr;

   function Find_Item
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String;
      Instance  : Positive) return Item_Info_Ptr;

   function Find_Wrap
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return Wrap_Info_Ptr;

   function Contains_Name
     (Seq : Sequence;
      Name : String) return Boolean;

   procedure Read_Code_File (Name : String) is
      use XML_IO;
      package R renames XML_IO.Stream_Readers;

      Stream  : aliased Text_Streams.File.File_Text_Stream;
      Parser  : R.Reader (Stream'Access, R.Default_Buffer_Size);

      Current_Rule     : Unbounded_String;
      Last_Seq_Info    : Seq_Info_Ptr;

      function Get_Attribute (Name : String) return String is
      begin
         return R.Attribute_Value (Parser, Name);
      end Get_Attribute;

      procedure On_Element is
         Local_Name : constant String := R.Name (Parser);
      begin
         if Local_Name = "rule" then
            declare
               Name : constant String := Get_Attribute ("name");
            begin
               Current_Rule := To_Unbounded_String (Name);
            end;
         elsif Local_Name = "seq" then
            declare
               Name       : constant String := Get_Attribute ("contains_name");
               Pass       : constant String := Get_Attribute ("pass-through");
               Node       : constant String := Get_Attribute ("node");
               True_Node  : constant String := Get_Attribute ("true-node");
               False_Node : constant String := Get_Attribute ("false-node");
               Infix      : constant String := Get_Attribute ("infix");
               L          : Seq_Info_Ptr renames Last_Seq_Info;
            begin
               L := new Seq_Info;
               L.Rule_Name      := Current_Rule;
               L.Containts_Name := To_Unbounded_String (Name);
               L.Node_Name      := To_Unbounded_String (Node);
               L.True_Node      := To_Unbounded_String (True_Node);
               L.False_Node     := To_Unbounded_String (False_Node);
               L.Infix          := To_Unbounded_String (Infix);
               L.Pass_Through   := Pass /= "";
               Seq_Info_Lists.Append (All_Seq, L);
               Last_Wrap        := 1;
            end;
         elsif Local_Name = "wrap" then
            declare
               Node       : constant String := Get_Attribute ("node");
               Item       : constant String := Get_Attribute ("item");
               Attr       : constant String := Get_Attribute ("attr");
               Pos        : constant String := Get_Attribute ("pos");
               Instance   : constant String := Get_Attribute ("instance");
               L          : constant Wrap_Info_Ptr := new Wrap_Info;
            begin
               L.Node_Name := To_Unbounded_String (Node);
               L.Item_Name := To_Unbounded_String (Item);
               L.Attr_Name := To_Unbounded_String (Attr);
               L.Position  := To_Unbounded_String (Pos);
               L.Index     := Last_Wrap;
               L.Parent    := Get_Parent_Wrap;
               if Instance /= "" then
                  L.Instance := Integer'Value (Instance);
               end if;
               Last_Wrap   := Last_Wrap + 1;
               Wrap_Info_Lists.Prepend (Wrap_Stack, L);
            end;
         elsif Local_Name = "item" then
            declare
               Name       : constant String := Get_Attribute ("name");
               Attr       : constant String := Get_Attribute ("attr");
               Trait      : constant String := Get_Attribute ("trait");
               Opt_Node   : constant String := Get_Attribute ("on-option-node");
               Instance   : constant String := Get_Attribute ("instance");
               Create     : constant String := Get_Attribute ("create");
               Choise     : constant String := Get_Attribute ("choise");
               I          : constant Item_Info_Ptr := new Item_Info;
            begin
               I.Item_Name := To_Unbounded_String (Name);
               I.Attr_Name := To_Unbounded_String (Attr);
               I.On_Option_Node_Name := To_Unbounded_String (Opt_Node);
               I.Trait_Name := To_Unbounded_String (Trait);
               I.Create := To_Unbounded_String (Create);
               I.Choise := To_Unbounded_String (Choise);
               I.Wrapper := Get_Parent_Wrap;

               if Instance /= "" then
                  I.Instance := Integer'Value (Instance);
               end if;

               Item_Info_Lists.Append (Last_Seq_Info.Items, I);
            end;
         end if;
      end On_Element;

   begin
      Text_Streams.File.Open (Stream, Name);
      R.Initialize (Parser);

      while R.More_Pieces (Parser) loop
         case R.Piece_Kind (Parser) is
            when Start_Element =>
               On_Element;

            when End_Element =>
               if R.Name (Parser) = "wrap" then
                  declare
                     L : Seq_Info_Ptr renames Last_Seq_Info;
                     W : Wrap_Info_Ptr;
                  begin
                     Wrap_Info_Lists.Delete_First (Wrap_Stack, W);
                     Wrap_Info_Lists.Append (L.Wraps, W);
                  end;
               end if;

            when others =>
               null;
         end case;

         R.Next (Parser);
      end loop;
   end Read_Code_File;

   function "=" (Left, Right : Item_Info) return Boolean is
   begin
      return Left.Item_Name = Right.Item_Name;
   end "=";

   function Get_Next (Item : Item_Info_Ptr) return Item_Info_Ptr is
   begin
      return Item.Next;
   end Get_Next;

   procedure Set_Next (Item, Next : Item_Info_Ptr) is
   begin
      Item.Next := Next;
   end Set_Next;

   function "=" (Left, Right : Seq_Info) return Boolean is
   begin
      return Left.Rule_Name = Right.Rule_Name and
        Left.Containts_Name = Right.Containts_Name;
   end "=";

   function Get_Next (Item : Seq_Info_Ptr) return Seq_Info_Ptr is
   begin
      return Item.Next;
   end Get_Next;

   procedure Set_Next (Item, Next : Seq_Info_Ptr) is
   begin
      Item.Next := Next;
   end Set_Next;

   function "=" (Left, Right : Wrap_Info) return Boolean is
   begin
      return Left.Index = Right.Index;
   end "=";

   function Get_Next (Item : Wrap_Info_Ptr) return Wrap_Info_Ptr is
   begin
      return Item.Next;
   end Get_Next;

   procedure Set_Next (Item, Next : Wrap_Info_Ptr) is
   begin
      Item.Next := Next;
   end Set_Next;

   function Node_Name
     (Rule_Name : String;
      Seq       : Sequence) return String
   is
      Info_Ptr : constant Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.Node_Name);
      else
         return "";
      end if;
   end Node_Name;

   function Infix
     (Rule_Name : String;
      Seq       : Sequence) return String
   is
      Info_Ptr : constant Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.Infix);
      else
         return "";
      end if;
   end Infix;

   function True_Node
     (Rule_Name : String;
      Seq       : Sequence) return String
   is
      Info_Ptr : constant Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.True_Node);
      else
         return "";
      end if;
   end True_Node;

   function False_Node
     (Rule_Name : String;
      Seq       : Sequence) return String
   is
      Info_Ptr : constant Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.False_Node);
      else
         return "";
      end if;
   end False_Node;


   function Pass_Throgh
     (Rule_Name : String;
      Seq       : Sequence) return Boolean
   is
      Info_Ptr    : constant Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
      Ref_Count   : Natural := 0;
      Other_Count : Natural := 0;
   begin
      if Info_Ptr /= null then
         return Info_Ptr.Pass_Through;
      end if;
      for I in 1 .. Count (Seq) loop
         declare
            Child : Item'Class renames Get_Item (Seq, I).all;
         begin
            if Child in Reference then
               Ref_Count := Ref_Count + 1;
            elsif Child in List or Child in Option then
               Other_Count := Other_Count + 1;
            end if;
         end;
      end loop;
      return Ref_Count = 1 and Other_Count = 0;
   end Pass_Throgh;

   function Find_Seq
     (Rule_Name : String;
      Seq       : Sequence) return Seq_Info_Ptr
   is
      use Seq_Info_Lists;
      Next : aliased Seq_Info_Ptr;
   begin
      while Iterate (All_Seq, Next'Access) loop
         if Rule_Name = Next.Rule_Name then
            if Next.Containts_Name = ""  or else
              Contains_Name (Seq, To_String (Next.Containts_Name)) then

               return Next;

            end if;
         end if;
      end loop;

      return null;
   end Find_Seq;

   function Contains_Name (Seq : Sequence; Name : String) return Boolean is
   begin
      for I in 1 .. Count (Seq) loop
         declare
            Child_Name : constant String := Item_Name (Get_Item (Seq, I).all);
         begin
            if Name = Child_Name then
               return True;
            end if;
         end;
      end loop;
      return False;
   end Contains_Name;

   function Get_Use_Attr
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String;
      Instance  : Positive) return String
   is
      Info_Ptr : constant Item_Info_Ptr :=
        Find_Item (Rule_Name, Seq, Item_Name, Instance);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.Attr_Name);
      else
         return "";
      end if;
   end Get_Use_Attr;

   function Find_Item
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String;
      Instance  : Positive) return Item_Info_Ptr
   is
      use Item_Info_Lists;
      Found   : constant Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
      Next    : aliased Item_Info_Ptr;
   begin
      if Found = null then
         return null;
      end if;

      while Iterate (Found.Items, Next'Access) loop
         if Next.Item_Name = Item_Name and Next.Instance = Instance then
            return Next;
         end if;
      end loop;

      return null;
   end Find_Item;

   function Alternative_Node_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String
   is
      Info_Ptr : constant Item_Info_Ptr :=
        Find_Item (Rule_Name, Seq, Item_Name, 1);
   begin
      if Info_Ptr /= null then
         return Nodes.Get_Node_Type_Name
           (To_String (Info_Ptr.On_Option_Node_Name));
      else
         return "";
      end if;
   end Alternative_Node_Name;

   function Trait_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String
   is
      Info_Ptr : constant Item_Info_Ptr :=
        Find_Item (Rule_Name, Seq, Item_Name, 1);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.Trait_Name);
      else
         return "";
      end if;
   end Trait_Name;

   function Created_Node_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String
   is
      Info_Ptr : constant Item_Info_Ptr :=
        Find_Item (Rule_Name, Seq, Item_Name, 1);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.Create);
      else
         return "";
      end if;
   end Created_Node_Name;

   function Choise
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String) return String
   is
      Info_Ptr : constant Item_Info_Ptr :=
        Find_Item (Rule_Name, Seq, Item_Name, 1);
   begin
      if Info_Ptr /= null then
         return To_String (Info_Ptr.Choise);
      else
         return "";
      end if;
   end Choise;

   function Wrapper_Index
     (Rule_Name : String;
      Seq       : Sequence;
      Item_Name : String;
      Instance  : Positive) return Natural
   is
      Info_Ptr : constant Item_Info_Ptr :=
        Find_Item (Rule_Name, Seq, Item_Name, Instance);
   begin
      if Info_Ptr /= null then
         return Info_Ptr.Wrapper;
      else
         return 0;
      end if;
   end Wrapper_Index;

   function Get_Parent_Wrap return Natural is
   begin
      if Wrap_Info_Lists.Is_Empty (Wrap_Stack) then
         return 0;
      else
         return Wrap_Info_Lists.First (Wrap_Stack).Index;
      end if;
   end Get_Parent_Wrap;

   function Wrapper_Index
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return Natural
   is
      Wrap_Ptr : constant Wrap_Info_Ptr :=
        Find_Wrap (Rule_Name, Seq, Wrapper);
   begin
      if Wrap_Ptr /= null then
         return Wrap_Ptr.Parent;
      else
         return 0;
      end if;
   end Wrapper_Index;

   function Wrapper_Instance
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return Positive
   is
      Wrap_Ptr : constant Wrap_Info_Ptr :=
        Find_Wrap (Rule_Name, Seq, Wrapper);
   begin
      return Wrap_Ptr.Instance;
   end Wrapper_Instance;

   function Find_Wrap
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return Wrap_Info_Ptr
   is
      use Item_Info_Lists;
      package Search is new Wrap_Info_Lists.Generic_Search;
      Found   : Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
      Wrp     : Wrap_Info;
   begin
      if Found = null then
         return null;
      end if;

      Wrp.Index := Wrapper;

      return Search.Find (Found.Wraps, Wrp);
   end Find_Wrap;

   function User_Wraps
     (Rule_Name : String;
      Seq       : Sequence) return Natural
   is
      Info_Ptr : constant Seq_Info_Ptr := Find_Seq (Rule_Name, Seq);
   begin
      if Info_Ptr = null then
         return 0;
      else
         return Natural (Wrap_Info_Lists.Length (Info_Ptr.Wraps));
      end if;
   end User_Wraps;

   function User_Wrap_Node
     (Rule_Name : String;
      Seq       : Sequence;
      Index     : Positive) return String
   is
      Wrap_Ptr : constant Wrap_Info_Ptr :=
        Find_Wrap (Rule_Name, Seq, Index);
   begin
      if Wrap_Ptr /= null then
         return To_String (Wrap_Ptr.Node_Name);
      else
         return "";
      end if;
   end User_Wrap_Node;

   function Wrap_Item_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Index     : Positive) return String
   is
      Wrap_Ptr : constant Wrap_Info_Ptr :=
        Find_Wrap (Rule_Name, Seq, Index);
   begin
      if Wrap_Ptr /= null then
         return To_String (Wrap_Ptr.Item_Name);
      else
         return "";
      end if;
   end Wrap_Item_Name;

   function Wrap_Attr_Name
     (Rule_Name : String;
      Seq       : Sequence;
      Index     : Positive) return String
   is
      Wrap_Ptr : constant Wrap_Info_Ptr :=
        Find_Wrap (Rule_Name, Seq, Index);
   begin
      if Wrap_Ptr /= null then
         return To_String (Wrap_Ptr.Attr_Name);
      else
         return "";
      end if;
   end Wrap_Attr_Name;

   function Wrapper_Position
     (Rule_Name : String;
      Seq       : Sequence;
      Wrapper   : Positive) return String
   is
      Wrap_Ptr : constant Wrap_Info_Ptr :=
        Find_Wrap (Rule_Name, Seq, Wrapper);
   begin
      if Wrap_Ptr /= null then
         return To_String (Wrap_Ptr.Position);
      else
         return "";
      end if;
   end Wrapper_Position;

end Gramar_Items.Code;


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

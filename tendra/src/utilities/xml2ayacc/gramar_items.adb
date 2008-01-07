with Nodes;
with Tokens;
with Asis_Trait_Kinds;
with Gramar_Items.Code;
with Text_Streams.File;
with XML_IO.Stream_Readers;
with Ada.Characters.Handling;
with Gela.Embeded_Links.Lists;

package body Gramar_Items is

   Format_Error : exception;

   function Get_Trait_Kind (Name : String) return String;

   -------------------
   -- Sequence_Node --
   -------------------

   function Get_Next (Item : Item_Ptr) return Item_Ptr;
   procedure Set_Next (Item, Next : Item_Ptr);

   package Item_Lists is
      new Gela.Embeded_Links.Lists (Item'Class, Item_Ptr);

   type Sequence_Node is tagged limited record
      Next         : Sequence;
      List         : Item_Lists.List;
      Parent       : Rule;
      Parent_Item  : Item_Ptr;
      Item_Index   : Natural := 0;
      List_Index   : Natural := 0;
   end record;

   function Get_Next (Item : Sequence) return Sequence;
   procedure Set_Next (Item, Next : Sequence);

   package Sequence_Lists is
      new Gela.Embeded_Links.Lists (Sequence_Node'Class, Sequence);

   ---------------
   -- Rule_Node --
   ---------------

   type Rule_Node is tagged limited record
      List : Sequence_Lists.List;
      Name : Unbounded_String;
      Next : Rule;
   end record;

   function Get_Next (Item : Rule) return Rule;
   procedure Set_Next (Item, Next : Rule);

   package Rule_Lists is
      new Gela.Embeded_Links.Lists (Rule_Node'Class, Rule);

   -----------------
   -- Gramar_Node --
   -----------------

   type Gramar_Node is record
      List : Rule_Lists.List;
   end record;

   type Gramar_Ptr is access all Gramar_Node;

   Gramar       : Gramar_Ptr;

   type Option_Node is record
      List : Sequence_Lists.List;
   end record;

   function Compound_Name
     (Item     : Sequence;
      Conflict : Boolean := False)
     return String;

   function Compound_Name (Item : Sequence; Part : Positive) return String;

   function Find_Item
      (Seq  : Sequence;
       Name : String;
       Inst : Positive) return Natural;

   type Reference_Ptr is access all Reference;
   type Keyword_Ptr is access all Keyword;
   type Delimiter_Ptr is access all Delimiter;
   type List_Ptr is access all List;
   type Option_Ptr is access all Option;

   -----------
   -- Count --
   -----------

   function Count (Item : Sequence) return Natural is
   begin
      return Natural (Item_Lists.Length (Item.List));
   end Count;

   -----------
   -- Count --
   -----------

   function Count (Item : Rule) return Natural is
   begin
      return Natural (Sequence_Lists.Length (Item.List));
   end Count;

   -----------
   -- Count --
   -----------

   function Count (Item : Option) return Natural is
   begin
      return Natural (Sequence_Lists.Length (Item.Node.List));
   end Count;

   ---------------------
   -- Get_Alternative --
   ---------------------

   function Get_Alternative
     (Item  : Rule;
      Index : Positive)
      return Sequence
   is
      use Sequence_Lists;
      Result : Sequence := First (Item.List);
   begin
      for J in 2 .. Index loop
         Result := Next (Item.List, Result);
      end loop;

      return Result;
   end Get_Alternative;

   --------------
   -- Get_Item --
   --------------

   function Get_Item
     (Object : Sequence;
      Index  : Positive)
      return Item_Ptr
   is
      use Item_Lists;
      Result : Item_Ptr := First (Object.List);
   begin
      for J in 2 .. Index loop
         Result := Next (Object.List, Result);
      end loop;

      return Result;
   end Get_Item;

   -----------
   -- Index --
   -----------

   function Wrapper_Index (Object : Wrapper) return Natural is
   begin
      return Object.Index;
   end Wrapper_Index;

   --------------
   -- Is_Token --
   --------------

   function Is_Token (Item : Reference) return Boolean is
   begin
      return Item.Is_Token;
   end Is_Token;

   -----------
   -- Items --
   -----------

   function Items
     (Item  : Option;
      Index : Positive := 1) return Sequence
   is
      use Sequence_Lists;
      Result : Sequence := First (Item.Node.List);
   begin
      for J in 2 .. Index loop
         Result := Next (Item.Node.List, Result);
      end loop;

      return Result;
   end Items;

   -----------
   -- Items --
   -----------

   function Items (Item : List) return Sequence is
   begin
      return Item.Items;
   end Items;

   ----------
   -- Name --
   ----------

   function Name (Item : Rule) return String is
   begin
      return To_String (Item.Name);
   end Name;

   ----------
   -- Name --
   ----------

   function Name (Item : Reference) return String is
   begin
      return To_String (Item.Name);
   end Name;

   ----------
   -- Text --
   ----------

   function Text (Item : Keyword) return String is
   begin
      return To_String (Item.Text);
   end Text;

   ----------
   -- Text --
   ----------

   function Text (Item : Delimiter) return String is
   begin
      return To_String (Item.Text);
   end Text;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Item_Ptr) is
   begin
      Item.Next := Next;
   end Set_Next;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Rule) is
   begin
      Item.Next := Next;
   end Set_Next;

   --------------
   -- Set_Next --
   --------------

   procedure Set_Next (Item, Next : Sequence) is
   begin
      Item.Next := Next;
   end Set_Next;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Item_Ptr) return Item_Ptr is
   begin
      return Item.Next;
   end Get_Next;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Sequence) return Sequence is
   begin
      return Item.Next;
   end Get_Next;

   --------------
   -- Get_Next --
   --------------

   function Get_Next (Item : Rule) return Rule is
   begin
      return Item.Next;
   end Get_Next;

   ------------------
   -- Set_Sequence --
   ------------------

   procedure Set_Sequence
     (Object : in out Item;
      Child  : in     Sequence) is
   begin
      raise Format_Error;
   end Set_Sequence;

   ------------------
   -- Set_Sequence --
   ------------------

   procedure Set_Sequence
     (Object : in out Option;
      Child  : in     Sequence) is
   begin
      Sequence_Lists.Append (Object.Node.List, Child);
   end Set_Sequence;

   ------------------
   -- Set_Sequence --
   ------------------

   procedure Set_Sequence
     (Object : in out List;
      Child  : in     Sequence) is
   begin
      Object.Items := Child;
   end Set_Sequence;

   ---------------
   -- Read_File --
   ---------------

   procedure Read_File (Name : String) is
      use XML_IO;
      package R renames XML_IO.Stream_Readers;

      Max_Level     : constant := 8;
      Stream        : aliased Text_Streams.File.File_Text_Stream;
      Parser        : R.Reader (Stream'Access, R.Default_Buffer_Size);
      Last_Rule     : Rule;
      Seq           : array (1 .. Max_Level) of Sequence;
      Last_Seq      : Natural := 0;
      Items         : array (1 .. Max_Level) of Item_Ptr;
      Last_Item     : Natural := 0;

      -------------------
      -- Last_Sequence --
      -------------------

      function Last_Sequence return Sequence is
      begin
         return Seq (Last_Seq);
      end Last_Sequence;

      ---------------------
      -- Count_Instances --
      ---------------------

      function Count_Instances (Name : String) return Positive is
         use Item_Lists;
         Instance : Positive := 1;
         Item     : aliased Item_Ptr;
      begin
         while Iterate (Last_Sequence.List, Item'Access) loop
            if Name = Item_Name (Item.all) then
               Instance := Instance + 1;
            end if;
         end loop;

         return Instance;
      end Count_Instances;

      -------------------
      -- Get_Attribute --
      -------------------

      function Get_Attribute (Name : String) return String is
      begin
         return R.Attribute_Value (Parser, Name);
      end Get_Attribute;

      -------------------
      -- Get_Attribute --
      -------------------

      function Get_Attribute (Name : String) return Unbounded_String is
      begin
         return To_Unbounded_String (R.Attribute_Value (Parser, Name));
      end Get_Attribute;

      ----------------
      -- On_Element --
      ----------------

      procedure On_Element is
         use Item_Lists;
         use Rule_Lists;
         use Sequence_Lists;

         Local_Name : constant String := R.Name (Parser);
      begin
         if Local_Name = "gramar" then
            Gramar := new Gramar_Node;
         elsif Local_Name = "rule" then
            Last_Rule      := new Rule_Node;
            Last_Rule.Name := Get_Attribute ("name");
            Append (Gramar.List, Last_Rule);
         elsif Local_Name = "seq" then
            Last_Seq := Last_Seq + 1;
            Seq (Last_Seq) := new Sequence_Node;

            if Last_Item > 0 then
               Set_Sequence (Items (Last_Item).all, Last_Sequence);
               Last_Sequence.Parent_Item := Items (Last_Item);
            else
               Append (Last_Rule.List, Last_Sequence);
               Last_Sequence.Parent := Last_Rule;
            end if;
         elsif Local_Name = "ref" then
            declare
               Node : constant Reference_Ptr := new Reference;
               Name : constant String := Get_Attribute ("name");
            begin
               Node.Name     := To_Unbounded_String (Name);
               Node.Instance := Count_Instances (Name);
               Node.Parent   := Last_Sequence;

               if Node.Name = "identifier"        or
                 Node.Name  = "numeric_literal"   or
                 Node.Name  = "character_literal" or
                 Node.Name  = "string_literal"
               then
                  Node.Is_Token := True;
               end if;

               Append (Last_Sequence.List, Item_Ptr (Node));
            end;
         elsif Local_Name = "keyword" then
            declare
               Node : constant Keyword_Ptr := new Keyword;
               Name : constant String := Get_Attribute ("text");
            begin
               Node.Text     := To_Unbounded_String (Name);
               Node.Instance := Count_Instances (Name);
               Node.Parent   := Last_Sequence;
               Append (Last_Sequence.List, Item_Ptr (Node));
            end;
         elsif Local_Name = "delim" then
            declare
               Node : constant Delimiter_Ptr := new Delimiter;
               Name : constant String := Get_Attribute ("text");
            begin
               Node.Text     := To_Unbounded_String (Name);
               Node.Parent   := Last_Sequence;
               Append (Last_Sequence.List, Item_Ptr (Node));
            end;
         elsif Local_Name = "list" then
            declare
               Node : constant List_Ptr := new List;
            begin
               Last_Item         := Last_Item + 1;
               Items (Last_Item) := Item_Ptr (Node);
               Node.Parent       := Last_Sequence;
               Append (Last_Sequence.List, Item_Ptr (Node));
            end;
         elsif Local_Name = "opt" then
            declare
               Data : constant Option_Node_Ptr := new Option_Node;
               Node : constant Option_Ptr := new Option;
            begin
               Node.Node         := Data;
               Last_Item         := Last_Item + 1;
               Items (Last_Item) := Item_Ptr (Node);
               Node.Parent       := Last_Sequence;
               Append (Last_Sequence.List, Item_Ptr (Node));
            end;
         else
            raise Format_Error;
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
               if R.Name (Parser) = "seq" then
                  Last_Seq := Last_Seq - 1;
               elsif R.Name (Parser) = "opt" or R.Name (Parser) = "list" then
                  Last_Item := Last_Item - 1;
               end if;
            when others =>
               null;
         end case;

         R.Next (Parser);
      end loop;
   end Read_File;

   function Rule_Count return Natural is
   begin
      return Natural (Rule_Lists.Length (Gramar.List));
   end Rule_Count;

   function Get_Rule (Index : Positive) return Rule is
      use Rule_Lists;
      Result : Rule := First (Gramar.List);
   begin
      for J in 2 .. Index loop
         Result := Next (Gramar.List, Result);
      end loop;

      return Result;
   end Get_Rule;

   function Pass_Through (Item : Sequence) return Boolean is
   begin
      return Code.Pass_Throgh (Rule_Name (Item), Item);
   end Pass_Through;

   function Infix (Item : Sequence) return String is
   begin
      return Code.Infix (Rule_Name (Item), Item);
   end Infix;

   function True_Node (Item : Sequence) return String is
   begin
      return Nodes.Get_Node_Type_Name
        (Code.True_Node (Rule_Name (Item), Item));
   end True_Node;

   function False_Node (Item : Sequence) return String is
   begin
      return Nodes.Get_Node_Type_Name
        (Code.False_Node (Rule_Name (Item), Item));
   end False_Node;

   function Node_Name   (Item : Sequence) return String is
      R_Name : constant String := Rule_Name (Item);
      C_Name : constant String := Code.Node_Name (R_Name, Item);
   begin
      if Item = null then
         return "";
      elsif C_Name /= "" then
            return Nodes.Get_Node_Type_Name (C_Name);
      elsif Pass_Through (Item) then
         declare
            I : constant Natural := Find_First_Reference (Item);
         begin
            if I /= 0 then
               return Node_Name (Get_Item (Item, I).all);
            else
               return "";
            end if;
         end;
--      elsif Is_Item_And_List (Item) then
--         declare
--            List_Index : constant Natural := Find_First_List (Item);
--         begin
--            return Node_Name (Get_Item (Item, List_Index));
--         end;
      else
         declare
            Wrap_Name : constant String :=
              Code.User_Wrap_Node (R_Name, Item, 1);
         begin
            if Wrap_Name /= "" then
               return Nodes.Get_Node_Type_Name (Wrap_Name);
            else
               return Nodes.Get_Node_Type_Name (R_Name);
            end if;
         end;
      end if;
   end Node_Name;

   function Alternative_Node_Name (Item : Option) return String is
      I_Name : constant String := Item_Name (Item);
      R_Name : constant String := Rule_Name (Item.Parent);
   begin
      return Code.Alternative_Node_Name(R_Name, Item.Parent, I_Name);
   end Alternative_Node_Name;

   function Trait_Name (Object : Item) return String is
      I_Name : constant String := Item_Name (Item'Class (Object));
      R_Name : constant String := Rule_Name (Object.Parent);
      Trait  : constant String := Get_Trait_Kind (I_Name);
      C_Trt  : constant String := Code.Trait_Name(R_Name, Object.Parent, I_Name);
   begin
      if C_Trt /= "" then
         return Get_Trait_Kind (C_Trt);
      else
         return Trait;
      end if;
   end Trait_Name;

   function Item_Name (Object : Reference) return String is
   begin
      return Name (Object);
   end Item_Name;

   function Item_Name (Object : Option) return String is
   begin
      if Count (Object) > 1 then
         return Compound_Name (Items (Object)) & "option"
           & To_String (Count (Object));
      elsif Separate_Option (Object) then
         declare
            Name : constant String :=
              Compound_Name (Items (Object)) & "option";
         begin
            if Code.Conflict_Name (Name) then
               return Compound_Name (Items (Object), True) & "option";
            else
               return Name;
            end if;
         end;
      else
         return Item_Name (Get_Item (Items (Object), 1).all);
      end if;
   end Item_Name;

   function Item_Name (Object : List) return String is
   begin
      return Compound_Name (Items (Object)) & "list";
   end Item_Name;

   function Item_Name (Object : Keyword) return String is
   begin
      return Text (Object);
   end Item_Name;

   function Item_Name (Object : Delimiter) return String is
   begin
      return Tokens.Delimiter_Name (Text (Object));
   end Item_Name;

   function Separate_Option (Item : in Option) return Boolean is
      Seq   : constant Sequence := Items (Item);
      Child : Gramar_Items.Item'Class renames Get_Item (Seq, 1).all;
   begin
      if Count (Item) > 1 then
         return False;
      end if;

      if Count (Seq) = 1 and then
        (Child in Reference or
         Child in Keyword or
         Child in Delimiter) then

         return False;
      else
         return True;
      end if;
   end Separate_Option;

   function Inline_Option (Item : Option) return Boolean is
   begin
      return Code.Inline_Option (Item_Name (Item), Items (Item));
   end Inline_Option;

   function Compound_Name
     (Item     : Sequence;
      Conflict : Boolean := False)
     return String
   is
      Length : constant Positive := Count (Item);
   begin
      if Conflict then
         return Compound_Name (Item, Part => 1) &
           Compound_Name (Item, Part => 2) &
           Compound_Name (Item, Part => Length);
      elsif Length > 1 then
         return Compound_Name (Item, Part => 1) &
           Compound_Name (Item, Part => 2);
      else
         return Compound_Name (Item, Part => 1);
      end if;
   end Compound_Name;

   function Compound_Name (Item : Sequence; Part : Positive ) return String is
      Child : Gramar_Items.Item'Class renames Get_Item (Item, Part).all;
   begin
      if Child in Option then
         return Compound_Name (Items (Option (Child)));
      elsif Child in List then
         return Compound_Name (Items (List (Child)));
      elsif Child in Keyword then
         return Text (Keyword (Child)) & "_";
      elsif Child in Reference then
         return Name (Reference (Child)) & "_";
      elsif Child in Delimiter then
         return Tokens.Delimiter_Name (Text (Delimiter (Child))) & "_";
      else
         return "";
      end if;
   end Compound_Name;

   function Node_Name (Item : Rule) return String is
      Result : constant String := Node_Name (Get_Alternative (Item, 1));
   begin
      if Result = "" then
         return "";
      end if;
      for I in 2 .. Count (Item) loop
         if Result /= Node_Name (Get_Alternative (Item, I)) then
            return "";
         end if;
      end loop;
      return Result;
   end Node_Name;

   function Node_Name (Object : Item) return String is
   begin
      return "";
   end Node_Name;

   function Node_Name (Object : Option) return String is
   begin
      return Node_Name (Items (Object));
   end Node_Name;

   function Node_Name (Object : List) return String is
   begin
      return Node_Name (Object.Items);
   end Node_Name;

   function Node_Name (Object : Reference) return String is
   begin
      if Is_Token (Object) then
         return Nodes.Capitalise (Item_Name (Object) & "_Node");
      end if;
      return Node_Name (Get_Rule (Item_Name (Object)));
   exception
      when Not_Found =>
         return "";
   end Node_Name;

   function Get_Rule (Name  : String) return Rule is
      use Rule_Lists;
      Found : aliased Rule;
   begin
      while Iterate (Gramar.List, Found'Access) loop
         if Found.Name = Name then
            return Found;
         end if;
      end loop;

      raise Not_Found;
   end Get_Rule;

   function Find_First_Reference (Item : Sequence) return Natural is
   begin
      for I in 1 .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
         begin
            if Child in Reference then

               return I;

            end if;
         end;
      end loop;
      return 0;
   end Find_First_Reference;

   function Choise_Item_Index (Item : Sequence) return Natural  is
   begin
      for I in 1 .. Count (Item) loop
         if Choise (Get_Item (Item, I).all) /= "" then
            return I;
         end if;
      end loop;
      return 0;
   end Choise_Item_Index;

   function Find_First_List (Item : Sequence) return Natural is
   begin
      for I in 1 .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
         begin
            if Child in List then

               return I;

            end if;
         end;
      end loop;
      return 0;
   end Find_First_List;

   function User_Attr (Object : Item) return String is
      I_Name : constant String := Item_Name (Item'Class (Object));
      R_Name : constant String := Rule_Name (Object.Parent);
   begin
      return Code.Get_Use_Attr
        (R_Name, Object.Parent, I_Name, Object.Instance);
   end User_Attr;

   function Create_Node (Object : Item) return String is
      I_Name : constant String := Item_Name (Item'Class (Object));
      R_Name : constant String := Rule_Name (Object.Parent);
   begin
      return Nodes.Get_Node_Type_Name
        (Code.Created_Node_Name (R_Name, Object.Parent, I_Name));
   end Create_Node;

   function Choise (Object : Item) return String is
      I_Name : constant String := Item_Name (Item'Class (Object));
      R_Name : constant String := Rule_Name (Object.Parent);
   begin
      return Code.Choise (R_Name, Object.Parent, I_Name);
   end Choise;

   function Rule_Name (Seq : Sequence) return String is
   begin
      if Seq.Parent /= null then
         return Name (Seq.Parent);
      elsif Seq.Parent_Item.all in Option and then
        Inline_Option (Option (Seq.Parent_Item.all))
      then
         return Rule_Name (Seq.Parent_Item.Parent);
      else
         return Item_Name (Seq.Parent_Item.all);
      end if;
   end Rule_Name;

   function Is_Item_And_List (Seq : Sequence) return Boolean is

   begin
      for I in 1 .. Count (Seq) loop
         declare
            The_List : Gramar_Items.Item'Class renames Get_Item (Seq, I).all;
         begin
            if The_List in List then
               if List_Item_Node_Name (List (The_List)) /= "" then
                  for J in 1 .. Count (Seq) loop
                     declare
                        The_Ref : Gramar_Items.Item'Class renames
                          Get_Item (Seq, J).all;
                     begin
                        if The_Ref in Reference and then
                          Node_Name (The_Ref) =
                          List_Item_Node_Name (List (The_List)) then

                           Seq.List_Index := I;
                           Seq.Item_Index := J;
                           return True;
                        end if;
                     end;
                  end loop;
               end if;
            end if;
         end;
      end loop;

      return False;

   end Is_Item_And_List;

   function List_Item_Node_Name (Object : List) return String is
      Seq       : constant Sequence :=  Items (Object);
      Ref_Index : constant Natural := Find_First_Reference (Seq);
   begin
      if Ref_Index > 0 then
         return Node_Name (Get_Item (Seq, Ref_Index).all);
      else
         return "";
      end if;
   end List_Item_Node_Name;

   function Item_Of_List_Index (Seq : Sequence) return Natural is
   begin
      return Seq.Item_Index;
   end Item_Of_List_Index;

   function List_For_Item_Index (Seq : Sequence) return Natural is
   begin
      return Seq.List_Index;
   end List_For_Item_Index;

   function Node_Name (Object : Wrapper) return String is
   begin
      return To_String (Object.Node_Name);
   end Node_Name;

   function Parent (Object : Wrapper) return Wrapper is
   begin
      return Get_Wrapper (Object.Seq, Object.Parent);
   end Parent;

   function Item_Index (Object : Wrapper) return Natural is
   begin
      return Object.Item_Index;
   end Item_Index;

   function Object_Name (Object : Wrapper) return String is
   begin
      return To_String (Object.Object_Name);
   end Object_Name;

   function User_Attr_Name (Object : Wrapper) return String is
   begin
      return To_String (Object.Attr_Name);
   end User_Attr_Name;

   function Position (Object : Wrapper) return String is
   begin
      return To_String (Object.Position);
   end Position;

   function Wrap_Count  (Item : Sequence) return Natural is
      R_Name     : constant String := Rule_Name (Item);
      User_Wraps : constant Natural := Code.User_Wraps (R_Name, Item);
   begin
      if User_Wraps > 0 then
         return User_Wraps;
      else
         if Pass_Through (Item) then
            return 0;
         elsif Is_Item_And_List (Item) and then Node_Name (Item) /= "" then
            return 2;
         else
            return 1;
         end if;
      end if;
   end Wrap_Count;

   function Get_Wrapper
     (Seq   : Sequence;
      Index : Positive) return Wrapper
   is
      function U (Text : String) return Unbounded_String
         renames To_Unbounded_String;

      R_Name     : constant String := Rule_Name (Seq);
      User_Wraps : constant Natural := Code.User_Wraps (R_Name, Seq);

   begin
      if User_Wraps > 0 then
         declare
            Node : constant String := Code.User_Wrap_Node (R_Name, Seq, Index);
            Name : constant String := Nodes.Get_Node_Type_Name (Node);
            Item : constant String := Code.Wrap_Item_Name (R_Name, Seq, Index);
            Attr : constant String := Code.Wrap_Attr_Name (R_Name, Seq, Index);
            Pos  : constant String := Code.Wrapper_Position (R_Name, Seq, Index);
            Inst : constant Positive := Code.Wrapper_Instance (R_Name, Seq, Index);
            Ind  : constant Natural := Find_Item (Seq, Item, Inst);
         begin
            return (Node_Name   => U (Name),
                    Object_Name => U ("Wrap" & To_String (Index)),
                    Parent      => Code.Wrapper_Index (R_Name, Seq, Index),
                    Attr_Name   => U (Attr),
                    Position    => U (Pos),
                    Item_Index  => Ind,
                    Seq         => Seq,
                    Index       => Index);
         end;
      else
         if Is_Item_And_List (Seq) then
            declare
               List_Index : constant Natural := List_For_Item_Index (Seq);
               The_List   : Item'Class renames Get_Item (Seq, List_Index).all;
               List_Name  : constant String  := Node_Name (The_List);
               Wrap       : constant String  := Node_Name (Seq);
            begin
               if Index = 1 then
                  if Wrap = "" then
                     return (Node_Name   => U (List_Name),
                             Object_Name => U ("New_Node"),
                             Attr_Name   => Null_Unbounded_String,
                             Position    => Null_Unbounded_String,
                             Parent      => 0,
                             Item_Index  => List_Index,
                             Seq         => Seq,
                             Index       => 0);
                  else
                     return (Node_Name   => U (Wrap),
                             Object_Name => U ("Wrap"),
                             Attr_Name   => Null_Unbounded_String,
                             Position    => Null_Unbounded_String,
                             Parent      => 0,
                             Item_Index  => 0,
                             Seq         => Seq,
                             Index       => 0);
                  end if;
               else
                  return (Node_Name   => U (List_Name),
                          Object_Name => U ("New_Node"),
                          Attr_Name   => Null_Unbounded_String,
                          Position    => Null_Unbounded_String,
                          Parent      => 1,
                          Item_Index  => List_Index,
                          Seq         => Seq,
                          Index       => 0);
               end if;
            end;
         else
            return (Node_Name   => U (Node_Name (Seq)),
                    Object_Name => U ("New_Node"),
                    Attr_Name   => Null_Unbounded_String,
                    Position    => Null_Unbounded_String,
                    Parent      => 0,
                    Item_Index  => 0,
                    Seq         => Seq,
                    Index       => 0);
         end if;
      end if;
   end Get_Wrapper;

   function Parent (Object : Item) return Wrapper is
      I_Name : constant String := Item_Name (Item'Class (Object));
      R_Name : constant String := Rule_Name (Object.Parent);
      Wrap_I : Natural :=
         Code.Wrapper_Index (R_Name, Object.Parent, I_Name, Object.Instance);
   begin
      if Wrap_I = 0 then
         Wrap_I := 1;
      end if;
      return Get_Wrapper (Object.Parent, Wrap_I);
   end Parent;

   function To_String (X : Natural) return String is
      Image : constant String := Natural'Image (X);
   begin
      return Image (2 .. Image'Last);
   end To_String;

   function Find_Item
      (Seq  : Sequence;
       Name : String;
       Inst : Positive) return Natural
   is
      Cnt : Positive := Inst;
   begin
      if Name = "" then
         return 0;
      end if;
      for I in 1 .. Count (Seq) loop
         if Item_Name (Get_Item (Seq, I).all) = Name then
            if Cnt = 1 then
               return I;
            else
               Cnt := Cnt - 1;
            end if;
         end if;
      end loop;
      return 0;
   end Find_Item;

   function Top (Object : Wrapper) return Boolean is
   begin
      return Object.Parent = 0;
   end Top;

   function Get_Trait_Kind (Name : String) return String is
      use Asis_Trait_Kinds;
      use Ada.Characters.Handling;
      Upper_Name1 : constant String := "A_" & To_Upper (Name) & "_TRAIT";
      Upper_Name2 : constant String := "AN_" & To_Upper (Name) & "_TRAIT";
   begin
      for I in Trait_Kinds loop
         declare
            Image : constant String := Trait_Kinds'Image (I);
            Upper : constant String := To_Upper (Image);
         begin
            if Upper = Upper_Name1 or Upper = Upper_Name2 then
               return Nodes.Capitalise (Image);
            end if;
         end;
      end loop;
      return "";
   end Get_Trait_Kind;

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

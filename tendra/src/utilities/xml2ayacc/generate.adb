with Nodes;
with Tokens;
with Gela.Containers.Lists;
with Ada.Text_IO;
with Gramar_Items;           use Gramar_Items;
with Ada.Strings.Unbounded;

package body Generate is

   procedure Print_Token (Name : in String);
   procedure Print_Rule (Item : in Rule);
   procedure Print_Token_Rule (Name : in String);

   subtype Item_Position is Positive;
   type Positions_List is array (Positive range <>) of Item_Position;

   Empty_List : constant Positions_List := (1 .. 0 => 1);

   procedure Print_Sequence
     (Item                : in Sequence;
      Rule_Name           : in String;
      Name_Of_List        : in String := "");

   procedure Print_Sequence
     (Item                : in Sequence;
      Rule_Name           : in String;
      Start_From          : in Item_Position;
      Processed_Positions : in Positions_List;
      Total_Positions     : in Natural;
      Name_Of_List        : in String);

   procedure Print_Sequence_Code
     (Item                : in Sequence;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String);

   procedure Print_List_Code
     (Item                : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String);

   procedure Print_Infix_Code
     (Seq                 : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String);

   procedure Print_Infix_Code1
     (Seq                 : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String);

   procedure Print_Infix_Code2
     (Processed_Positions : in Positions_List);

   procedure Print_Infix_Code3
     (Seq                 : in Sequence;
      Name_Of_List        : in String);

   procedure Print_Infix_Code4
     (Processed_Positions : in Positions_List;
      List_Index          : in Positive := 2);

   procedure Print_Infix_Code5
     (Seq                 : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String);

   procedure Print_Infix_Code6
     (Seq                 : in Sequence;
      Name_Of_List        : in String);

   procedure Print_Infix_Code7
     (Seq                 : in Sequence;
      Name_Of_List        : in String);

   procedure Create_Alt_Nodes
     (Seq                 : in Sequence;
      Processed_Positions : in Positions_List);

   function Count_Total_Positions (Item : Sequence) return Natural;

   function Include
     (Positions : Positions_List;
      Position  : Item_Position) return Boolean;

   procedure Put_Line (Text : String) renames Ada.Text_IO.Put_Line;
   procedure New_Line;
   procedure Put (Text : String) renames Ada.Text_IO.Put;
   procedure Options_And_Lists_In_Sequence (Item : Sequence);
   procedure Print_List (Item : in List);
   procedure Print_Option (Item : in Option);

   procedure Create_Node_Code
     (Item                : in Sequence;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String;
      Node_Type_Name      : in String);

   procedure Print_Code
     (Child       : Item'Class;
      Parent_Type : String;
      Parent_Name : String;
      Index       : Positive;
      Force       : Boolean);

   procedure Print_Wrap_Code (Child : Wrapper);

   function Find_Attribute
     (Child          : Item'Class;
      Node_Type_Name : String) return String;

   function Find_Attribute
     (Name      : String;
      Type_Name : String;
      User_Attr : String;
      Node_Type_Name : String) return String;

   function Find_Procedure
     (Node_Name : String;
      Attr_Name : String) return String;

   function Indent return String;

   procedure Step_Indent (Step : Integer);

   --  Append "_r" for pragma and range names
   function Translate_Name (Name : String) return String;
   function Is_List (Item : Sequence) return Boolean;
   function Is_List_Type (Node_Name : String) return Boolean;
   function Quote (Text : String; Double : Boolean) return String;

   function Processed
     (Seq                 : in Sequence;
      Processed_Positions : in Positions_List;
      Index               : Positive) return Boolean;

   function Real_Index
     (Seq                 : in Sequence;
      Processed_Positions : in Positions_List;
      Index               : in Positive;
      Name_Of_List        : in String) return Positive;

   function New_Node (Type_Name : String) return String;

   procedure Set_Name_Image_Code
     (Name     : in String;
      Child    : in Item'Class;
      Index    : in Positive := 1;
      Proc     : in String   := "Set_Name_Image";
      In_Quote : in Boolean  := True);

   function Is_First
     (Seq                 : in Sequence;
      Index               : in Positive;
      Processed_Positions : in Positions_List) return Boolean;

   function Is_Last
     (Seq                 : in Sequence;
      Index               : in Positive;
      Processed_Positions : in Positions_List) return Boolean;

   function Just_Keywords (Item : in Sequence) return Boolean;

   package U renames Ada.Strings.Unbounded;
   use type U.Unbounded_String;

   package Unbounded_String_Lists is
      new Gela.Containers.Lists (U.Unbounded_String);

   Printed_Lists   : Unbounded_String_Lists.List;
   Printed_Options : Unbounded_String_Lists.List;
   List_Phase      : Boolean := False;

   procedure All_Tokens is
      procedure Print_Tokens is new Tokens.For_Each_Name (Print_Token);
   begin
      Print_Tokens;
   end All_Tokens;

   procedure Print_Token (Name : in String) is
   begin
      Put_Line ("%token " & Name & "_Token");
   end Print_Token;

   procedure Start_Rule is
   begin
      New_Line;
      Put_Line ("%start compilation");
      New_Line;
      Put_Line ("{");
      Put_Line ("   subtype YYSTYPE is Asis.Element;");
      Put_Line ("   subtype T       is YYSTYPE;");
      Put_Line ("}");
      New_Line;
      Put_Line ("%%");
      New_Line;
   end Start_Rule;

   procedure All_Rules is
   begin
      for I in 1 .. Rule_Count loop
         Print_Rule (Get_Rule (I));
      end loop;
   end All_Rules;

   procedure Print_Rule (Item : in Rule) is
      Rule_Name : constant String := Translate_Name (Name (Item));
   begin
      Put_Line (Rule_Name & " :");
      for I in 1 .. Count (Item) loop
         if I > 1 then
            Put ("   |");
         else
            Put ("    ");
         end if;
         Print_Sequence (Get_Alternative (Item, I), Rule_Name);
      end loop;
      Put_Line (";");
      New_Line;
   end Print_Rule;

   procedure Print_Sequence
     (Item                : in Sequence;
      Rule_Name           : in String;
      Name_Of_List        : in String := "")
   is
      Count      : constant Natural := Count_Total_Positions (Item);
   begin
      Print_Sequence (Item, Rule_Name, 1, Empty_List, Count, Name_Of_List);
   end Print_Sequence;

   procedure Print_Sequence
     (Item                : in Sequence;
      Rule_Name           : in String;
      Start_From          : in Item_Position;
      Processed_Positions : in Positions_List;
      Total_Positions     : in Natural;
      Name_Of_List        : in String)
   is
      use type Ada.Text_IO.Count;
   begin
      for I in Start_From .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
         begin
            if Child in List or Child in Option then

               Print_Sequence         --  recursive call
                 (Item                => Item,
                  Rule_Name           => Rule_Name,
                  Start_From          => I + 1,
                  Processed_Positions => Processed_Positions & I,
                  Total_Positions     => Total_Positions,
                  Name_Of_List        => Name_Of_List);

            end if;
         end;
      end loop;

      if Total_Positions /= Processed_Positions'Length then
         Put ("   |");
      end if;

      if Name_Of_List /= "" then
         Put(" " & Name_Of_List);
      end if;

      for I in 1 .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
            Print : Boolean := False;
         begin
            if (Child in List or Child in Option) then
               if Include (Processed_Positions, I) then
                  Print := True;
               end if;
            else
               Print := True;
            end if;
            if Print then
               if Ada.Text_IO.Col > 55 then
                  New_Line;
                  Put ("    ");
               end if;
               if Child in Reference then
                  Put(" " & Translate_Name (Item_Name (Child)));
               else
                  Put(" " & Item_Name (Child));
               end if;
            end  if;
         end;
      end loop;

      New_Line;

      Print_Sequence_Code (Item, Processed_Positions, Name_Of_List);

   end Print_Sequence;

   function Count_Total_Positions (Item : Sequence) return Natural is
      Counted : Natural := 0;
   begin
      for I in 1 .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
         begin
            if Child in List or Child in Option then
               Counted := Counted + 1;
            end if;
         end;
      end loop;
      return Counted;
   end Count_Total_Positions;

   function Include
     (Positions : Positions_List;
      Position  : Item_Position) return Boolean is
   begin
      for I in Positions'Range loop
         if Positions (I) = Position then
            return True;
         end if;
      end loop;
      return False;
   end Include;

   procedure New_Line is
   begin
      Ada.Text_IO.New_Line;
   end New_Line;

   procedure Options_And_Lists is
   begin
      List_Phase := True;
      for I in 1 .. Rule_Count loop
         declare
            Current_Rule : constant Rule := Get_Rule (I);
         begin
            for J in 1 .. Count (Current_Rule) loop
               Options_And_Lists_In_Sequence
                 (Get_Alternative (Current_Rule, J));
            end loop;
         end;
      end loop;
      --  Put_Line ("%%");
   end Options_And_Lists;

   procedure Options_And_Lists_In_Sequence (Item : Sequence) is
   begin
      for I in 1 .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
         begin
            if Child in List then
               Print_List (List (Child));
               Options_And_Lists_In_Sequence (Items (List (Child)));
            elsif Child in Option then
               Print_Option (Option (Child));
               Options_And_Lists_In_Sequence (Items (Option (Child)));
            end if;
         end;
      end loop;
   end Options_And_Lists_In_Sequence;

   procedure Print_List (Item : in List) is
      use Unbounded_String_Lists;
      Name : constant String := Item_Name (Item);
   begin
      if not Contains (Printed_Lists, U.To_Unbounded_String (Name)) then
         Put_Line (Name & " :");
         Put ("    ");
         Print_Sequence (Items (Item), Name, Name);
         Put ("   |");
         Print_Sequence (Items (Item), Name);
         Put_Line (";");
         New_Line;
         Append (Printed_Lists, U.To_Unbounded_String (Name));
      end if;
   end Print_List;

   procedure Print_Option (Item : in Option) is
      use Unbounded_String_Lists;
      Name : constant String := Item_Name (Item);
   begin
      if Separate_Option (Item) then
         if not Contains (Printed_Options, U.To_Unbounded_String (Name)) then
            Put_Line (Name & " :");
            Put ("    ");
            Print_Sequence (Items (Item), Name);
            Put_Line (";");
            New_Line;
            Append (Printed_Options, U.To_Unbounded_String (Name));
         end if;
      end if;
   end Print_Option;

   function Is_List (Item : Sequence) return Boolean is
      R_Name : constant String := Rule_Name (Item);
      N_Name : constant String := Node_Name (Item);
   begin
      if R_Name'Length > 4 and then
        R_Name (R_Name'Last - 4 .. R_Name'Last) = "_list" then

         return True;
      end if;
      if N_Name'Length > 4 and then
        N_Name (N_Name'Last - 4 .. N_Name'Last) = ".List" then

         return True;
      end if;
      return False;
   end Is_List;

   procedure Print_Sequence_Code
     (Item                : in Sequence;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String)
   is
      R_Name : constant String := Rule_Name (Item);
   begin

      if Infix (Item) /= "" then

         Print_Infix_Code (Item, R_Name, Processed_Positions, Name_Of_List);
         return;

      end if;

      if False and then List_Phase and then Is_List (Item) then

         Print_List_Code (Item, R_Name, Processed_Positions, Name_Of_List);
         return;

      end if;

      if Pass_Through (Item) then

         declare
            First_Reference : constant Natural := Find_First_Reference (Item);
         begin
            if First_Reference = 0 and Count (Item) > 1 then
               declare
                  Child : Gramar_Items.Item'Class
                    renames Get_Item (Item, 2).all;
               begin
                  if Child in Option and Include (Processed_Positions, 2) then
                     Put_Line ("{$$ := $2;}");
                  end if;
               end;
            elsif First_Reference /= 0 then
               declare
                  Index : constant Positive := Real_Index (Item,
                     Processed_Positions, First_Reference, Name_Of_List);
               begin
                  Put_Line ("{ $$ := $" & To_String (Index) & ";}");
               end;
            end if;
         end;
         return;

      end if;

      if True_Node (Item) /= "" then
         declare
            Index : constant Natural := Choise_Item_Index (Item);
            Child : Gramar_Items.Item'Class renames Get_Item (Item, Index).all;
         begin
            if Child not in Option or else
              Include (Processed_Positions, Index) then

               Create_Alt_Nodes (Item, Processed_Positions);
               return;
            end if;
         end;
      end if;


      if R_Name = "statement" then
         if Include (Processed_Positions, 1) then
            Put_Line ("{");
            Put_Line (Indent & "Set_Label_Names (Statement_Node ($2.all), $1);");
            Put_Line (Indent & "$$ := $2;");
            Put_Line ("}");
         end if;
      elsif Node_Name (Item) /= "" then
         Put_Line ("{");
         Create_Node_Code (Item, Processed_Positions, Name_Of_List, "");
         Put_Line ("}");
      end if;

   end Print_Sequence_Code;

   procedure Create_Node_Code
     (Item                : in Sequence;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String;
      Node_Type_Name      : in String)
   is

      function Get_Node_Name
        (Wrap  : Wrapper) return String is
      begin
         if Top (Wrap) and Node_Type_Name /= "" then
            return Node_Type_Name;
         end if;
         for I in 1 .. Count (Item) loop
            declare
               Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
            begin
               if Child in Option and then
                 Include (Processed_Positions, I) and then
                 Alternative_Node_Name (Option (Child)) /= "" and then
                 Parent (Child) = Wrap then

                 return Alternative_Node_Name (Option (Child));

               end if;
            end;
         end loop;
         return Node_Name (Wrap);
      end Get_Node_Name;

      Index : Positive := 1;
      Force : Boolean := Just_Keywords (Item);
   begin

      Put_Line (Indent & "declare");
      Step_Indent (+1);

      for I in 1 .. Wrap_Count (Item) loop
         declare
            Wrap : constant Wrapper := Get_Wrapper (Item, I);
            Node : constant String  := Get_Node_Name (Wrap);
            Ptr  : constant String  := Nodes.Get_Pointer_Name (Node);
            Ind  : constant Natural := Item_Index (Wrap);
         begin
            Put_Line (Indent  & Object_Name (Wrap) & " : constant " &
                      Ptr & " :=");
            if Ind > 0 and then
              Processed (Item, Processed_Positions, Ind) then

               Put_Line (Indent & "  " & Ptr & " ($" & To_String (
                 Real_Index (Item, Processed_Positions, Ind, Name_Of_List)) &
                 ");");

            elsif I = 1 and Name_Of_List /= "" then

               Put_Line (Indent & "  " & Ptr & " ($1);");

            else
               Put_Line (Indent & "  " & New_Node (Node) & ";");
            end if;
         end;
      end loop;
      Step_Indent (-1);
      Put_Line (Indent & "begin");

      Step_Indent (+1);

      declare
         Wrap : constant Wrapper := Get_Wrapper (Item, 1);
      begin
         if Rule_Name (Item) = "compilation" then
            Put_Line (Indent & "Last_Compilation := T (" &
                      Object_Name (Wrap) & ");");
         else
            Put_Line (Indent & "$$ := YYSTYPE (" & Object_Name (Wrap) & ");");
         end if;
      end;

      if Name_Of_List /= "" then
         Index := Index + 1;
      end if;

      for I in 1 .. Count (Item) loop
         declare
            Child       : Gramar_Items.Item'Class
              renames Get_Item (Item, I).all;
            Wrap        : constant Wrapper := Parent (Child);
            Parent_Node : constant String := Get_Node_Name (Wrap);
            Parent_Name : constant String := Object_Name (Wrap);
            Wrap_Index  : constant Natural := Item_Index (Wrap);
         begin
            if Processed (Item, Processed_Positions, I) then

               if I /= Wrap_Index then
                  if Parent_Node /= "Primary_Token_Lists.List_Node" then
                     Force := False;
                  end if;

                  if (not Is_List_Type (Parent_Node) or Child in Keyword)
                    and then Is_First (Item, I, Processed_Positions)
                  then

                     Put_Line (Indent & "Set_Start_Position (" & Parent_Name &
                               ".all, Start_Position ($" &
                               To_String (Index) & ".all));");

                  end if;

                  if Parent_Node /= "Primary_Token_Lists.List_Node" then
                     Force := False;
                  end if;

                  Print_Code (Child, Parent_Node, Parent_Name, Index, Force);

                  if (not Is_List_Type (Parent_Node) or Child in Keyword)
                    and then Is_Last (Item, I, Processed_Positions)
                  then

                     Put_Line (Indent & "Set_End_Position (" & Parent_Name &
                               ".all, End_Position ($" &
                               To_String (Index) & ".all));");

                  end if;

               end if;

               Index := Index + 1;

            end  if;
         end;
      end loop;

      for I in reverse 2 .. Wrap_Count (Item) loop
         Print_Wrap_Code (Get_Wrapper (Item, I));
      end loop;

      Step_Indent (-1);
      Put_Line (Indent & "end;");

   end Create_Node_Code;

   procedure Print_Code
     (Child       : Item'Class;
      Parent_Type : String;
      Parent_Name : String;
      Index       : Positive;
      Force       : Boolean)
   is
      use Nodes;
      Attr        : constant String := Find_Attribute (Child, Parent_Type);
      Proc        : constant String := Find_Procedure (Parent_Type, Attr);
      Trait_Attr  : constant String :=
         Find_Attribute (Parent_Type, "Trait_Kind");
   begin

      if Trait_Attr /= "" then
         declare
            Proc  : constant String := Find_Procedure (Parent_Type, Trait_Attr);
            Trait : constant String := Trait_Name (Child);
         begin
            if Trait /= "" then
               Put_Line (Indent & Proc & " (" & Parent_Name &
                         ".all, " & Trait & ");");

            end if;
         end;
      end if;

      if not Force and Attr = "" and
        (Child in Keyword or Child in Delimiter) then

         return;

      end if;

      if Proc /= "" then
         if Attribute_Type (Parent_Type, Attr) = "Unbounded_Wide_String" then

            Set_Name_Image_Code (Parent_Name, Child, Index, Proc,
                In_Quote => Parent_Type = "Operator_Symbol_Node");

         else

            Put_Line (Indent & Proc & " (" & Parent_Name & ".all, $" &
                      To_String (Index) & ");");
         end if;
      end if;
   end Print_Code;

   Current_Indent : Positive := 3;

   function Indent return String is
      Spaces : constant String := "                                    ";
   begin
      return Spaces (1 .. Current_Indent);
   end;

   procedure Step_Indent (Step : Integer) is
   begin
      Current_Indent := Current_Indent + 3 * Step;
   end Step_Indent;

   procedure Token_Rules is
      procedure Print_Token_Rules is
         new Tokens.For_Each_Name (Print_Token_Rule);
   begin
      Print_Token_Rules;
   end Token_Rules;

   procedure Print_Token_Rule (Name : in String) is
      Length : constant Natural := Tokens.Token_Length (Name);
      Cap    : constant String  := Nodes.Capitalise (Name);
   begin
      Put_Line (Name & " : " & Name & "_Token");
      Put_Line ("   {");
      Put_Line (Indent & "declare");
      if Length /= 0 then
         Put_Line (Indent &
                   "   Node :  constant Token_Ptr := " &
                   New_Node ("Token_Node") & ";");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Init_Token (Element => Node.all,");
         Put_Line (Indent & "               Line    => Get_Current_Line,");
         Put_Line (Indent & "               Column  => Get_Current_Column,");
         Put_Line (Indent & "               Image   => Get_Token_Value,");
         Put_Line (Indent &
                   "               Length  => " & To_String (Length) & ");");
      else
         declare
            Node_Type_Name : constant String := Cap & "_Node";
            Ptr  : constant String := Nodes.Get_Pointer_Name (Node_Type_Name);
            Attr : constant String := Nodes.Find_Attr_By_Type
              (Node_Type_Name, "Unbounded_Wide_String");
            Proc : constant String := Nodes.Find_Procedure
              (Node_Type_Name, Attr);
         begin
            Put_Line (Indent & "   Node :  constant " & Ptr &
                      " := " & New_Node (Node_Type_Name) & ";");
            Put_Line (Indent & "   Value : constant Wide_String := Get_Token_Value;");
            Put_Line (Indent & "begin");
            Put_Line (Indent & "   " & Proc & " (Node.all, Value);");
            Put_Line (Indent & "   Set_Start_Position (Node.all,");
            Put_Line (Indent & "     (Get_Current_Line, Get_Current_Column - Value'Length));");
            Put_Line (Indent & "   Set_End_Position (Node.all,");
            Put_Line (Indent & "     (Get_Current_Line, Get_Current_Column - 1));");
         end;
      end if;
      Put_Line (Indent & "   $$ := YYSTYPE (Node);");
      Put_Line (Indent & "end;");
      Put_Line ("   };");
      New_Line;
   end Print_Token_Rule;

   function Find_Attribute
     (Child          : Item'Class;
      Node_Type_Name : String) return String
   is
      Name      : constant String := Item_Name (Child);
      Type_Name : constant String := Node_Name (Child);
      U_Attr    : constant String := User_Attr (Child);
   begin
      return Find_Attribute (Name, Type_Name, U_Attr, Node_Type_Name);
   end Find_Attribute;

   function Find_Attribute
     (Name      : String;
      Type_Name : String;
      User_Attr : String;
      Node_Type_Name : String) return String
   is
   begin
--      Put_Line ("Find_Attribute: " & Name);
--      Put_Line ("Type_Name: " & Type_Name);

      if User_Attr /= "" and then
        Nodes.Find_Attribute (Node_Type_Name, User_Attr) /= "" then

         return User_Attr;

      end if;

      if Type_Name /= "" then
         declare
            Stripped : String renames Type_Name (1 .. Type_Name'Last - 5);
            By_Name  : constant String := Nodes.Find_Attribute
              (Node_Type_Name, Stripped);
            By_Type  : constant String := Nodes.Find_Attr_By_Type
              (Node_Type_Name, Stripped);
         begin
            if By_Name /= "" then
               return By_Name;
            end if;
            if By_Type /= "" then
               return By_Type;
            end if;
         end;
      end if;

      declare
         Attr_Type : constant String := Nodes.Capitalise (Name);
         By_Name   : constant String := Nodes.Find_Attribute
           (Node_Type_Name, Attr_Type);
         By_Type   : constant String := Nodes.Find_Attr_By_Type
           (Node_Type_Name, Attr_Type);
      begin
         if By_Name /= "" then
            return By_Name;
         end if;
         if By_Type /= "" then
            return By_Type;
         end if;
      end;

      if Name = "identifier" then
         declare
            Attr_Name : constant String := Nodes.Find_Attr_By_Type
              (Node_Type_Name, "Unbounded_Wide_String");
         begin
            if Attr_Name /= "" then
               return Attr_Name;
            end if;
         end;
      end if;

      if Name = "defining_identifier" or Name = "defining_identifier_list" then

         declare
            Attr_Name : constant String := Nodes.Find_Attribute
              (Node_Type_Name, "Name");
         begin
            if Attr_Name /= "" then
               return Attr_Name;
            end if;
         end;

      end if;

      return "";
   end Find_Attribute;

   --  Append "_r" for pragma and range names
   function Translate_Name (Name : String) return String is
   begin
      if Name = "pragma" or Name = "range" or Name = "body" then
         return Name & "_r";
      else
         return Name;
      end if;
   end Translate_Name;

   function Just_Keywords (Item : in Sequence) return Boolean is
   begin
      for I in 1 .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
         begin
            if Child in Option then
               if not Just_Keywords (Items (Option (Child))) then
                  return False;
               end if;
            elsif not (Child in Delimiter or Child in Keyword) then
               return False;
            end if;
         end;
      end loop;

      return Count (Item) /= 0;
   end Just_Keywords;

   procedure Print_List_Code
     (Item                : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String)
   is

      Index     : Positive := 1;
      Node      : constant String := Node_Name (Item);
      Node_Ptr  : constant String := Nodes.Get_Pointer_Name (Node);
      Create    : constant String := Create_Node (Get_Item (Item, 1).all);
      Crt_Ptr   : constant String := Nodes.Get_Pointer_Name (Create);
      Proc      : constant String := Find_Procedure (Node, "");
   begin
      if Node = "" then
         return;
      end if;

      Put_Line ("{");

      Put_Line (Indent & "declare");
      if Name_Of_List /= "" then
         Put_Line (Indent & "   New_Node : constant " & Node_Ptr & " :=");
         Put_Line (Indent & "     " & Node_Ptr & " ($1);");
         Index := Index + 1;
      else
         Put_Line (Indent & "   New_Node : constant " & Node_Ptr & " :=");
         Put_Line (Indent & "     " & New_Node (Node) & ";");
      end if;

      if Create /= "" then
         Put_Line (Indent & "   Crt_Node : constant " & Crt_Ptr & " :=");
         Put_Line (Indent & "     " & New_Node (Create) & ";");
      end if;

      Put_Line (Indent & "begin");
      Step_Indent (+1);
      Put_Line (Indent & "$$ := YYSTYPE (New_Node);");

      if Create /= "" then
         Put_Line (Indent & "Add (New_Node.all, Crt_Node);");
      end if;

      for I in 1 .. Count (Item) loop
         declare
            Child : Gramar_Items.Item'Class renames Get_Item (Item, I).all;
            Print : Boolean := True;
         begin
            if (Child in List or Child in Option) then
               if not Include (Processed_Positions, I) then
                  Print := False;
               end if;
            elsif (Child in Delimiter or Child in Keyword)
              and then not Just_Keywords (Item)
            then
               Index := Index + 1;
               Print := False;
            end if;
            if Print then
               if Proc /= "" then
                  Put_Line (Indent & Proc & " (New_Node.all, $"
                            & To_String (Index) & ");");
               end if;
               Index := Index + 1;
            end  if;
         end;
      end loop;

      Step_Indent (-1);
      Put_Line (Indent & "end;");
      Put_Line ("}");

   end Print_List_Code;

   procedure Print_Infix_Code
     (Seq                 : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String)
   is
      First : Item'Class renames Get_Item (Seq, 1).all;
   begin
      if Count (Seq) = 5 then
         Print_Infix_Code5 (Seq, Rule_Name, Processed_Positions, Name_Of_List);
      elsif Count (Seq) = 4 then
         Print_Infix_Code1 (Seq, Rule_Name, Processed_Positions, Name_Of_List);
      elsif First in Option then
         Print_Infix_Code2 (Processed_Positions);
      elsif Count (Seq) = 2 and (First in Keyword or First in Delimiter) then
         Print_Infix_Code3 (Seq, Name_Of_List);
      elsif First in Keyword then
         Print_Infix_Code6 (Seq, Name_Of_List);
      else
         declare
            Second : Item'Class renames Get_Item (Seq, 2).all;
         begin
            if Second in Reference then
               Print_Infix_Code7 (Seq, Name_Of_List);
            else
               Print_Infix_Code4 (Processed_Positions);
            end if;
         end;
      end if;
   end Print_Infix_Code;

   --  ref keyword ref list

   procedure Print_Infix_Code1
     (Seq                 : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String)
   is
      Child : Item'Class renames Get_Item (Seq, 2).all;
   begin
      if Include (Processed_Positions, 4) then
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Call_Node1 : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "   Arg_List   : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Arg_Node1  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_Node2  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Call_Node2 : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     Function_Call_Ptr ($4);");
         Put_Line (Indent & "   Sym_Node   : constant Operator_Symbol_Ptr :=");
         Put_Line (Indent & "     new Operator_Symbol_Node;");
         Put_Line (Indent & "begin");
         Step_Indent (+1);
         Put_Line (Indent & "Set_Actual_Parameter (Arg_Node1.all, $1);");
         Put_Line (Indent & "Set_Start_Position (Arg_Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node1.all, End_Position ($1.all));");
         Put_Line (Indent & "Set_Actual_Parameter (Arg_Node2.all, $3);");
         Put_Line (Indent & "Set_Start_Position (Arg_Node2.all, Start_Position ($3.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node2.all, End_Position ($3.all));");
         Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node1));");
         Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node2));");
         Put_Line (Indent & "Set_Function_Call_Parameters (Call_Node1.all, T (Arg_List));");
         Put_Line (Indent & "Set_Start_Position (Call_Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Call_Node1.all, End_Position ($3.all));");
         Set_Name_Image_Code ("Sym_Node", Child, 2);
         Put_Line (Indent & "Set_Start_Position (Sym_Node.all, Start_Position ($2.all));");
         Put_Line (Indent & "Set_End_Position (Sym_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "Set_Prefix (Call_Node1.all, T (Sym_Node));");
         Put_Line (Indent & "Set_Is_Prefix_Call (Call_Node1.all, False);");
         Put_Line (Indent & "Push_Argument (Call_Node2.all, T (Call_Node1));");
         Put_Line (Indent & "Set_Start_Position (Call_Node2.all, Start_Position ($1.all));");
         Put_Line (Indent & "$$ := YYSTYPE (Call_Node2);");
         Step_Indent (-1);
         Put_Line (Indent & "end;");
         Put_Line ("}");
      else
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Call_Node1 : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "   Arg_List   : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Arg_Node1  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_Node2  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Sym_Node   : constant Operator_Symbol_Ptr :=");
         Put_Line (Indent & "     new Operator_Symbol_Node;");
         Put_Line (Indent & "begin");
         Step_Indent (+1);
         Put_Line (Indent & "Set_Actual_Parameter (Arg_Node1.all, $1);");
         Put_Line (Indent & "Set_Start_Position (Arg_Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node1.all, End_Position ($1.all));");
         Put_Line (Indent & "Set_Actual_Parameter (Arg_Node2.all, $3);");
         Put_Line (Indent & "Set_Start_Position (Arg_Node2.all, Start_Position ($3.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node2.all, End_Position ($3.all));");
         Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node1));");
         Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node2));");
         Put_Line (Indent & "Set_Function_Call_Parameters (Call_Node1.all, T (Arg_List));");
         Put_Line (Indent & "Set_Start_Position (Call_Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Call_Node1.all, End_Position ($3.all));");
         Put_Line (Indent & "Set_Prefix (Call_Node1.all, T (Sym_Node));");
         Set_Name_Image_Code ("Sym_Node", Child, 2);
         Put_Line (Indent & "Set_Start_Position (Sym_Node.all, Start_Position ($2.all));");
         Put_Line (Indent & "Set_End_Position (Sym_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "Set_Is_Prefix_Call (Call_Node1.all, False);");
         Put_Line (Indent & "$$ := YYSTYPE (Call_Node1);");
         Step_Indent (-1);
         Put_Line (Indent & "end;");
         Put_Line ("}");
      end if;
   end Print_Infix_Code1;

   --  opt(unar_op) ref list

   procedure Print_Infix_Code2
     (Processed_Positions : in Positions_List)
   is
   begin
      if not Include (Processed_Positions, 1) then
         Print_Infix_Code4 (Processed_Positions, 3);
         return;
      end if;
      if Include (Processed_Positions, 3) then
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Call_Node1 : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "   Arg_List   : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Arg_Node1  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Call_Node2 : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     Function_Call_Ptr ($3);");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Actual_Parameter (Arg_Node1.all, $2);");
         Put_Line (Indent & "   Set_Start_Position (Arg_Node1.all, Start_Position ($2.all));");
         Put_Line (Indent & "   Set_End_Position (Arg_Node1.all, End_Position ($2.all));");
         Put_Line (Indent & "   Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node1));");
         Put_Line (Indent & "   Set_Function_Call_Parameters (Call_Node1.all, T (Arg_List));");
         Put_Line (Indent & "   Set_Prefix (Call_Node1.all, $1);");
         Put_Line (Indent & "   Set_Start_Position (Call_Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Call_Node1.all, End_Position ($2.all));");
         Put_Line (Indent & "   Set_Is_Prefix_Call (Call_Node1.all, False);");
         Put_Line (Indent & "   Push_Argument (Call_Node2.all, T (Call_Node1));");
         Put_Line (Indent & "   Set_Start_Position (Call_Node2.all, Start_Position ($1.all));");
         Put_Line (Indent & "   $$ := YYSTYPE (Call_Node2);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      else
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Call_Node : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "   Arg_List  : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Arg_Node  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Actual_Parameter (Arg_Node.all, $2);");
         Put_Line (Indent & "   Set_Start_Position (Arg_Node.all, Start_Position ($2.all));");
         Put_Line (Indent & "   Set_End_Position (Arg_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "   Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node));");
         Put_Line (Indent & "   Set_Function_Call_Parameters (Call_Node.all, T (Arg_List));");
         Put_Line (Indent & "   Set_Prefix (Call_Node.all, $1);");
         Put_Line (Indent & "   Set_Start_Position (Call_Node.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Call_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "   Set_Is_Prefix_Call (Call_Node.all, False);");
         Put_Line (Indent & "   $$ := YYSTYPE (Call_Node);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      end if;
   end Print_Infix_Code2;

   --  keyword ref
   --  delimiter ref

   procedure Print_Infix_Code3
     (Seq                 : in Sequence;
      Name_Of_List        : in String)
   is
      First : Item'Class renames Get_Item (Seq, 1).all;
      Name  : constant String := Item_Name (First);
   begin
      if Name_Of_List = "" then
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Call_Node  : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "   Arg_List   : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Arg_Node   : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Sym_Node   : constant Operator_Symbol_Ptr :=");
         Put_Line (Indent & "     new Operator_Symbol_Node;");
         if Name = "and" or Name = "or" or Name = "xor" or Name = "double_star" then
            Put_Line (Indent & "   Arg_2_Node : constant Parameter_Association_Ptr :=");
            Put_Line (Indent & "     new Parameter_Association_Node;");
            Put_Line (Indent & "begin");
            Step_Indent (+1);
            -- make placeholder for first argument
            Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_2_Node));");
         else
            Put_Line (Indent & "begin");
            Step_Indent (+1);
         end if;
         Put_Line (Indent & "Set_Actual_Parameter (Arg_Node.all, $2);");
         Put_Line (Indent & "Set_Start_Position (Arg_Node.all, Start_Position ($2.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node));");
         Put_Line (Indent & "Set_Function_Call_Parameters (Call_Node.all, T (Arg_List));");
         Put_Line (Indent & "Set_Start_Position (Arg_Node.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "Set_Prefix (Call_Node.all, T (Sym_Node));");
         Set_Name_Image_Code ("Sym_Node", First);
         Put_Line (Indent & "Set_Start_Position (Sym_Node.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Sym_Node.all, End_Position ($1.all));");
         Put_Line (Indent & "Set_Start_Position (Call_Node.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Call_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "Set_Is_Prefix_Call (Call_Node.all, False);");
         Put_Line (Indent & "$$ := YYSTYPE (Call_Node);");
         Step_Indent (-1);
         Put_Line (Indent & "end;");
         Put_Line ("}");
      else
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Arg_Node1  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_Node2  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_List   : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Call_Node : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "   Sym_Node   : constant Operator_Symbol_Ptr :=");
         Put_Line (Indent & "     new Operator_Symbol_Node;");
         Put_Line (Indent & "begin");
         Step_Indent (+1);
         Put_Line (Indent & "Set_Actual_Parameter (Arg_Node1.all, $1);");
         Put_Line (Indent & "Set_Start_Position (Arg_Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node1.all, End_Position ($1.all));");
         Put_Line (Indent & "Set_Actual_Parameter (Arg_Node2.all, $3);");
         Put_Line (Indent & "Set_Start_Position (Arg_Node2.all, Start_Position ($3.all));");
         Put_Line (Indent & "Set_End_Position (Arg_Node2.all, End_Position ($3.all));");
         Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node1));");
         Put_Line (Indent & "Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node2));");
         Put_Line (Indent & "Set_Function_Call_Parameters (Call_Node.all, T (Arg_List));");
         Put_Line (Indent & "Set_Start_Position (Call_Node.all, Start_Position ($1.all));");
         Put_Line (Indent & "Set_End_Position (Call_Node.all, End_Position ($3.all));");
         Set_Name_Image_Code ("Sym_Node", First, 2);
         Put_Line (Indent & "Set_Start_Position (Sym_Node.all, Start_Position ($2.all));");
         Put_Line (Indent & "Set_End_Position (Sym_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "Set_Prefix (Call_Node.all, T (Sym_Node));");
         Put_Line (Indent & "Set_Is_Prefix_Call (Call_Node.all, False);");
         Put_Line (Indent & "$$ := YYSTYPE (Call_Node);");
         Step_Indent (-1);
         Put_Line (Indent & "end;");
         Put_Line ("}");
      end if;
   end Print_Infix_Code3;

   --  ref (list|option)

   procedure Print_Infix_Code4
     (Processed_Positions : in Positions_List;
      List_Index          : in Positive := 2)
   is
   begin
      if not Include (Processed_Positions, List_Index) then
         return;
      end if;
      Put_Line ("{");
      Put_Line (Indent & "declare");
      Put_Line (Indent & "   Call_Node : constant Function_Call_Ptr :=");
      Put_Line (Indent & "     Function_Call_Ptr ($2);");
      Put_Line (Indent & "begin");
      Put_Line (Indent & "   Push_Argument (Call_Node.all, $1);");
      Put_Line (Indent & "   Set_Start_Position (Call_Node.all, Start_Position ($1.all));");
      Put_Line (Indent & "   $$ := YYSTYPE (Call_Node);");
      Put_Line (Indent & "end;");
      Put_Line ("}");
   end Print_Infix_Code4;

   --  ref keyword keyword ref list

   procedure Print_Infix_Code5
     (Seq                 : in Sequence;
      Rule_Name           : in String;
      Processed_Positions : in Positions_List;
      Name_Of_List        : in String)
   is
      Node     : constant String := Node_Name (Seq);
      Node_Ptr : constant String := Nodes.Get_Pointer_Name (Node);
   begin
      if Include (Processed_Positions, 5) then
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Node1 : constant " & Node_Ptr & ":=");
         Put_Line (Indent & "     " & New_Node (Node) & ";");
         Put_Line (Indent & "   Node2 : constant " & Node_Ptr & ":=");
         Put_Line (Indent & "     " & Node_Ptr & " ($5);");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Short_Circuit_Operation_Left_Expression (Node1.all, $1);");
         Put_Line (Indent & "   Set_Start_Position (Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Node1.all, End_Position ($4.all));");
         Put_Line (Indent & "   Set_Short_Circuit_Operation_Right_Expression (Node1.all, $4);");
         Put_Line (Indent & "   Push_Argument (Node2.all, T (Node1));");
         Put_Line (Indent & "   Set_Start_Position (Node2.all, Start_Position ($1.all));");
         Put_Line (Indent & "   $$ := YYSTYPE (Node2);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      else
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Node1 : constant " & Node_Ptr & ":=");
         Put_Line (Indent & "     " & New_Node (Node) & ";");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Short_Circuit_Operation_Left_Expression (Node1.all, $1);");
         Put_Line (Indent & "   Set_Short_Circuit_Operation_Right_Expression (Node1.all, $4);");
         Put_Line (Indent & "   Set_Start_Position (Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Node1.all, End_Position ($4.all));");
         Put_Line (Indent & "   $$ := YYSTYPE (Node1);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      end if;
   end Print_Infix_Code5;

   -- list : keyword keyword ref

   procedure Print_Infix_Code6
     (Seq                 : in Sequence;
      Name_Of_List        : in String)
   is
      Node     : constant String := Node_Name (Seq);
      Node_Ptr : constant String := Nodes.Get_Pointer_Name (Node);
   begin
      if Name_Of_List /= "" then
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Node1 : constant " & Node_Ptr & ":=");
         Put_Line (Indent & "     " & New_Node (Node) & ";");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Short_Circuit_Operation_Left_Expression (Node1.all, $1);");
         Put_Line (Indent & "   Set_Short_Circuit_Operation_Right_Expression (Node1.all, $4);");
         Put_Line (Indent & "   Set_Start_Position (Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Node1.all, End_Position ($4.all));");
         Put_Line (Indent & "   $$ := YYSTYPE (Node1);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      else
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Node1 : constant " & Node_Ptr & ":=");
         Put_Line (Indent & "     " & New_Node (Node) & ";");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Short_Circuit_Operation_Right_Expression (Node1.all, $3);");
         Put_Line (Indent & "   Set_Start_Position (Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Node1.all, End_Position ($3.all));");
         Put_Line (Indent & "   $$ := YYSTYPE (Node1);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      end if;
   end Print_Infix_Code6;

   -- list: ref (oper) ref (term)

   procedure Print_Infix_Code7
     (Seq                 : in Sequence;
      Name_Of_List        : in String) is
   begin
      if Name_Of_List /= "" then
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Arg_Node1  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_Node2  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_List   : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Call_Node : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Actual_Parameter (Arg_Node1.all, $1);");
         Put_Line (Indent & "   Set_Start_Position (Arg_Node1.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Arg_Node1.all, End_Position ($1.all));");
         Put_Line (Indent & "   Set_Actual_Parameter (Arg_Node2.all, $3);");
         Put_Line (Indent & "   Set_Start_Position (Arg_Node2.all, Start_Position ($3.all));");
         Put_Line (Indent & "   Set_End_Position (Arg_Node2.all, End_Position ($3.all));");
         Put_Line (Indent & "   Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node1));");
         Put_Line (Indent & "   Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node2));");
         Put_Line (Indent & "   Set_Function_Call_Parameters (Call_Node.all, T (Arg_List));");
         Put_Line (Indent & "   Set_Start_Position (Call_Node.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Call_Node.all, End_Position ($3.all));");
         Put_Line (Indent & "   Set_Prefix (Call_Node.all, $2);");
         Put_Line (Indent & "   Set_Is_Prefix_Call (Call_Node.all, False);");
         Put_Line (Indent & "   $$ := YYSTYPE (Call_Node);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      else
         Put_Line ("{");
         Put_Line (Indent & "declare");
         Put_Line (Indent & "   Arg_Node1  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_Node2  : constant Parameter_Association_Ptr :=");
         Put_Line (Indent & "     new Parameter_Association_Node;");
         Put_Line (Indent & "   Arg_List   : constant Primary_Association_Lists.List :=");
         Put_Line (Indent & "     new Primary_Association_Lists.List_Node;");
         Put_Line (Indent & "   Call_Node : constant Function_Call_Ptr :=");
         Put_Line (Indent & "     new Function_Call_Node;");
         Put_Line (Indent & "begin");
         Put_Line (Indent & "   Set_Actual_Parameter (Arg_Node2.all, $2);");
         Put_Line (Indent & "   Set_Start_Position (Arg_Node2.all, Start_Position ($2.all));");
         Put_Line (Indent & "   Set_End_Position (Arg_Node2.all, End_Position ($2.all));");
         Put_Line (Indent & "   Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node1));");
         Put_Line (Indent & "   Primary_Association_Lists.Add (Arg_List.all, T (Arg_Node2));");
         Put_Line (Indent & "   Set_Function_Call_Parameters (Call_Node.all, T (Arg_List));");
         Put_Line (Indent & "   Set_Start_Position (Call_Node.all, Start_Position ($1.all));");
         Put_Line (Indent & "   Set_End_Position (Call_Node.all, End_Position ($2.all));");
         Put_Line (Indent & "   Set_Prefix (Call_Node.all, $1);");
         Put_Line (Indent & "   Set_Is_Prefix_Call (Call_Node.all, False);");
         Put_Line (Indent & "   $$ := YYSTYPE (Call_Node);");
         Put_Line (Indent & "end;");
         Put_Line ("}");
      end if;
   end Print_Infix_Code7;

   procedure Create_Alt_Nodes
     (Seq                 : in Sequence;
      Processed_Positions : in Positions_List)
   is
      Index   : constant Natural := Choise_Item_Index (Seq);
      R_Ind   : constant Natural :=
        Real_Index (Seq, Processed_Positions, Index, "");
      Ch_Name : constant String := Choise (Get_Item (Seq, Index).all);
   begin

      Put_Line ("{");
      Put_Line (Indent & "if $" & To_String (R_Ind) &
                ".all in " & Ch_Name & " then");
      Step_Indent (+1);
      Create_Node_Code (Seq, Processed_Positions,
                        "", True_Node (Seq));
      Step_Indent (-1);
      Put_Line (Indent & "else");
      Step_Indent (+1);
      Create_Node_Code (Seq, Processed_Positions,
                        "", False_Node (Seq));
      Step_Indent (-1);
      Put_Line (Indent & "end if;");
      Put_Line ("}");
   end Create_Alt_Nodes;

   function Processed
     (Seq                 : in Sequence;
      Processed_Positions : in Positions_List;
      Index               : Positive) return Boolean
   is
      Child : Item'Class renames Get_Item (Seq, Index).all;
   begin
      if (Child in Option or Child in List) and then
         not Include (Processed_Positions, Index) then

         return False;

      else
         return True;
      end if;
   end Processed;

   function Real_Index
     (Seq                 : in Sequence;
      Processed_Positions : in Positions_List;
      Index               : in Positive;
      Name_Of_List        : in String) return Positive
   is
      Result : Positive := Index;
   begin
      if Name_Of_List /= "" then
         Result := Result + 1;
      end if;
      for I in 1 .. Index - 1 loop
         if not Processed (Seq, Processed_Positions, I) then
            Result := Result - 1;
         end if;
      end loop;
      return Result;
   end Real_Index;

   procedure Print_Wrap_Code (Child : Wrapper) is
      Child_Name  : constant String  := Object_Name (Child);
      Child_Node  : constant String  := Node_Name (Child);
      Child_Pos   : constant String  := Position (Child);
      Wrap        : constant Wrapper := Parent (Child);
      Attr_Name   : constant String  := User_Attr_Name (Child);
      Parent_Node : constant String  := Node_Name (Wrap);
      Parent_Name : constant String  := Object_Name (Wrap);
      Attr        : constant String :=
        Find_Attribute (Child_Name, Child_Node, Attr_Name, Parent_Node);
      Proc : constant String := Find_Procedure (Parent_Node, Attr);
   begin
      if Child_Pos = "start" or Child_Pos = "both" then
         Put_Line (Indent & "Set_Start_Position (" & Parent_Name &
                   ".all, Start_Position (T (" & Child_Name & ").all));");
      end if;
      if Proc /= "" then
         Put_Line (Indent & Proc & " (" & Parent_Name & ".all, T (" &
                   Child_Name & "));");
      end if;
      if Child_Pos = "end" or Child_Pos = "both" then
         Put_Line (Indent & "Set_End_Position (" & Parent_Name &
                   ".all, End_Position (T (" & Child_Name & ").all));");
      end if;
   end Print_Wrap_Code;

   function Find_Procedure
     (Node_Name : String;
      Attr_Name : String) return String
   is
   begin
      if Is_List_Type (Node_Name) then
         return Node_Name (1 .. Node_Name'Last - 9) & "Add";
      end if;
      return Nodes.Find_Procedure (Node_Name, Attr_Name);
   end Find_Procedure;

   function New_Node (Type_Name : String) return String is
   begin
      if Type_Name = "Any_Compilation_Unit_Node" then
         return
           "Any_Compilation_Unit_Ptr (New_Compilation_Unit (The_Context))";
      else
         return "new " & Type_Name;
      end if;
   end New_Node;

   function Is_List_Type (Node_Name : String) return Boolean is
   begin
      return Node_Name'Length > 9 and then
        Node_Name (Node_Name'Last - 9 .. Node_Name'Last) = ".List_Node";
   end Is_List_Type;

   function Quote (Text : String; Double : Boolean) return String is
   begin
      if Double then
         return """""""" & Text & """""""";
      else
         return """" & Text & """";
      end if;
   end Quote;

   procedure Set_Name_Image_Code
     (Name     : in     String;
      Child    : in     Item'Class;
      Index    : in     Positive := 1;
      Proc     : in     String := "Set_Name_Image";
      In_Quote : in     Boolean  := True)
   is
   begin
      if Child in Delimiter then
         Put_Line (Indent & Proc & " (" & Name & ".all, " &
                   Quote (Text (Delimiter (Child)), In_Quote) & ");");
      elsif Child in Reference then
         declare
            Node : constant String := Node_Name (Child);
            Ptr  : constant String := Nodes.Get_Pointer_Name (Node);
            Attr : constant String := Nodes.Find_Attr_By_Type
              (Node, "Unbounded_Wide_String");
         begin
            Put_Line (Indent & Proc & " (" & Name & ".all, " & Attr & " (" &
                      Ptr & " ($" & To_String (Index) & ").all));");
         end;
      elsif In_Quote then
         Put_Line (Indent & Proc & " (" & Name & ".all, '""' & " &
                   "Value_Image ($" & To_String (Index) &
                   ".all) & '""');");
      else
         Put_Line (Indent & Proc & " (" & Name & ".all, " &
                   "Value_Image ($" & To_String (Index) &
                   ".all));");
--                 Quote (Item_Name (Child), In_Quote) & ");");
      end if;
   end Set_Name_Image_Code;

   function Is_First
     (Seq                 : in Sequence;
      Index               : in Positive;
      Processed_Positions : in Positions_List) return Boolean
   is
      Child : Item'Class renames Get_Item (Seq, Index).all;
      Wrap  : Wrapper := Parent (Child);
   begin
      for I in 1 .. Index - 1 loop
         if Processed (Seq, Processed_Positions, I) then
            declare
               Child_I : Item'Class renames Get_Item (Seq, I).all;
               Wrap_I  : Wrapper := Parent (Child_I);
            begin
               if Wrap_I = Wrap then
                  return False;
               end if;
            end;
         end if;
      end loop;
      return True;
   end Is_First;

   function Is_Last
     (Seq                 : in Sequence;
      Index               : in Positive;
      Processed_Positions : in Positions_List) return Boolean
   is
      Child : Item'Class renames Get_Item (Seq, Index).all;
      Wrap  : Wrapper := Parent (Child);
   begin
      for I in Index + 1 .. Count (Seq) loop
         if Processed (Seq, Processed_Positions, I) then
            declare
               Child_I : Item'Class renames Get_Item (Seq, I).all;
               Wrap_I  : Wrapper := Parent (Child_I);
            begin
               if Wrap_I = Wrap then
                  return False;
               end if;
            end;
         end if;
      end loop;
      return True;
   end Is_Last;

end Generate;



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

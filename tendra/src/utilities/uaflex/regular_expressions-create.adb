with Macros;
with Ada.Characters.Handling;
with Symbols.Unicode;

function Regular_Expressions.Create
  (Source : String)
   return Expression
is

   --  Full_Exp = Alter_Exp
   --
   --  Alter_Exp= Con_Exp {|Con_Exp}
   --  Con_Exp  = Item_Exp { Item_Exp }
   --  Item_Exp = Base_Exp |
   --             Base_Exp* |
   --             Base_Exp+ |
   --             Base_Exp?;
   --  Base_Exp = (Alter_Exp) |
   --             Symbol |
   --             {Macro} |
   --             Square
   --  Square   = [in_square]


   I      : Positive := Source'First;
   Result : Expression;

   procedure Next;
   function  Char                   return Character;
   function  Char_In (Set : String) return Boolean;
   function  Has_More               return Boolean;
   function  Do_Alternative         return Boolean;
   function  Do_Concatenate         return Boolean;
   function  Do_Item                return Boolean;
   function  Do_Base                return Boolean;
   function  Do_Square              return Boolean;
   function  Get_Literal            return Expression;

   procedure Read_Char (Read    : out Symbol;
                        Success : out Boolean;
                        Slash   : in  Boolean := False);

   procedure Next is
   begin
      I := I + 1;
   end Next;

   function Char return Character is
   begin
      return Source (I);
   end Char;

   function Has_More return Boolean is
   begin
      return I in Source'Range;
   end Has_More;

   function Char_In (Set : String) return Boolean is
   begin
      for J in Set'Range loop
         if Source (I) = Set (J) then
            return True;
         end if;
      end loop;

      return False;
   end;

   function Get_Literal return Expression is
      Success : Boolean;
      To_Read : Symbol;
   begin
      if Char = ']' then
         return null;
      end if;

      Read_Char (To_Read, Success);
      return New_Literal (To_Range (To_Read));
   end Get_Literal;

   function "+" (Char : Character) return Symbol is
   begin
      return Symbol (Character'Pos (Char));
   end "+";

   function Do_Alternative return Boolean is
      Left : Expression;
   begin
      if Do_Concatenate then
         Left := Result;

         while Has_More and then Char = '|'
         loop
            Next;

            if Do_Concatenate then
               Left := New_Alternative (Left, Result);
            else
               return False;
            end if;
         end loop;

         Result := Left;
         return True;
      else
         return False;
      end if;
   end Do_Alternative;

   function Do_Concatenate return Boolean is
      Left : Expression;
   begin
      if Do_Item then
         Left := Result;

         while Has_More and then Do_Item
         loop
            Left := New_Sequence (Left, Result);
         end loop;

         Result := Left;
         return True;
      else
         return False;
      end if;
   end Do_Concatenate;

   function Do_Item return Boolean is
   begin
      if Do_Base then
         if Has_More then
            case Char is
               when '*' =>
                  Result := New_Iteration (Result);
                  Next;
               when '+' =>
                  Result := New_Iteration (Result, Allow_Zero => False);
                  Next;
               when '?' =>
                  Result := New_Optional (Result);
                  Next;
               when others =>
                  null;
            end case;
         end if;

         return True;
      else
         return False;
      end if;
   end Do_Item;

   procedure Do_Name
     (From, To : out Positive;
      Success  : out Boolean) is
   begin
      Success := True;

      if not (Has_More and then Char = '{') then
         Success := False;
         return;
      end if;

      Next;
      From := I;

      while Has_More and then Char /= '}' loop
         To := I;
         Next;
      end loop;

      if Has_More and then Char = '}' then
         Next;
      else
         Success := False;
      end if;
   end Do_Name;

   function Do_Macro return Boolean is
      From, To : Positive;
      Success  : Boolean;
   begin
      Do_Name (From, To, Success);

      if Success then
         Result := Macros.Find (Source (From .. To));
      end if;

      return Success;
   end Do_Macro;

   function Do_Base return Boolean is
   begin
      case Char is
         when '[' =>
            return Do_Square;
         when '(' =>
            Next;

            if Do_Alternative and then Char = ')' then
               Next;
               return True;
            else
               return False;
            end if;
         when '{' =>
            if Do_Macro then
               Result := New_Apply (Result);
               return True;
            else
               return False;
            end if;
         when ')' =>
            return False;
         when '|' =>
            return False;
         when others =>
            Result := Get_Literal;
            return Result /= null;
      end case;
   end Do_Base;

   --    in_square = ^? ?] {-|base} (-[in_square]) ?
   --    base = char | range | \p{category} | \m{macro}
   --    range = char-char
   --    char = \?a | \uXXXX

   procedure Read_Char (Read    : out Symbol;
                        Success : out Boolean;
                        Slash   : Boolean := False)
   is
      use Ada.Characters.Handling;

      function Hex (Char : Character) return Symbol is
         Img : constant String := "16#" & Char & "#";
      begin
         return Symbol'Value (Img);
      end Hex;
   begin
      Success := True;

      if Slash or else Char = '\' then
         if not Slash then
            Next;
         end if;

         if not Has_More then
            Success := False;
            return;
         end if;

         case Char is
            when 'f' =>
               Read := +Ascii.FF;
               Next;
            when 'n' =>
               Read := +Ascii.LF;
               Next;
            when 'r' =>
               Read := +Ascii.CR;
               Next;
            when 't' =>
               Read := +Ascii.HT;
               Next;
            when 'v' =>
               Read := +Ascii.VT;
               Next;
            when 'u' =>
               Read := 0;
               Next;
               Success := Has_More and then Is_Hexadecimal_Digit (Char);

               while Has_More and then Is_Hexadecimal_Digit (Char) loop
                  Read := Read * 16 + Hex (Char);
                  Next;
               end loop;

            when others =>
               Read := +Char;
               Next;
         end case;
--      elsif Char = ']' then
--         Success := False;
--         return;
      else
         Read := +Char;
         Next;
      end if;
   end Read_Char;

   --    base = char | range | \p{category} | \m{macro}

   procedure In_Square_Base (Set     : in out Symbol_Set;
                             Success :    out Boolean) is
      First  : Symbol;
      Second : Symbol;
      Slash  : Boolean := False;
      From   : Positive;
      To     : Positive;
   begin
      Success := True;

      if Char = '\' then
         Next;

         if Char = 'p' then
            Next;
            Do_Name (From, To, Success);

            if Success then
               Set := Set or
                 Symbols.Unicode.General_Category (Source (From .. To));
            end if;

            return;
         elsif Char = 'm' then
            Next;

            if Do_Macro then
               if Result.Kind = Literal then
                  Set := Set or Result.Chars;
               else
                  Success := False;
               end if;
            else
               Success := False;
            end if;

            return;
         else
            Slash := True;
         end if;
      end if;

      Read_Char (First, Success, Slash);

      if not Success then
         return;
      end if;

      if Has_More and then Char = '-' then
         Next;
         Read_Char (Second, Success);

         if not Success then
            return;
         end if;

         Set := Set or To_Range (First, Second);
      else
         Set := Set or To_Range (First);
      end if;
   end In_Square_Base;

   --    in_square = ^? ?] {-|base} (-[in_square]) ?

   procedure In_Square
     (Set     : out Symbol_Set;
      Success : out Boolean)
   is
      Invert  : Boolean    := False;
   begin
      Success := True;

      if Char = '^' then
         Invert := True;
         Next;
      end if;

      if Char = ']' then
         Set := To_Range (+Char);
         Next;
      else
         Set := Empty;
      end if;

      while Success and then Has_More and then Char /= ']' loop
         if Char = '-' then
            Next;

            if not Has_More or else Char /= '[' then
               Set := Set or To_Range (+'-');
               Next;
            else
               --  charclass substraction
               Next;

               declare
                  Right : Symbol_Set;
               begin
                  In_Square (Right, Success);

                  if Success then
                     Set := Set - Right;

                     if Has_More and then Char = ']' then
                        Next;
                     else
                        Success := False;
                     end if;
                  end if;
               end;

               exit;
            end if;
         else
            In_Square_Base (Set, Success);
         end if;
      end loop;

      if Success and Invert then
         Set := To_Range (0, Not_A_Symbol - 1) - Set;
      end if;
   end In_Square;

   function Do_Square return Boolean is
      Set     : Symbol_Set;
      Success : Boolean;
   begin
      if Char /= '[' then
         return False;
      end if;

      Next;
      In_Square (Set, Success);

      if not Success or else not Has_More or else Char /= ']' then
         return False;
      end if;

      Next;
      Result := New_Literal (Set);

      return True;
   end Do_Square;

begin
   if Do_Alternative then
      return Result;
   else
      raise Syntax_Error;
   end if;
end Regular_Expressions.Create;


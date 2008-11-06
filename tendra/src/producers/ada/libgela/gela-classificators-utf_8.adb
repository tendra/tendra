package body Gela.Classificators.UTF_8 is

   type Second_Table is
     array (Code_Point range 0 .. 255) of
     Character_Class_Buffers.Character_Class;

   type Second_Table_Access is access all Second_Table;

   type First_Table is
     array (Code_Point range 0 .. Code_Point'Last / 256) of
     Second_Table_Access;

   Table : First_Table;

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize (Index : in Code_Point) is
      Round  : constant Code_Point := Index * 256;
      Object : constant Second_Table_Access := new Second_Table;
   begin
      for J in Round .. Round + 255 loop
         Object (J mod 256) := To_Character_Class (J);
      end loop;

      Table (Index) := Object;
   end Initialize;

   ----------
   -- Read --
   ----------

   procedure Read
     (Object : in out Classificator;
      Input  : in out Source_Buffers.Cursor;
      Buffer : in out Character_Class_Buffers.Character_Class_Buffer)
   is
      use Gela.Source_Buffers;
      use Gela.Character_Class_Buffers;

      Full         : Boolean;
      Code         : Code_Unit;
      Item         : Code_Point;
      Class        : Character_Class;
      Skip         : Natural range  0 .. 5;
      Second_Table : Second_Table_Access;
   begin
      loop
         Code  := Element (Input);
         Item  := Code_Unit'Pos (Code);

         if Code = End_Of_File then
            Class := Table (Item / 256) (Item mod 256);
            Put (Buffer, Class, Full);
            return;
         end if;

         case Item is
            when 16#00# .. 16#7F# =>
               Skip := 0;
            when 16#80# .. 2#1101_1111# =>
               Skip := 1;
               Next (Input);
               Item := (Item and 2#1_1111#) * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);
            when 2#1110_0000# .. 2#1110_1111# =>
               Skip := 2;
               Next (Input);
               Item := (Item and 2#1111#) * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);

               Next (Input);
               Item := Item * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);
            when 2#1111_0000# .. 2#1111_0111# =>
               Skip := 3;
               Next (Input);
               Item := (Item and 2#111#) * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);

               Next (Input);
               Item := Item * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);

               Next (Input);
               Item := Item * 2 ** 6 +
                 (Code_Unit'Pos (Element (Input)) and 2#11_1111#);
            when 2#1111_1000# .. 2#1111_1011# =>
               Skip := 4;
               Item := 16#FFFF#;
               Next (Input);
               Next (Input);
               Next (Input);
               Next (Input);
            when others =>
               Skip := 5;
               Item := 16#FFFF#;
               Next (Input);
               Next (Input);
               Next (Input);
               Next (Input);
               Next (Input);
         end case;

         Second_Table := Table (Item / 256);

         if Second_Table = null then
            Initialize (Item / 256);
            Second_Table := Table (Item / 256);
         end if;

         Class := Second_Table (Item mod 256);
         Put (Buffer, Class, Full);
         Next (Input);

         for J in 1 .. Skip loop
            Put (Buffer, Skip_Code, Full);
         end loop;

         if Full then
            Put (Buffer, End_Of_Buffer, Full);
            return;
         end if;
      end loop;
   end Read;

begin
   Initialize (0);
end Gela.Classificators.UTF_8;

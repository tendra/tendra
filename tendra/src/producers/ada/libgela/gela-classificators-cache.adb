package body Gela.Classificators.Cache is

   type Second_Table is
     array (Code_Point range 0 .. 255) of
     Character_Class_Buffers.Character_Class;

   type Second_Table_Access is access all Second_Table;

   type First_Table is
     array (Code_Point range 0 .. Code_Point'Last / 256) of
     Second_Table_Access;

   Table : First_Table;

   procedure Initialize (Index : in Code_Point);

   -------------------------
   -- Get_Character_Class --
   -------------------------

   function Get_Character_Class
     (Code : Code_Point)
     return Character_Class_Buffers.Character_Class
   is
      Second_Table : Second_Table_Access := Table (Code / 256);
   begin
      if Second_Table = null then
         Initialize (Code / 256);
         Second_Table := Table (Code / 256);
      end if;

      return Second_Table (Code mod 256);
   end Get_Character_Class;

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

   ----------------
   -- Initialize --
   ----------------

   procedure Initialize is
   begin
      if Table (0) = null then
         Initialize (0);
      end if;
   end Initialize;

end Gela.Classificators.Cache;

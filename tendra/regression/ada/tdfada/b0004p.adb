package body B0004P is

   ------------------
   -- And_Operator --
   ------------------

   procedure And_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left and Right;
   end And_Operator;

   -----------------
   -- Or_Operator --
   -----------------

   procedure Or_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left or Right;
   end Or_Operator;

   ------------------
   -- Xor_Operator --
   ------------------

   procedure Xor_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left xor Right;
   end Xor_Operator;

   --------------------
   -- Equal_Operator --
   --------------------

   procedure Equal_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left = Right;
   end Equal_Operator;

   ------------------------
   -- Not_Equal_Operator --
   ------------------------

   procedure Not_Equal_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left /= Right;
   end Not_Equal_Operator;

   ------------------------
   -- Less_Than_Operator --
   ------------------------

   procedure Less_Than_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left < Right;
   end Less_Than_Operator;

   ---------------------------------
   -- Less_Than_Or_Equal_Operator --
   ---------------------------------

   procedure Less_Than_Or_Equal_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left <= Right;
   end Less_Than_Or_Equal_Operator;

   ---------------------------
   -- Greater_Than_Operator --
   ---------------------------

   procedure Greater_Than_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left > Right;
   end Greater_Than_Operator;

   ------------------------------------
   -- Greater_Than_Or_Equal_Operator --
   ------------------------------------

   procedure Greater_Than_Or_Equal_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left >= Right;
   end Greater_Than_Or_Equal_Operator;

   ------------------
   -- Not_Operator --
   ------------------

   procedure Not_Operator
     (Left   : Boolean;
      Result : out Boolean)
   is
   begin
      Result := not Left;
   end Not_Operator;

   -----------------------
   -- And_Then_Operator --
   -----------------------

   procedure And_Then_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left and then Right;
   end And_Then_Operator;

   ----------------------
   -- Or_Else_Operator --
   ----------------------

   procedure Or_Else_Operator
     (Left, Right : Boolean;
      Result : out Boolean)
   is
   begin
      Result := Left or else Right;
   end Or_Else_Operator;

end B0004P;

package B0004P is
   procedure And_Operator 
     (Left, Right : Boolean; Result : out Boolean);
   procedure Or_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Xor_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Equal_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Not_Equal_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Less_Than_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Less_Than_Or_Equal_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Greater_Than_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Greater_Than_Or_Equal_Operator
     (Left, Right : Boolean; Result : out Boolean);
   procedure Not_Operator
     (Left : Boolean; Result : out Boolean);
   procedure And_Then_Operator 
     (Left, Right : Boolean; Result : out Boolean);
   procedure Or_Else_Operator
     (Left, Right : Boolean; Result : out Boolean);
end;

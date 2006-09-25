Tokdec Boolean.V : [] VARIETY;
Tokdec ~Set_signal_handler : [] EXP;
Tokdec .~rep_var_width : [NAT] NAT;

Iddec TDF_Exception:proc;

Tokdef A_UNIVERSAL_INTEGER_DEFINITION.V =
  [] VARIETY

  var_width (true, 64);

Tokdef One =
  [] EXP

  1 (A_UNIVERSAL_INTEGER_DEFINITION.V);

Tokdef A_ROOT_INTEGER_DEFINITION.V =
  [] VARIETY

  var_width (true, 64);

Tokdef A_ROOT_INTEGER_DEFINITION =
  [] SHAPE

  integer (A_ROOT_INTEGER_DEFINITION.V);

Tokdef A_ROOT_INTEGER_DEFINITION.A_SUCC_ATTRIBUTE =
  [Left:EXP] EXP

  (Left + 1 (A_ROOT_INTEGER_DEFINITION.V));

Tokdef A_ROOT_INTEGER_DEFINITION.A_PRED_ATTRIBUTE =
  [Left:EXP] EXP

  (Left - 1 (A_ROOT_INTEGER_DEFINITION.V));

Tokdef Character.LOWER =
  [] EXP

  0(A_UNIVERSAL_INTEGER_DEFINITION.V);

Tokdef Character.UPPER =
  [] EXP

  255(A_UNIVERSAL_INTEGER_DEFINITION.V);

Tokdef Integer.LOWER =
  [] EXP

  -2147483647(A_UNIVERSAL_INTEGER_DEFINITION.V) - One;
/* Temporary until trans bug #79 fixed
  -2147483648(A_UNIVERSAL_INTEGER_DEFINITION.V);
*/

Tokdef Integer.UPPER =
  [] EXP

  2147483647(A_UNIVERSAL_INTEGER_DEFINITION.V);


Tokdef COMPARE_INTEGER_VALUE =
  [Test  : NTEST,
   Left  : EXP,
   Right : EXP] EXP

?{
   ?(Left Test Right);
   1(Boolean.V)
   | 0(Boolean.V)
};

Tokdef BOOLEAN_JUMP =
  [Inv    : NAT,
   Value  : EXP,
   Target : LABEL] EXP

?(Value != + Inv(Boolean.V) | Target);

Proc Ada_Init = top ()
{
  ~Set_signal_handler;
  return(make_top)
};         

Tokdef ~Throw = [x : NAT] EXP
{
  TDF_Exception[top](+ x(Int));
};

Tokdef CONSTRAINT_ERROR_IF =
  [Value  : EXP,
   Target : LABEL] EXP

?{
   Value
   | :Target: TDF_Exception[top](111(Int))
};

Tokdef ENUM_SUCC_PRED_ATTR =
  [Value   : EXP,
   Limit   : EXP,
   Type    : VARIETY,
   Is_Pred : NAT] EXP

?{
   ?(Value NTEST ? (+ Is_Pred(Boolean.V), <= , >= ) Limit);
   TDF_Exception[top](111(Int));
   make_value (integer (Type))
   | plus (impossible,
           Value,
           EXP ? (+ Is_Pred(Boolean.V), -1(Type), 1(Type)))
};

Tokdef SIGNED_SUCC_PRED_ATTR =
  [Value   : EXP,
   Type    : VARIETY,
   Is_Pred : NAT] EXP

?{
   plus (to_raise,
         Value,
         EXP ? (+ Is_Pred(Boolean.V), -1(Type), 1(Type)))
   | :to_raise:
     make_value (integer (Type))
};

/*  Temporary until trans bug #80 fixed
?{
   plus (to_raise,
         Value,
         EXP ? (+ Is_Pred(Boolean.V), -1(Type), 1(Type)))
   | :to_raise:
     TDF_Exception[top](111(Int));
     make_value (integer (Type))
};
*/

Tokdef ENUM_VAL_ATTR =
  [Value   : EXP,
   Lower   : EXP,
   Upper   : EXP,
   Type    : VARIETY] EXP

?{ 
   Let Temp = change_variety (to_raise, Type, Value)
   {
     ?(Temp < Lower | to_raise);
     ?(Temp > Upper | to_raise);
     Temp
   }
   | :to_raise:
     TDF_Exception[top](111(Int));
     make_value (integer (Type))
};

Tokdef SIGNED_VAL_ATTR =
  [Value   : EXP,
   Type    : VARIETY] EXP

?{ 
   change_variety (to_raise, Type, Value)
   | :to_raise:
     make_value (integer (Type))
};

/*  Temporary until trans bug #80 fixed
?{ 
   change_variety (to_raise, Type, Value)
   | :to_raise:
     TDF_Exception[top](111(Int));
     make_value (integer (Type))
};
*/

/* S'Base'First/Last related tokens */

Tokdef Bits =
  [] VARIETY

  var_width (false, 8);

Tokdef ITEST = [a:EXP, comp:NTEST, b:EXP] EXP	/* exp integer test */
  ?{ ?(a comp b); 1(Bits) | 0(Bits) };

Tokdef Is_Size_Supported =
  [Size  : NAT] EXP

  ITEST [+ Size (Bits), ==, + .~rep_var_width [Size] (Bits)];

Tokdef Signed_Fits_Size =
  [Value : EXP,
   Size  : NAT,
   Type  : VARIETY] EXP

  ITEST [([Type] Value >> (+ Size (Bits) - 1 (Bits))),
         ==,
         EXP ?(ITEST [[Type] Value, <, 0(Type)], - 1(Type), 0(Type)) ];

Tokdef Range_Fits_Size =
  [Upper : EXP,
   Lower : EXP,
   Size  : NAT,
   Type  : VARIETY] EXP

  Is_Size_Supported [Size]
  And
  (Signed_Fits_Size [Upper, Size, Type]
   And
   Signed_Fits_Size [Lower, Size, Type]);

Tokdef SIGNED_BASE_UPPER =
  [Upper : EXP,
   Lower : EXP,
   Type  : VARIETY] EXP

  EXP ? (Range_Fits_Size [Upper, Lower, 8, Type], 16r7f(Type),
    EXP ? (Range_Fits_Size [Upper, Lower, 16, Type], 16r7fff(Type),
      EXP ? (Range_Fits_Size [Upper, Lower, 32, Type], 16r7fffffff(Type),
        EXP ? (Range_Fits_Size [Upper, Lower, 64, Type],
               16r7fffffffffffffff(Type),
               # "Range too wide"
  ))));

Tokdef SIGNED_BASE_LOWER =
  [Upper : EXP,
   Lower : EXP,
   Type  : VARIETY] EXP

  EXP ? (Range_Fits_Size [Upper, Lower, 8, Type], -16r80(Type),
    EXP ? (Range_Fits_Size [Upper, Lower, 16, Type], -16r8000(Type),
      EXP ? (Range_Fits_Size [Upper, Lower, 32, Type], -16r80000000(Type),
        EXP ? (Range_Fits_Size [Upper, Lower, 64, Type],
               -16r8000000000000000(Type),
               # "Range too wide"
  ))));

/* Mod integer related tokens */

Tokdef Is_Non_Binary =
  [Last  : EXP] EXP

  ((Last + One) And Last);

Tokdef Non_Binary_Mod_Oper =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY,
   Oper  : TOKEN[EXP,EXP]EXP,
   Wider : VARIETY] EXP

  ([Type] (Oper [[Wider] Left, [Wider] Right] %1 [Wider] (Last + One)));

Tokdef Binary_Mod_Oper =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY,
   Oper  : TOKEN[EXP,EXP]EXP] EXP

  (Oper [Left, Right] And [Type] Last);

Tokdef MOD_PLUS =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        Non_Binary_Mod_Oper [Left, Right, Last, Type,
                             Use [a:EXP, b:EXP] EXP (a + b),
                             0 : + computed_nat (Last + Last)],
        Binary_Mod_Oper [Left, Right, Last, Type,
                         Use [a:EXP, b:EXP] EXP (a + b)]);

Tokdef MOD_MINUS =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        Non_Binary_Mod_Oper [Left, Right, Last, Type,
                             Use [a:EXP, b:EXP] EXP (a - b),
                             - computed_nat (Last) : + computed_nat (Last)],
        Binary_Mod_Oper [Left, Right, Last, Type,
                         Use [a:EXP, b:EXP] EXP (a - b)]);

Tokdef MOD_MULTIPLY =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        Non_Binary_Mod_Oper [Left, Right, Last, Type,
                             Use [a:EXP, b:EXP] EXP (a * b),
                             0 : + computed_nat (Last * Last)],
        Binary_Mod_Oper [Left, Right, Last, Type,
                         Use [a:EXP, b:EXP] EXP (a * b)]);

Tokdef MOD_OR =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        Non_Binary_Mod_Oper [Left, Right, Last, Type,
                             Use [a:EXP, b:EXP] EXP (a Or b),
                             Type],
        Left Or Right);

Tokdef MOD_XOR =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        Non_Binary_Mod_Oper [Left, Right, Last, Type,
                             Use [a:EXP, b:EXP] EXP (a Xor b),
                             Type],
        Left Xor Right);

Tokdef MOD_AND =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        Non_Binary_Mod_Oper [Left, Right, Last, Type,
                             Use [a:EXP, b:EXP] EXP (a And b),
                             Type],
        Left And Right);

Tokdef MOD_NOT =
  [Left  : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        ([Type] Last) - Left,
        Left Xor [Type] Last);

Tokdef MOD_NEGATIVE =
  [Left  : EXP,
   Last  : EXP,
   Type  : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        (([Type] (Last + One)) - Left) %1 [Type] (Last + One),
        - (Left) And [Type] Last);

Tokdef Non_Binary_Mod_Power =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY,
   LType : VARIETY] EXP

  Var r : integer (Type)  = 1 (Type)
  Var x : integer (Type)  = Left
  Var y : integer (LType) = Right
  {
    ?{  ?( * y <= 0 (LType));
        |
        Rep {
            ?{ ?( * y And 1 (LType) != 0 (LType));
               r = Non_Binary_Mod_Oper [* r, * x, Last, Type,
                                        Use [a:EXP, b:EXP] EXP (a * b),
                                        0 : + computed_nat (Last * Last)];
               y = (* y  -  1 (LType))
             |
               x = Non_Binary_Mod_Oper [* x, * x, Last, Type,
                                        Use [a:EXP, b:EXP] EXP (a * b),
                                        0 : + computed_nat (Last * Last)];
               y = (* y  >>  1 (LType))
            };
           ?( * y <= 0 (LType))
        }
    };
    * r
  };


Tokdef MOD_POWER =
  [Left  : EXP,
   Right : EXP,
   Last  : EXP,
   Type  : VARIETY,
   LType : VARIETY] EXP

  EXP ?(Is_Non_Binary [Last],
        Non_Binary_Mod_Power [Left, Right, Last, Type, LType],
        Binary_Mod_Oper [Left, Right, Last, Type,
                         Use [a:EXP, b:EXP] EXP (power (wrap, a, b))]);

/*
Tokdef T = [] VARIETY 0 : 9;

Var x : Int = MOD_MINUS [3 (T), 8 (T),
  9 (A_UNIVERSAL_INTEGER_DEFINITION.V), T];
*/

Tokdef TEST_RANGE_JUMP =
  [Value  : EXP,
   Lower  : EXP,
   Upper  : EXP,
   Inv    : NAT,
   Target : LABEL] EXP
  EXP ?(+ Inv (Boolean.V),
        ?{
          ?(Value >= Lower);
          ?(Value > Upper | Target)
          | make_top
        },
        {
          ?(Value >= Lower | Target);
          ?(Value <= Upper | Target)
        });

Keep (COMPARE_INTEGER_VALUE,
      BOOLEAN_JUMP,
      Character.LOWER,
      Character.UPPER,
      Integer.LOWER,
      Integer.UPPER,
      A_UNIVERSAL_INTEGER_DEFINITION.V,
      A_ROOT_INTEGER_DEFINITION.V,
      A_ROOT_INTEGER_DEFINITION,
      A_ROOT_INTEGER_DEFINITION.A_SUCC_ATTRIBUTE,
      A_ROOT_INTEGER_DEFINITION.A_PRED_ATTRIBUTE,
      Ada_Init,
      ~Throw,
      CONSTRAINT_ERROR_IF,
      ENUM_SUCC_PRED_ATTR,
      SIGNED_SUCC_PRED_ATTR,
      ENUM_VAL_ATTR,
      SIGNED_VAL_ATTR,
      SIGNED_BASE_UPPER,
      SIGNED_BASE_LOWER,
      MOD_PLUS,
      MOD_MINUS,
      MOD_MULTIPLY,
      MOD_OR,
      MOD_XOR,
      MOD_AND,
      MOD_NOT,
      MOD_NEGATIVE,
      MOD_POWER,
      TEST_RANGE_JUMP
      )


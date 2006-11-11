Tokdec Boolean.V : [] VARIETY;
Tokdec ~Set_signal_handler : [] EXP;
Tokdec .~rep_var_width     : [NAT] NAT;
Tokdec .~rep_fv            : [NAT] FLOATING_VARIETY;
Tokdec .~rep_fv_width      : [NAT] NAT;
Tokdec .~rep_fv_radix      : [NAT] NAT;
Tokdec .~rep_fv_mantissa   : [NAT] NAT;
Tokdec .~rep_fv_max_val    : [NAT] EXP;
Tokdec .~rep_fv_min_exp    : [NAT] NAT;
Tokdec .~rep_fv_max_exp    : [NAT] NAT;

Iddec TDF_Exception:proc;

Tokdef A_UNIVERSAL_INTEGER_DEFINITION.V =
  [] VARIETY

  var_width (true, 64);

Tokdef universal =     /* shortcut */
  [] VARIETY

  A_UNIVERSAL_INTEGER_DEFINITION.V;

Tokdef One =
  [] EXP

  1 (universal);

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

  0(universal);

Tokdef Character.UPPER =
  [] EXP

  255(universal);

Tokdef Integer.LOWER =
  [] EXP

  -2147483647(universal) - One;
/* Temporary until trans bug #79 fixed
  -2147483648(universal);
*/

Tokdef Integer.UPPER =
  [] EXP

  2147483647(universal);


Tokdef COMPARE_INTEGER_VALUE =
  [Test  : NTEST,
   Left  : EXP,
   Right : EXP] EXP

?{
   ?(Left Test Right);
   1(Boolean.V)
   | 0(Boolean.V)
};

Tokdef COMPARE_FLOAT_VALUE =
  [Test  : NTEST,
   Left  : EXP,
   Right : EXP] EXP

?{
   F?(Left Test Right);
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
  TDF_Exception[bottom](+ x(Int));
};

Tokdef CONSTRAINT_ERROR_IF =
  [Value  : EXP,
   Target : LABEL] EXP

?{
   Value
   | :Target: TDF_Exception[bottom](111(Int))
};


Iddec printf:proc;
String s1 = "%d is not in [%d,%d]\n";

Tokdef IN_BOUNDS =
  [First  : EXP,
   Last   : EXP,
   Value  : EXP] EXP

Let Temp = Value
?{
   ?(First <= Temp);
   ?(Temp  <= Last);
   Temp
 | TDF_Exception[bottom](111(Int))
};

Tokdef FLOAT_IN_BOUNDS =
  [First  : EXP,
   Last   : EXP,
   Value  : EXP] EXP

Let Temp = Value
?{
   F?(First <= Temp);
   F?(Temp  <= Last);
   Temp
 | TDF_Exception[bottom](111(Int))
};

Tokdef ENUM_SUCC_PRED_ATTR =
  [Value   : EXP,
   Limit   : EXP,
   Type    : VARIETY,
   Is_Pred : NAT] EXP

?{
   ?(Value NTEST ? (+ Is_Pred(Boolean.V), <= , >= ) Limit);
   TDF_Exception[bottom](111(Int))
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
     TDF_Exception[bottom](111(Int))
};

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
     TDF_Exception[bottom](111(Int))
};

Tokdef SIGNED_VAL_ATTR =
  [Value   : EXP,
   Type    : VARIETY] EXP

?{ 
   change_variety (to_raise, Type, Value)
   | :to_raise:
     TDF_Exception[bottom](111(Int))
};


/* S'Base'First/Last related tokens */

Tokdef Bits =
  [] VARIETY

  var_width (false, 8);

Tokdef ITEST = [a:EXP, comp:NTEST, b:EXP] EXP	/* exp integer test */
  ?{ ?(a comp b); 1(Bits) | 0(Bits) };

Tokdef FTEST = [a:EXP, comp:NTEST, b:EXP] EXP	/* exp float test */
  ?{ F? (a comp b); 1(Bits) | 0(Bits) };

Tokdef NATTEST = [a:NAT, comp:NTEST, b:NAT] EXP
  ITEST [+ a (universal),
         comp,
         + b (universal)];

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

/* Float point tokens */

Tokdef A_UNIVERSAL_REAL_DEFINITION.V =
  [] FLOATING_VARIETY

  flvar_parms (2, 128, 16384, 32768);

Tokdef Check_Float_Id =
  [Id        : NAT,
   Lower     : EXP,
   Upper     : EXP,
   Digits_10 : EXP,
   Digits_2  : EXP] EXP

  EXP ? (
   NATTEST [.~rep_fv_width [Id], ==, 0],
   # "no such float",
    (NATTEST [.~rep_fv_radix [Id], ==, 2]
     And
     ITEST [Digits_2, <=,
            + .~rep_fv_mantissa [Id] (universal)])
    /*
     this traps installer with signal 11
     And
     FTEST [Upper, <=, change_floating_variety
             (imposible, A_UNIVERSAL_REAL_DEFINITION.V, .~rep_fv_max_val [Id])]
    */
    Or
     (NATTEST [.~rep_fv_radix [Id], ==, 10]
      And
      ITEST [Digits_10, <=,
             + .~rep_fv_mantissa [Id] (universal)])
  )
;

Tokdef Check_Float_Id_10 =
  [Id     : NAT,
   Lower  : EXP,
   Upper  : EXP,
   Digits : EXP] EXP
  Check_Float_Id
    [Id,
     Lower,
     Upper,
     Digits,
     ((332 (universal) * Digits)
       / 100 (universal)) + One];

Tokdef MAKE_FLOAT_RANGE_ID =
  [Lower  : EXP,
   Upper  : EXP,
   Digits : EXP] NAT
  NAT ?(Check_Float_Id_10 [1, Lower, Upper, Digits], 1,
    NAT ?(Check_Float_Id_10 [2, Lower, Upper, Digits], 2,
      NAT ?(Check_Float_Id_10 [3, Lower, Upper, Digits], 3, 4)));

Tokdef MAKE_FLOAT_ID =
  [Digits : EXP] NAT
  MAKE_FLOAT_RANGE_ID /* -10 ** (4*D) .. 10 ** (4*D) */
    [floating_power (impossible,
                     10.0 (A_UNIVERSAL_REAL_DEFINITION.V),
                     4 (universal) * Digits),
     floating_negate (impossible,
       floating_power (impossible,
                       10.0 (A_UNIVERSAL_REAL_DEFINITION.V),
                       4 (universal) * Digits)),
     Digits];

Tokdef MAKE_MACHINE_EMAX_ATTRIBUTE =
  [Id : NAT] EXP
  One + (+ .~rep_fv_max_exp [Id] (universal));

Tokdef MAKE_MACHINE_EMIN_ATTRIBUTE =
  [Id : NAT] EXP
  (- .~rep_fv_min_exp [Id] (universal))
  +
  (+ .~rep_fv_mantissa [Id] (universal));

Tokdef MAKE_MACHINE_MANTISSA_ATTRIBUTE =
  [Id : NAT] EXP
  (+ .~rep_fv_mantissa [Id] (universal));

Tokdef MAKE_MACHINE_RADIX_ATTRIBUTE =
  [Id : NAT] EXP
  (+ .~rep_fv_radix [Id] (universal));

/* x86 dependent: */

Tokdef Float.FLOAT_ID = [] NAT
  1;

Tokdef MAKE_DENORM_ATTRIBUTE =
  [Id : NAT] EXP
  1 (Boolean.V); /* Are Float & Double really Denorm? */

Tokdef MAKE_MACHINE_OVERFLOWS_ATTRIBUTE =
  [Id : NAT] EXP
  1 (Boolean.V);

Tokdef MAKE_MACHINE_ROUNDS_ATTRIBUTE =
  [Id : NAT] EXP
  1 (Boolean.V);

Tokdef MAKE_SIGNED_ZEROS_ATTRIBUTE =
  [Id : NAT] EXP
  1 (Boolean.V);

Tokdef Round =
  [Value : EXP,
   Width : NAT,
   float : FLOATING_VARIETY,
   Mode  : ROUNDING_MODE] EXP
  ?{
     float_int
       (impossible,
        float,
        round_with_mode
          (Target,
           Mode,
           var_width (false, Width),
           Value))
     | :Target: Value
  };

Tokdef MAKE_CEILING_ATTRIBUTE =
  [Id    : NAT,
   Value : EXP] EXP
  Let X = Value
  ?{
     F?(X >= 0.0 (.~rep_fv [Id]));
     Round [X, .~rep_fv_mantissa [Id], .~rep_fv [Id], toward_larger]
     | floating_negate (impossible,
       Round [floating_negate (impossible, X),
              .~rep_fv_mantissa [Id], .~rep_fv [Id], toward_smaller])
  };

Tokdef MAKE_FLOOR_ATTRIBUTE =
  [Id    : NAT,
   Value : EXP] EXP
  Let X = Value
  ?{
     F?(X >= 0.0 (.~rep_fv [Id]));
     Round [X, .~rep_fv_mantissa [Id], .~rep_fv [Id], toward_smaller]
     | floating_negate (impossible,
       Round [floating_negate (impossible, X),
              .~rep_fv_mantissa [Id], .~rep_fv [Id], toward_larger])
  };

Tokdef MAKE_ROUNDING_ATTRIBUTE =
  [Id    : NAT,
   Value : EXP] EXP
  Let X = Value
  ?{
     F?(X >= 0.0 (.~rep_fv [Id]));
     Round [X, .~rep_fv_mantissa [Id], .~rep_fv [Id], to_nearest]
     | floating_negate (impossible,
       Round [floating_negate (impossible, X),
              .~rep_fv_mantissa [Id], .~rep_fv [Id], to_nearest])
  };

Tokdef MAKE_TRUNCATION_ATTRIBUTE =
  [Id    : NAT,
   Value : EXP] EXP
  Let X = Value
  ?{
     F?(X >= 0.0 (.~rep_fv [Id]));
     Round [X, .~rep_fv_mantissa [Id], .~rep_fv [Id], toward_smaller]
     | floating_negate (impossible,
       Round [floating_negate (impossible, X),
              .~rep_fv_mantissa [Id], .~rep_fv [Id], toward_smaller])
  };

/* Fixed point tokens */

Tokdef A_UNIVERSAL_FIXED_DEFINITION.V =
  [] VARIETY

  var_width (true, 64);

Tokdef To_Small =
  [Power : SIGNED_NAT] EXP
  floating_power (impossible,
                  2.0 (A_UNIVERSAL_REAL_DEFINITION.V),
                  Power (universal));

Tokdef Check_Small =
  [Delta : EXP,
   Power : SIGNED_NAT] EXP
  FTEST [Delta, >=, To_Small [Power]];

/* Perhaps recursive tokens could help with this:
*/

Tokdef MAKE_SMALL_ATTRIBUTE =
  [Delta : EXP] EXP
  EXP ? (Check_Small [Delta, 8], To_Small [ 8],
  EXP ? (Check_Small [Delta, 7], To_Small [ 7],
  EXP ? (Check_Small [Delta, 6], To_Small [ 6],
  EXP ? (Check_Small [Delta, 5], To_Small [ 5],
  EXP ? (Check_Small [Delta, 4], To_Small [ 4],
  EXP ? (Check_Small [Delta, 3], To_Small [ 3],
  EXP ? (Check_Small [Delta, 2], To_Small [ 2],
  EXP ? (Check_Small [Delta, 1], To_Small [ 1],
  EXP ? (Check_Small [Delta, 0], To_Small [ 0],
  EXP ? (Check_Small [Delta,-1], To_Small [-1],
  EXP ? (Check_Small [Delta,-2], To_Small [-2],
  EXP ? (Check_Small [Delta,-3], To_Small [-3],
  EXP ? (Check_Small [Delta,-4], To_Small [-4],
  EXP ? (Check_Small [Delta,-5], To_Small [-5],
  EXP ? (Check_Small [Delta,-6], To_Small [-6],
  EXP ? (Check_Small [Delta,-7], To_Small [-7],
  EXP ? (Check_Small [Delta,-8], To_Small [-8],
 # "Delta too small")))))))))))))))))
;

/*
Tokdef Fixed_Fits_Size =
  [Lower : EXP,
   Upper : EXP,
   Small : EXP,
   Size  : NAT] EXP
  Range_Fits_Size
   [round_with_mode (impossible,
                     toward_zero,
                     A_UNIVERSAL_INTEGER_DEFINITION.V,
                     floating_div (impossible, Lower, Small)),
    round_with_mode (impossible,
                     toward_zero,
                     A_UNIVERSAL_INTEGER_DEFINITION.V,
                     floating_div (impossible, Upper, Small)),
    Size,
    A_UNIVERSAL_INTEGER_DEFINITION.V];
*/

Tokdef Div_Scale =
  [Left_Small  : EXP,
   Right_Small : EXP,
   Small       : EXP] EXP

  EXP ? (FTEST [Left_Small, >=, Right_Small F* Small],
         round_with_mode (impossible, to_nearest, universal,
           Left_Small F/ (Right_Small F* Small)),
         round_with_mode (impossible, to_nearest, universal,
           (Right_Small F* Small) F/ Left_Small)
         );

Tokdef Fixed_Div =
  [Left        : EXP,
   Right       : EXP,
   Cast        : VARIETY,
   M_Scale     : EXP,
   D_Scale     : EXP,
   Raise       : ERROR_TREATMENT] EXP

  (
    div2 (Raise, Raise, ([Cast] Left * [Cast] M_Scale), [Cast] Right)
      / [Cast] D_Scale
  );

Tokdef FIXED_DIVIDE =
  [Left        : EXP,
   Right       : EXP,
   Result      : VARIETY,
   Left_Upper  : EXP,
   Right_Upper : EXP,
   Left_Small  : EXP,
   Right_Small : EXP,
   Small       : EXP,
   Raise       : ERROR_TREATMENT] EXP

  EXP ? (FTEST [Left_Small, >=, Right_Small F* Small],

    EXP ? (ITEST [[universal] Left_Upper
                  * Div_Scale [Left_Small, Right_Small, Small],
                  >=,
                  [universal] Right_Upper],
      [Result] Fixed_Div [Left, Right,
         /* Cast => */    - computed_nat ([universal] Left_Upper
                            * Div_Scale [Left_Small, Right_Small, Small])
                          :
                          + computed_nat ([universal] Left_Upper
                            * Div_Scale [Left_Small, Right_Small, Small]),
         /* M_Scale => */ Div_Scale [Left_Small, Right_Small, Small],
                          1 (universal), Raise],

    /* else: Left_Upper * Scale < Right_Upper */

      [Result] Fixed_Div [Left, Right,
         /* Cast => */    - computed_nat (Right_Upper)
                          :
                          + computed_nat (Right_Upper),
         /* M_Scale => */ Div_Scale [Left_Small, Right_Small, Small],
                          1 (universal), Raise]),

  /* else: Left_Small < Right_Small * Small */

    EXP ? (ITEST [Left_Upper, >=, Right_Upper],
      [Result] Fixed_Div [Left, Right,
                          - computed_nat (Left_Upper)
                          :
                          + computed_nat (Left_Upper),
                          1 (universal),
                          Div_Scale [Left_Small, Right_Small, Small],
                          Raise],

    /* else: Left_Upper < Right_Upper */

      [Result] Fixed_Div [Left, Right,
                          - computed_nat (Right_Upper)
                          :
                          + computed_nat (Right_Upper),
                          1 (universal),
                          Div_Scale [Left_Small, Right_Small, Small],
                          Raise])
  );


Tokdef Mult_Scale =
  [Left_Small  : EXP,
   Right_Small : EXP,
   Small       : EXP] EXP

  EXP ? (FTEST [Left_Small F* Right_Small, >=, Small],
         round_with_mode (impossible, to_nearest, universal,
           (Left_Small F* Right_Small) F/ Small),
         round_with_mode (impossible, to_nearest, universal,
           Small F/ (Right_Small F* Left_Small))
         );

Tokdef Fixed_Mult =
  [Left        : EXP,
   Right       : EXP,
   Cast        : VARIETY,
   M_Scale     : EXP,
   D_Scale     : EXP,
   Raise       : ERROR_TREATMENT] EXP

  (
    mult (Raise,
          mult (Raise, [Cast] Left, [Cast] Right),
          [Cast] M_Scale)
    / [Cast] D_Scale
  );

Tokdef FIXED_MULTIPLY =
  [Left        : EXP,
   Right       : EXP,
   Result      : VARIETY,
   Left_Upper  : EXP,
   Right_Upper : EXP,
   Left_Small  : EXP,
   Right_Small : EXP,
   Small       : EXP,
   Raise       : ERROR_TREATMENT] EXP

  EXP ? (FTEST [Left_Small F* Right_Small, >=, Small],

    [Result] Fixed_Mult [Left, Right,
       /* Cast => */    - computed_nat ([universal] Left_Upper
                                        * [universal] Right_Upper)
                        :
                        + computed_nat ([universal] Left_Upper
                                        * [universal] Right_Upper),
       /* M_Scale => */ Mult_Scale [Left_Small, Right_Small, Small],
                        1 (universal), Raise],

  /* else: Left_Small < Right_Small * Small */

    [Result] Fixed_Mult [Left, Right,
       /* Cast => */    - computed_nat ([universal] Left_Upper
                                        * [universal] Right_Upper)
                        :
                        + computed_nat ([universal] Left_Upper
                                        * [universal] Right_Upper),
                        1 (universal),
       /* D_Scale => */ Mult_Scale [Left_Small, Right_Small, Small],
                        Raise]
  );

Tokdef FIXED_TO_FLOAT =
  [Left        : EXP,
   Left_Small  : EXP,
   Left_Type   : VARIETY,
   Result      : FLOATING_VARIETY,
   Raise       : ERROR_TREATMENT] EXP

   floating_mult (Raise,
                  float_int (Raise, Result, Left),
                  change_floating_variety (impossible, Result, Left_Small));

Tokdef FIXED_TO_INT =
  [Left        : EXP,
   Left_Small  : EXP,
   Left_Type   : VARIETY,
   Result      : VARIETY,
   Raise       : ERROR_TREATMENT] EXP

  EXP ? (FTEST [Left_Small, <, 1.0 (A_UNIVERSAL_REAL_DEFINITION.V)],
    change_variety (Raise, Result,
      (Left
       +
       round_with_mode (impossible, to_nearest, Left_Type,
                        0.5 (A_UNIVERSAL_REAL_DEFINITION.V) F/ Left_Small))
      / round_with_mode (impossible, to_nearest, Left_Type,
                         1.0 (A_UNIVERSAL_REAL_DEFINITION.V) F/ Left_Small)),
    /* else: Small >= 1 */
    mult (Raise,
          change_variety (Raise, Result, Left),
          round_with_mode (Raise, to_nearest, Result, Left_Small)));

Tokdef INT_TO_FIXED =
  [Left        : EXP,
   Small       : EXP,
   Left_Type   : VARIETY,
   Result      : VARIETY,
   Raise       : ERROR_TREATMENT] EXP

  EXP ? (FTEST [Small, <, 1.0 (A_UNIVERSAL_REAL_DEFINITION.V)],
    mult (Raise,
          change_variety (Raise, Result, Left),
          round_with_mode (Raise, to_nearest, Result,
                           1.0 (A_UNIVERSAL_REAL_DEFINITION.V) F/ Small)),
    /* else: Small >= 1 */
    change_variety (Raise, Result,
          Left / round_with_mode (Raise, to_nearest, Left_Type, Small)));
         
Tokdef FLOAT_TO_FIXED =
  [Left        : EXP,
   Small       : EXP,
   Left_Type   : FLOATING_VARIETY,
   Result      : VARIETY,
   Raise       : ERROR_TREATMENT] EXP

  round_with_mode (Raise, to_nearest, Result,
    Left F/ change_floating_variety (impossible, Left_Type, Small));

Tokdef FIXED_TO_FIXED =
  [Left        : EXP,
   Left_Small  : EXP,
   Small       : EXP,
   Left_Type   : VARIETY,
   Result      : VARIETY,
   Raise       : ERROR_TREATMENT] EXP

  EXP ? (FTEST [Left_Small, <, Small],
    change_variety (Raise, Result,
       Left / round_with_mode (Raise, to_nearest, Left_Type,
                               Small F/ Left_Small)),
    /* else: Left_Small >=  Small */
    mult (Raise,
          change_variety (Raise, Result, Left),
          round_with_mode (Raise, to_nearest, Result,
                           Left_Small F/ Small)));

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
      TEST_RANGE_JUMP,
      A_UNIVERSAL_REAL_DEFINITION.V,
      Float.FLOAT_ID,
      MAKE_FLOAT_RANGE_ID,
      MAKE_FLOAT_ID,
      COMPARE_FLOAT_VALUE,
      MAKE_DENORM_ATTRIBUTE,
      MAKE_MACHINE_EMAX_ATTRIBUTE,
      MAKE_MACHINE_EMIN_ATTRIBUTE,
      MAKE_MACHINE_MANTISSA_ATTRIBUTE,
      MAKE_MACHINE_OVERFLOWS_ATTRIBUTE,
      MAKE_MACHINE_RADIX_ATTRIBUTE,
      MAKE_MACHINE_ROUNDS_ATTRIBUTE,
      MAKE_SIGNED_ZEROS_ATTRIBUTE,
      MAKE_CEILING_ATTRIBUTE,
      MAKE_FLOOR_ATTRIBUTE,
      MAKE_ROUNDING_ATTRIBUTE,
      MAKE_TRUNCATION_ATTRIBUTE,
      A_UNIVERSAL_FIXED_DEFINITION.V,
      MAKE_SMALL_ATTRIBUTE,
      FIXED_DIVIDE,
      FIXED_MULTIPLY,
      FIXED_TO_FLOAT,
      FIXED_TO_INT,
      INT_TO_FIXED,
      FLOAT_TO_FIXED,
      FIXED_TO_FIXED,
      IN_BOUNDS,
      FLOAT_IN_BOUNDS
      )


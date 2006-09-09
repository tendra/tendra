Tokdec Boolean.V : [] VARIETY;
Tokdec ~Set_signal_handler : [] EXP;
Iddec TDF_Exception:proc;

Tokdef A_UNIVERSAL_INTEGER_DEFINITION.V =
  [] VARIETY

  var_width (true, 64);

Tokdef A_ROOT_INTEGER_DEFINITION.V =
  [] VARIETY

  var_width (true, 64);

Tokdef Character.LOWER =
  [] EXP

  0(A_UNIVERSAL_INTEGER_DEFINITION.V);

Tokdef Character.UPPER =
  [] EXP

  255(A_UNIVERSAL_INTEGER_DEFINITION.V);

Tokdef Integer.LOWER =
  [] EXP

  -2147483647(A_UNIVERSAL_INTEGER_DEFINITION.V)
    - 1(A_UNIVERSAL_INTEGER_DEFINITION.V);
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
/*
?{ 
   change_variety (to_raise, Type, Value)
   | :to_raise:
     TDF_Exception[top](111(Int));
     make_value (integer (Type))
};
*/

Keep (COMPARE_INTEGER_VALUE,
      BOOLEAN_JUMP,
      Character.LOWER,
      Character.UPPER,
      Integer.LOWER,
      Integer.UPPER,
      A_UNIVERSAL_INTEGER_DEFINITION.V,
      A_ROOT_INTEGER_DEFINITION.V,
      Ada_Init,
      ~Throw,
      CONSTRAINT_ERROR_IF,
      ENUM_SUCC_PRED_ATTR,
      SIGNED_SUCC_PRED_ATTR,
      ENUM_VAL_ATTR,
      SIGNED_VAL_ATTR
      )


Tokdec Boolean.V : [] VARIETY;
Tokdec ~Set_signal_handler : [] EXP;
Iddec TDF_Exception:proc;

Tokdef Character.LOWER =
  [] SIGNED_NAT

  0;

Tokdef Character.UPPER =
  [] SIGNED_NAT

  255;

Tokdef Integer.LOWER =
  [] SIGNED_NAT

  -2147483648;

Tokdef Integer.UPPER =
  [] SIGNED_NAT

  2147483647;


Tokdef COMPARE_INTEGER_VALUE =
  [Test  : NTEST,
   Left  : EXP,
   Right : EXP] EXP

  ?{ ?(Left Test Right); 1(Boolean.V) | 0(Boolean.V) };

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

Keep (COMPARE_INTEGER_VALUE,
      BOOLEAN_JUMP,
      Character.LOWER,
      Character.UPPER,
      Integer.LOWER,
      Integer.UPPER,
      Ada_Init,
      ~Throw
      )


Tokdec Boolean.V : [] VARIETY;

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


Keep (COMPARE_INTEGER_VALUE,
      BOOLEAN_JUMP,
      Character.LOWER,
      Character.UPPER,
      Integer.LOWER,
      Integer.UPPER)


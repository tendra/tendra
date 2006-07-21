Tokdec Boolean.V : [] VARIETY;

Tokdef Character.LOWER =
  [] SIGNED_NAT

  0;

Tokdef Character.UPPER =
  [] SIGNED_NAT

  255;


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

Tokdef BOOLEAN_VALUE =
  [Target : LABEL,
   Value  : EXP] EXP

  ?{ Value; 1(Boolean.V) | :Target: 0(Boolean.V) };

Tokdef GENERIC_NAME =
  [Addr  : NAT,
   Const : NAT,
   Name  : TAG,
   Type  : TOKEN [] SHAPE] EXP

  EXP ? (+ Const(Boolean.V),
    EXP ? (+ Addr(Boolean.V),
             # "Can't get address of unaliased constant",
             Name),
    EXP ? (+ Addr(Boolean.V),
             Name,
             * (Type) Name));

Keep (COMPARE_INTEGER_VALUE,
      BOOLEAN_JUMP,
      BOOLEAN_VALUE,
      GENERIC_NAME,
      Character.LOWER,
      Character.UPPER)


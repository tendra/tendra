/*
 * Copyright 2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * Target dependency tokens
 */

Tokdec .~rep_var_width      : [NAT] NAT;
Tokdec .~rep_atomic_width   : [] NAT;
Tokdec .~rep_fv             : [NAT] FLOATING_VARIETY;
Tokdec .~rep_fv_width       : [NAT] NAT;
Tokdec .~rep_fv_radix       : [NAT] NAT;
Tokdec .~rep_fv_mant        : [NAT] NAT;
Tokdec .~rep_fv_min_exp     : [NAT] NAT;
Tokdec .~rep_fv_max_exp     : [NAT] NAT;
Tokdec .~rep_fv_epsilon     : [NAT] EXP;
Tokdec .~rep_fv_min_val     : [NAT] EXP;
Tokdec .~rep_fv_max_val     : [NAT] EXP;
Tokdec .~ptr_width          : [] NAT;
Tokdec .~best_div           : [] NAT;
Tokdec .~little_endian      : [] BOOL;
Tokdec .~ptr_to_ptr         : [ALIGNMENT, ALIGNMENT, EXP] EXP;
Tokdec .~ptr_to_int         : [ALIGNMENT, VARIETY, EXP] EXP;
Tokdec .~int_to_ptr         : [VARIETY, ALIGNMENT, EXP] EXP;
Tokdec .~f_to_ptr           : [ALIGNMENT, EXP] EXP;
Tokdec .~ptr_to_f           : [ALIGNMENT, EXP] EXP;

/*
 * C mapping tokens
 */

Tokdec .~char_width         : [] NAT;
Tokdec .~short_width        : [] NAT;
Tokdec .~int_width          : [] NAT;
Tokdec .~long_width         : [] NAT;
Tokdec .~longlong_width     : [] NAT;
Tokdec .~size_t_width       : [] NAT;
Tokdec .~fl_rep             : [] NAT;
Tokdec .~dbl_rep            : [] NAT;
Tokdec .~ldbl_rep           : [] NAT;
Tokdec .~min_struct_rep     : [] NAT;

Tokdec .~pv_align           : [] ALIGNMENT;

Tokdec .~char_is_signed     : [] BOOL;
Tokdec .~bitfield_is_signed : [] BOOL;

/*
 * Variety encoding constants for representing integer
 * types in conversion, promotion rules etc.
 */

Tokdef t_char     = [] SIGNED_NAT  0;
Tokdef t_short    = [] SIGNED_NAT  1;
Tokdef t_int      = [] SIGNED_NAT  2;
Tokdef t_long     = [] SIGNED_NAT  3;

Tokdef t_signed   = [] SIGNED_NAT  4;
Tokdef t_unsigned = [] SIGNED_NAT  8;
Tokdef t_longlong = [] SIGNED_NAT 16;

Tokdef t_vmask    = [] SIGNED_NAT 19;
Tokdef t_smask    = [] SIGNED_NAT 12;

Tokdef t_vty = [] VARIETY /* variety for above constants */
	var_width(false, 8);

/*
 * Constants derived from the above
 */

Tokdef t_s_char = [] SIGNED_NAT
	computed_signed_nat(t_char(t_vty) Or t_signed(t_vty));

Tokdef t_u_char = [] SIGNED_NAT
	computed_signed_nat(t_char(t_vty) Or t_unsigned(t_vty));

Tokdef t_s_short = [] SIGNED_NAT
	computed_signed_nat(t_short(t_vty) Or t_signed(t_vty));

Tokdef t_u_short = [] SIGNED_NAT
	computed_signed_nat(t_short(t_vty) Or t_unsigned(t_vty));

Tokdef t_s_int = [] SIGNED_NAT
	computed_signed_nat(t_int(t_vty) Or t_signed(t_vty));

Tokdef t_u_int = [] SIGNED_NAT
	computed_signed_nat(t_int(t_vty) Or t_unsigned(t_vty));

Tokdef t_s_long = [] SIGNED_NAT
	computed_signed_nat(t_long(t_vty) Or t_signed(t_vty));

Tokdef t_u_long = [] SIGNED_NAT
	computed_signed_nat(t_long(t_vty) Or t_unsigned(t_vty));

Tokdef t_s_longlong = [] SIGNED_NAT
	computed_signed_nat(t_longlong(t_vty) Or t_s_long(t_vty));

Tokdef t_u_longlong = [] SIGNED_NAT
	computed_signed_nat(t_longlong(t_vty) Or t_u_long(t_vty));

/*
 * C integer and float varieties
 */

Tokdef ~char              = [] VARIETY var_width(.~char_is_signed, .~char_width);
Tokdef ~signed_char       = [] VARIETY var_width(true,  .~char_width);
Tokdef ~unsigned_char     = [] VARIETY var_width(false, .~char_width);
Tokdef ~signed_short      = [] VARIETY var_width(true,  .~short_width);
Tokdef ~unsigned_short    = [] VARIETY var_width(false, .~short_width);
Tokdef ~signed_int        = [] VARIETY var_width(true,  .~int_width);
Tokdef ~unsigned_int      = [] VARIETY var_width(false, .~int_width);
Tokdef ~signed_long       = [] VARIETY var_width(true,  .~long_width);
Tokdef ~unsigned_long     = [] VARIETY var_width(false, .~long_width);
Tokdef ~signed_longlong   = [] VARIETY var_width(true,  .~longlong_width);
Tokdef ~unsigned_longlong = [] VARIETY var_width(false, .~longlong_width);

Tokdef ~float             = [] FLOATING_VARIETY .~rep_fv[.~fl_rep];
Tokdef ~double            = [] FLOATING_VARIETY .~rep_fv[.~dbl_rep];
Tokdef ~long_double       = [] FLOATING_VARIETY .~rep_fv[.~ldbl_rep];

/*
 * max values needed to determine types of literals
 */

Tokdef max_signed_int = [] SIGNED_NAT
computed_signed_nat (
  (1(~unsigned_int) <<
	(snat_from_nat(false,.~int_width)(~unsigned_int) - 1(~unsigned_int)))
  - 1(~unsigned_int)
);

Tokdef max_unsigned_int = [] SIGNED_NAT
computed_signed_nat (
  (0(~unsigned_int) - 1(~unsigned_int))
);

Tokdef max_signed_long = [] SIGNED_NAT
computed_signed_nat (
  (1(~unsigned_long) <<
	(snat_from_nat(false,.~long_width)(~unsigned_long) - 1(~unsigned_long)))
  - 1(~unsigned_long)
);

Tokdef max_signed_longlong = [] SIGNED_NAT
computed_signed_nat (
  (1(~unsigned_longlong) <<
	(snat_from_nat(false,.~longlong_width)(~unsigned_long) - 1(~unsigned_long)))
  - 1(~unsigned_longlong)
);

/*
 * Shorthand tests producing EXP boolean
 * for use in constant evaluation constructions
 */

/* exp integer test */
Tokdef ITEST = [a:EXP, comp:NTEST, b:EXP] EXP
	? { ?(a comp b); 1(~unsigned_int) | 0(~unsigned_int) };

/* exp offset test */
Tokdef OTEST = [a:EXP, comp:NTEST, b:EXP] EXP
	? { .?(a comp b); 1(~unsigned_int) | 0(~unsigned_int) };

/* s_nat test */
Tokdef SNTEST = [a:SIGNED_NAT, comp:NTEST, b:SIGNED_NAT] EXP
	ITEST [a(~unsigned_long), comp, b(~unsigned_long)];

/* s_nat test */
Tokdef SNLLTEST = [a:SIGNED_NAT, comp:NTEST, b:SIGNED_NAT] EXP
	ITEST [a(~unsigned_longlong), comp, b(~unsigned_longlong)];

/* nat test */
Tokdef NATTEST = [a:NAT, comp:NTEST, b:NAT] EXP
	SNTEST [snat_from_nat(false,a), comp, snat_from_nat(false,b)];

/* s_nat test */
Tokdef TV_SNTEST = [a:SIGNED_NAT, comp:NTEST, b:SIGNED_NAT] EXP
	ITEST [a(t_vty), comp, b(t_vty)];

Tokdef BOOLTEST = [b:BOOL] EXP
	ITEST [snat_from_nat(b,1)(~signed_int), <, 0(~signed_int)];


Tokdef ~div = [arg1:EXP, arg2:EXP] EXP
	div0(impossible, wrap, arg1, arg2);

Tokdef ~rem = [arg1:EXP, arg2:EXP] EXP
	rem0(impossible, wrap, arg1, arg2);

Tokdef ~assign = [ptr:EXP, val:EXP, sh:SHAPE] EXP
	Let desttag = ptr {
		desttag = val ;
		* (sh) desttag
	};

Tokdef ~assign_vol = [ptr:EXP, val:EXP, sh:SHAPE] EXP
	Let assigned_val = val {
		assign_with_mode (volatile, ptr, assigned_val) ;
		assigned_val
	};

Tokdef ~ptr_add = [ptr:EXP, n:EXP, sh:SHAPE] EXP
	( ptr *+. ( Sizeof(sh) .* n ) );

Tokdef ~ptr_sub = [ptr:EXP, n:EXP, sh:SHAPE] EXP
	( ptr *+. offset_negate(( Sizeof(sh) .* n )) );

Tokdef ~sizeof = [sh:SHAPE] EXP
	offset_div (
		var_width (false, .~size_t_width),
		Sizeof (sh),
		Sizeof (integer(~unsigned_char))
	);

Tokdef ~comp_off = [sz:EXP] EXP
	offset_pad (
		alignment (integer (var_width (false, .~min_struct_rep))),
		offset_pad (alignment(compound(sz)), sz)
	);

Tokdef ~convert = [which_v:SIGNED_NAT] VARIETY
VARIETY ? ( TV_SNTEST [which_v, ==, t_char],
  ~char,
  VARIETY ? ( TV_SNTEST [which_v, ==, t_s_char],
    ~signed_char,
    VARIETY ? ( TV_SNTEST [which_v, ==, t_u_char],
      ~unsigned_char,
      VARIETY ? ( TV_SNTEST [which_v, ==, t_s_short],
        ~signed_short,
        VARIETY ? ( TV_SNTEST [which_v, ==, t_u_short],
          ~unsigned_short,
          VARIETY ? ( TV_SNTEST [which_v, ==, t_s_int],
            ~signed_int,
            VARIETY ? ( TV_SNTEST [which_v, ==, t_u_int],
              ~unsigned_int,
              VARIETY ? ( TV_SNTEST [which_v, ==, t_s_long],
                ~signed_long,
                VARIETY ? ( TV_SNTEST [which_v, ==, t_u_long],
                  ~unsigned_long,
                  VARIETY ? ( TV_SNTEST [which_v, ==, t_s_longlong],
                    ~signed_longlong,
                    ~unsigned_longlong
                  )
                )
              )
            )
          )
        )
      )
    )
  )
);

Tokdef OLDarith_type = [arg1:SIGNED_NAT, arg2:SIGNED_NAT] SIGNED_NAT
SIGNED_NAT ? ( TV_SNTEST [arg1, ==, t_u_long],
  t_u_long,
  SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_u_long],
    t_u_long,
    SIGNED_NAT ? ( TV_SNTEST [arg1, ==, t_s_long],
      SIGNED_NAT ? ( NATTEST [.~long_width, >, .~int_width],
        t_s_long,
        SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_u_int],
          t_u_long,
          t_s_long
        )
      ),
      SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_s_long],
        SIGNED_NAT ? ( NATTEST [.~long_width, >, .~int_width],
          t_s_long,
          SIGNED_NAT ? ( TV_SNTEST [arg1, ==, t_u_int],
            t_u_long,
            t_s_long
          )
        ),
        SIGNED_NAT ? ( TV_SNTEST [arg1, ==, t_u_int],
          t_u_int,
          SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_u_int],
            t_u_int,
            t_s_int
          )
        )
      )
    )
  )
);

Tokdef ~arith_type = [arg1:SIGNED_NAT, arg2:SIGNED_NAT] SIGNED_NAT
SIGNED_NAT ? ( TV_SNTEST [arg1, ==, t_u_longlong],
  t_u_longlong,
  SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_u_longlong],
    t_u_longlong,
    SIGNED_NAT ? ( TV_SNTEST [arg1, ==, t_s_longlong],
      SIGNED_NAT ? ( NATTEST [.~longlong_width, >, .~long_width],
        t_s_longlong,
        SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_u_long],
          t_u_longlong,
          SIGNED_NAT ? ( NATTEST [.~longlong_width, >, .~int_width],
            t_s_longlong,
            SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_u_int],
              t_u_longlong,
              t_s_longlong
            )
          )
        )
      ),
      SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_s_longlong],
        SIGNED_NAT ? ( NATTEST [.~longlong_width, >, .~long_width],
          t_s_longlong,
          SIGNED_NAT ? ( TV_SNTEST [arg1, ==, t_u_long],
            t_u_longlong,
            SIGNED_NAT ? ( NATTEST [.~longlong_width, >, .~int_width],
              t_s_longlong,
              SIGNED_NAT ? ( TV_SNTEST [arg2, ==, t_u_int],
                t_u_longlong,
                t_s_longlong
              )
            )
          )
        ),
        OLDarith_type [arg1, arg2]
      )
    )
  )
);

Tokdef ~int_promot = [] SIGNED_NAT
	SIGNED_NAT ? ( NATTEST [.~int_width, >, .~short_width],
		t_s_int,
		t_u_int
	);


Tokdef ~promote = [arg:SIGNED_NAT] SIGNED_NAT
computed_signed_nat(
  EXP ? ( TV_SNTEST [arg, ==, t_u_short],
    ~int_promot(t_vty),
    ? { ?( (arg(t_vty) And t_vmask(t_vty)) < t_int(t_vty));
        t_s_int(t_vty)
      | arg(t_vty)
    }
  )
);


Tokdef ~sign_promote = [arg:SIGNED_NAT] SIGNED_NAT
computed_signed_nat(
  ? { ?( (arg(t_vty) And t_vmask(t_vty)) < t_int(t_vty));
      ? { ?( (arg(t_vty) And t_smask(t_vty)) == t_unsigned(t_vty));
          t_u_int(t_vty)
        | t_s_int(t_vty)
      }
    | arg(t_vty)
  }
);


Tokdef ~lit_int = [arg:SIGNED_NAT] SIGNED_NAT
SIGNED_NAT ? ( SNTEST [arg, <=, max_signed_int],
  t_s_int,
  SIGNED_NAT ? ( SNTEST [arg, <=, max_signed_long],
    t_s_long,
    t_u_long
  )
);


Tokdef ~lit_hex = [arg:SIGNED_NAT] SIGNED_NAT
SIGNED_NAT ? ( SNTEST [arg, <=, max_signed_int],
  t_s_int,
  SIGNED_NAT ? ( SNTEST [arg, <=, max_unsigned_int],
    t_u_int,
    SIGNED_NAT ? ( SNTEST [arg, <=, max_signed_long],
      t_s_long,
      t_u_long
    )
  )
);

Tokdef ~lit_unsigned = [arg:SIGNED_NAT] SIGNED_NAT
	SIGNED_NAT ? ( SNTEST [arg, <=, max_unsigned_int],
		t_u_int,
		t_u_long
	);

Tokdef ~lit_long = [arg:SIGNED_NAT] SIGNED_NAT
	SIGNED_NAT ? ( SNTEST [arg, <=, max_signed_long],
		t_s_long,
		t_u_long
	);

Tokdef ~lit_ulong = [arg:SIGNED_NAT] SIGNED_NAT
	t_u_long;

Tokdef ~lit_longlong = [arg:SIGNED_NAT] SIGNED_NAT
	SIGNED_NAT ? ( SNLLTEST [arg, <=, max_signed_longlong],
		t_s_longlong,
		t_u_longlong
	);

Tokdef ~lit_ulonglong = [arg:SIGNED_NAT] SIGNED_NAT
	t_u_longlong;

Tokdef ~char_lit = [chars:EXP, length:SIGNED_NAT, v:VARIETY] EXP
	EXP ? ( SNTEST [length, ==, 1],
		Var char_val = chars {
			[ v ] * (integer(~char)) char_val
		},
		#"Too many characters in char literal"
	);


Tokdef ~wchar_lit = [chars:EXP, length:SIGNED_NAT, v:VARIETY] EXP
	~char_lit [ chars, length, v ];

Tokdef ~string_lit = [string:EXP, length:SIGNED_NAT, v:VARIETY] EXP
	(string);

Tokdef ~checked_plus = [arg1:EXP, arg2:EXP] EXP
	EXP ? ( ITEST [arg1, >, (max_signed_int(~unsigned_long) - arg2)],
		#"Constant out of range for its type",
		arg1 + arg2
	);

/*
 * pointer conversions, simple for byte-addressed architectures
 */

Tokdef ~ptr_void = [] SHAPE
	pointer (.~pv_align);

Tokdef ~ptr_to_ptr = [from_al:ALIGNMENT, to_al:ALIGNMENT, ptr:EXP] EXP
	.~ptr_to_ptr[from_al, to_al, ptr];

Tokdef ~to_ptr_void = [al:ALIGNMENT, ptr:EXP] EXP
	.~ptr_to_ptr[al, .~pv_align, ptr];

Tokdef ~from_ptr_void = [al:ALIGNMENT, ptr:EXP] EXP
	.~ptr_to_ptr[.~pv_align, al, ptr];

Tokdef ~i_to_p = [v:VARIETY, al:ALIGNMENT, val:EXP] EXP
	.~int_to_ptr[v, al, val];

Tokdef ~p_to_i = [al:ALIGNMENT, v:VARIETY, val:EXP] EXP
	.~ptr_to_int[al, v, val];

Tokdef ~null_pv = [] EXP
	make_null_ptr(.~pv_align);

Tokdef ~pv_test = [ptr:EXP, escape:LABEL, comparison:NTEST] EXP
	*?(ptr comparison ~null_pv | escape);

Tokdef ~cpp.pv_compare = [ptr1:EXP, ptr2:EXP, escape:LABEL, comparison:NTEST] EXP
	*?(ptr1 comparison ptr2 | escape);

Tokdef ~pad = [off:EXP, sh1:SHAPE, sh2:SHAPE] EXP
		EXP ? ( OTEST [offset_pad(alignment(sh1), (off .+. shape_offset(sh2))),
			>,
			offset_pad(alignment(sh1), off)],
		offset_pad(alignment(sh1), off),
		offset_pad(alignment(sh2), off)
	);

Tokdef ~i_to_pv = [v:VARIETY, val:EXP] EXP
	~i_to_p [ v, .~pv_align, val ];

Tokdef ~pv_to_i = [v:VARIETY, val:EXP] EXP
	~p_to_i [ .~pv_align, v, val ];

Tokdef ~f_to_pv = [fn:EXP] EXP
	.~f_to_ptr [ .~pv_align, fn ];

Tokdef ~pv_to_f = [ptr:EXP] EXP
	.~ptr_to_f [ .~pv_align, ptr ];

Tokdef ~debug_exp = [diagi:NAT, body:EXP] EXP
	(body);

Tokdef ~debug_scope = [starti:NAT, endi:NAT, body:EXP] EXP
	(body);

Tokdef ~fn_scope = [body:EXP, starti:NAT, endi:NAT] EXP
	(body);

Tokdef ~little_endian = [] EXP
	EXP ? ( BOOLTEST [.~little_endian],
		1(~signed_int),
		0(~signed_int)
	);

Tokdef ~cpp.empty.offset = [] EXP
	~comp_off [
		offset_add (
			offset_zero(alignment(integer(~char))),
			shape_offset(integer(~char)))
	];

Tokdef ~cpp.empty.shape = [] SHAPE
	compound(~cpp.empty.offset);

Tokdef ~cpp.empty.align = [] ALIGNMENT
	alignment(floating(~long_double));

Tokdef ~cpp.bitf_sign = [which_v: SIGNED_NAT] BOOL
		BOOL ? ( BOOLTEST [.~bitfield_is_signed],
			BOOL ? ( which_v(t_vty) And t_unsigned(t_vty),
				false,
				true
			),
			false
	);

Tokdef ~cpp.ptr_rep = [] SIGNED_NAT
	SIGNED_NAT ? ( NATTEST [.~ptr_width, ==, .~int_width],
		t_s_int,
		t_s_long
	);

Keep (
	~char, ~unsigned_char, ~signed_char,
	~unsigned_short, ~signed_short,
	~unsigned_int, ~signed_int,
	~unsigned_long, ~signed_long,
	~unsigned_longlong, ~signed_longlong,

	~float, ~double, ~long_double,

	~div, ~rem,
	~assign, ~assign_vol,
	~ptr_add, ~ptr_sub,
	~sizeof,
	~comp_off,

	~convert,
	~arith_type,
	~int_promot, ~promote, ~sign_promote,

	~lit_int, ~lit_hex, ~lit_unsigned, ~lit_long, ~lit_ulong,
	~lit_longlong, ~lit_ulonglong,
	~char_lit, ~wchar_lit, ~string_lit,

	~checked_plus,
	~ptr_void,
	~ptr_to_ptr, ~to_ptr_void, ~from_ptr_void,
	~i_to_p, ~p_to_i,

	~null_pv, ~pv_test, ~cpp.pv_compare,

	~pad,

	~i_to_pv, ~pv_to_i, ~f_to_pv, ~pv_to_f,

	~debug_exp, ~debug_scope, ~fn_scope,

	~little_endian,

	~cpp.empty.offset, ~cpp.empty.shape, ~cpp.empty.align,
	~cpp.bitf_sign, ~cpp.ptr_rep
)


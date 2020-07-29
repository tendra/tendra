/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997-1998, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */

/*
 * TYPE SYSTEM SPECIFICATION
 *
 * The main type system for the program is specified using the calculus tool.
 * This generates two representations of the type algebra, c_class. The files
 * in obj_tok describe the output type system abstractly in terms of the TenDRA
 * '#pragma token' constructs. These may be used to apply extremely rigorous
 * type checking to the program. The files in obj_c give the implementation of
 * the type system in C terms. The implementation specific parts of the
 * program, including the memory management, is handled in obj_c/c_class.c.
 */

ALGEBRA c_class (1.1) :


/*
 * PRIMITIVE TYPES
 *
 * These are the primitive types from which the algebra is built. int, unsigned
 * and string are self-explanitory. BITSTREAM_P represents a series of bits,
 * and is used to hold any compiled code. PPTOKEN_P represents a list of
 * preprocessing tokens, and is used in macro definitions etc.
 */

int =			"int" ;
unsigned =		"unsigned" ;
string =		"character *" ;
ulong_type (ulong) =	"unsigned long" ;
BITSTREAM_P (bits) =	"struct bits_tag *" ;
PPTOKEN_P (pptok) =	"struct pptok_tag *" ;


/*
 * TYPE REPRESENTING A CONST-VOLATILE SPECIFIER
 *
 * The const and volatile type qualifiers are represented by an enumeration
 * type (which is actually a bit pattern). An additional value is used to
 * indicate lvalues. Type linkage specifiers are also included.
 */

enum !CV_SPEC (cv) = {
    none =		0,
    const =		1 << 0,
    volatile =		1 << 1,
    lvalue =		1 << 2,

    c =			1 << 3,
    cpp =		1 << 4,

    qual =		const | volatile,
    mask =		qual | lvalue,
    language =		c | cpp
} ;


/*
 * TYPE REPRESENTING A BUILT-IN TYPE
 *
 * The built-in types have two representations - as a BASE_TYPE (see below) or
 * as a BUILTIN_TYPE. The latter is used primarily as an index into various
 * tables.
 */

enum !BUILTIN_TYPE (ntype) = {
    none =		0,
    char =		1,
    schar =		2,
    uchar =		3,
    sshort =		4,
    ushort =		5,
    sint =		6,
    uint =		7,
    slong =		8,
    ulong =		9,
    sllong =		10,
    ullong =		11,
    float =		12,
    double =		13,
    ldouble =		14,
    void =		15,
    bottom =		16,
    bool =		17,
    ptrdiff_t =		18,
    size_t =		19,
    wchar_t =		20,
    ellipsis =		21
} ;


/*
 * TYPE REPRESENTING A BASIC TYPE
 *
 * The basic types are represented by an enumeration type (which is actually a
 * bit pattern except for the named type component). The composite bitpatterns
 * for the maximally valid combinations are also given. The elaborated type
 * keys are also represented by this type.
 */

enum !BASE_TYPE (btype) = {
    none =		0,
    class =		1,
    struct_ =		2,
    union_ =		3,
    enum_ =		4,
    alias =		5,
    any =		6,
    named =		7,

    signed =		1 << 3,
    unsigned =		1 << 4,
    char =		1 << 5,
    short =		1 << 6,
    int =		1 << 7,
    long =		1 << 8,
    long2 =		1 << 9,
    float =		1 << 10,
    double =		1 << 11,
    void =		1 << 12,
    bottom =		1 << 13,
    bool =		1 << 14,
    ptrdiff_t =		1 << 15,
    size_t =		1 << 16,
    wchar_t =		1 << 17,

    schar =		signed | char,
    uchar =		unsigned | char,
    sshort =		signed | short | int,
    ushort =		unsigned | short | int,
    sint =		signed | int,
    uint =		unsigned | int,
    slong =		signed | long | int,
    ulong =		unsigned | long | int,
    llong =		long | long2,
    sllong =		signed | llong | int,
    ullong =		unsigned | llong | int,
    ldouble =		long | double,

    ellipsis =		1 << 18,
    star =		1 << 19,
    template =		1 << 20,
    typename =		1 << 21,
    args =		1 << 22,
    keyword =		float | double | void | bool | wchar_t,
    other =		keyword | bottom | ptrdiff_t | size_t,
    arith =		int | float,
    scalar =		int | float | star
} ;


/*
 * TYPE REPRESENTING AN INTEGRAL TYPE
 *
 * An integral type can be one of the built-in types, an integral promotion
 * type or an arithmetic conversion type. The promotion type for each integral
 * type is stored as part of its definition.
 */

union INT_TYPE (itype) = {
    TYPE prom ;
    LIST TYPE cases ;
    BUILTIN_TYPE unprom = "ntype_none" ;
    ulong_type itok = "LINK_NONE" ;
    ulong_type ntok = "LINK_NONE" ;
    ulong_type diag = "LINK_NONE" ;
} + {
    basic -> {
	/* Built-in types */
	BASE_TYPE rep ;
	BUILTIN_TYPE no ;
    },
    bitfield -> {
	/* Bitfield types */
	TYPE sub ;
	BASE_TYPE rep ;
	NAT size ;
	DECL_SPEC info ;
    },
    promote -> {
	/* Promotion types */
	INT_TYPE arg ;
    },
    arith -> {
	/* Arithmetic conversion types */
	INT_TYPE arg1, arg2 ;
    },
    literal -> {
	/* Target dependent literal type */
	NAT nat ;
	int spec ;
	int form, suff ;
	IDENTIFIER tok ;
    },
    token -> {
	/* Tokenised integral type */
	IDENTIFIER tok ;
	LIST TOKEN args ;
    }
} ;


/*
 * TYPE REPRESENTING A FLOATING POINT TYPE
 *
 * A floating point type can be one of the built-in types or an arithmetic
 * conversion type. Note that all floating point types are their own arithmetic
 * promotions, but they do have distinct argument promotions.
 */

union FLOAT_TYPE (ftype) = {
    TYPE arg_prom ;
    ulong_type ftok = "LINK_NONE" ;
    ulong_type ntok = "LINK_NONE" ;
    ulong_type diag = "LINK_NONE" ;
    LIST FLOAT small = "NULL_list ( FLOAT )" ;
} + {
    basic -> {
	/* Built-in types */
	BASE_TYPE rep ;
	BUILTIN_TYPE no ;
    },
    arg_promote -> {
	/* Argument promotion types */
	FLOAT_TYPE arg ;
    },
    arith -> {
	/* Arithmetic conversion types */
	FLOAT_TYPE arg1, arg2 ;
    },
    token -> {
	/* Tokenised floating type */
	IDENTIFIER tok ;
	LIST TOKEN args ;
    }
} ;


/*
 * TYPE REPRESENTING CLASS INFORMATION
 *
 * This type is a bitpattern giving information about a class, for example, if
 * it is complete, whether it has base classes, non-static data members, and so
 * on.
 */

enum !CLASS_INFO (cinfo) = {
    none =		0,
    complete =		1 << 0,		/* completed definition */
    defined =		1 << 1,		/* started definition */
    struct_ =		1 << 2,		/* structure class */
    union_ =		1 << 3,		/* union class */
    template =		1 << 4,		/* template class */
    token =		1 << 5,		/* tokenised structure */
    pod =		1 << 6,		/* plain ol' data structure */
    nested =		1 << 7,		/* is nested class */
    rescan =		1 << 8,		/* expands by rescanning */
    recursive =		1 << 9,		/* recursively defined */
    incomplete =	1 << 10,	/* warn if not completed */
    base =		1 << 11,	/* has base class */
    multiple_base =	1 << 12,	/* multiple inheritance */
    virtual_base =	1 << 13,	/* has virtual base class */
    templ_base =	1 << 14,	/* has template base class */
    ambiguous =		1 << 15,	/* has ambiguous base class */
    empty =		1 << 16,	/* empty class */
    private =		1 << 17,	/* non-public data member */
    const =		1 << 18,	/* const data member */
    static =		1 << 19,	/* static data member */
    function =		1 << 20,	/* function member */
    params =		1 << 21,	/* layout dependent on parameters */
    polymorphic =	1 << 22,	/* virtual function */
    poly_base =		1 << 23,	/* polymorphic base class */
    abstract =		1 << 24,	/* pure function */
    trivial_constr =	1 << 25,	/* trivial constructor */
    trivial_destr =	1 << 26,	/* trivial destructor */
    trivial_copy =	1 << 27,	/* trivial copy constructor */
    trivial_assign =	1 << 28,	/* trivial assign operator */
    const_copy =	1 << 29,	/* const copy constructor */
    const_assign =	1 << 30,	/* const assign operator */
    usr_constr =	1 << 31,	/* user defined constructor */

    key =		struct_ | union_,
    non_aggregate =	private | usr_constr | base | polymorphic | token,
    force_copy =	static | function | params,
    trivial_make =	trivial_constr | trivial_copy | trivial_assign,
    trivial =		trivial_make | trivial_destr,
    implicit =		trivial | const_copy | const_assign,
    default =		implicit | empty | pod
} ;


/*
 * TYPE REPRESENTING CLASS USAGE INFORMATION
 *
 * This type is a bitpattern used to represent information on how a class is
 * used.
 */

enum !CLASS_USAGE (cusage) = {
    none =		0,
    address =		1 << 0,		/* address of incomplete */
    destr =		1 << 1,		/* destroyed incomplete */
    delete =		1 << 2,		/* deleted incomplete */
    delete_array =	1 << 3		/* deleted incomplete array */
} ;


/*
 * TYPE REPRESENTING A CLASS TYPE
 *
 * A class type has an associated type name, type key (class, struct or union),
 * and class information. The hash table entries for the constructors and
 * destructors, plus a list of the conversion functions on the class are
 * maintained within the class definition. The class members themselves are
 * just a namespace. The base classes are represented by a graph.
 */

union CLASS_TYPE (ctype) = {
    IDENTIFIER name ;
    CLASS_INFO info ;
    CLASS_USAGE usage ;
    NAMESPACE member ;
    GRAPH base ;
    unsigned no_bases ;
    TYPE prev ;
    TYPE form = "NULL_type" ;
    IDENTIFIER constr = "NULL_id" ;
    IDENTIFIER destr = "NULL_id" ;
    VIRTUAL virt = "NULL_virt" ;
    LIST GRAPH vbase = "NULL_list ( GRAPH )" ;
    LIST IDENTIFIER conv = "NULL_list ( IDENTIFIER )" ;
    LIST CLASS_TYPE chums = "NULL_list ( CLASS_TYPE )" ;
    LIST IDENTIFIER pals = "NULL_list ( IDENTIFIER )" ;
    LIST IDENTIFIER nest = "NULL_list ( IDENTIFIER )" ;
    ulong_type tok1 = "LINK_NONE" ;
    ulong_type tok2 = "LINK_NONE" ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
 * TYPE REPRESENTING A GRAPH OF DERIVED CLASSES
 *
 * This type is used to represent the directed acyclic graphs of base classes
 * associated with a class. Each node of this graph consists of a class and a
 * list of its base classes. The access of each base class, and other
 * information, is recorded. Identical virtual bases are linked using the equal
 * field. The next field is used to link all instances of a class within a
 * graph, whether virtual or not.
 */

union GRAPH (graph) = {
    CLASS_TYPE head ;
    DECL_SPEC access ;
    LIST GRAPH tails = "NULL_list ( GRAPH )" ;
    GRAPH top = "NULL_graph" ;
    GRAPH equal = "NULL_graph" ;
    GRAPH up = "NULL_graph" ;
    unsigned no = "0" ;
    OFFSET off = "NULL_off" ;
    LIST IDENTIFIER member = "NULL_list ( IDENTIFIER )" ;
    ulong_type tok1 = "LINK_NONE" ;
    ulong_type tok2 = "LINK_NONE" ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
 * TYPE REPRESENTING A VIRTUAL FUNCTION
 *
 * This type is used to represent a virtual function table or an entry of such
 * a table. Each table entry has an associated function plus information on
 * where this was inherited from and any difference in the return type of an
 * overriding function.
 */

union VIRTUAL (virt) = {
    IDENTIFIER func ;
    ulong_type no ;
    GRAPH base ;
    VIRTUAL next = "NULL_virt" ;
} + {
    table -> {
	/* Virtual function table */
	OFFSET off ;
	LIST VIRTUAL entries = "NULL_list ( VIRTUAL )" ;
	ulong_type tok = "LINK_NONE" ;
	ulong_type tbl = "LINK_NONE" ;
	ulong_type rtti = "LINK_NONE" ;
	int rtti_used = "0" ;
    },
    simple -> {
	/* New virtual function */
    },
    override -> {
	/* Overriding virtual function */
	GRAPH ret ;
	IDENTIFIER orig ;
	GRAPH src ;
    },
    inherit -> {
	/* Inherited primary function */
    },
    complex -> {
	/* Inherited overriding virtual function */
	GRAPH ret ;
	IDENTIFIER orig ;
	GRAPH src ;
    },
    link -> {
	/* Symbolic link */
	PTR VIRTUAL to ;
    }
} ;


/*
 * TYPE REPRESENTING AN ENUMERATION TYPE
 *
 * An enumeration type has an associated type name, a class information field
 * (which is only used to indicate whether the type is complete), and an
 * underlying integral type. The enumerators themselves are given as a simple
 * list (note that they do not form a namespace).
 */

union ENUM_TYPE (etype) = {
    IDENTIFIER name ;
    CLASS_INFO info ;
    TYPE rep ;
    TYPE form = "NULL_type" ;
    LIST IDENTIFIER values = "NULL_list ( IDENTIFIER )" ;
    EXP value = "NULL_exp" ;
    ulong_type plus = "0" ;
} + {
    basic -> {
	/* empty */
    }
} ;


/*
 * TYPE REPRESENTING A TYPE
 *
 * The types are represented by a union type, with one field per type
 * class. Any type may be qualified using const, volatile and lvalue.
 */

union TYPE (type) = {
    /* Type qualifiers */
    CV_SPEC qual ;
    IDENTIFIER name = "NULL_id" ;
} + {
    pre -> {
	/* Pre-types (used during parsing only) */
	BASE_TYPE rep ;
	QUALIFIER nqual ;
    },
    integer -> {
	/* Integer types */
	INT_TYPE rep ;
	INT_TYPE sem ;
    },
    floating -> {
	/* Floating point types */
	FLOAT_TYPE rep ;
	FLOAT_TYPE sem ;
    },
    top, bottom -> {
	/* The void types */
    },
    ptr, ref -> {
	/* Pointer and reference types */
	TYPE sub ;
    },
    ptr_mem -> {
	/* Pointer to member types */
	CLASS_TYPE of ;
	TYPE sub ;
    },
    func -> {
	/* Function types */
	TYPE ret ;
	LIST TYPE ptypes ;
	int ellipsis ;
	CV_SPEC mqual ;
	LIST TYPE mtypes ;
	NAMESPACE pars ;
	LIST IDENTIFIER pids ;
	LIST TYPE except ;
    },
    array -> {
	/* Array types */
	TYPE sub ;
	NAT size ;
    },
    bitfield -> {
	/* Bitfield types */
	INT_TYPE defn ;
    },
    compound -> {
	/* Class types */
	CLASS_TYPE defn ;
    },
    enumerate -> {
	/* Enumeration types */
	ENUM_TYPE defn ;
    },
    token -> {
	/* Tokenised type */
	IDENTIFIER tok ;
	LIST TOKEN args ;
	INSTANCE app = "NULL_inst" ;
    },
    templ -> {
	/* Template type */
	TOKEN sort ;
	TYPE defn ;
	int fix ;
    },
    instance -> {
	/* Template member type */
	IDENTIFIER id ;
	DECL_SPEC access ;
    },
    dummy -> {
	/* Dummy special token type */
	int tok ;
    },
    error -> {
	/* Error propagation type */
    }
} ;


/*
 * TYPE REPRESENTING A DECLARATION SPECIFIER
 *
 * The basic declaration specifiers (i.e. the storage class specifiers, the
 * function specifiers, friend and typedef) are represented by an enumeration
 * type (which is actually a bit pattern). Other declaration and linkage
 * information is also included, including access specifiers. The fact that
 * public < protected < private is used extensively. The values none, static
 * and extern are also used to specify the linkage of an object.
 */

enum DECL_SPEC (dspec) = {
    none =		0,
    used =		1 << 0,
    called =		1 << 1,
    defn =		1 << 2,
    inherit =		1 << 3,
    alias =		1 << 4,
    done =		1 << 5,

    static =		1 << 6,
    extern =		1 << 7,
    auto =		1 << 8,
    register =		1 << 9,
    mutable =		1 << 10,
    inline =		1 << 11,
    virtual =		1 << 12,
    explicit =		1 << 13,
    friend =		1 << 14,
    typedef =		1 << 15,

    public =		1 << 16,
    protected =		2 << 16,
    private =		3 << 16,

    public2 =		public << 2,
    protected2 =	protected << 2,
    private2 =		private << 2,

    c =			1 << 20,
    cpp =		1 << 21,

    ignore =		1 << 22,
    implicit =		1 << 23,
    instance =		1 << 24,
    main =		1 << 25,
    pure =		1 << 26,
    reserve =		1 << 27,
    temp =		1 << 28,
    template =		1 << 29,
    token =		1 << 30,
    trivial =		1 << 31,

    linkage =		static | extern,
    storage =		static | extern | auto | register | mutable,
    function =		inline | virtual | explicit,
    keyword =		storage | function | friend | typedef,
    duplicate =		keyword,
    access =		public | protected | private,
    access2 =		public2 | protected2 | private2,
    language =		c | cpp,
    other =		ignore | implicit | instance | main | pure |
			reserve | temp | template | token | trivial
} ;


/*
 * TYPE REPRESENTING A HASH TABLE ENTRY
 *
 * Identifier names are represented by a hash table entry. There are several
 * different types of names (simp1e strings, destructor names and so on). Each
 * hash table entry contains, in effect, a built-in namespace member indicating
 * the underlying meaning of this name. It also contains the hash value for
 * this entry.
 */

union HASHID (hashid) = {
    IDENTIFIER id = "NULL_id" ;
    IDENTIFIER cache = "NULL_id" ;
    HASHID next ;
    ulong_type hash ;
} + {
    name, ename -> {
	/* Simple and extended identifiers */
	string text ;
    },
    constr, destr, conv -> {
	/* Constructors, destructors and conversion functions */
	TYPE type ;
	IDENTIFIER tid ;
    },
    op -> {
	/* Overloaded operator name */
	int lex ;
    },
    anon -> {
	/* Unnamed identifier */
	ulong_type uniq ;
    }
} ;


/*
 * TYPE REPRESENTING AN IDENTIFIER QUALIFIER
 *
 * These values are used to identify how an identifier is qualified, either
 * unqualified, a nested qualifier (for example A::B::n), a full nested
 * qualifier (for example ::A::B::n), or a top nested qualifier (for example
 * ::n). A value to mark resolved overloaded functions is also included.
 */

enum !QUALIFIER (qual) = {
    none =		0,
    nested =		1,
    full =		2,
    top =		3,
    mark =		4,
    explicit =		nested | full | top
} ;


/*
 * TYPE REPRESENTING AN IDENTIFIER
 *
 * Identifiers have an associated hash table entry, indicating the identifier
 * name, plus a location indicating where the identifier was first declared.
 * The various things an identifier can represent are given by the different
 * fields of the union.
 */

union IDENTIFIER (id) = {
    HASHID name ;
    DECL_SPEC storage ;
    NAMESPACE parent ;
    LOCATION loc ;
    IDENTIFIER alias = "%0" ;
    ulong_type no = "LINK_NONE" ;
    ulong_type dump = "LINK_NONE" ;
} + {
    dummy -> {
	/* Undefined identifier */
    },
    keyword, iso_keyword, reserved -> {
	/* Keywords */
    },
    builtin -> {
	/* Built-in operators */
	TYPE ret ;
	LIST TYPE ptypes ;
    },
    obj_macro -> {
	/* Object-like macros */
	PPTOKEN_P defn ;
    },
    func_macro -> {
	/* Function-like macros */
	PPTOKEN_P defn ;
	LIST HASHID params ;
	unsigned no_params ;
    },
    predicate -> {
	/* Predicates */
	LIST PPTOKEN_P values = "NULL_list ( PPTOKEN_P )" ;
    },
    class_name, enum_name,
    class_alias, enum_alias, type_alias -> {
	/* Type names */
	TYPE defn ;
	BASE_TYPE rep = "btype_none" ;
    },
    nspace_name, nspace_alias -> {
	/* Namespace names */
	NAMESPACE defn ;
    },
    variable, parameter, stat_member -> {
	/* Variables (including static members) */
	TYPE type ;
	EXP init = "NULL_exp" ;
	EXP term = "NULL_exp" ;
    },
    weak_param -> {
	/* Non-prototype function parameters */
    },
    function, mem_func, stat_mem_func -> {
	/* Functions (including member functions) */
	TYPE type ;
	IDENTIFIER over ;
	TYPE form = "NULL_type" ;
	LIST CLASS_TYPE chums = "NULL_list ( CLASS_TYPE )" ;
	EXP defn = "NULL_exp" ;
    },
    member -> {
	/* Simple data member */
	TYPE type ;
	OFFSET off = "NULL_off" ;
	GRAPH base = "NULL_graph" ;
    },
    enumerator -> {
	/* Enumerators */
	TYPE etype ;
	EXP value ;
    },
    label -> {
	/* Labels */
	int op ;
	EXP stmt = "NULL_exp" ;
	EXP gotos = "NULL_exp" ;
	LIST VARIABLE vars = "NULL_list ( VARIABLE )" ;
    },
    token -> {
	/* Tokens */
	TOKEN sort ;
	IDENTIFIER alt ;
    },
    ambig -> {
	/* Ambiguous identifier */
	LIST IDENTIFIER ids ;
	int over ;
    },
    undef -> {
	/* Undefined identifier */
	TYPE form = "NULL_type" ;
    },
    pending -> {
	/* Pending identifier (used in spec input) */
	unsigned itag ;
	TYPE type ;
    }
} ;


/*
 * TYPE REPRESENTING A NAMESPACE MEMBER
 *
 * There are two kinds of namespace member, small and large, corresponding to
 * the two kinds of namespace. The important section consists of two
 * identifiers, giving the current meanings of a name in the namespace.
 * Everything else is just links to other members.
 */

union MEMBER (member) = {
    IDENTIFIER id = "NULL_id" ;
    IDENTIFIER alt = "NULL_id" ;
    MEMBER next ;
} + {
    small -> {
	/* empty */
    },
    large -> {
	MEMBER tnext ;
    }
} ;


/*
 * TYPE REPRESENTING A NAMESPACE
 *
 * There are two kinds of namespace, small and large. The small namespaces are
 * the block and parameter spaces, the large ones are the class and namespace
 * spaces. Every namespace has an associated namespace name (which may be the
 * null identifier). A small namespace consists of a simple linked list of
 * small members (in reverse order of declaration). A large namespace consists
 * of a hash table of large members, plus a list of all such members in order
 * of declaration. The distinct orders reflect the distinct purposes the two
 * kinds of namespace are put to.
 */

union NAMESPACE (nspace) = {
    IDENTIFIER name ;
    MEMBER last = "NULL_member" ;
    MEMBER prev = "NULL_member" ;
    NAMESPACE parent ;
    LIST NAMESPACE use = "NULL_list ( NAMESPACE )" ;
    LIST NAMESPACE join = "NULL_list ( NAMESPACE )" ;
    STACK IDENTIFIER set = "NULL_stack ( IDENTIFIER )" ;
    ulong_type dump = "LINK_NONE" ;
} + {
    block, param, dummy, label, templ -> {
	/* Member list */
    },
    named, unnamed, global, ctype -> {
	/* Member hash table */
	MEMBER first = "NULL_member" ;
	LIST IDENTIFIER extra = "NULL_list ( IDENTIFIER )" ;
	ulong_type size ;
	PTR MEMBER table ;
    }
} ;


/*
 * TYPE REPRESENTING AN INTEGER LITERAL
 *
 * An integer literal (or constant integral expression) is represented by a
 * sign and a list of numbers in the range [0,0xffff] representing the value
 * base 0x10000. The case where there is only one digit is dealt with
 * separately. It is also possible to form an integer literal from an
 * expression.
 */

union NAT (nat) = {
    /* empty */
} + {
    small -> {
	/* Single digit */
	unsigned value ;
    },
    large -> {
	/* Multiple digits */
	LIST unsigned values ;
    },
    calc -> {
	/* Calculated value */
	EXP value ;
	ulong_type tok = "LINK_NONE" ;
    },
    neg -> {
	/* Negation */
	NAT arg ;
    },
    token -> {
	/* Tokenised expression */
	IDENTIFIER tok ;
	LIST TOKEN args ;
    }
} ;


/*
 * TYPE REPRESENTING A FLOATING POINT LITERAL
 *
 * A floating point literal is represented by a sign, two strings giving the
 * digits before and after the decimal point, plus an exponent.
 */

union FLOAT (flt) = {
    ulong_type tok = "LINK_NONE" ;
} + {
    simple -> {
	/* Simple literal */
	string int_part ;
	string frac_part ;
	NAT exponent ;
    }
} ;


/*
 * TYPE REPRESENTING A STRING LITERAL
 *
 * A string literal consists of a sequence of characters of a given length.
 * Characters, wide characters, strings and wide strings are represented by
 * distinct fields of the union.
 */

union STRING (str) = {
    STRING next = "NULL_str" ;
} + {
    simple -> {
	/* Simple literals */
	ulong_type len ;
	string text ;
	unsigned kind ;
	ulong_type tok = "LINK_NONE" ;
    }
} ;


/*
 * TYPE REPRESENTING A TEST
 *
 * Test and comparison operators are represented by an enumeration type which
 * happen to be in the same order as the TDF encoding. Complementary tests
 * (for example '<' and '>=') always add up to the same value, negate.
 */

enum !NTEST (ntest) = {
    eq =		0,
    greater =		1,
    greater_eq =	2,
    less =		3,
    less_eq =		4,
    not_eq =		5,
    not_greater =	6,
    not_greater_eq =	7,
    not_less =		8,
    not_less_eq =	9,
    not_not_eq =	10,
    none =		11,
    negate =		eq + not_eq,
    not =		not_eq,
    not_not =		not_not_eq
} ;


/*
 * TYPE REPRESENTING A ROUNDING MODE
 *
 * Floating point rounding modes are represented by an enumeration type which
 * happen to be in the same order as the TDF encoding.
 */

enum !RMODE (rmode) = {
    as_state =		0,
    to_nearest =	1,
    to_larger =		2,
    to_smaller =	3,
    to_zero =		4
} ;


/*
 * TYPE REPRESENTING AN EXPRESSION OR STATEMENT
 *
 * The expressions and statements are represented by a union type, with one
 * field per expression or statement class. Every expression has an associated
 * type.
 */

union EXP (exp) = {
    /* Expression type */
    TYPE type ;
} + {
    identifier, member, ambiguous, undeclared -> {
	/* Identifiers */
	IDENTIFIER id ;
	QUALIFIER qual ;
    },
    int_lit -> {
	/* Integer literal */
	NAT nat ;
	unsigned etag ;
    },
    float_lit -> {
	/* Floating point literal */
	FLOAT flt ;
    },
    char_lit -> {
	/* Character literal */
	STRING str ;
	int digit ;
    },
    string_lit -> {
	/* String literal */
	STRING str ;
    },
    value -> {
	/* Undefined value */
    },
    null, zero -> {
	/* Null value (null pointer, zero etc.) */
    },
    paren, copy -> {
	/* Identity operation (used for parentheses) */
	EXP arg ;
    },
    assign -> {
	/* Assignment */
	EXP ref, arg ;
    },
    init -> {
	/* Initialisation */
	IDENTIFIER id ;
	EXP arg ;
    },
    preinc -> {
	/* Pre-increment */
	EXP ref, op ;
	int becomes ;
    },
    postinc -> {
	/* Post-increment */
	EXP ref, value, op ;
    },
    indir -> {
	/* Indirection */
	EXP ptr ;
	int index = "0" ;
    },
    contents -> {
	/* Contents */
	EXP ptr ;
    },
    address -> {
	/* Address of an object */
	EXP arg ;
    },
    address_mem -> {
	/* Address of a member */
	EXP arg ;
	int paren ;
    },
    func -> {
	/* Function call */
	EXP fn ;
	LIST EXP args ;
	unsigned extra = "0" ;
    },
    func_id -> {
	/* Named function call */
	IDENTIFIER id ;
	LIST EXP args ;
	EXP virt ;
	unsigned extra = "0" ;
    },
    call -> {
	/* Member function call */
	EXP ptr, arg ;
	GRAPH base ;
    },
    negate, compl, not, abs -> {
	/* Simple unary operations */
	EXP arg ;
    },
    plus, minus, mult, div, rem,
    and, or, xor, log_and, log_or,
    lshift, rshift, max, min -> {
	/* Simple binary operations */
	EXP arg1, arg2 ;
    },
    test -> {
	/* Compare against null value */
	NTEST tst ;
	EXP arg ;
    },
    compare -> {
	/* Compare two values */
	NTEST tst ;
	EXP arg1, arg2 ;
    },
    cast -> {
	/* Casts */
	unsigned conv ;
	EXP arg ;
    },
    base_cast -> {
	/* Base class conversion */
	unsigned conv ;
	EXP arg ;
	OFFSET off ;
    },
    dyn_cast -> {
	/* Dynamic cast */
	EXP arg ;
	EXP except ;
    },
    add_ptr -> {
	/* Add a value to a pointer */
	EXP ptr ;
	OFFSET off ;
	int virt ;
    },
    offset_size -> {
	/* Size of offset */
	OFFSET off ;
	TYPE step ;
	int pad ;
    },
    constr -> {
	/* Constructor call */
	EXP call, obj, alt ;
	int info ;
    },
    destr -> {
	/* Destructor call */
	EXP call, obj ;
	EXP count = "NULL_exp" ;
    },
    alloc -> {
	/* Allocator call */
	EXP call, init ;
	EXP garbage, size ;
    },
    dealloc -> {
	/* Deallocator call */
	EXP term, call ;
	EXP arg, size ;
    },
    rtti -> {
	/* Run-time type information */
	EXP arg ;
	EXP except ;
	int op ;
    },
    rtti_type -> {
	/* Run-time type information */
	TYPE arg ;
	int op ;
    },
    rtti_no -> {
	/* Arithmetic type number */
	TYPE arg ;
    },
    dynamic -> {
	/* Dynamic initialiser */
	EXP arg ;
    },
    aggregate -> {
	/* Aggregate initialisers */
	LIST EXP args ;
	LIST OFFSET offs ;
    },
    initialiser -> {
	/* Compound initialisers */
	LIST EXP args ;
	LIST OFFSET offs ;
	int kind ;
	unsigned virt, base ;
    },
    nof -> {
	/* Array initialisers */
	EXP start ;
	NAT size ;
	EXP pad ;
	EXP end ;
    },
    comma -> {
	/* Comma operator */
	LIST EXP args ;
    },
    set, unused -> {
	/* Variable analysis operators */
	EXP arg ;
    },
    reach, unreach -> {
	/* Flow analysis operators */
	EXP parent = "NULL_exp" ;
	EXP body ;
    },
    sequence -> {
	/* Sequence of statements */
	EXP parent = "NULL_exp" ;
	LIST EXP first, last ;
	NAMESPACE decl ;
	int block ;
    },
    solve_stmt -> {
	/* Label complex */
	EXP parent = "NULL_exp" ;
	EXP body ;
	LIST IDENTIFIER labels = "NULL_list ( IDENTIFIER )" ;
	LIST IDENTIFIER vars = "NULL_list ( IDENTIFIER )" ;
    },
    decl_stmt -> {
	/* Declaration statement */
	EXP parent = "NULL_exp" ;
	IDENTIFIER id ;
	EXP body ;
    },
    if_stmt -> {
	/* If statement */
	EXP parent = "NULL_exp" ;
	EXP cond ;
	EXP true_code, false_code ;
	IDENTIFIER label ;
    },
    while_stmt -> {
	/* While and for statements */
	EXP parent = "NULL_exp" ;
	EXP cond ;
	EXP body = "NULL_exp" ;
	IDENTIFIER break_lab ;
	IDENTIFIER cont_lab ;
	IDENTIFIER loop_lab ;
	LIST IDENTIFIER cond_id = "NULL_list ( IDENTIFIER )" ;
    },
    do_stmt -> {
	/* Do statements */
	EXP parent = "NULL_exp" ;
	EXP cond ;
	EXP body = "NULL_exp" ;
	IDENTIFIER break_lab ;
	IDENTIFIER cont_lab ;
	IDENTIFIER loop_lab ;
    },
    switch_stmt -> {
	/* Switch statement */
	EXP parent = "NULL_exp" ;
	EXP control ;
	EXP body ;
	LIST NAT cases = "NULL_list ( NAT )" ;
	LIST IDENTIFIER case_labs = "NULL_list ( IDENTIFIER )" ;
	IDENTIFIER default_lab = "NULL_id" ;
	int exhaust ;
	IDENTIFIER break_lab ;
    },
    hash_if -> {
	/* #if statement */
	EXP parent = "NULL_exp" ;
	EXP cond ;
	EXP true_code, false_code ;
	EXP last = "NULL_exp" ;
    },
    return_stmt -> {
	/* Return statement */
	EXP parent = "NULL_exp" ;
	EXP value ;
    },
    goto_stmt -> {
	/* Goto statement (including break and continue statements) */
	EXP parent = "NULL_exp" ;
	IDENTIFIER label ;
	EXP join ;
	EXP next ;
    },
    label_stmt -> {
	/* Labelled statement (including case and default statements) */
	EXP parent = "NULL_exp" ;
	IDENTIFIER label ;
	EXP body ;
	IDENTIFIER next = "NULL_id" ;
    },
    try_block -> {
	/* Try block */
	EXP parent = "NULL_exp" ;
	EXP body ;
	int func ;
	LIST EXP handlers = "NULL_list ( EXP )" ;
	LIST TYPE htypes = "NULL_list ( TYPE )" ;
	EXP ellipsis = "NULL_exp" ;
	LIST TYPE ttypes = "NULL_list ( TYPE )" ;
	LIST LOCATION tlocs = "NULL_list ( LOCATION )" ;
	ulong_type no = "LINK_NONE" ;
    },
    handler -> {
	/* Exception handler */
	EXP parent = "NULL_exp" ;
	IDENTIFIER except ;
	EXP body ;
	ulong_type diag = "LINK_NONE" ;
    },
    exception -> {
	/* Throw expression */
	EXP arg ;
	EXP size, destr ;
	int expl ;
    },
    thrown -> {
	/* Caught expression */
	int done ;
    },
    op -> {
	/* Undetermined operation */
	int lex ;
	EXP arg1, arg2 ;
    },
    opn -> {
	/* Undetermined operation */
	int lex ;
	LIST EXP args ;
    },
    assembler -> {
	/* asm expression */
	STRING op ;
	LIST EXP args ;
    },
    uncompiled -> {
	/* Uncompiled expression */
	LOCATION start ;
	PPTOKEN_P defn ;
    },
    location -> {
	/* Location expression */
	LOCATION end ;
	EXP arg ;
    },
    fail -> {
	/* Install-time failure */
	string msg ;
    },
    token -> {
	/* Tokenised expression */
	EXP parent = "NULL_exp" ;
	IDENTIFIER tok ;
	LIST TOKEN args ;
    },
    dummy -> {
	/* Dummy expression */
	EXP value ;
	ulong_type no ;
	OFFSET off ;
	int virt = "0" ;
	int cont ;
    }
} ;


/*
 * TYPE REPRESENTING AN OFFSET
 *
 * This type is used to represent an offset between two pointers. The type
 * construct gives the offset between successive elements of an array of that
 * type. The other constructs are fairly obvious.
 */

union OFFSET (off) = {
    /* empty */
} + {
    zero -> {
	/* Zero offset */
	TYPE type ;
    },
    type -> {
	/* Type offset */
	TYPE type ;
    },
    array -> {
	/* Array offset */
	TYPE type ;
	unsigned arg ;
    },
    extra -> {
	/* Extra offset for array allocator */
	TYPE type ;
	int scale ;
    },
    base -> {
	/* Base class offset */
	GRAPH graph ;
    },
    deriv -> {
	/* Derived class offset */
	GRAPH graph ;
	OFFSET direct ;
	OFFSET indirect ;
    },
    member -> {
	/* Member offset */
	IDENTIFIER id ;
    },
    ptr_mem -> {
	/* Pointer member offset */
	EXP arg ;
    },
    negate -> {
	/* Offset negation */
	OFFSET arg ;
    },
    plus -> {
	/* Offset addition */
	OFFSET arg1, arg2 ;
    },
    mult -> {
	/* Offset multiplication */
	OFFSET arg1 ;
	EXP arg2 ;
    },
    ptr_diff -> {
	/* Pointer difference */
	EXP ptr1, ptr2 ;
    },
    token -> {
	/* Tokenised offset */
	IDENTIFIER tok ;
	LIST TOKEN args ;
    }
} ;


/*
 * TYPE REPRESENTING A TOKEN
 *
 * This type is used to represent a TDF token. The various fields correspond to
 * the kinds of token - expressions, statements, types etc. Each simple
 * component also contains a field for holding a value of that kind, thus a
 * list of token arguments can themselves be expressed as a list of tokens.
 */

union TOKEN (tok) = {
    /* empty */
} + {
    exp -> {
	/* Expression tokens */
	TYPE type ;
	int constant ;
	EXP value ;
    },
    stmt -> {
	/* Statement tokens */
	EXP value ;
    },
    nat, snat -> {
	/* Integer constant tokens */
	NAT value ;
    },
    type -> {
	/* Type tokens */
	BASE_TYPE kind ;
	TYPE value ;
	TYPE alt = "NULL_type" ;
    },
    func -> {
	/* Function tokens */
	TYPE type ;
	IDENTIFIER defn = "NULL_id" ;
	TOKEN proc = "NULL_tok" ;
    },
    member -> {
	/* Class member tokens */
	TYPE of ;
	TYPE type ;
	OFFSET value ;
    },
    class -> {
	/* Template class tokens */
	TYPE type ;
	IDENTIFIER value ;
	TYPE alt = "NULL_type" ;
    },
    proc -> {
	/* Procedure tokens */
	TOKEN res ;
	NAMESPACE pars ;
	int key ;
	INSTANCE apps = "NULL_inst" ;
	LIST IDENTIFIER bids = "NULL_list ( IDENTIFIER )" ;
	LIST IDENTIFIER pids = "NULL_list ( IDENTIFIER )" ;
    },
    templ -> {
	/* Template tokens */
	DECL_SPEC usage ;
	NAMESPACE pars ;
	INSTANCE apps = "NULL_inst" ;
	LIST IDENTIFIER pids = "NULL_list ( IDENTIFIER )" ;
	LIST TOKEN dargs = "NULL_list ( TOKEN )" ;
    }
} ;


/*
 * TYPE REPRESENTING A TEMPLATE INSTANCE
 *
 * A template instance consists of an identifier, a type giving the template
 * form and a specifier giving declaration information.
 */

union INSTANCE (inst) = {
    TYPE form ;
    INSTANCE alias = "%0" ;
    INSTANCE next ;
} + {
    templ -> {
	/* Template instance */
	IDENTIFIER id ;
	TYPE spec = "NULL_type" ;
	DECL_SPEC access ;
	PPTOKEN_P mode = "NULL" ;
	LIST IDENTIFIER mems = "NULL_list ( IDENTIFIER )" ;
	INSTANCE prev ;
    },
    token -> {
	/* Token type instance */
	ulong_type no = "LINK_NONE" ;
    }
} ;


/*
 * TYPE REPRESENTING A VARIABLE ANALYSIS STATE
 *
 * This type is used in the variable analysis routines to record the state of a
 * local variable.
 */

struct VARIABLE (var) = {
    IDENTIFIER id ;
    DECL_SPEC info ;
} ;


/*
 * TYPE REPRESENTING AN ERROR
 *
 * An error can be either a simple message, described by an error number, or a
 * compound formed from two other errors. Some trickery is used to store the
 * arguments for a simple error after its size field.
 */

union ERROR (err) = {
    int severity ;
} + {
    simple -> {
	/* Simple errors */
	int number ;
	unsigned size = "0" ;
	/* arguments ... */
    },
    compound -> {
	/* Compound errors */
	ERROR head, tail ;
    }
} ;


/*
 * TYPE REPRESENTING A FILE POSITION
 *
 * A file position consists of a line number plus a pointer to a type giving
 * the file name.
 */

struct LOCATION (loc) = {
    ulong_type line ;
    ulong_type column ;
    PTR POSITION posn ;
} ;

struct POSITION (posn) = {
    string file ;
    string input ;
    string base ;
    string dir ;
    ulong_type offset ;
    PTR LOCATION from ;
    ulong_type datestamp ;
    ulong_type tok = "LINK_NONE" ;
} ;


package body scanner is

beglin : boolean := false;
i, bracelevel: integer;

function get_token return Token is
    toktype : Token;
    didadef, indented_code : boolean;
    cclval : integer;
    nmdefptr : vstring;
    nmdef, tmpbuf : vstring;

procedure ACTION_ECHO is
begin
    text_io.put( temp_action_file, yytext(1..YYLength) );
end ACTION_ECHO;

procedure MARK_END_OF_PROLOG is
begin
     text_io.put( temp_action_file, "%%%% end of prolog" );
     text_io.new_line( temp_action_file );
end MARK_END_OF_PROLOG;

procedure PUT_BACK_STRING(str : vstring; start : integer) is
begin
	for i in reverse start+1..tstring.len(str) loop
	    unput( CHAR(str,i) );
	end loop;
end PUT_BACK_STRING;

function check_yylex_here return boolean is
begin
	return ( (yytext'length >= 2) and then
			((yytext(1) = '#') and (yytext(2) = '#')));
end check_yylex_here;

function YYLex return Token is
subtype short is integer range -32768..32767;
    yy_act : integer;
    yy_c : short;

-- returned upon end-of-file
YY_END_TOK : constant integer := 0;
YY_END_OF_BUFFER : constant := 82;
subtype yy_state_type is integer;
yy_current_state : yy_state_type;
INITIAL : constant := 0;
SECT2 : constant := 1;
SECT2PROLOG : constant := 2;
SECT3 : constant := 3;
PICKUPDEF : constant := 4;
SC : constant := 5;
CARETISBOL : constant := 6;
NUM : constant := 7;
QUOTE : constant := 8;
FIRSTCCL : constant := 9;
CCL : constant := 10;
ACTION : constant := 11;
RECOVER : constant := 12;
BRACEERROR : constant := 13;
ACTION_STRING : constant := 14;
yy_accept : constant array(0..206) of short :=
    (   0,
        0,    0,    0,    0,    0,    0,   80,   80,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,    0,    0,    0,
       82,   13,    6,   12,   10,    1,   11,   13,   13,   13,
        9,   39,   31,   32,   25,   39,   38,   23,   39,   39,
       39,   31,   21,   39,   39,   24,   81,   19,   80,   80,
       15,   14,   16,   45,   81,   41,   42,   44,   46,   60,
       61,   58,   57,   59,   47,   49,   48,   47,   53,   52,
       53,   53,   55,   55,   55,   56,   66,   71,   70,   72,
       66,   72,   67,   64,   65,   81,   17,   63,   62,   73,

       75,   76,   77,    6,   12,   10,    1,   11,    0,    0,
        2,    0,    7,    4,    5,    0,    9,   31,   32,    0,
       28,    0,    0,    0,   78,   78,   27,   26,   27,    0,
       31,   21,    0,    0,   35,    0,    0,   19,   18,   80,
       80,   15,   14,   43,   44,   57,   79,   79,   50,   51,
       54,   66,    0,   69,    0,   66,   67,    0,   17,   73,
       74,    0,    7,    0,    0,    3,    0,   29,    0,   36,
        0,   78,   27,   27,   37,    0,    0,    0,   35,    0,
       30,   79,   66,   68,    0,    0,    8,    0,    0,    0,
        0,    0,    0,    0,    0,    0,    0,   22,    0,   22,

        0,   22,    4,    0,   34,    0
    ) ;
--98/02/21 Wolfgang Lohmann:
yy_ec : constant array(CHARACTER'FIRST..CHARACTER'LAST) of short :=
    (   0,
        1,    1,    1,    1,    1,    1,    1,    1,    2,    3,
        1,    4,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        1,    5,    1,    6,    7,    8,    9,    1,   10,   11,
       11,   11,   11,   12,   13,   11,   14,   15,   15,   15,
       15,   15,   15,   15,   15,   15,   15,    1,    1,   16,
        1,   17,   11,    1,   23,   22,   22,   22,   24,   25,
       22,   22,   22,   22,   22,   22,   22,   22,   26,   22,
       22,   27,   28,   29,   22,   22,   22,   30,   22,   22,
       18,   19,   20,   21,   22,    1,   23,   22,   22,   22,

       24,   25,   22,   22,   22,   22,   22,   22,   22,   22,
       26,   22,   22,   27,   28,   29,   22,   22,   22,   30,
       22,   22,   31,   32,   33,    1,    others => 1
    ) ;

yy_meta : constant array(0..33) of short :=
    (   0,
        1,    2,    3,    2,    2,    4,    1,    1,    1,    5,
        1,    1,    6,    5,    7,    1,    1,    1,    8,    9,
        1,   10,   10,   10,   10,   10,   10,   10,   10,   10,
        5,   11,   12
    ) ;

yy_base : constant array(0..254) of short :=
    (   0,
        0,   29,   58,   89,  503,  499,  498,  305,    4,    8,
      119,  147,  286,  285,   32,   34,   65,   67,   93,   96,
      110,  113,  177,    0,  302,  301,   12,   15,   82,  121,
      303,  880,   76,  880,    0,   37,  880,  299,   11,  288,
        0,  880,   11,  880,  880,   14,  880,  284,  280,  283,
      196,  225,  880,  288,  283,  880,  292,    0,  291,  880,
        0,  133,  880,  880,  880,  880,  272,    0,  880,  880,
      880,  880,  277,  880,  880,  880,  880,  276,  880,  880,
      274,  275,  880,    0,  272,  880,    0,  880,  880,  109,
      273,  880,    0,  880,  880,  282,  880,  880,  880,    0,

      880,  880,    0,  149,  880,    0,  152,  880,  271,  280,
      880,  272,    0,  247,  880,  263,    0,   72,  880,  262,
      880,  240,   63,  119,  880,  248,    0,  880,  245,  249,
      277,  880,  248,  153,    0,  256,  253,    0,  880,  252,
      880,    0,  156,  880,    0,  239,  880,  238,  880,  880,
      880,    0,  221,  880,    0,  309,    0,  249,  880,    0,
      880,  248,    0,  227,  246,  880,  245,  880,  221,  880,
      148,  231,    0,    0,  880,  232,  229,  230,    0,  241,
      880,  226,    0,  880,  236,  234,  880,  209,  210,  197,
      231,  212,  159,  128,  108,  194,  115,  880,  108,  880,

       84,  880,  880,    4,  880,  880,  342,  354,  366,  378,
      390,  402,  414,  426,  438,  450,  462,  474,  486,  493,
      502,  508,  520,  527,  536,  547,  559,  571,  583,  595,
      607,  619,  631,  638,  648,  660,  672,  684,  695,  702,
      712,  724,  736,  748,  760,  772,  784,  795,  807,  819,
      831,  843,  855,  867
    ) ;

yy_def : constant array(0..254) of short :=
    (   0,
      207,  207,  208,  208,  209,  209,  210,  210,  211,  211,
      212,  212,  213,  213,  214,  214,  215,  215,  216,  216,
      217,  217,  206,   23,  218,  218,  213,  213,  219,  219,
      206,  206,  206,  206,  220,  221,  206,  222,  223,  206,
      224,  206,  225,  206,  206,  206,  206,  206,  226,  227,
      228,  229,  206,  206,  206,  206,  230,  231,  232,  206,
      233,  206,  206,  206,  206,  206,  206,  234,  206,  206,
      206,  206,  206,  206,  206,  206,  206,  227,  206,  206,
      235,  236,  206,  237,  227,  206,  238,  206,  206,  239,
      238,  206,  240,  206,  206,  241,  206,  206,  206,  242,

      206,  206,  243,  206,  206,  220,  221,  206,  206,  222,
      206,  206,  244,  206,  206,  245,  224,  225,  206,  246,
      206,  206,  226,  226,  206,  206,  247,  206,  247,  206,
      229,  206,  206,  246,  248,  249,  230,  231,  206,  232,
      206,  233,  206,  206,  234,  206,  206,  206,  206,  206,
      206,  238,  239,  206,  239,  206,  240,  241,  206,  242,
      206,  250,  244,  206,  245,  206,  246,  206,  206,  206,
      226,  206,  247,  129,  206,  206,  249,  246,  248,  249,
      206,  206,  156,  206,  251,  250,  206,  206,  206,  226,
      252,  253,  254,  206,  206,  226,  252,  206,  253,  206,

      254,  206,  206,  206,  206,    0,  206,  206,  206,  206,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206,  206
    ) ;

yy_nxt : constant array(0..913) of short :=
    (   0,
      206,   33,   34,   33,   33,   62,   63,   62,   62,   62,
       63,   62,   62,  119,   98,  121,  121,   98,  121,  113,
      205,   35,   35,   35,   35,   35,   35,   35,   35,   35,
       36,   37,   36,   36,   71,   38,   71,   39,  114,  108,
      115,   40,  120,   72,   99,   72,   73,   99,   73,  109,
       41,   41,   41,   41,   41,   41,   41,   41,   41,   43,
       44,   43,   43,   45,   74,   46,   74,   76,   47,   76,
       77,   47,   77,   48,  119,   49,   50,  104,  105,  104,
      104,  124,  170,   78,  101,   78,  202,  102,   51,   47,
       52,   53,   52,   52,   45,   65,   46,   54,   65,   47,

      103,   55,   47,  120,   48,   80,   49,   50,   80,   56,
      200,   81,   65,   82,   81,   65,   82,  198,  154,   51,
       47,   65,   84,  101,  204,   84,  102,  155,   85,   86,
       66,   85,   86,  171,  143,   67,  143,  143,  123,  103,
       68,   68,   68,   68,   68,   68,   68,   68,   68,   65,
      104,  105,  104,  104,  108,  168,  203,  143,   66,  143,
      143,  202,  190,   67,  109,  178,  124,  170,   68,   68,
       68,   68,   68,   68,   68,   68,   68,   87,   87,   88,
       87,   87,   89,   87,   87,   87,   90,   87,   87,   91,
       92,   87,   87,   87,   87,   87,   87,   87,   93,   93,

       93,   93,   93,   93,   93,   93,   93,   94,   87,   95,
      128,  196,  124,  170,  200,  124,  170,  129,  129,  129,
      129,  129,  129,  129,  129,  129,  131,  132,  131,  131,
      154,  181,  168,  198,  195,  194,  187,  133,  184,  155,
      147,  192,  193,  181,  191,  125,  189,  168,  166,  188,
      187,  159,  182,  146,  141,  138,  134,  174,  181,  174,
      177,  176,  172,  169,  168,  166,  174,  174,  174,  174,
      174,  174,  174,  174,  174,  164,  162,  175,  131,  132,
      131,  131,  111,  116,  159,  156,  126,  150,  148,  133,
      126,  146,  144,  141,  138,  136,  135,  126,  124,  122,

      116,  111,  206,   97,   97,   69,   69,   60,  134,  183,
      183,  184,  183,  183,  185,  183,  183,  183,  185,  183,
      183,  183,  185,  183,  183,  183,  183,  183,  183,  183,
      185,  185,  185,  185,  185,  185,  185,  185,  185,  185,
      183,  185,   32,   32,   32,   32,   32,   32,   32,   32,
       32,   32,   32,   32,   42,   42,   42,   42,   42,   42,
       42,   42,   42,   42,   42,   42,   57,   57,   57,   57,
       57,   57,   57,   57,   57,   57,   57,   57,   59,   59,
       59,   59,   59,   59,   59,   59,   59,   59,   59,   59,
       61,   61,   61,   61,   61,   61,   61,   61,   61,   61,

       61,   61,   64,   64,   64,   64,   64,   64,   64,   64,
       64,   64,   64,   64,   65,   65,   65,   65,   65,   65,
       65,   65,   65,   65,   65,   65,   70,   70,   70,   70,
       70,   70,   70,   70,   70,   70,   70,   70,   75,   75,
       75,   75,   75,   75,   75,   75,   75,   75,   75,   75,
       79,   79,   79,   79,   79,   79,   79,   79,   79,   79,
       79,   79,   83,   83,   83,   83,   83,   83,   83,   83,
       83,   83,   83,   83,   96,   96,   96,   96,   96,   96,
       96,   96,   96,   96,   96,   96,  100,  100,  100,  100,
      100,  100,  100,  100,  100,  100,  100,  100,  106,  106,

       60,   58,  106,  107,  107,   58,  206,  107,  110,  110,
      110,  110,  110,  110,  110,  110,  110,  110,  110,  110,
      112,  112,  112,  112,  112,  112,  112,  112,  112,  112,
      112,  112,  117,  117,  206,  206,  117,  118,  118,  206,
      206,  206,  206,  206,  206,  206,  118,  123,  123,  206,
      123,  123,  123,  123,  123,  206,  123,  123,  123,  125,
      125,  206,  125,  125,  125,  125,  125,  125,  125,  125,
      125,  127,  127,  206,  127,  127,  127,  127,  127,  127,
      127,  127,  127,  130,  130,  130,  130,  130,  130,  130,
      130,  130,  130,  130,  130,  137,  137,  137,  137,  137,

      137,  137,  137,  137,  137,  137,  137,  139,  206,  206,
      139,  139,  139,  139,  139,  139,  139,  139,  139,  140,
      140,  140,  140,  140,  140,  140,  140,  140,  140,  140,
      140,  142,  142,  206,  142,  142,  142,  142,  142,  142,
      142,  142,  142,  145,  145,  206,  206,  145,  147,  147,
      206,  147,  147,  147,  147,  147,  147,  147,  147,  147,
      149,  149,  206,  149,  149,  149,  149,  149,  149,  149,
      149,  149,  151,  151,  206,  151,  151,  151,  151,  151,
      206,  151,  151,  151,  152,  152,  206,  206,  206,  152,
      152,  152,  152,  206,  152,  153,  153,  206,  153,  153,

      153,  153,  153,  153,  153,  153,  153,  157,  157,  206,
      206,  157,  158,  158,  158,  158,  158,  158,  158,  158,
      158,  158,  158,  158,  160,  160,  206,  206,  160,  160,
      160,  206,  160,  160,  160,  160,  161,  161,  206,  161,
      161,  161,  161,  161,  161,  161,  161,  161,  163,  163,
      206,  163,  163,  163,  163,  163,  163,  163,  163,  163,
      165,  165,  165,  165,  165,  165,  165,  165,  165,  165,
      165,  165,  167,  167,  167,  167,  167,  167,  167,  167,
      167,  167,  167,  167,  173,  173,  206,  173,  173,  173,
      173,  173,  173,  173,  173,  179,  179,  206,  179,  179,

      179,  179,  179,  179,  179,  179,  179,  180,  180,  180,
      180,  180,  180,  180,  180,  180,  180,  180,  180,  186,
      186,  186,  186,  186,  186,  186,  186,  186,  186,  186,
      186,  185,  185,  185,  185,  185,  185,  185,  185,  185,
      185,  185,  185,  197,  197,  197,  197,  197,  197,  197,
      197,  197,  197,  197,  197,  199,  199,  199,  199,  199,
      199,  199,  199,  199,  199,  199,  199,  201,  201,  201,
      201,  201,  201,  201,  201,  201,  201,  201,  201,   31,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,

      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206
    ) ;

yy_chk : constant array(0..913) of short :=
    (   0,
        0,    1,    1,    1,    1,    9,    9,    9,    9,   10,
       10,   10,   10,   43,   27,   46,   46,   28,   46,   39,
      204,    1,    1,    1,    1,    1,    1,    1,    1,    1,
        2,    2,    2,    2,   15,    2,   16,    2,   39,   36,
       39,    2,   43,   15,   27,   16,   15,   28,   16,   36,
        2,    2,    2,    2,    2,    2,    2,    2,    2,    3,
        3,    3,    3,    3,   15,    3,   16,   17,    3,   18,
       17,    3,   18,    3,  118,    3,    3,   33,   33,   33,
       33,  123,  123,   17,   29,   18,  201,   29,    3,    3,
        4,    4,    4,    4,    4,   19,    4,    4,   20,    4,

       29,    4,    4,  118,    4,   19,    4,    4,   20,    4,
      199,   19,   21,   19,   20,   22,   20,  197,   90,    4,
        4,   11,   21,   30,  195,   22,   30,   90,   21,   21,
       11,   22,   22,  124,   62,   11,   62,   62,  124,   30,
       11,   11,   11,   11,   11,   11,   11,   11,   11,   12,
      104,  104,  104,  104,  107,  134,  194,  143,   12,  143,
      143,  193,  171,   12,  107,  134,  171,  171,   12,   12,
       12,   12,   12,   12,   12,   12,   12,   23,   23,   23,
       23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
       23,   23,   23,   23,   23,   23,   23,   23,   23,   23,

       23,   23,   23,   23,   23,   23,   23,   23,   23,   23,
       51,  190,  196,  196,  192,  190,  190,   51,   51,   51,
       51,   51,   51,   51,   51,   51,   52,   52,   52,   52,
      153,  177,  178,  191,  189,  188,  186,   52,  185,  153,
      182,  177,  178,  180,  176,  172,  169,  167,  165,  164,
      162,  158,  148,  146,  140,  137,   52,  129,  136,  129,
      133,  130,  126,  122,  120,  116,  129,  129,  129,  129,
      129,  129,  129,  129,  129,  114,  112,  129,  131,  131,
      131,  131,  110,  109,   96,   91,   85,   82,   81,  131,
       78,   73,   67,   59,   57,   55,   54,   50,   49,   48,

       40,   38,   31,   26,   25,   14,   13,    8,  131,  156,
      156,  156,  156,  156,  156,  156,  156,  156,  156,  156,
      156,  156,  156,  156,  156,  156,  156,  156,  156,  156,
      156,  156,  156,  156,  156,  156,  156,  156,  156,  156,
      156,  156,  207,  207,  207,  207,  207,  207,  207,  207,
      207,  207,  207,  207,  208,  208,  208,  208,  208,  208,
      208,  208,  208,  208,  208,  208,  209,  209,  209,  209,
      209,  209,  209,  209,  209,  209,  209,  209,  210,  210,
      210,  210,  210,  210,  210,  210,  210,  210,  210,  210,
      211,  211,  211,  211,  211,  211,  211,  211,  211,  211,

      211,  211,  212,  212,  212,  212,  212,  212,  212,  212,
      212,  212,  212,  212,  213,  213,  213,  213,  213,  213,
      213,  213,  213,  213,  213,  213,  214,  214,  214,  214,
      214,  214,  214,  214,  214,  214,  214,  214,  215,  215,
      215,  215,  215,  215,  215,  215,  215,  215,  215,  215,
      216,  216,  216,  216,  216,  216,  216,  216,  216,  216,
      216,  216,  217,  217,  217,  217,  217,  217,  217,  217,
      217,  217,  217,  217,  218,  218,  218,  218,  218,  218,
      218,  218,  218,  218,  218,  218,  219,  219,  219,  219,
      219,  219,  219,  219,  219,  219,  219,  219,  220,  220,

        7,    6,  220,  221,  221,    5,    0,  221,  222,  222,
      222,  222,  222,  222,  222,  222,  222,  222,  222,  222,
      223,  223,  223,  223,  223,  223,  223,  223,  223,  223,
      223,  223,  224,  224,    0,    0,  224,  225,  225,    0,
        0,    0,    0,    0,    0,    0,  225,  226,  226,    0,
      226,  226,  226,  226,  226,    0,  226,  226,  226,  227,
      227,    0,  227,  227,  227,  227,  227,  227,  227,  227,
      227,  228,  228,    0,  228,  228,  228,  228,  228,  228,
      228,  228,  228,  229,  229,  229,  229,  229,  229,  229,
      229,  229,  229,  229,  229,  230,  230,  230,  230,  230,

      230,  230,  230,  230,  230,  230,  230,  231,    0,    0,
      231,  231,  231,  231,  231,  231,  231,  231,  231,  232,
      232,  232,  232,  232,  232,  232,  232,  232,  232,  232,
      232,  233,  233,    0,  233,  233,  233,  233,  233,  233,
      233,  233,  233,  234,  234,    0,    0,  234,  235,  235,
        0,  235,  235,  235,  235,  235,  235,  235,  235,  235,
      236,  236,    0,  236,  236,  236,  236,  236,  236,  236,
      236,  236,  237,  237,    0,  237,  237,  237,  237,  237,
        0,  237,  237,  237,  238,  238,    0,    0,    0,  238,
      238,  238,  238,    0,  238,  239,  239,    0,  239,  239,

      239,  239,  239,  239,  239,  239,  239,  240,  240,    0,
        0,  240,  241,  241,  241,  241,  241,  241,  241,  241,
      241,  241,  241,  241,  242,  242,    0,    0,  242,  242,
      242,    0,  242,  242,  242,  242,  243,  243,    0,  243,
      243,  243,  243,  243,  243,  243,  243,  243,  244,  244,
        0,  244,  244,  244,  244,  244,  244,  244,  244,  244,
      245,  245,  245,  245,  245,  245,  245,  245,  245,  245,
      245,  245,  246,  246,  246,  246,  246,  246,  246,  246,
      246,  246,  246,  246,  247,  247,    0,  247,  247,  247,
      247,  247,  247,  247,  247,  248,  248,    0,  248,  248,

      248,  248,  248,  248,  248,  248,  248,  249,  249,  249,
      249,  249,  249,  249,  249,  249,  249,  249,  249,  250,
      250,  250,  250,  250,  250,  250,  250,  250,  250,  250,
      250,  251,  251,  251,  251,  251,  251,  251,  251,  251,
      251,  251,  251,  252,  252,  252,  252,  252,  252,  252,
      252,  252,  252,  252,  252,  253,  253,  253,  253,  253,
      253,  253,  253,  253,  253,  253,  253,  254,  254,  254,
      254,  254,  254,  254,  254,  254,  254,  254,  254,  206,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,

      206,  206,  206,  206,  206,  206,  206,  206,  206,  206,
      206,  206,  206
    ) ;


-- copy whatever the last rule matched to the standard output

procedure ECHO is
begin
   if (text_io.is_open(user_output_file)) then
     text_io.put( user_output_file, yytext );
   else
     text_io.put( yytext );
   end if;
end ECHO;

-- enter a start condition.
-- Using procedure requires a () after the ENTER, but makes everything
-- much neater.

procedure ENTER( state : integer ) is
begin
     yy_start := 1 + 2 * state;
end ENTER;

-- action number for EOF rule of a given start state
function YY_STATE_EOF(state : integer) return integer is
begin
     return YY_END_OF_BUFFER + state + 1;
end YY_STATE_EOF;

-- return all but the first 'n' matched characters back to the input stream
procedure yyless(n : integer) is
begin
        yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
        yy_cp := yy_bp + n;
        yy_c_buf_p := yy_cp;
        YY_DO_BEFORE_ACTION; -- set up yytext again
end yyless;

-- redefine this if you have something you want each time.
procedure YY_USER_ACTION is
begin
        null;
end;

-- yy_get_previous_state - get the state just before the EOB char was reached

function yy_get_previous_state return yy_state_type is
    yy_current_state : yy_state_type;
    yy_c : short;
    yy_bp : integer := yytext_ptr;
begin
    yy_current_state := yy_start;
    if ( yy_ch_buf(yy_bp-1) = ASCII.LF ) then
	yy_current_state := yy_current_state + 1;
    end if;

    for yy_cp in yytext_ptr..yy_c_buf_p - 1 loop
	yy_c := yy_ec(yy_ch_buf(yy_cp));
	if ( yy_accept(yy_current_state) /= 0 ) then
	    yy_last_accepting_state := yy_current_state;
	    yy_last_accepting_cpos := yy_cp;
	end if;
	while ( yy_chk(yy_base(yy_current_state) + yy_c) /= yy_current_state ) loop
	    yy_current_state := yy_def(yy_current_state);
	    if ( yy_current_state >= 207 ) then
		yy_c := yy_meta(yy_c);
	    end if;
	end loop;
	yy_current_state := yy_nxt(yy_base(yy_current_state) + yy_c);
    end loop;

    return yy_current_state;
end yy_get_previous_state;

procedure yyrestart( input_file : file_type ) is
begin
   open_input(text_io.name(input_file));
end yyrestart;

begin -- of YYLex
<<new_file>>
        -- this is where we enter upon encountering an end-of-file and
        -- yywrap() indicating that we should continue processing

    if ( yy_init ) then
        if ( yy_start = 0 ) then
            yy_start := 1;      -- first start state
        end if;

        -- we put in the '\n' and start reading from [1] so that an
        -- initial match-at-newline will be true.

        yy_ch_buf(0) := ASCII.LF;
        yy_n_chars := 1;

        -- we always need two end-of-buffer characters.  The first causes
        -- a transition to the end-of-buffer state.  The second causes
        -- a jam in that state.

        yy_ch_buf(yy_n_chars) := YY_END_OF_BUFFER_CHAR;
        yy_ch_buf(yy_n_chars + 1) := YY_END_OF_BUFFER_CHAR;

        yy_eof_has_been_seen := false;

        yytext_ptr := 1;
        yy_c_buf_p := yytext_ptr;
        yy_hold_char := yy_ch_buf(yy_c_buf_p);
        yy_init := false;
    end if; -- yy_init

    loop                -- loops until end-of-file is reached


        yy_cp := yy_c_buf_p;

        -- support of yytext
        yy_ch_buf(yy_cp) := yy_hold_char;

        -- yy_bp points to the position in yy_ch_buf of the start of the
        -- current run.
	yy_bp := yy_cp;
	yy_current_state := yy_start;
	if ( yy_ch_buf(yy_bp-1) = ASCII.LF ) then
	    yy_current_state := yy_current_state + 1;
	end if;
	loop
		yy_c := yy_ec(yy_ch_buf(yy_cp));
		if ( yy_accept(yy_current_state) /= 0 ) then
		    yy_last_accepting_state := yy_current_state;
		    yy_last_accepting_cpos := yy_cp;
		end if;
		while ( yy_chk(yy_base(yy_current_state) + yy_c) /= yy_current_state ) loop
		    yy_current_state := yy_def(yy_current_state);
		    if ( yy_current_state >= 207 ) then
			yy_c := yy_meta(yy_c);
		    end if;
		end loop;
		yy_current_state := yy_nxt(yy_base(yy_current_state) + yy_c);
	    yy_cp := yy_cp + 1;
if ( yy_current_state = 206 ) then
    exit;
end if;
	end loop;
	yy_cp := yy_last_accepting_cpos;
	yy_current_state := yy_last_accepting_state;

<<next_action>>
	    yy_act := yy_accept(yy_current_state);
            YY_DO_BEFORE_ACTION;
            YY_USER_ACTION;

        if aflex_debug then  -- output acceptance info. for (-d) debug mode
            text_io.put( Standard_Error, "--accepting rule #" );
            text_io.put( Standard_Error, INTEGER'IMAGE(yy_act) );
            text_io.put_line( Standard_Error, "(""" & yytext & """)");
        end if;


<<do_action>>   -- this label is used only to access EOF actions
            case yy_act is
		when 0 => -- must backtrack
		-- undo the effects of YY_DO_BEFORE_ACTION
		yy_ch_buf(yy_cp) := yy_hold_char;
		yy_cp := yy_last_accepting_cpos;
		yy_current_state := yy_last_accepting_state;
		goto next_action;



when 1 => 
--# line 46 "ascan.l"
 indented_code := true; 

when 2 => 
--# line 47 "ascan.l"
 linenum := linenum + 1; ECHO;
				-- treat as a comment;
			

when 3 => 
--# line 50 "ascan.l"
 linenum := linenum + 1; ECHO; 

when 4 => 
--# line 51 "ascan.l"
 return ( SCDECL ); 

when 5 => 
--# line 52 "ascan.l"
 return ( XSCDECL ); 

when 6 => 
--# line 54 "ascan.l"
 return ( WHITESPACE ); 

when 7 => 
--# line 56 "ascan.l"

			sectnum := 2;
			misc.line_directive_out;
			ENTER(SECT2PROLOG);
			return ( SECTEND );
			

when 8 => 
--# line 63 "ascan.l"

			text_io.put( Standard_Error, "old-style lex command at line " );
			int_io.put( Standard_Error, linenum );
			text_io.put( Standard_Error, "ignored:" );
			text_io.new_line( Standard_Error );
			text_io.put( Standard_Error, ASCII.HT );
			text_io.put( Standard_Error, yytext(1..YYLength) );
			linenum := linenum + 1;
			

when 9 => 
--# line 73 "ascan.l"

			nmstr := vstr(yytext(1..YYLength));
			didadef := false;
			ENTER(PICKUPDEF);
			

when 10 => 
--# line 79 "ascan.l"
 nmstr := vstr(yytext(1..YYLength));
			  return NAME;
			

when 11 => 
--# line 82 "ascan.l"
 linenum := linenum + 1;
			  -- allows blank lines in section 1;
			

when 12 => 
--# line 85 "ascan.l"
 linenum := linenum + 1; return Newline; 

when 13 => 
--# line 86 "ascan.l"
 misc.synerr( "illegal character" );ENTER(RECOVER);

when 14 => 
--# line 88 "ascan.l"
 null;
			  -- separates name and definition;
			

when 15 => 
--# line 92 "ascan.l"

			nmdef := vstr(yytext(1..YYLength));

			i := tstring.len( nmdef );
			while ( i >= tstring.first ) loop
			    if ( (CHAR(nmdef,i) /= ' ') and
				 (CHAR(nmdef,i) /= ASCII.HT) ) then
				exit;
			    end if;
			    i := i - 1;
			end loop;

                        sym.ndinstal( nmstr,
				tstring.slice(nmdef, tstring.first, i) );
			didadef := true;
			

when 16 => 
--# line 109 "ascan.l"

			if ( not didadef ) then
			    misc.synerr( "incomplete name definition" );
			end if;
			ENTER(0);
			linenum := linenum + 1;
			

when 17 => 
--# line 117 "ascan.l"
 linenum := linenum + 1;
			  ENTER(0);
			  nmstr := vstr(yytext(1..YYLength));
			  return NAME;
			

when 18 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
yy_cp := yy_cp - 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 123 "ascan.l"

			linenum := linenum + 1;
			ACTION_ECHO;
			MARK_END_OF_PROLOG;
			ENTER(SECT2);
			

when 19 => 
--# line 130 "ascan.l"
 linenum := linenum + 1; ACTION_ECHO; 

when YY_END_OF_BUFFER +SECT2PROLOG + 1 
 =>
--# line 132 "ascan.l"
 MARK_END_OF_PROLOG;
			  return End_Of_Input;
			

when 21 => 
--# line 136 "ascan.l"
 linenum := linenum + 1;
			  -- allow blank lines in sect2;

			-- this rule matches indented lines which
			-- are not comments.
when 22 => 
--# line 141 "ascan.l"

			misc.synerr("indented code found outside of action");
			linenum := linenum + 1;
			

when 23 => 
--# line 146 "ascan.l"
 ENTER(SC); return ( '<' ); 

when 24 => 
--# line 147 "ascan.l"
 return ( '^' );  

when 25 => 
--# line 148 "ascan.l"
 ENTER(QUOTE); return ( '"' ); 

when 26 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
 yy_cp := yy_bp + 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 149 "ascan.l"
 ENTER(NUM); return ( '{' ); 

when 27 => 
--# line 150 "ascan.l"
 ENTER(BRACEERROR); 

when 28 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
 yy_cp := yy_bp + 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 151 "ascan.l"
 return ( '$' ); 

when 29 => 
--# line 153 "ascan.l"
 continued_action := true;
			  linenum := linenum + 1;
			  return Newline;
			

when 30 => 
--# line 158 "ascan.l"
 linenum := linenum + 1; ACTION_ECHO; 

when 31 => 
--# line 160 "ascan.l"

			-- this rule is separate from the one below because
			-- otherwise we get variable trailing context, so
			-- we can't build the scanner using -f,F

			bracelevel := 0;
			continued_action := false;
			ENTER(ACTION);
			return Newline;
			

when 32 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
yy_cp := yy_cp - 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 171 "ascan.l"

			bracelevel := 0;
			continued_action := false;
			ENTER(ACTION);
			return Newline;
			

when 33 => 
--# line 178 "ascan.l"
 linenum := linenum + 1; return Newline; 

when 34 => 
--# line 180 "ascan.l"
 return ( EOF_OP ); 

when 35 => 
--# line 182 "ascan.l"

			sectnum := 3;
			ENTER(SECT3);
			return ( End_Of_Input );
			-- to stop the parser
			

when 36 => 
--# line 189 "ascan.l"


			nmstr := vstr(yytext(1..YYLength));

			-- check to see if we've already encountered this ccl
                        cclval := sym.ccllookup( nmstr );
			if ( cclval /= 0 ) then
			    yylval := cclval;
			    cclreuse := cclreuse + 1;
			    return ( PREVCCL );
			else
			    -- we fudge a bit.  We know that this ccl will
			    -- soon be numbered as lastccl + 1 by cclinit
			    sym.cclinstal( nmstr, lastccl + 1 );

			    -- push back everything but the leading bracket
			    -- so the ccl can be rescanned

			    PUT_BACK_STRING(nmstr, 1);

			    ENTER(FIRSTCCL);
			    return ( '[' );
			end if;
			

when 37 => 
--# line 214 "ascan.l"

			nmstr := vstr(yytext(1..YYLength));
			-- chop leading and trailing brace
			tmpbuf := slice(vstr(yytext(1..YYLength)),
								2, YYLength-1);

			nmdefptr := sym.ndlookup( tmpbuf );
			if ( nmdefptr = NUL ) then
			    misc.synerr( "undefined {name}" );
			else
			    -- push back name surrounded by ()'s
			    unput(')');
			    PUT_BACK_STRING(nmdefptr, 0);
			    unput('(');
			end if;
			

when 38 => 
--# line 231 "ascan.l"
 tmpbuf := vstr(yytext(1..YYLength));
			  case tstring.CHAR(tmpbuf,1) is
				when '/' => return '/';
				when '|' => return '|';
				when '*' => return '*';
				when '+' => return '+';
				when '?' => return '?';
				when '.' => return '.';
				when '(' => return '(';
				when ')' => return ')';
				when others =>
					misc.aflexerror("error in aflex case");
			  end case;
			

when 39 => 
--# line 245 "ascan.l"
 tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			

when 40 => 
--# line 249 "ascan.l"
 linenum := linenum + 1; return Newline; 

when 41 => 
--# line 252 "ascan.l"
 return ( ',' ); 

when 42 => 
--# line 253 "ascan.l"
 ENTER(SECT2); return ( '>' ); 

when 43 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
 yy_cp := yy_bp + 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 254 "ascan.l"
 ENTER(CARETISBOL); return ( '>' ); 

when 44 => 
--# line 255 "ascan.l"
 nmstr := vstr(yytext(1..YYLength));
			  return NAME;
			

when 45 => 
--# line 258 "ascan.l"
 misc.synerr( "bad start condition name" ); 

when 46 => 
--# line 260 "ascan.l"
 ENTER(SECT2); return ( '^' ); 

when 47 => 
--# line 263 "ascan.l"
 tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			

when 48 => 
--# line 267 "ascan.l"
 ENTER(SECT2); return ( '"' ); 

when 49 => 
--# line 269 "ascan.l"

			misc.synerr( "missing quote" );
			ENTER(SECT2);
			linenum := linenum + 1;
			return ( '"' );
			

when 50 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
 yy_cp := yy_bp + 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 277 "ascan.l"
 ENTER(CCL); return ( '^' ); 

when 51 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
 yy_cp := yy_bp + 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 278 "ascan.l"
 return ( '^' ); 

when 52 => 
--# line 279 "ascan.l"
 ENTER(CCL); yylval := CHARACTER'POS('-'); return ( CHAR ); 

when 53 => 
--# line 280 "ascan.l"
 ENTER(CCL);
			  tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			

when 54 => 
yy_ch_buf(yy_cp) := yy_hold_char; -- undo effects of setting up yytext
 yy_cp := yy_bp + 1;
yy_c_buf_p := yy_cp;
YY_DO_BEFORE_ACTION; -- set up yytext again
--# line 286 "ascan.l"
 return ( '-' ); 

when 55 => 
--# line 287 "ascan.l"
 tmpbuf := vstr(yytext(1..YYLength));
			  yylval := CHARACTER'POS(CHAR(tmpbuf,1));
			  return CHAR;
			

when 56 => 
--# line 291 "ascan.l"
 ENTER(SECT2); return ( ']' ); 

when 57 => 
--# line 294 "ascan.l"

			yylval := misc.myctoi( vstr(yytext(1..YYLength)) );
			return ( NUMBER );
			

when 58 => 
--# line 299 "ascan.l"
 return ( ',' ); 

when 59 => 
--# line 300 "ascan.l"
 ENTER(SECT2); return ( '}' ); 

when 60 => 
--# line 302 "ascan.l"

			misc.synerr( "bad character inside {}'s" );
			ENTER(SECT2);
			return ( '}' );
			

when 61 => 
--# line 308 "ascan.l"

			misc.synerr( "missing }" );
			ENTER(SECT2);
			linenum := linenum + 1;
			return ( '}' );
			

when 62 => 
--# line 316 "ascan.l"
 misc.synerr( "bad name in {}'s" ); ENTER(SECT2); 

when 63 => 
--# line 317 "ascan.l"
 misc.synerr( "missing }" );
			  linenum := linenum + 1;
			  ENTER(SECT2);
			

when 64 => 
--# line 322 "ascan.l"
 bracelevel := bracelevel + 1; 

when 65 => 
--# line 323 "ascan.l"
 bracelevel := bracelevel - 1; 

when 66 => 
--# line 324 "ascan.l"
 ACTION_ECHO; 

when 67 => 
--# line 325 "ascan.l"
 ACTION_ECHO; 

when 68 => 
--# line 326 "ascan.l"
 linenum := linenum + 1; ACTION_ECHO; 

when 69 => 
--# line 327 "ascan.l"
 ACTION_ECHO;
				  -- character constant;
			

when 70 => 
--# line 331 "ascan.l"
 ACTION_ECHO; ENTER(ACTION_STRING); 

when 71 => 
--# line 333 "ascan.l"

			linenum := linenum + 1;
			ACTION_ECHO;
			if ( bracelevel = 0 ) then
			    text_io.new_line ( temp_action_file );
			    ENTER(SECT2);
	                end if;
			

when 72 => 
--# line 341 "ascan.l"
 ACTION_ECHO; 

when 73 => 
--# line 343 "ascan.l"
 ACTION_ECHO; 

when 74 => 
--# line 344 "ascan.l"
 ACTION_ECHO; 

when 75 => 
--# line 345 "ascan.l"
 linenum := linenum + 1; ACTION_ECHO; 

when 76 => 
--# line 346 "ascan.l"
 ACTION_ECHO; ENTER(ACTION); 

when 77 => 
--# line 347 "ascan.l"
 ACTION_ECHO; 

when 78 => 
--# line 350 "ascan.l"

			yylval := CHARACTER'POS(misc.myesc( vstr(yytext(1..YYLength)) ));
			return ( CHAR );
			

when 79 => 
--# line 355 "ascan.l"

			yylval := CHARACTER'POS(misc.myesc( vstr(yytext(1..YYLength)) ));
			ENTER(CCL);
			return ( CHAR );
			

when 80 => 
--# line 362 "ascan.l"
 if ( check_yylex_here ) then
				return End_Of_Input;
			  else
				ECHO;
			  end if;
			

when 81 => 
--# line 368 "ascan.l"
raise AFLEX_SCANNER_JAMMED;
when YY_END_OF_BUFFER + INITIAL + 1 |
YY_END_OF_BUFFER + SECT2 + 1 |
YY_END_OF_BUFFER + SECT3 + 1 |
YY_END_OF_BUFFER + PICKUPDEF + 1 |
YY_END_OF_BUFFER + SC + 1 |
YY_END_OF_BUFFER + CARETISBOL + 1 |
YY_END_OF_BUFFER + NUM + 1 |
YY_END_OF_BUFFER + QUOTE + 1 |
YY_END_OF_BUFFER + FIRSTCCL + 1 |
YY_END_OF_BUFFER + CCL + 1 |
YY_END_OF_BUFFER + ACTION + 1 |
YY_END_OF_BUFFER + RECOVER + 1 |
YY_END_OF_BUFFER + BRACEERROR + 1 |
YY_END_OF_BUFFER + ACTION_STRING + 1 => 
    return End_Of_Input;
                when YY_END_OF_BUFFER =>
                    -- undo the effects of YY_DO_BEFORE_ACTION
                    yy_ch_buf(yy_cp) := yy_hold_char;

                    yytext_ptr := yy_bp;

                    case yy_get_next_buffer is
                        when EOB_ACT_END_OF_FILE =>
                            begin
                            if ( yywrap ) then
                                -- note: because we've taken care in
                                -- yy_get_next_buffer() to have set up yytext,
                                -- we can now set up yy_c_buf_p so that if some
                                -- total hoser (like aflex itself) wants
                                -- to call the scanner after we return the
                                -- End_Of_Input, it'll still work - another
                                -- End_Of_Input will get returned.

                                yy_c_buf_p := yytext_ptr;

                                yy_act := YY_STATE_EOF((yy_start - 1) / 2);

                                goto do_action;
                            else
                                --  start processing a new file
                                yy_init := true;
                                goto new_file;
                            end if;
                            end;
                        when EOB_ACT_RESTART_SCAN =>
                            yy_c_buf_p := yytext_ptr;
                            yy_hold_char := yy_ch_buf(yy_c_buf_p);
                        when EOB_ACT_LAST_MATCH =>
                            yy_c_buf_p := yy_n_chars;
                            yy_current_state := yy_get_previous_state;

                            yy_cp := yy_c_buf_p;
                            yy_bp := yytext_ptr;
                            goto next_action;
                        when others => null;
                        end case; -- case yy_get_next_buffer()
                when others =>
                    text_io.put( "action # " );
                    text_io.put( INTEGER'IMAGE(yy_act) );
                    text_io.new_line;
                    raise AFLEX_INTERNAL_ERROR;
            end case; -- case (yy_act)
        end loop; -- end of loop waiting for end of file
end YYLex;
--# line 368 "ascan.l"
begin
    if (call_yylex) then
    	toktype := YYLex;
    	call_yylex := false;
    	return toktype;
    end if;

    if ( eofseen ) then
	toktype := End_Of_Input;
    else
	toktype := YYLex;
    end if;
-- this tracing code allows easy tracing of aflex runs
if (trace) then
text_io.new_line(Standard_Error);
text_io.put(Standard_Error, "toktype = :" );
text_io.put(Standard_Error, Token'image(toktype));
text_io.put_line(Standard_Error, ":" );
end if;

    if ( toktype = End_Of_Input ) then
	eofseen := true;

	if ( sectnum = 1 ) then
	    misc.synerr(  "unexpected EOF" );
	    sectnum := 2;
	    toktype := SECTEND;
	else
	    if ( sectnum = 2 ) then
	    	sectnum := 3;
	    	toktype := SECTEND;
	    end if;
    	end if;
    end if;
    
    if ( trace ) then
	if ( beglin ) then
	    int_io.put( Standard_Error, num_rules + 1 );
	    text_io.put( Standard_Error, ASCII.HT );
	    beglin := false;
    	end if;

	case toktype is
	    when '<' | '>'|'^'|'$'|'"'|'['|']'|'{'|'}'|'|'|'('|
    	    	 ')'|'-'|'/'|'?'|'.'|'*'|'+'|',' =>
		text_io.put( Standard_Error, Token'image(toktype) );

	    when NEWLINE =>
		text_io.new_line(Standard_Error);
		if ( sectnum = 2 ) then
		    beglin := true;
    	    	end if;

	    when SCDECL =>
		text_io.put( Standard_Error, "%s" );

	    when XSCDECL =>
   		text_io.put( Standard_Error, "%x" );

	    when WHITESPACE =>
       		text_io.put( Standard_Error, " " );

	    when SECTEND =>
       		text_io.put_line( Standard_Error, "%%" );	   

		-- we set beglin to be true so we'll start
		-- writing out numbers as we echo rules.  aflexscan() has
		-- already assigned sectnum

		if ( sectnum = 2 ) then
		    beglin := true;
    	    	end if;

	    when NAME =>
		text_io.put( Standard_Error, ''' );
		text_io.put( Standard_Error, YYText);
		text_io.put( Standard_Error, ''' );

	    when CHAR =>
	    	if ( (yylval < CHARACTER'POS(' ')) or
		     (yylval = CHARACTER'POS(ASCII.DEL)) ) then
		    text_io.put( Standard_Error, '\' );
		    int_io.put( Standard_Error, yylval );
    		    text_io.put( Standard_Error, '\' );
		else
		    text_io.put( Standard_Error, Token'image(toktype) );
    	    	end if;

	    when NUMBER =>
    	    	int_io.put( Standard_Error, yylval );

	    when PREVCCL =>
		text_io.put( Standard_Error, '[' );
   	    	int_io.put( Standard_Error, yylval );
		text_io.put( Standard_Error, ']' );		

    	    when End_Of_Input =>
    	    	text_io.put( Standard_Error, "End Marker" );

	    when others =>
	    	text_io.put( Standard_Error, "Something weird:" );
		text_io.put_line( Standard_Error, Token'image(toktype));
    	end case;
    end if;
	    
    return toktype;

end get_token;
end scanner;

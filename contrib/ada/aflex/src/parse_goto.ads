package Parse_Goto is

    type Small_Integer is range -32_000 .. 32_000;

    type Goto_Entry is record
        Nonterm  : Small_Integer;
        Newstate : Small_Integer;
    end record;

  --pragma suppress(index_check);

    subtype Row is Integer range -1 .. Integer'Last;

    type Goto_Parse_Table is array (Row range <>) of Goto_Entry;

    Goto_Matrix : constant Goto_Parse_Table :=
       ((-1,-1)  -- Dummy Entry.
-- State  0
,(-3, 1),(-2, 2)
-- State  1
,(-4, 3)
-- State  2

-- State  3
,(-8, 10)
,(-5, 9)
-- State  4

-- State  5

-- State  6

-- State  7

-- State  8

-- State  9
,(-6, 12)
-- State  10

-- State  11

-- State  12
,(-7, 14)
-- State  13
,(-9, 15)

-- State  14
,(-18, 28),(-17, 26),(-16, 24),(-15, 25)
,(-12, 20),(-11, 18),(-10, 34)
-- State  15

-- State  16

-- State  17

-- State  18
,(-18, 28)
,(-17, 26),(-16, 24),(-15, 25),(-12, 37)

-- State  19
,(-18, 28),(-17, 26),(-16, 24),(-15, 25)
,(-12, 40)
-- State  20
,(-13, 42)
-- State  21

-- State  22

-- State  23
,(-14, 45)
-- State  24
,(-18, 28)
,(-17, 26),(-15, 48)
-- State  25
,(-18, 28),(-17, 49)

-- State  26

-- State  27

-- State  28

-- State  29

-- State  30
,(-19, 54)
-- State  31
,(-18, 28),(-17, 26),(-16, 24)
,(-15, 25),(-12, 55)
-- State  32

-- State  33
,(-20, 56)
-- State  34

-- State  35

-- State  36

-- State  37
,(-13, 60)

-- State  38
,(-18, 28),(-17, 26),(-16, 24),(-15, 25)
,(-12, 61)
-- State  39

-- State  40
,(-13, 62)
-- State  41

-- State  42

-- State  43
,(-18, 28),(-17, 26)
,(-15, 63)
-- State  44

-- State  45

-- State  46

-- State  47

-- State  48
,(-18, 28),(-17, 49)
-- State  49

-- State  50

-- State  51

-- State  52

-- State  53

-- State  54

-- State  55

-- State  56

-- State  57
,(-20, 72)

-- State  58

-- State  59

-- State  60

-- State  61
,(-13, 73)
-- State  62

-- State  63
,(-18, 28),(-17, 49)
-- State  64

-- State  65

-- State  66

-- State  67

-- State  68

-- State  69

-- State  70

-- State  71

-- State  72

-- State  73

-- State  74

-- State  75

-- State  76

-- State  77

-- State  78

-- State  79

-- State  80

-- State  81

-- State  82

);
--  The offset vector
GOTO_OFFSET : array (0.. 82) of Integer :=
( 0,
 2, 3, 3, 5, 5, 5, 5, 5, 5, 6,
 6, 6, 7, 8, 15, 15, 15, 15, 20, 25,
 26, 26, 26, 27, 30, 32, 32, 32, 32, 32,
 33, 38, 38, 39, 39, 39, 39, 40, 45, 45,
 46, 46, 46, 49, 49, 49, 49, 49, 51, 51,
 51, 51, 51, 51, 51, 51, 51, 52, 52, 52,
 52, 53, 53, 55, 55, 55, 55, 55, 55, 55,
 55, 55, 55, 55, 55, 55, 55, 55, 55, 55,
 55, 55);

subtype Rule        is Natural;
subtype Nonterminal is Integer;

   Rule_Length : array (Rule range  0 ..  52) of Natural := ( 2,
 5, 0, 5, 0, 2, 1, 1, 1,
 3, 1, 1, 4, 0, 0, 4, 3,
 3, 2, 2, 1, 1, 3, 3, 1,
 1, 1, 0, 3, 2, 1, 2, 2,
 1, 2, 2, 2, 6, 5, 4, 1,
 1, 1, 3, 3, 1, 3, 4, 4,
 2, 0, 2, 0);
   Get_LHS_Rule: array (Rule range  0 ..  52) of Nonterminal := (-1,
-2,-3,-4,-4,-4,-5,-8,-8,
-9,-9,-9,-6,-6,-7,-10,-10,
-10,-10,-10,-10,-10,-11,-14,-14,
-14,-13,-13,-12,-12,-12,-16,-15,
-15,-17,-17,-17,-17,-17,-17,-17,
-17,-17,-17,-17,-17,-18,-18,-20,
-20,-20,-19,-19);
end Parse_Goto;

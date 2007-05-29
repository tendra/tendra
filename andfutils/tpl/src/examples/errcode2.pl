/*
    		 Crown Copyright (c) 1997
    
    This TenDRA(r) Computer Program is subject to Copyright
    owned by the United Kingdom Secretary of State for Defence
    acting through the Defence Evaluation and Research Agency
    (DERA).  It is made available to Recipients with a
    royalty-free licence for its use, reproduction, transfer
    to other parties and amendment for any purpose not excluding
    product development provided that any such use et cetera
    shall be deemed to be acceptance of the following conditions:-
    
        (1) Its Recipients shall ensure that this Notice is
        reproduced upon any copies or amended versions of it;
    
        (2) Any amended version of it shall be clearly marked to
        show both the nature of and the organisation responsible
        for the relevant amendment or amendments;
    
        (3) Its onward transfer from a recipient to another
        party shall be deemed to be that party's acceptance of
        these conditions;
    
        (4) DERA gives no warranty or assurance as to its
        quality or suitability for any purpose and DERA accepts
        no liability whatsoever in relation to any use to which
        it may be put.
*/


Iddec printf:proc;
Iddec main:proc;


Tokdec TRY :[EXP, NAT, EXP]EXP;
Tokdec ~Set_signal_handler: []EXP;


String passed = "passed\n";
String failed = "failed\n";
String s = "\n";

String s8  = "\n\nInt8:\n\n";
String u8  = "\n\nUInt8:\n\n";
String s16 = "\n\nInt16:\n\n";
String u16 = "\n\nUInt16:\n\n";
String s32 = "\n\nInt32:\n\n";
String u32 = "\n\nUInt32:\n\n";


Tokdef Int8  = [] VARIETY var_width (true,8);
Tokdef Int16 = [] VARIETY var_width (true,16);
Tokdef Int32 = [] VARIETY var_width (true,32);

Tokdef UInt8  = [] VARIETY var_width (false,8);
Tokdef UInt16 = [] VARIETY var_width (false,16);
Tokdef UInt32 = [] VARIETY var_width (false,32);


Tokdef Check = [e:EXP, p:EXP, f:EXP] EXP
{
    TRY[{e; printf [top] (f)},
	error_val(overflow),
	printf [top] (p)];
};



Proc main = top()
    Let p = make_null_ptr(alignment(Int))
    Let msize = env_size(main)
    Let tosize = msize .+. 
		(offset_pad(alignment(Int),shape_offset(Int)) .* 100(Int))

    {
/* Check Int8 */
	~Set_signal_handler;
	printf [top] (s8);

	Check [plus([overflow],  127(Int8),  1(Int8)), passed, failed];
	Check [plus([overflow],  127(Int8), -1(Int8)), failed, passed];
	Check [plus([overflow], -128(Int8),  1(Int8)), failed, passed];
	Check [plus([overflow], -128(Int8), -1(Int8)), passed, failed];

	Check [minus([overflow],  127(Int8), -1(Int8)), passed, failed];
	Check [minus([overflow],  127(Int8),  1(Int8)), failed, passed];
	Check [minus([overflow], -128(Int8), -1(Int8)), failed, passed];
	Check [minus([overflow], -128(Int8),  1(Int8)), passed, failed];

	Check [mult([overflow], -128(Int8), -1(Int8)), passed, failed];
	Check [mult([overflow], -127(Int8), -1(Int8)), failed, passed];
	Check [mult([overflow],   64(Int8),  2(Int8)), passed, failed];
	Check [mult([overflow],   63(Int8),  2(Int8)), failed, passed];

	Check [div2(impossible, [overflow], -128(Int8), -1(Int8)), passed, failed];
	Check [div2(impossible, [overflow], -127(Int8), -1(Int8)), failed, passed];

	Check [abs([overflow], -128(Int8)), passed, failed];
	Check [abs([overflow], -127(Int8)), failed, passed];

	Check [negate([overflow], -128(Int8)), passed, failed];
	Check [negate([overflow], -127(Int8)), failed, passed];


/* Check UInt8 */

	printf [top] (u8);

	Check [plus([overflow], 255(UInt8), 1(UInt8)), passed, failed];
	Check [plus([overflow], 0(UInt8),   1(UInt8)), failed, passed];
	Check [minus([overflow], 0(UInt8),   1(UInt8)), passed, failed];
	Check [minus([overflow], 255(UInt8), 1(UInt8)), failed, passed];


/* Check Int16 */

	printf [top] (s16);

	Check [plus([overflow],  32767(Int16),  1(Int16)), passed, failed];
	Check [plus([overflow],  32767(Int16), -1(Int16)), failed, passed];
	Check [plus([overflow], -32768(Int16),  1(Int16)), failed, passed];
	Check [plus([overflow], -32768(Int16), -1(Int16)), passed, failed];
	Check [minus([overflow],  32767(Int16), -1(Int16)), passed, failed];
	Check [minus([overflow],  32767(Int16),  1(Int16)), failed, passed];
	Check [minus([overflow], -32768(Int16), -1(Int16)), failed, passed];
	Check [minus([overflow], -32768(Int16),  1(Int16)), passed, failed];

	Check [mult([overflow], -32768(Int16), -1(Int16)), passed, failed];
	Check [mult([overflow], -32767(Int16), -1(Int16)), failed, passed];
	Check [mult([overflow],  16384(Int16),  2(Int16)), passed, failed];
	Check [mult([overflow],  16383(Int16),  2(Int16)), failed, passed];

	Check [div2(impossible, [overflow], -32768(Int16), -1(Int16)), passed, failed];
	Check [div2(impossible, [overflow], -32767(Int16), -1(Int16)), failed, passed];

	Check [abs([overflow], -32768(Int16)), passed, failed];
	Check [abs([overflow], -32767(Int16)), failed, passed];

	Check [negate([overflow], -32768(Int16)), passed, failed];
	Check [negate([overflow], -32767(Int16)), failed, passed];


/* Check UInt16 */

	printf [top] (u16);

	Check [plus([overflow], 65535(UInt16), 1(UInt16)), passed, failed];
	Check [plus([overflow], 0(UInt16),   1(UInt16)), failed, passed];
	Check [minus([overflow], 0(UInt16),   1(UInt16)), passed, failed];
	Check [minus([overflow], 65535(UInt16), 1(UInt16)), failed, passed];


/* Check Int32 */

	printf [top] (s32);

	Check [plus([overflow],  2147483647(Int32),  1(Int32)), passed, failed];
	Check [plus([overflow],  2147483647(Int32), -1(Int32)), failed, passed];
	Check [plus([overflow], -2147483648(Int32),  1(Int32)), failed, passed];
	Check [plus([overflow], -2147483648(Int32), -1(Int32)), passed, failed];

	Check [minus([overflow],  2147483647(Int32), -1(Int32)), passed, failed];
	Check [minus([overflow],  2147483647(Int32),  1(Int32)), failed, passed];
	Check [minus([overflow], -2147483648(Int32), -1(Int32)), failed, passed];
	Check [minus([overflow], -2147483648(Int32),  1(Int32)), passed, failed];

	Check [mult([overflow], -2147483648(Int32), -1(Int32)), passed, failed];
	Check [mult([overflow], -2147483647(Int32), -1(Int32)), failed, passed];
	Check [mult([overflow],  1073741824(Int32),  2(Int32)), passed, failed];
	Check [mult([overflow],  1073741823(Int32),  2(Int32)), failed, passed];

	Check [div2(impossible, [overflow], -2147483648(Int32), -1(Int32)), passed, failed];
	Check [div2(impossible, [overflow], -2147483647(Int32), -1(Int32)), failed, passed];

	Check [abs([overflow], -2147483648(Int32)), passed, failed];
	Check [abs([overflow], -2147483647(Int32)), failed, passed];

	Check [negate([overflow], -2147483648(Int32)), passed, failed];
	Check [negate([overflow], -2147483647(Int32)), failed, passed];


/* Check UInt32 */

	printf [top] (u32);

	Check [plus([overflow], 4294967295(UInt32), 1(UInt32)), passed, failed];
	Check [plus([overflow], 0(UInt32),   1(UInt32)), failed, passed];
	Check [minus([overflow], 0(UInt32),   1(UInt32)), passed, failed];
	Check [minus([overflow], 4294967295(UInt32), 1(UInt32)), failed, passed];


	return(make_top)  
    };


Keep (main)

/* $Id$ */

/*
 * Copyright 2002-2011, The TenDRA Project.
 * Copyright 1997, United Kingdom Secretary of State for Defence.
 *
 * See doc/copyright/ for the full copyright terms.
 */


#ifndef CHAR_INCLUDED
#define CHAR_INCLUDED


/*
    CODESET MAPPINGS

    These routines give the mappings of the native codeset to and from
    ASCII and checks on unicode characters.
*/

extern void init_ascii(void);
extern void map_ascii(unsigned char *);
extern unsigned long to_ascii(unsigned long, int *);
extern unsigned long from_ascii(unsigned long, int *);
extern int unicode_alpha(unsigned long);
extern int is_ascii;


/*
    DOES HOST MACHINE HAVE EXTENDED CHARACTERS?

    Most of the parser assumes that all characters lie in the range [0, 255].
    The macro FS_EXTENDED_CHAR is true if characters can be greater than 255.
    Note that limits.h needs to be included for UCHAR_MAX.
*/

#ifdef UCHAR_MAX

#define NO_CHAR			256
#define IS_EXTENDED(C)		((unsigned)(C) >= NO_CHAR)

#ifndef FS_EXTENDED_CHAR
#define FS_EXTENDED_CHAR	(UCHAR_MAX >= NO_CHAR)
#endif

#endif


/*
    CHARACTER SET

    These macros represent the legal characters.  All character literals
    within the program are referenced using these macros.
*/

#define char_space		' '
#define char_tab		'\t'
#define char_newline		'\n'
#define char_backspace		'\b'
#define char_form_feed		'\f'
#define char_return		'\r'
#define char_vert_tab		'\v'
#define char_sub		'\032'
#define char_alert		'\a'
#define char_ampersand		'&'
#define char_asterix		'*'
#define char_backslash		'\\'
#define char_bar		'|'
#define char_circum		'^'
#define char_close_brace	'}'
#define char_close_round	')'
#define char_close_square	']'
#define char_colon		':'
#define char_comma		','
#define char_dot		'.'
#define char_equal		'='
#define char_exclaim		'!'
#define char_greater		'>'
#define char_hash		'#'
#define char_less		'<'
#define char_minus		'-'
#define char_open_brace		'{'
#define char_open_round		'('
#define char_open_square	'['
#define char_percent		'%'
#define char_plus		'+'
#define char_question		'?'
#define char_quote		'"'
#define char_semicolon		';'
#define char_single_quote	'\''
#define char_slash		'/'
#define char_tilde		'~'

#define char_zero		'0'
#define char_one		'1'
#define char_two		'2'
#define char_three		'3'
#define char_four		'4'
#define char_five		'5'
#define char_six		'6'
#define char_seven		'7'
#define char_eight		'8'
#define char_nine		'9'

#define char_A			'A'
#define char_B			'B'
#define char_C			'C'
#define char_D			'D'
#define char_E			'E'
#define char_F			'F'
#define char_G			'G'
#define char_H			'H'
#define char_I			'I'
#define char_J			'J'
#define char_K			'K'
#define char_L			'L'
#define char_M			'M'
#define char_N			'N'
#define char_O			'O'
#define char_P			'P'
#define char_Q			'Q'
#define char_R			'R'
#define char_S			'S'
#define char_T			'T'
#define char_U			'U'
#define char_V			'V'
#define char_W			'W'
#define char_X			'X'
#define char_Y			'Y'
#define char_Z			'Z'

#define char_a			'a'
#define char_b			'b'
#define char_c			'c'
#define char_d			'd'
#define char_e			'e'
#define char_f			'f'
#define char_g			'g'
#define char_h			'h'
#define char_i			'i'
#define char_j			'j'
#define char_k			'k'
#define char_l			'l'
#define char_m			'm'
#define char_n			'n'
#define char_o			'o'
#define char_p			'p'
#define char_q			'q'
#define char_r			'r'
#define char_s			's'
#define char_t			't'
#define char_u			'u'
#define char_v			'v'
#define char_w			'w'
#define char_x			'x'
#define char_y			'y'
#define char_z			'z'

#define char_at			'@'
#define char_back_quote		'`'
#define char_dollar		'$'
#define char_underscore		'_'

#define char_illegal		0x00


/*
    END OF FILE MARKERS

    The value char_eof is used to indicate the end of file.  char_end equals
    ( char_eof & 0xff ) and is used to mark possible end of file positions
    in the input buffer (see file.c).
*/

#define char_eof	-1
#define char_end	0xff


/*
    SELECTED ASCII CODES

    These macros give selected ASCII character codes.
*/

#define ascii_T	0x54
#define ascii_D	0x44
#define ascii_F	0x46
#define ascii_C	0x43
#define ascii_K	0x4b


#endif /* CHAR_INCLUDED */


/*
    CHARACTER LOOK-UP TABLES

    This table gives the look-up values for the character set in the various
    mapping tables.  The entries give the character type, the value as a
    digit, and the escape character value.  Note that the table is listed
    in ASCII order.
*/

#ifdef CHAR_DATA

CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 0 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 1 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 2 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 3 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 4 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 5 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 6 */

CHAR_DATA(ILLEG, NONE, NONE, char_alert)
CHAR_DATA(ILLEG, NONE, NONE, char_backspace)
CHAR_DATA(SPACE, NONE, NONE, char_tab)
CHAR_DATA(NLINE, NONE, NONE, char_newline)
CHAR_DATA(SPACE, NONE, NONE, char_vert_tab)
CHAR_DATA(SPACE, NONE, NONE, char_form_feed)
CHAR_DATA(ILLEG, NONE, NONE, char_return)

CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 14 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 15 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 16 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 17 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 18 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 19 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 20 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 21 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 22 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 23 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 24 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 25 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 26 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 27 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 28 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 29 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 30 */
CHAR_DATA (ILLEG, NONE, NONE, NONE)		/* 31 */

CHAR_DATA(SPACE, NONE, NONE, char_space)
CHAR_DATA(SYMBL, NONE, NONE, char_exclaim)
CHAR_DATA(SYMBL, NONE, char_quote, char_quote)
CHAR_DATA(SYMBL, NONE, NONE, char_hash)
CHAR_DATA(ILLEG, NONE, NONE, char_dollar)
CHAR_DATA(SYMBL, NONE, NONE, char_percent)
CHAR_DATA(SYMBL, NONE, NONE, char_ampersand)
CHAR_DATA(SYMBL, NONE, char_single_quote, char_single_quote)
CHAR_DATA(SYMBL, NONE, NONE, char_open_round)
CHAR_DATA(SYMBL, NONE, NONE, char_close_round)
CHAR_DATA(SYMBL, NONE, NONE, char_asterix)
CHAR_DATA(SYMBL, NONE, NONE, char_plus)
CHAR_DATA(SYMBL, NONE, NONE, char_comma)
CHAR_DATA(SYMBL, NONE, NONE, char_minus)
CHAR_DATA(POINT, NONE, NONE, char_dot)
CHAR_DATA(SYMBL, NONE, NONE, char_slash)

CHAR_DATA(DIGIT, 0x00, OCTE, char_zero)
CHAR_DATA(DIGIT, 0x01, OCTE, char_one)
CHAR_DATA(DIGIT, 0x02, OCTE, char_two)
CHAR_DATA(DIGIT, 0x03, OCTE, char_three)
CHAR_DATA(DIGIT, 0x04, OCTE, char_four)
CHAR_DATA(DIGIT, 0x05, OCTE, char_five)
CHAR_DATA(DIGIT, 0x06, OCTE, char_six)
CHAR_DATA(DIGIT, 0x07, OCTE, char_seven)
CHAR_DATA(DIGIT, 0x08, NONE, char_eight)
CHAR_DATA(DIGIT, 0x09, NONE, char_nine)

CHAR_DATA(SYMBL, NONE, NONE, char_colon)
CHAR_DATA(SYMBL, NONE, NONE, char_semicolon)
CHAR_DATA(SYMBL, NONE, NONE, char_less)
CHAR_DATA(SYMBL, NONE, NONE, char_equal)
CHAR_DATA(SYMBL, NONE, NONE, char_greater)
CHAR_DATA(SYMBL, NONE, char_question, char_question)

CHAR_DATA(ILLEG, NONE, NONE, char_at)
CHAR_DATA(ALPHA, 0x0a, NONE, char_A)
CHAR_DATA(ALPHA, 0x0b, NONE, char_B)
CHAR_DATA(ALPHA, 0x0c, NONE, char_C)
CHAR_DATA(ALPHA, 0x0d, NONE, char_D)
CHAR_DATA(ALPHA, 0x0e, NONE, char_E)
CHAR_DATA(ALPHA, 0x0f, NONE, char_F)
CHAR_DATA(ALPHA, 0x10, NONE, char_G)
CHAR_DATA(ALPHA, 0x11, NONE, char_H)
CHAR_DATA(ALPHA, 0x12, NONE, char_I)
CHAR_DATA(ALPHA, 0x13, NONE, char_J)
CHAR_DATA(ALPHA, 0x14, NONE, char_K)
CHAR_DATA(ALPHA, 0x15, NONE, char_L)
CHAR_DATA(ALPHA, 0x16, NONE, char_M)
CHAR_DATA(ALPHA, 0x17, NONE, char_N)
CHAR_DATA(ALPHA, 0x18, NONE, char_O)
CHAR_DATA(ALPHA, 0x19, NONE, char_P)
CHAR_DATA(ALPHA, 0x1a, NONE, char_Q)
CHAR_DATA(ALPHA, 0x1b, NONE, char_R)
CHAR_DATA(ALPHA, 0x1c, NONE, char_S)
CHAR_DATA(ALPHA, 0x1d, NONE, char_T)
CHAR_DATA(ALPHA, 0x1e, UNI8, char_U)
CHAR_DATA(ALPHA, 0x1f, NONE, char_V)
CHAR_DATA(ALPHA, 0x20, NONE, char_W)
CHAR_DATA(ALPHA, 0x21, NONE, char_X)
CHAR_DATA(ALPHA, 0x22, NONE, char_Y)
CHAR_DATA(ALPHA, 0x23, NONE, char_Z)
CHAR_DATA(SYMBL, NONE, NONE, char_open_square)
CHAR_DATA(SYMBL, NONE, char_backslash, char_backslash)
CHAR_DATA(SYMBL, NONE, NONE, char_close_square)
CHAR_DATA(SYMBL, NONE, NONE, char_circum)
CHAR_DATA(ALPHA, NONE, NONE, char_underscore)

CHAR_DATA(ILLEG, NONE, NONE, char_back_quote)
CHAR_DATA(ALPHA, 0x0a, char_alert, char_a)
CHAR_DATA(ALPHA, 0x0b, char_backspace, char_b)
CHAR_DATA(ALPHA, 0x0c, NONE, char_c)
CHAR_DATA(ALPHA, 0x0d, NONE, char_d)
CHAR_DATA(ALPHA, 0x0e, NONE, char_e)
CHAR_DATA(ALPHA, 0x0f, char_form_feed, char_f)
CHAR_DATA(ALPHA, 0x10, NONE, char_g)
CHAR_DATA(ALPHA, 0x11, NONE, char_h)
CHAR_DATA(ALPHA, 0x12, NONE, char_i)
CHAR_DATA(ALPHA, 0x13, NONE, char_j)
CHAR_DATA(ALPHA, 0x14, NONE, char_k)
CHAR_DATA(ALPHA, 0x15, NONE, char_l)
CHAR_DATA(ALPHA, 0x16, NONE, char_m)
CHAR_DATA(ALPHA, 0x17, char_newline, char_n)
CHAR_DATA(ALPHA, 0x18, NONE, char_o)
CHAR_DATA(ALPHA, 0x19, NONE, char_p)
CHAR_DATA(ALPHA, 0x1a, NONE, char_q)
CHAR_DATA(ALPHA, 0x1b, char_return, char_r)
CHAR_DATA(ALPHA, 0x1c, NONE, char_s)
CHAR_DATA(ALPHA, 0x1d, char_tab, char_t)
CHAR_DATA(ALPHA, 0x1e, UNI4, char_u)
CHAR_DATA(ALPHA, 0x1f, char_vert_tab, char_v)
CHAR_DATA(ALPHA, 0x20, NONE, char_w)
CHAR_DATA(ALPHA, 0x21, HEXE, char_x)
CHAR_DATA(ALPHA, 0x22, NONE, char_y)
CHAR_DATA(ALPHA, 0x23, NONE, char_z)
CHAR_DATA(SYMBL, NONE, NONE, char_open_brace)
CHAR_DATA(SYMBL, NONE, NONE, char_bar)
CHAR_DATA(SYMBL, NONE, NONE, char_close_brace)
CHAR_DATA(SYMBL, NONE, NONE, char_tilde)

CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 127 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 128 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 129 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 130 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 131 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 132 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 133 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 134 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 135 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 136 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 137 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 138 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 139 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 140 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 141 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 142 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 143 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 144 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 145 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 146 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 147 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 148 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 149 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 150 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 151 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 152 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 153 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 154 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 155 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 156 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 157 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 158 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 159 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 160 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 161 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 162 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 163 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 164 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 165 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 166 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 167 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 168 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 169 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 170 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 171 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 172 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 173 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 174 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 175 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 176 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 177 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 178 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 179 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 180 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 181 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 182 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 183 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 184 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 185 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 186 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 187 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 188 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 189 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 190 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 191 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 192 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 193 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 194 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 195 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 196 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 197 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 198 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 199 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 200 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 201 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 202 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 203 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 204 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 205 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 206 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 207 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 208 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 209 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 210 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 211 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 212 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 213 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 214 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 215 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 216 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 217 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 218 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 219 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 220 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 221 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 222 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 223 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 224 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 225 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 226 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 227 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 228 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 229 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 230 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 231 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 232 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 233 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 234 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 235 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 236 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 237 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 238 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 239 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 240 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 241 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 242 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 243 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 244 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 245 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 246 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 247 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 248 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 249 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 250 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 251 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 252 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 253 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 254 */
CHAR_DATA(ILLEG, NONE, NONE, NONE)		/* 255 */

#endif /* CHAR_DATA */

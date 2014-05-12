# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


# CAE, X/Open Curses, Issue 4

+USE "c/c89", "stdio.h.ts" ;	# FILE
+USE "c/c89", "stdarg.h.ts", "va_args" (!?) ;

# at least including unsigned short values
+TYPE (int) attr_t ;

+TYPE (int) bool ;

# at least including unsigned char values
+SUBSET "chtype" := { +TYPE (int) chtype ; } ;

+TYPE SCREEN ;
+IMPLEMENT "c/c89", "stddef.h.ts", "wchar_t" ;
+TYPE (int) cchar_t ;
+TYPE WINDOW ;

+IMPLEMENT "c/c90", "wchar.h.ts", "wint" ;	# wint_t and WEOF

+EXP (extern) int COLOR_PAIRS ;
+EXP (extern) int COLORS ;
+EXP (extern) int COLS ;
+EXP (extern) WINDOW *curscr ;
+EXP (extern) int LINES ;
+EXP (extern) WINDOW *stdscr ;

+IMPLEMENT "c/c89", "stdio.h.ts", "eof" ;
+CONST int ERR ;
+CONST bool FALSE ;
+CONST int OK ;
+CONST bool TRUE ;

+CONST attr_t WA_ALTCHARSET, WA_BLINK, WA_BOLD, WA_DIM, WA_HORIZONTAL;
+CONST attr_t WA_INVIS, WA_LEFT, WA_LOW, WA_PROTECT, WA_REVERSE;
+CONST attr_t WA_RIGHT, WA_STANDOUT, WA_TOP, WA_UNDERLINE, WA_VERTICAL;

+CONST chtype A_ALTCHARSET, A_BLINK, A_BOLD, A_DIM, A_INVIS ;
+CONST chtype A_PROTECT, A_REVERSE, A_STANDOUT, A_UNDERLINE ;

+CONST chtype A_ATTRIBUTES, A_CHARTEXT, A_COLOR ;

+EXP char ACS_ULCORNER, ACS_LLCORNER, ACS_URCORNER, ACS_LRCORNER ;
+EXP char ACS_RTEE, ACS_LTEE, ACS_BTEE, ACS_TTEE ;
+EXP char ACS_HLINE, ACS_VLINE, ACS_PLUS ;
+EXP char ACS_S1, ACS_S9, ACS_DIAMOND, ACS_CKBOARD ;
+EXP char ACS_DEGREE, ACS_PLMINUS, ACS_BULLET ;
+EXP char ACS_LARROW, ACS_RARROW, ACS_DARROW, ACS_UARROW ;
+EXP char ACS_BOARD, ACS_LANTERN, ACS_BLOCK ;

+EXP cchar_t WACS_ULCORNER, WACS_LLCORNER, WACS_URCORNER, WACS_LRCORNER ;
+EXP cchar_t WACS_RTEE, WACS_LTEE, WACS_BTEE, WACS_TTEE ;
+EXP cchar_t WACS_HLINE, WACS_VLINE, WACS_PLUS ;
+EXP cchar_t WACS_S1, WACS_S9, WACS_DIAMOND, WACS_CKBOARD ;
+EXP cchar_t WACS_DEGREE, WACS_PLMINUS, WACS_BULLET ;
+EXP cchar_t WACS_LARROW, WACS_RARROW, WACS_DARROW, WACS_UARROW ;
+EXP cchar_t WACS_BOARD, WACS_LANTERN, WACS_BLOCK ;

+MACRO int COLOR_PAIR ( int ) ;
+MACRO int PAIR_NUMBER ( int ) ;
+CONST int COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED ;
+CONST int COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE ;

+MACRO void getbegyx ( WINDOW *, lvalue int, lvalue int ) ;
+MACRO void getmaxyx ( WINDOW *, lvalue int, lvalue int ) ;
+MACRO void getparyx ( WINDOW *, lvalue int, lvalue int ) ;
+MACRO void getyx ( WINDOW *, lvalue int, lvalue int ) ;

+CONST int KEY_CODE_YES ;
+CONST int KEY_BREAK, KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_HOME ;
+CONST int KEY_BACKSPACE, KEY_F0 ;
+MACRO int KEY_F ( int ) ;
+CONST int KEY_DL, KEY_IL, KEY_DC, KEY_IC, KEY_EIC, KEY_CLEAR, KEY_EOS ;
+CONST int KEY_EOL, KEY_SF, KEY_SR, KEY_NPAGE, KEY_PPAGE, KEY_STAB, KEY_CTAB ;
+CONST int KEY_CATAB, KEY_ENTER, KEY_SRESET, KEY_RESET, KEY_PRINT, KEY_LL ;
+CONST int KEY_A1, KEY_A3, KEY_B2, KEY_C1, KEY_C3 ;

+CONST int KEY_BTAB, KEY_BEG ;
+CONST int KEY_CANCEL, KEY_CLOSE, KEY_COMMAND, KEY_COPY, KEY_CREATE, KEY_END ;
+CONST int KEY_EXIT, KEY_FIND, KEY_HELP, KEY_MARK, KEY_MESSAGE, KEY_MOVE ;
+CONST int KEY_NEXT, KEY_OPEN, KEY_OPTIONS, KEY_PREVIOUS, KEY_REDO ;
+CONST int KEY_REFERENCE, KEY_REFRESH, KEY_REPLACE, KEY_RESTART, KEY_RESUME ;
+CONST int KEY_SAVE, KEY_SBEG, KEY_SCANCEL, KEY_SCOMMAND, KEY_SCOPY ;
+CONST int KEY_SCREATE, KEY_SDC, KEY_SDL, KEY_SELECT, KEY_SEND, KEY_SEOL ;
+CONST int KEY_SEXIT, KEY_SFIND, KEY_SHELP, KEY_SHOME, KEY_SIC, KEY_SLEFT ;
+CONST int KEY_SMESSAGE, KEY_SMOVE, KEY_SNEXT, KEY_SOPTIONS, KEY_SPREVIOUS ;
+CONST int KEY_SPRINT, KEY_SREDO, KEY_SREPLACE, KEY_SRIGHT, KEY_SRSUME ;
+CONST int KEY_SSAVE, KEY_SSUSPEND, KEY_SUNDO, KEY_SUSPEND, KEY_UNDO ;


+IMPLEMENT "cae/xcurses4v2", "term.h.ts", "curs" ;	# FUNC both in term.h and curses.h

+FUNC int addch ( const chtype ) ;
+FUNC int addchstr ( chtype * const ) ;
+FUNC int addchnstr ( chtype * const, int ) ;
+FUNC int addnstr ( char * const, int ) ;
+FUNC int addstr ( char * const ) ;
+FUNC int addnwstr ( wchar_t * const, int ) ;
+FUNC int addwstr ( wchar_t * const ) ;
+FUNC int add_wch ( cchar_t * const ) ;
+FUNC int add_wchnstr ( cchar_t * const, int ) ;
+FUNC int add_wchstr ( cchar_t * const ) ;
+FUNC int attroff ( int ) ;
+FUNC int attron ( int ) ;
+FUNC int attrset ( int ) ;
+FUNC attr_t attr_get ( void ) ;
+FUNC int attr_off ( attr_t ) ;
+FUNC int attr_on ( attr_t ) ;
+FUNC int attr_set ( attr_t ) ;

+FUNC int baudrate ( void ) ;
+FUNC int beep ( void ) ;
+FUNC int bkgd ( chtype ) ;
+FUNC void bkgdset ( chtype ) ;
+FUNC void bkgrndset ( cchar_t * const ) ;
+FUNC int bkgrnd ( cchar_t * const ) ;
+FUNC int border ( chtype, chtype, chtype, chtype, chtype, chtype,
    chtype, chtype ) ;
+FUNC int border_set ( cchar_t * const, cchar_t * const, cchar_t * const,
    cchar_t * const, cchar_t * const, cchar_t * const, cchar_t * const,
    cchar_t * const ) ;
+FUNC int box ( WINDOW *, chtype, chtype ) ;
+FUNC int box_set ( WINDOW *, cchar_t * const, cchar_t * const ) ;

+FUNC bool can_change_color ( void ) ;
+FUNC int cbreak ( void ) ;
+FUNC int chgat ( int, attr_t, short, void * const ) ;
+FUNC int clear ( void ) ;
+FUNC int clearok ( WINDOW *, bool ) ;
+FUNC int clrtobot ( void ) ;
+FUNC int clrtoeol ( void ) ;
+FUNC int color_content ( short, short *, short *, short * ) ;
+FUNC int copywin ( WINDOW * const, WINDOW *, int, int, int, int, int,
    int, int ) ;
+FUNC int curs_set ( int ) ;

+FUNC int def_prog_mode ( void ) ;
+FUNC int def_shell_mode ( void ) ;
+FUNC int delay_output ( int ) ;
+FUNC int delch ( void ) ;
+FUNC void delscreen ( SCREEN * ) ;
+FUNC int delwin ( WINDOW * ) ;
+FUNC int deleteln ( void ) ;
+FUNC WINDOW *derwin ( WINDOW *, int, int, int, int ) ;
+FUNC int doupdate ( void ) ;
+FUNC WINDOW *dupwin ( WINDOW * ) ;

+FUNC int echo ( void ) ;
+FUNC int echochar ( const chtype ) ;
+FUNC int echo_wchar ( cchar_t * const ) ;
+FUNC int endwin ( void ) ;
+FUNC int erase ( void ) ;
+FUNC char erasechar ( void ) ;
+FUNC int erasewchar ( wchar_t * ) ;

+FUNC void filter ( void ) ;
+FUNC int flash ( void ) ;
+FUNC int flushinp ( void ) ;

+FUNC chtype getbkgd ( WINDOW * ) ;
+FUNC int getbkgrnd ( cchar_t * ) ;
+FUNC int getcchar ( cchar_t * const, wchar_t *, attr_t *, short *, void * ) ;
+FUNC int getch ( void ) ;
+FUNC int getnstr ( char *, int ) ;
+FUNC int getn_wstr ( wint_t *, int ) ;
+FUNC int getstr ( char * ) ;
+FUNC int get_wch ( wint_t * ) ;
+FUNC WINDOW *getwin ( FILE * ) ;
+FUNC int get_wstr ( wint_t * ) ;

+FUNC int halfdelay ( int ) ;
+FUNC bool has_colors ( void ) ;
+FUNC bool has_ic ( void ) ;
+FUNC bool has_il ( void ) ;
+FUNC int hline ( chtype, int ) ;
+FUNC int hline_set ( cchar_t * const, int ) ;

+FUNC void idcok ( WINDOW *, bool ) ;
+FUNC int idlok ( WINDOW *, bool ) ;
+FUNC void immedok ( WINDOW *, bool ) ;
+FUNC chtype inch ( void ) ;
+FUNC int inchnstr ( chtype *, int ) ;
+FUNC int inchstr ( chtype * ) ;
+FUNC WINDOW *initscr ( void ) ;
+FUNC int init_color ( short, short, short, short ) ;
+FUNC int init_pair ( short, short, short ) ;
+FUNC int innstr ( char *, int ) ;
+FUNC int innwstr ( wchar_t *, int ) ;
+FUNC int insch ( chtype ) ;
+FUNC int insdelln ( int ) ;
+FUNC int insertln ( void ) ;
+FUNC int insnstr ( char * const, int ) ;
+FUNC int insstr ( char * const ) ;
+FUNC int instr ( char * ) ;
+FUNC int ins_nwstr ( wchar_t * const, int ) ;
+FUNC int ins_wch ( cchar_t * const ) ;
+FUNC int ins_wstr ( wchar_t * const ) ;
+FUNC int intrflush ( WINDOW *, bool ) ;
+FUNC int in_wch ( cchar_t * ) ;
+FUNC int in_wchstr ( cchar_t * ) ;
+FUNC int in_wchnstr ( cchar_t *, int ) ;
+FUNC int inwstr ( wchar_t * ) ;
+FUNC bool isendwin ( void ) ;
+FUNC bool is_linetouched ( WINDOW *, int ) ;
+FUNC bool is_wintouched ( WINDOW * ) ;

+FUNC char *keyname ( int ) ;
+FUNC char *key_name ( wchar_t ) ;
+FUNC int keypad ( WINDOW *, bool ) ;
+FUNC char killchar ( void ) ;
+FUNC int killwchar ( wchar_t * ) ;

+FUNC int leaveok ( WINDOW *, bool ) ;
+FUNC char *longname ( void ) ;

+FUNC int meta ( WINDOW *, bool ) ;
+FUNC int move ( int, int ) ;
+FUNC int mvaddch ( int, int, const chtype ) ;
+FUNC int mvaddchnstr ( int, int, chtype * const, int ) ;
+FUNC int mvaddchstr ( int, int, chtype * const ) ;
+FUNC int mvaddnstr ( int, int, char * const, int ) ;
+FUNC int mvaddnwstr ( int, int, wchar_t * const, int ) ;
+FUNC int mvaddstr ( int, int, char * const ) ;
+FUNC int mvaddwstr ( int, int, wchar_t * const ) ;
+FUNC int mvadd_wch ( int, int, cchar_t * const ) ;
+FUNC int mvadd_wchnstr ( int, int, cchar_t * const, int ) ;
+FUNC int mvadd_wchstr ( int, int, cchar_t * const ) ;
+FUNC int mvchgat ( int, int, int, attr_t, short, void * const ) ;
+FUNC int mvcur ( int, int, int, int ) ;
+FUNC int mvdelch ( int, int ) ;
+FUNC int mvderwin ( WINDOW *, int, int ) ;
+FUNC int mvgetch ( int, int ) ;
+FUNC int mvgetnstr ( int, int, char *, int ) ;
+FUNC int mvgetn_wstr ( int, int, wint_t *, int ) ;
+FUNC int mvgetstr ( int, int, char * ) ;
+FUNC int mvget_wch ( int, int, wint_t * ) ;
+FUNC int mvget_wstr ( int, int, wint_t * ) ;
+FUNC int mvhline ( int, int, chtype, int ) ;
+FUNC int mvhline_set ( int, int, cchar_t * const, int ) ;
+FUNC chtype mvinch ( int, int ) ;
+FUNC int mvinchnstr ( int, int, chtype *, int ) ;
+FUNC int mvinchstr ( int, int, chtype * ) ;
+FUNC int mvinnstr ( int, int, char *, int ) ;
+FUNC int mvinnwstr ( int, int, wchar_t *, int ) ;
+FUNC int mvinsch ( int, int, chtype ) ;
+FUNC int mvinsnstr ( int, int, char * const, int ) ;
+FUNC int mvinsstr ( int, int, char * const ) ;
+FUNC int mvinstr ( int, int, char * ) ;
+FUNC int mvins_nwstr ( int, int, wchar_t * const, int ) ;
+FUNC int mvins_wch ( int, int, cchar_t * const ) ;
+FUNC int mvins_wstr ( int, int, wchar_t * const ) ;
+FUNC int mvinwstr ( int, int, wchar_t * ) ;
+FUNC int mvin_wch ( int, int, cchar_t * ) ;
+FUNC int mvin_wchnstr ( int, int, cchar_t *, int ) ;
+FUNC int mvin_wchstr ( int, int, cchar_t * ) ;
+FUNC int mvprintw ( int, int, char *, ... ) ;
+FUNC int mvscanw ( int, int, char *, ... ) ;
+FUNC int mvvline ( int, int, chtype, int ) ;
+FUNC int mvvline_set ( int, int, cchar_t * const, int ) ;
+FUNC int mvwaddch ( WINDOW *, int, int, const chtype ) ;
+FUNC int mvwaddchnstr ( WINDOW *, int, int, chtype * const, int ) ;
+FUNC int mvwaddchstr ( WINDOW *, int, int, chtype * const ) ;
+FUNC int mvwaddnstr ( WINDOW *, int, int, char * const, int ) ;
+FUNC int mvwaddnwstr ( WINDOW *, int, int, wchar_t * const, int ) ;
+FUNC int mvwaddstr ( WINDOW *, int, int, char * const ) ;
+FUNC int mvwaddwstr ( WINDOW *, int, int, wchar_t * const ) ;
+FUNC int mvwadd_wch ( WINDOW *, int, int, cchar_t * const ) ;
+FUNC int mvwadd_wchnstr ( WINDOW *, int, int, cchar_t * const, int ) ;
+FUNC int mvwadd_wchstr ( WINDOW *, int, int, cchar_t * const ) ;
+FUNC int mvwchgat ( WINDOW *, int, int, int, attr_t, short, void * const ) ;
+FUNC int mvwdelch ( WINDOW *, int, int ) ;
+FUNC int mvwgetch ( WINDOW *, int, int ) ;
+FUNC int mvwgetnstr ( WINDOW *, int, int, char *, int ) ;
+FUNC int mvwgetn_wstr ( WINDOW *, int, int, wint_t *, int ) ;
+FUNC int mvwgetstr ( WINDOW *, int, int, char * ) ;
+FUNC int mvwget_wch ( WINDOW *, int, int, wint_t * ) ;
+FUNC int mvwget_wstr ( WINDOW *, int, int, wint_t * ) ;
+FUNC int mvwhline ( WINDOW *, int, int, chtype, int ) ;
+FUNC int mvwhline_set ( WINDOW *, int, int, cchar_t * const, int ) ;
+FUNC int mvwin ( WINDOW *, int, int ) ;
+FUNC chtype mvwinch ( WINDOW *, int, int ) ;
+FUNC int mvwinchnstr ( WINDOW *, int, int, chtype *, int ) ;
+FUNC int mvwinchstr ( WINDOW *, int, int, chtype * ) ;
+FUNC int mvwinnstr ( WINDOW *, int, int, char *, int ) ;
+FUNC int mvwinnwstr ( WINDOW *, int, int, wchar_t *, int ) ;
+FUNC int mvwinsch ( WINDOW *, int, int, chtype ) ;
+FUNC int mvwinsnstr ( WINDOW *, int, int, char * const, int ) ;
+FUNC int mvwinsstr ( WINDOW *, int, int, char * const ) ;
+FUNC int mvwinstr ( WINDOW *, int, int, char * ) ;
+FUNC int mvwins_nwstr ( WINDOW *, int, int, wchar_t * const, int ) ;
+FUNC int mvwins_wch ( WINDOW *, int, int, cchar_t * const ) ;
+FUNC int mvwins_wstr ( WINDOW *, int, int, wchar_t * const ) ;
+FUNC int mvwinwstr ( WINDOW *, int, int, wchar_t * ) ;
+FUNC int mvwin_wch ( WINDOW *, int, int, cchar_t * ) ;
+FUNC int mvwin_wchnstr ( WINDOW *, int, int, cchar_t *, int ) ;
+FUNC int mvwin_wchstr ( WINDOW *, int, int, cchar_t * ) ;
+FUNC int mvwprintw ( WINDOW *, int, int, char *, ... ) ;
+FUNC int mvwscanw ( WINDOW *, int, int, char *, ... ) ;
+FUNC int mvwvline ( WINDOW *, int, int, chtype, int ) ;
+FUNC int mvwvline_set ( WINDOW *, int, int, cchar_t * const, int ) ;

+FUNC int napms ( int ) ;
+FUNC WINDOW *newpad ( int, int ) ;
+FUNC SCREEN *newterm ( char *, FILE *, FILE * ) ;
+FUNC WINDOW *newwin ( int, int, int, int ) ;
+FUNC int nl ( void ) ;
+FUNC int nonl ( void ) ;
+FUNC int nocbreak ( void ) ;
+FUNC int nodelay ( WINDOW *, bool ) ;
+FUNC int noecho ( void ) ;
+FUNC void noqiflush ( void ) ;
+FUNC int noraw ( void ) ;
+FUNC int notimeout ( WINDOW *, bool ) ;

+FUNC int overlay ( WINDOW * const, WINDOW * ) ;
+FUNC int overwrite ( WINDOW * const, WINDOW * ) ;

+FUNC int pair_content ( short, short *, short * ) ;
+FUNC int pechochar ( WINDOW *, chtype * ) ;
+FUNC int pecho_wchar ( WINDOW *, cchar_t * const ) ;
+FUNC int pnoutrefresh ( WINDOW *, int, int, int, int, int, int ) ;
+FUNC int prefresh ( WINDOW *, int, int, int, int, int, int ) ;
+FUNC int printw ( char *, ... ) ;
+FUNC int putwin ( WINDOW *, FILE * ) ;

+FUNC void qiflush ( void ) ;

+FUNC int raw ( void ) ;
+FUNC int redrawwin ( WINDOW * ) ;
+FUNC int refresh ( void ) ;
+FUNC int resetty ( void ) ;
+FUNC int reset_prog_mode ( void ) ;
+FUNC int reset_shell_mode ( void ) ;
+FUNC int ripoffline ( int, int (*) ( WINDOW *, int ) ) ;

+FUNC int savetty ( void ) ;
+FUNC int scanw ( char *, ... ) ;
+FUNC int scr_dump ( char * const ) ;
+FUNC int scr_init ( char * const ) ;
+FUNC int scrl ( int ) ;
+FUNC int scroll ( WINDOW * ) ;
+FUNC int scrollok ( WINDOW *, bool ) ;
+FUNC int scr_restore ( char * const ) ;
+FUNC int scr_set ( char * const ) ;
+FUNC int setcchar ( cchar_t *, wchar_t * const, const attr_t, short,
    void * const ) ;
+FUNC int setscrreg ( int, int ) ;
+FUNC SCREEN *set_term ( SCREEN * ) ;
+FUNC int slk_attroff ( const chtype ) ;
+FUNC int slk_attr_off ( const attr_t ) ;
+FUNC int slk_attron ( const chtype ) ;
+FUNC int slk_attr_on ( const attr_t ) ;
+FUNC int slk_attrset ( const chtype ) ;
+FUNC int slk_attr_set ( const attr_t ) ;
+FUNC int slk_clear ( void ) ;
+FUNC int slk_init ( int ) ;
+FUNC char *slk_label ( int ) ;
+FUNC int slk_noutrefresh ( void ) ;
+FUNC int slk_refresh ( void ) ;
+FUNC int slk_restore ( void ) ;
+FUNC int slk_set ( int, char * const, int ) ;
+FUNC int slk_touch ( void ) ;
+FUNC int slk_wset ( int, wchar_t * const, int ) ;
+FUNC int standend ( void ) ;
+FUNC int standout ( void ) ;
+FUNC int start_color ( void ) ;
+FUNC WINDOW *subpad ( WINDOW *, int, int, int, int ) ;
+FUNC WINDOW *subwin ( WINDOW *, int, int, int, int ) ;
+FUNC int syncok ( WINDOW *, bool ) ;

+FUNC attr_t termattrs ( void ) ;
+FUNC char *termname ( void ) ;
+FUNC void timeout ( int ) ;
+FUNC int touchline ( WINDOW *, int, int ) ;
+FUNC int touchwin ( WINDOW * ) ;
+FUNC int typeahead ( int ) ;

+FUNC int ungetch ( int ) ;
+FUNC int unget_wch ( const wchar_t ) ;
+FUNC int untouchwin ( WINDOW * ) ;
+FUNC void use_env ( char ) ;

+FUNC int vidattr ( chtype ) ;
+FUNC int vid_attr ( attr_t ) ;
+FUNC int vidputs ( chtype, int (*) ( int ) ) ;
+FUNC int vid_puts ( attr_t, wint_t (*) ( wint_t ) ) ;
+FUNC int vline ( chtype, int ) ;
+FUNC int vline_set ( cchar_t * const, int ) ;
+FUNC int vwprintw ( WINDOW *, char *, va_list ) ;
+FUNC int vw_printw ( WINDOW *, char *, va_list ) ;
+FUNC int vwscanw ( WINDOW *, char *, va_list ) ;
+FUNC int vw_scanw ( WINDOW *, char *, va_list ) ;

+FUNC int waddch ( WINDOW *, const chtype ) ;
+FUNC int waddchnstr ( WINDOW *, chtype * const, int ) ;
+FUNC int waddchstr ( WINDOW *, chtype * const ) ;
+FUNC int waddnstr ( WINDOW *, char * const, int ) ;
+FUNC int waddnwstr ( WINDOW *, wchar_t * const, int ) ;
+FUNC int waddstr ( WINDOW *, char * const ) ;
+FUNC int waddwstr ( WINDOW *, wchar_t * const ) ;
+FUNC int wadd_wch ( WINDOW *, cchar_t * const ) ;
+FUNC int wadd_wchnstr ( WINDOW *, cchar_t * const, int ) ;
+FUNC int wadd_wchstr ( WINDOW *, cchar_t * const ) ;
+FUNC int wattroff ( WINDOW *, int ) ;
+FUNC int wattron ( WINDOW *, int ) ;
+FUNC int wattrset ( WINDOW *, int ) ;
+FUNC attr_t wattr_get ( WINDOW * ) ;
+FUNC int wattr_off ( WINDOW *, attr_t ) ;
+FUNC int wattr_on ( WINDOW *, attr_t ) ;
+FUNC int wattr_set ( WINDOW *, attr_t ) ;
+FUNC int wbkgd ( WINDOW *, chtype ) ;
+FUNC void wbkgdset ( WINDOW *, chtype ) ;
+FUNC int wbkgrnd ( WINDOW *, cchar_t * const ) ;
+FUNC void wbkgrndset ( WINDOW *, cchar_t * const ) ;
+FUNC int wborder ( WINDOW *, chtype, chtype, chtype, chtype, chtype,
    chtype, chtype, chtype ) ;
+FUNC int wborder_set ( WINDOW *, cchar_t * const, cchar_t * const,
    cchar_t * const, cchar_t * const, cchar_t * const, cchar_t * const,
    cchar_t * const, cchar_t * const ) ;
+FUNC int wchgat ( WINDOW *, int, attr_t, short, void * const ) ;
+FUNC int wclear ( WINDOW * ) ;
+FUNC int wclrtobot ( WINDOW * ) ;
+FUNC int wclrtoeol ( WINDOW * ) ;
+FUNC void wcursyncup ( WINDOW * ) ;
+FUNC int wdelch ( WINDOW * ) ;
+FUNC int wdeleteln ( WINDOW * ) ;
+FUNC int wechochar ( WINDOW *, const chtype ) ;
+FUNC int wecho_wchar ( WINDOW *, cchar_t * const ) ;
+FUNC int werase ( WINDOW * ) ;
+FUNC int wgetbkgrnd ( WINDOW *, cchar_t * ) ;
+FUNC int wgetch ( WINDOW * ) ;
+FUNC int wgetnstr ( WINDOW *, char *, int ) ;
+FUNC int wgetn_wstr ( WINDOW *, wint_t *, int ) ;
+FUNC int wgetstr ( WINDOW *, char * ) ;
+FUNC int wget_wch ( WINDOW *, wint_t * ) ;
+FUNC int wget_wstr ( WINDOW *, wint_t * ) ;
+FUNC int whline ( WINDOW *, chtype, int ) ;
+FUNC int whline_set ( WINDOW *, cchar_t * const, int ) ;
+FUNC chtype winch ( WINDOW * ) ;
+FUNC int winchnstr ( WINDOW *, chtype *, int ) ;
+FUNC int winchstr ( WINDOW *, chtype * ) ;
+FUNC int winnstr ( WINDOW *, char *, int ) ;
+FUNC int winnwstr ( WINDOW *, wchar_t *, int ) ;
+FUNC int winsch ( WINDOW *, chtype ) ;
+FUNC int winsdelln ( WINDOW *, int ) ;
+FUNC int winsertln ( WINDOW * ) ;
+FUNC int winsnstr ( WINDOW *, char * const, int ) ;
+FUNC int winsstr ( WINDOW *, char * const ) ;
+FUNC int winstr ( WINDOW *, char * ) ;
+FUNC int wins_nwstr ( WINDOW *, wchar_t * const, int ) ;
+FUNC int wins_wch ( WINDOW *, cchar_t * const ) ;
+FUNC int wins_wstr ( WINDOW *, wchar_t * const ) ;
+FUNC int winwstr ( WINDOW *, wchar_t * ) ;
+FUNC int win_wch ( WINDOW *, cchar_t * ) ;
+FUNC int win_wchnstr ( WINDOW *, cchar_t *, int ) ;
+FUNC int win_wchstr ( WINDOW *, cchar_t * ) ;
+FUNC int wmove ( WINDOW *, int, int ) ;
+FUNC int wnoutrefresh ( WINDOW * ) ;
+FUNC int wprintw ( WINDOW *, char *, ... ) ;
+FUNC int wredrawln ( WINDOW *, int, int ) ;
+FUNC int wrefresh ( WINDOW * ) ;
+FUNC int wscanw ( WINDOW *, char *, ... ) ;
+FUNC int wscrl ( WINDOW *, int ) ;
+FUNC int wsetscrreg ( WINDOW *, int, int ) ;
+FUNC int wstandend ( WINDOW * ) ;
+FUNC int wstandout ( WINDOW * ) ;
+FUNC void wsyncdown ( WINDOW * ) ;
+FUNC void wsyncup ( WINDOW * ) ;
+FUNC void wtimeout ( WINDOW *, int ) ;
+FUNC int wtouchln ( WINDOW *, int, int, int ) ;
+FUNC wchar_t *wunctrl ( cchar_t * ) ;
+FUNC int wvline ( WINDOW *, chtype, int ) ;
+FUNC int wvline_set ( WINDOW *, cchar_t * const, int ) ;

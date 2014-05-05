# $Id$

# Copyright 2002-2011, The TenDRA Project.
# Copyright 1997, United Kingdom Secretary of State for Defence.
#
# See doc/copyright/ for the full copyright terms.


+USE "svid3", "", "config" ;
+IF %% __SYSV_TERMINAL_INTERFACE %%

+USE "svid3", "stdio.h.ts" ;
+USE "svid3", "term.h.ts" (!?) ;
+USE "svid3", "unctrl.h.ts" (!?) ;
+USE "c/c89", "stdarg.h.ts", "va_args" (!?) ;

+TYPE WINDOW, SCREEN, ( int ) bool, ( int ) chtype ;

+DEFINE TRUE 1 ;
+DEFINE FALSE 0 ;
+DEFINE OK 0 ;
+DEFINE ERR %% ( -1 ) %% ;

+EXP lvalue int LINES, COLS ;
+EXP lvalue WINDOW *curscr, *stdscr ;

+EXP int ACS_ULCORNER, ACS_LLCORNER, ACS_URCORNER, ACS_LRCORNER, ACS_RTEE ;
+EXP int ACS_LTEE, ACS_BTEE, ACS_TTEE, ACS_HLINE, ACS_VLINE, ACS_PLUS ;
+EXP int ACS_S1, ACS_S9, ACS_DIAMOND, ACS_CKBOARD, ACS_DEGREE, ACS_PLMINUS ;
+EXP int ACS_BULLET, ACS_LARROW, ACS_RARROW, ACS_DARROW, ACS_UARROW ;
+EXP int ACS_BOARD, ACS_LANTERN, ACS_BLOCK ;

+CONST int A_STANDOUT, A_UNDERLINE, A_REVERSE, A_BLINK, A_DIM, A_BOLD ;
+CONST int A_ALTCHARSET, A_CHARTEXT ;
+MACRO int COLOR_PAIR ( int ) ;
+MACRO int PAIR_NUMBER ( int ) ;
+CONST int A_ATTRIBUTES, A_COLOR ;

+CONST int COLOR_BLACK, COLOR_BLUE, COLOR_GREEN, COLOR_CYAN, COLOR_RED ;
+CONST int COLOR_MAGENTA, COLOR_YELLOW, COLOR_WHITE ;

+CONST int KEY_BREAK, KEY_DOWN, KEY_UP, KEY_LEFT, KEY_RIGHT, KEY_HOME ;
+CONST int KEY_BACKSPACE, KEY_F0 ;
+MACRO int KEY_F ( int ) ;
+CONST int KEY_DL, KEY_IL, KEY_DC, KEY_IC, KEY_EIC, KEY_CLEAR, KEY_EOS ;
+CONST int KEY_EOL, KEY_SF, KEY_SR, KEY_NPAGE, KEY_PPAGE, KEY_STAB, KEY_CTAB ;
+CONST int KEY_CATAB, KEY_ENTER, KEY_SRESET, KEY_RESET, KEY_PRINT, KEY_LL ;
+CONST int KEY_A1, KEY_A3, KEY_B2, KEY_C1, KEY_C3, KEY_BTAB, KEY_BEG ;
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

+FUNC int addch ( chtype ) ;
+FUNC int waddch ( WINDOW *, chtype ) ;
+FUNC int mvaddch ( int, int, chtype ) ;
+FUNC int mvwaddch ( WINDOW *, int, int, chtype ) ;
+FUNC int echochar ( chtype ) ;
+FUNC int wechochar ( WINDOW *, chtype ) ;

+FUNC int addchstr ( chtype * ) ;
+FUNC int addchnstr ( chtype *, int ) ;
+FUNC int waddchstr ( WINDOW *, chtype * ) ;
+FUNC int waddchnstr ( WINDOW *, chtype *, int ) ;
+FUNC int mvaddchstr ( int, int, chtype * ) ;
+FUNC int mvaddchnstr ( int, int, chtype *, int ) ;
+FUNC int mvwaddchstr ( WINDOW *, int, int, chtype * ) ;
+FUNC int mvwaddchnstr ( WINDOW *, int, int, chtype *, int ) ;

+FUNC int addstr ( char * ) ;
+FUNC int addnstr ( char *, int ) ;
+FUNC int waddstr ( WINDOW *, char * ) ;
+FUNC int waddnstr ( WINDOW *, char *, int ) ;
+FUNC int mvaddstr ( int, int, char * ) ;
+FUNC int mvaddnstr ( int, int, char *, int ) ;
+FUNC int mvwaddstr ( WINDOW *, int, int, char * ) ;
+FUNC int mvwaddnstr ( WINDOW *, int, int, char *, int ) ;

/* Error in book */
+FUNC int attroff ( chtype ) ;
+FUNC int wattroff ( WINDOW *, chtype ) ;
+FUNC int attron ( chtype ) ;
+FUNC int wattron ( WINDOW *, chtype ) ;
+FUNC int attrset ( chtype ) ;
+FUNC int wattrset ( WINDOW *, chtype ) ;
+FUNC int standend ( void ) ;
+FUNC int wstandend ( WINDOW * ) ;
+FUNC int standout ( void ) ;
+FUNC int wstandout ( WINDOW * ) ;

+FUNC int beep ( void ) ;
+FUNC int flash ( void ) ;

+FUNC void bkgdset ( chtype ) ;
+FUNC void wbkgdset ( WINDOW *, chtype ) ;
+FUNC int bkgd ( chtype ) ;
+FUNC int wbkgd ( WINDOW *, chtype ) ;

+FUNC int border ( chtype, chtype, chtype, chtype, chtype, chtype,
		   chtype, chtype ) ;
+FUNC int wborder ( WINDOW *, chtype, chtype, chtype, chtype, chtype,
		    chtype, chtype, chtype ) ;
+FUNC int box ( WINDOW *, chtype, chtype ) ;
+FUNC int hline ( chtype, int ) ;
+FUNC int whline ( WINDOW *, chtype, int ) ;
+FUNC int vline ( chtype, int ) ;
+FUNC int wvline ( WINDOW *, chtype, int ) ;

+FUNC int erase ( void ) ;
+FUNC int werase ( WINDOW * ) ;
+FUNC int clear ( void ) ;
+FUNC int wclear ( WINDOW * ) ;
+FUNC int clrtobot ( void ) ;
+FUNC int wclrtobot ( WINDOW * ) ;
+FUNC int clrtoeol ( void ) ;
+FUNC int wclrtoeol ( WINDOW * ) ;

+FUNC int start_color ( void ) ;
+FUNC int init_pair ( short, short, short ) ;
+FUNC int init_color ( short, short, short, short ) ;
+FUNC bool has_colors ( void ) ;
+FUNC bool can_change_color ( void ) ;
+FUNC int color_content ( short, short *, short *, short * ) ;
+FUNC int pair_content ( short, short *, short * ) ;

+FUNC int delch ( void ) ;
+FUNC int wdelch ( WINDOW * ) ;
+FUNC int mvdelch ( int, int ) ;
+FUNC int mvwdelch ( WINDOW *, int, int ) ;

+FUNC int deleteln ( void ) ;
+FUNC int wdeleteln ( WINDOW * ) ;
+FUNC int insdelln ( int ) ;
+FUNC int winsdelln ( WINDOW *, int ) ;
+FUNC int insertln ( void ) ;
+FUNC int winsertln ( WINDOW * ) ;

+FUNC int getch ( void ) ;
+FUNC int wgetch ( WINDOW * ) ;
+FUNC int mvgetch ( int, int ) ;
+FUNC int mvwgetch ( WINDOW *, int, int ) ;
+FUNC int ungetch ( int ) ;

+FUNC int getstr ( char * ) ;
+FUNC int wgetstr ( WINDOW *, char * ) ;
+FUNC int mvgetstr ( int, int, char * ) ;
+FUNC int mvwgetstr ( WINDOW *, int, int, char * ) ;
+FUNC int wgetnstr ( WINDOW *,char *, int ) ;

+MACRO void getyx ( WINDOW *, lvalue int, lvalue int ) ;
+MACRO void getparyx ( WINDOW *, lvalue int, lvalue int ) ;
+MACRO void getbegyx ( WINDOW *, lvalue int, lvalue int ) ;
+MACRO void getmaxyx ( WINDOW *, lvalue int, lvalue int ) ;

+FUNC chtype inch ( void ) ;
+FUNC chtype winch ( WINDOW * ) ;
+FUNC chtype mvinch ( int, int ) ;
+FUNC chtype mvwinch ( WINDOW *, int, int ) ;

+FUNC int inchstr ( chtype * ) ;
+FUNC int inchnstr ( chtype *, int ) ;
+FUNC int winchstr ( WINDOW *, chtype * ) ;
+FUNC int winchnstr ( WINDOW *, chtype *, int ) ;
+FUNC int mvinchstr ( int, int, chtype * ) ;
+FUNC int mvinchnstr ( int, int, chtype *, int ) ;
+FUNC int mvwinchstr ( WINDOW *, int, int, chtype * ) ;
+FUNC int mvwinchnstr ( WINDOW *, int, int, chtype *, int ) ;

+FUNC WINDOW *initscr ( void ) ;
+FUNC int endwin ( void ) ;
+FUNC int isendwin ( void ) ;
+FUNC SCREEN *newterm ( char *, FILE *, FILE * ) ;
+FUNC SCREEN *set_term ( SCREEN * ) ;
+FUNC void delscreen ( SCREEN * ) ;

+FUNC int cbreak ( void ) ;
+FUNC int nocbreak ( void ) ;
+FUNC int echo ( void ) ;
+FUNC int noecho ( void ) ;
+FUNC int halfdelay ( int ) ;
+FUNC int intrflush ( WINDOW *, bool ) ;
+FUNC int keypad ( WINDOW *, bool ) ;
+FUNC int meta ( WINDOW *, bool ) ;
+FUNC int nodelay ( WINDOW *, bool ) ;
+FUNC int notimeout ( WINDOW *, bool ) ;
+FUNC int raw ( void ) ;
+FUNC int noraw ( void ) ;
+FUNC void noqiflush ( void ) ;
+FUNC void qiflush ( void ) ;
+FUNC void timeout ( int ) ;
+FUNC void wtimeout ( WINDOW *, int ) ;
+FUNC int typeahead ( int ) ;

+FUNC int insch ( chtype ) ;
+FUNC int winsch ( WINDOW *, chtype ) ;
+FUNC int mvinsch ( int, int, chtype ) ;
+FUNC int mvwinsch ( WINDOW *, int, int, chtype ) ;

+FUNC int insstr ( char * ) ;
+FUNC int insnstr ( char *, int ) ;
+FUNC int winsstr ( WINDOW *, char * ) ;
+FUNC int winsnstr ( WINDOW *, char *, int ) ;
+FUNC int mvinsstr ( int, int, char * ) ;
+FUNC int mvinsnstr ( int, int, char *, int ) ;
+FUNC int mvwinsstr ( WINDOW *, int, int, char * ) ;
+FUNC int mvwinsnstr ( WINDOW *, int, int, char *, int ) ;

+FUNC int instr ( char * ) ;
+FUNC int innstr ( char *, int ) ;
+FUNC int winstr ( WINDOW *, char * ) ;
+FUNC int winnstr ( WINDOW *, char *, int ) ;
+FUNC int mvinstr ( int, int, char * ) ;
+FUNC int mvinnstr ( int, int, char *, int ) ;
+FUNC int mvwinstr ( WINDOW *, int, int, char * ) ;
+FUNC int mvwinnstr ( WINDOW *, int, int, char *, int ) ;

+FUNC int def_prog_mode ( void ) ;
+FUNC int def_shell_mode ( void ) ;
+FUNC int reset_prog_mode ( void ) ;
+FUNC int reset_shell_mode ( void ) ;
+FUNC int resetty ( void ) ;
+FUNC int savetty ( void ) ;
+MACRO int getsyx ( lvalue int, lvalue int ) ;
+FUNC int setsyx ( int, int ) ;
+FUNC int ripoffline ( int, int (*) () ) ;
+FUNC int curs_set ( int ) ;
+FUNC int napms ( int ) ;

+FUNC int move ( int, int ) ;
+FUNC int wmove ( WINDOW *, int, int ) ;

+FUNC int clearok ( WINDOW *, bool ) ;
+FUNC int idlok ( WINDOW *, bool ) ;
+FUNC void idcok ( WINDOW *, bool ) ;
+FUNC void immedok ( WINDOW *, bool ) ;
+FUNC int leaveok ( WINDOW *, bool ) ;
+FUNC int setscrreg ( int, int ) ;
+FUNC int wsetscrreg ( WINDOW *, int, int ) ;
+FUNC int scrollok ( WINDOW *, bool ) ;
+FUNC int nl ( void ) ;
+FUNC int nonl ( void ) ;

+FUNC int overlay ( WINDOW *, WINDOW * ) ;
+FUNC int overwrite ( WINDOW *, WINDOW * ) ;
+FUNC int copywin ( WINDOW *, WINDOW *, int, int, int, int, int, int, int ) ;

+FUNC WINDOW *newpad ( int, int ) ;
+FUNC WINDOW *subpad ( WINDOW *, int, int, int, int ) ;
+FUNC int prefresh ( WINDOW *, int, int, int, int, int, int ) ;
+FUNC int pnoutrefresh ( WINDOW *, int, int, int, int, int, int ) ;
+FUNC int pechochar ( WINDOW *, chtype ) ;

+FUNC int printw ( char *, ... ) ;
+FUNC int wprintw ( WINDOW *, char *, ... ) ;
+FUNC int mvprintw ( int, int, char *, ... ) ;
+FUNC int mvwprintw ( WINDOW *, int, int, char *, ... ) ;
+FUNC int vwprintw ( WINDOW *, char *, va_list ) ;

+FUNC int refresh ( void ) ;
+FUNC int wrefresh ( WINDOW * ) ;
+FUNC int wnoutrefresh ( WINDOW * ) ;
+FUNC int doupdate ( void ) ;
+FUNC int redrawwin ( WINDOW * ) ;
+FUNC int wredrawln ( WINDOW *, int, int ) ;

+FUNC int scanw ( char *, ... ) ;
+FUNC int wscanw ( WINDOW *, char *, ... ) ;
+FUNC int mvscanw ( int, int, char *, ... ) ;
+FUNC int mvwscanw ( WINDOW *, int, int, char *, ... ) ;
+FUNC int vwscanw ( WINDOW *, char *, va_list ) ;

+FUNC int scr_dump ( char * ) ;
+FUNC int scr_restore ( char * ) ;
+FUNC int scr_init ( char * ) ;
+FUNC int scr_set ( char * ) ;

+FUNC int scroll ( WINDOW * ) ;
+FUNC int scrl ( int ) ;
+FUNC int wscrl ( WINDOW *, int ) ;

+FUNC int slk_init ( int ) ;
+FUNC int slk_set ( int, char *, int ) ;
+FUNC int slk_refresh ( void ) ;
+FUNC int slk_noutrefresh ( void ) ;
+FUNC char *slk_label ( int ) ;
+FUNC int slk_clear ( void ) ;
+FUNC int slk_restore ( void ) ;
+FUNC int slk_touch ( void ) ;
+FUNC int slk_attron ( chtype ) ;
+FUNC int slk_attrset ( chtype ) ;
+FUNC int slk_attroff ( chtype ) ;

+FUNC int baudrate ( void ) ;
+FUNC char erasechar ( void ) ;
+FUNC int has_ic ( void ) ;
+FUNC int has_il ( void ) ;
+FUNC char killchar ( void ) ;
+FUNC char *longname ( void ) ;
+FUNC chtype termattrs ( void ) ;
+FUNC char *termname ( void ) ;

+FUNC int setupterm ( char *, int, int * ) ;
+FUNC int setterm ( char * ) ;
/* Errata */
+FUNC TERMINAL *set_curterm ( TERMINAL * ) ;
+FUNC int del_curterm ( TERMINAL * ) ;
+FUNC int restartterm ( char *, int, int * ) ;
+FUNC char *tparm ( long, long, long, long, long, long, long, long, long ) ;
+FUNC int putp ( char * ) ;
+FUNC int vidputs ( chtype, int (*) () ) ;
+FUNC int vidattr ( chtype ) ;
+FUNC int mvcur ( int, int, int, int ) ;
+FUNC int tigetflag ( char * ) ;
+FUNC int tigetnum ( char * ) ;
+FUNC int tigetstr ( char * ) ;

+FUNC int touchwin ( WINDOW * ) ;
+FUNC int touchline ( WINDOW *, int, int ) ;
+FUNC int untouchwin ( WINDOW * ) ;
+FUNC int wtouchln ( WINDOW *, int, int, int ) ;
+FUNC int is_linetouched ( WINDOW *, int ) ;
+FUNC int is_wintouched ( WINDOW * ) ;

+FUNC char * keyname ( int ) ;
/* Error in book */
+FUNC void filter ( void ) ;
+FUNC void use_env ( char ) ;
+FUNC int putwin ( WINDOW *, FILE * ) ;
+FUNC WINDOW * getwin ( FILE * ) ;
+FUNC int delay_output ( int ) ;
+FUNC int flushinp ( void ) ;

+FUNC WINDOW *newwin ( int, int, int, int ) ;
+FUNC int delwin ( WINDOW * ) ;
+FUNC int mvwin ( WINDOW *, int, int ) ;
+FUNC WINDOW *subwin ( WINDOW *, int, int, int, int ) ;
+FUNC WINDOW *derwin ( WINDOW *, int, int, int, int ) ;
+FUNC int mvderwin ( WINDOW *, int, int ) ;
+FUNC WINDOW *dupwin ( WINDOW * ) ;
+FUNC void wsyncup ( WINDOW * ) ;
+FUNC int syncok ( WINDOW *, bool ) ;
+FUNC void wcursyncup ( WINDOW * ) ;
+FUNC void wsyncdown ( WINDOW * ) ;

+FUNC int tgetent ( char *, char * ) ;
+FUNC int tgetflag ( char [2] ) ;
+FUNC int tgetnum ( char [2] ) ;
+FUNC char *tgetstr ( char [2], char ** ) ;
+FUNC char *tgoto ( char *, int, int ) ;
+FUNC int tputs ( char *, int, int (*) () ) ;

+IF %% __SYSV_UPDATE %%

+USE "c/c89", "stddef.h.ts", "wchar_t" (!?) ;

+FUNC int addwch ( chtype ) ;
+FUNC int waddwch ( WINDOW *, chtype ) ;
+FUNC int mvaddwch ( int, int, chtype ) ;
+FUNC int mvwaddwch ( WINDOW *, int, int, chtype ) ;
+FUNC int echowchar ( chtype ) ;
+FUNC int wechowchar ( WINDOW *, chtype ) ;

+FUNC int addwchstr ( chtype * ) ;
+FUNC int addwchnstr ( chtype *, int ) ;
+FUNC int waddwchstr ( WINDOW *, chtype * ) ;
+FUNC int waddwchnstr ( WINDOW *, chtype *, int ) ;
+FUNC int mvaddwchstr ( int, int, chtype * ) ;
+FUNC int mvaddwchnstr ( int, int, chtype *, int ) ;
+FUNC int mvwaddwchstr ( WINDOW *, int, int, chtype * ) ;
+FUNC int mvwaddwchnstr ( WINDOW *, int, int, chtype *, int ) ;

+FUNC int addwstr ( wchar_t * ) ;
+FUNC int addnwstr ( wchar_t *, int ) ;
+FUNC int waddwstr ( WINDOW *, wchar_t * ) ;
+FUNC int waddnwstr ( WINDOW *, wchar_t *, int ) ;
+FUNC int mvaddwstr ( int, int, wchar_t * ) ;
+FUNC int mvaddnwstr ( int, int, wchar_t *, int ) ;
+FUNC int mvwaddwstr ( WINDOW *, int, int, wchar_t * ) ;
+FUNC int mvwaddnwstr ( WINDOW *, int, int, wchar_t *, int ) ;

+FUNC int getwch ( void ) ;
+FUNC int wgetwch ( WINDOW * ) ;
+FUNC int mvgetwch ( int, int ) ;
+FUNC int mvwgetwch ( WINDOW *, int, int ) ;
+FUNC int ungetwch ( int ) ;

+FUNC int getwstr ( wchar_t * ) ;
+FUNC int getnwstr ( wchar_t *, int ) ;
+FUNC int wgetwstr ( WINDOW *, wchar_t * ) ;
+FUNC int wgetnwstr ( WINDOW *, wchar_t *, int ) ;
+FUNC int mvgetwstr ( int, int, wchar_t * ) ;
+FUNC int mvgetnwstr ( int, int, wchar_t *, int ) ;
+FUNC int mvwgetwstr ( WINDOW *, int, int, wchar_t * ) ;
+FUNC int mvwgetnwstr ( WINDOW *, int, int, wchar_t *, int ) ;

+FUNC int inswch ( chtype ) ;
+FUNC int winswch ( WINDOW *, chtype ) ;
+FUNC int mvinswch ( int, int, chtype ) ;
+FUNC int mvwinswch ( WINDOW *, int, int, chtype ) ;

/* I think the book is wrong about these */
+FUNC int inswstr ( wchar_t * ) ;
+FUNC int insnwstr ( wchar_t *, int ) ;
+FUNC int winswstr ( WINDOW *, wchar_t * ) ;
+FUNC int winsnwstr ( WINDOW *, wchar_t *, int ) ;
+FUNC int mvinswstr ( int, int, wchar_t * ) ;
+FUNC int mvinsnwstr ( int, int, wchar_t *, int ) ;
+FUNC int mvwinswstr ( WINDOW *, int, int, wchar_t * ) ;
+FUNC int mvwinsnwstr ( WINDOW *, int, int, wchar_t *, int ) ;

+FUNC chtype inwch ( void ) ;
+FUNC chtype winwch ( WINDOW * ) ;
+FUNC chtype mvinwch ( int, int ) ;
+FUNC chtype mvwinwch ( WINDOW *, int, int ) ;

+FUNC int inwchstr ( chtype * ) ;
+FUNC int inwchnstr ( chtype *, int ) ;
+FUNC int winwchstr ( WINDOW *, chtype * ) ;
+FUNC int winwchnstr ( WINDOW *, chtype *, int ) ;
+FUNC int mvinwchstr ( int, int, chtype * ) ;
+FUNC int mvinwchnstr ( int, int, chtype *, int ) ;
+FUNC int mvwinwchstr ( WINDOW *, int, int, chtype * ) ;
+FUNC int mvwinwchnstr ( WINDOW *, int, int, chtype *, int ) ;

/* I think the book is wrong about these */
+FUNC int inwstr ( wchar_t * ) ;
+FUNC int innwstr ( wchar_t *, int ) ;
+FUNC int winwstr ( WINDOW *, wchar_t * ) ;
+FUNC int winnwstr ( WINDOW *, wchar_t *, int ) ;
+FUNC int mvinwstr ( int, int, wchar_t * ) ;
+FUNC int mvinnwstr ( int, int, wchar_t *, int ) ;
+FUNC int mvwinwstr ( WINDOW *, int, int, wchar_t * ) ;
+FUNC int mvwinnwstr ( WINDOW *, int, int, wchar_t *, int ) ;

+FUNC int pechowchar ( WINDOW *, chtype ) ;

+ENDIF
+ENDIF

# Makefile for lib/curses.

SRC=/usr/src/lib/curses
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(beep.o) \
	$(LIBRARY)(charpick.o) \
	$(LIBRARY)(curs_set.o) \
	$(LIBRARY)(cursesio.o) \
	$(LIBRARY)(endwin.o) \
	$(LIBRARY)(flash.o) \
	$(LIBRARY)(initscr.o) \
	$(LIBRARY)(longname.o) \
	$(LIBRARY)(move.o) \
	$(LIBRARY)(mvcursor.o) \
	$(LIBRARY)(newwin.o) \
	$(LIBRARY)(options.o) \
	$(LIBRARY)(overlay.o) \
	$(LIBRARY)(prntscan.o) \
	$(LIBRARY)(refresh.o) \
	$(LIBRARY)(scrreg.o) \
	$(LIBRARY)(setterm.o) \
	$(LIBRARY)(tabsize.o) \
	$(LIBRARY)(termmisc.o) \
	$(LIBRARY)(unctrl.o) \
	$(LIBRARY)(update.o) \
	$(LIBRARY)(waddch.o) \
	$(LIBRARY)(waddstr.o) \
	$(LIBRARY)(wbox.o) \
	$(LIBRARY)(wclear.o) \
	$(LIBRARY)(wclrtobot.o) \
	$(LIBRARY)(wclrtoeol.o) \
	$(LIBRARY)(wdelch.o) \
	$(LIBRARY)(wdeleteln.o) \
	$(LIBRARY)(werase.o) \
	$(LIBRARY)(wgetch.o) \
	$(LIBRARY)(wgetstr.o) \
	$(LIBRARY)(windel.o) \
	$(LIBRARY)(winmove.o) \
	$(LIBRARY)(winsch.o) \
	$(LIBRARY)(winscrol.o) \
	$(LIBRARY)(winsertln.o) \
	$(LIBRARY)(wintouch.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(beep.o):	$(SRC)/beep.c
	$(CC1) $(SRC)/beep.c

$(LIBRARY)(charpick.o):	$(SRC)/charpick.c
	$(CC1) $(SRC)/charpick.c

$(LIBRARY)(curs_set.o):	$(SRC)/curs_set.c
	$(CC1) $(SRC)/curs_set.c

$(LIBRARY)(cursesio.o):	$(SRC)/cursesio.c
	$(CC1) $(SRC)/cursesio.c

$(LIBRARY)(endwin.o):	$(SRC)/endwin.c
	$(CC1) $(SRC)/endwin.c

$(LIBRARY)(flash.o):	$(SRC)/flash.c
	$(CC1) $(SRC)/flash.c

$(LIBRARY)(initscr.o):	$(SRC)/initscr.c
	$(CC1) $(SRC)/initscr.c

$(LIBRARY)(longname.o):	$(SRC)/longname.c
	$(CC1) $(SRC)/longname.c

$(LIBRARY)(move.o):	$(SRC)/move.c
	$(CC1) $(SRC)/move.c

$(LIBRARY)(mvcursor.o):	$(SRC)/mvcursor.c
	$(CC1) $(SRC)/mvcursor.c

$(LIBRARY)(newwin.o):	$(SRC)/newwin.c
	$(CC1) $(SRC)/newwin.c

$(LIBRARY)(options.o):	$(SRC)/options.c
	$(CC1) $(SRC)/options.c

$(LIBRARY)(overlay.o):	$(SRC)/overlay.c
	$(CC1) $(SRC)/overlay.c

$(LIBRARY)(prntscan.o):	$(SRC)/prntscan.c
	$(CC1) $(SRC)/prntscan.c

$(LIBRARY)(refresh.o):	$(SRC)/refresh.c
	$(CC1) $(SRC)/refresh.c

$(LIBRARY)(scrreg.o):	$(SRC)/scrreg.c
	$(CC1) $(SRC)/scrreg.c

$(LIBRARY)(setterm.o):	$(SRC)/setterm.c
	$(CC1) $(SRC)/setterm.c

$(LIBRARY)(tabsize.o):	$(SRC)/tabsize.c
	$(CC1) $(SRC)/tabsize.c

$(LIBRARY)(termmisc.o):	$(SRC)/termmisc.c
	$(CC1) $(SRC)/termmisc.c

$(LIBRARY)(unctrl.o):	$(SRC)/unctrl.c
	$(CC1) $(SRC)/unctrl.c

$(LIBRARY)(update.o):	$(SRC)/update.c
	$(CC1) $(SRC)/update.c

$(LIBRARY)(waddch.o):	$(SRC)/waddch.c
	$(CC1) $(SRC)/waddch.c

$(LIBRARY)(waddstr.o):	$(SRC)/waddstr.c
	$(CC1) $(SRC)/waddstr.c

$(LIBRARY)(wbox.o):	$(SRC)/wbox.c
	$(CC1) $(SRC)/wbox.c

$(LIBRARY)(wclear.o):	$(SRC)/wclear.c
	$(CC1) $(SRC)/wclear.c

$(LIBRARY)(wclrtobot.o):	$(SRC)/wclrtobot.c
	$(CC1) $(SRC)/wclrtobot.c

$(LIBRARY)(wclrtoeol.o):	$(SRC)/wclrtoeol.c
	$(CC1) $(SRC)/wclrtoeol.c

$(LIBRARY)(wdelch.o):	$(SRC)/wdelch.c
	$(CC1) $(SRC)/wdelch.c

$(LIBRARY)(wdeleteln.o):	$(SRC)/wdeleteln.c
	$(CC1) $(SRC)/wdeleteln.c

$(LIBRARY)(werase.o):	$(SRC)/werase.c
	$(CC1) $(SRC)/werase.c

$(LIBRARY)(wgetch.o):	$(SRC)/wgetch.c
	$(CC1) $(SRC)/wgetch.c

$(LIBRARY)(wgetstr.o):	$(SRC)/wgetstr.c
	$(CC1) $(SRC)/wgetstr.c

$(LIBRARY)(windel.o):	$(SRC)/windel.c
	$(CC1) $(SRC)/windel.c

$(LIBRARY)(winmove.o):	$(SRC)/winmove.c
	$(CC1) $(SRC)/winmove.c

$(LIBRARY)(winsch.o):	$(SRC)/winsch.c
	$(CC1) $(SRC)/winsch.c

$(LIBRARY)(winscrol.o):	$(SRC)/winscrol.c
	$(CC1) $(SRC)/winscrol.c

$(LIBRARY)(winsertln.o):	$(SRC)/winsertln.c
	$(CC1) $(SRC)/winsertln.c

$(LIBRARY)(wintouch.o):	$(SRC)/wintouch.c
	$(CC1) $(SRC)/wintouch.c

# Makefile for lib/stdio.

SRC=/usr/src/lib/stdio
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC)

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(clearerr.o) \
	$(LIBRARY)(data.o) \
	$(LIBRARY)(doprnt.o) \
	$(LIBRARY)(doscan.o) \
	$(LIBRARY)(ecvt.o) \
	$(LIBRARY)(fclose.o) \
	$(LIBRARY)(feof.o) \
	$(LIBRARY)(ferror.o) \
	$(LIBRARY)(fflush.o) \
	$(LIBRARY)(fgetc.o) \
	$(LIBRARY)(fgetpos.o) \
	$(LIBRARY)(fgets.o) \
	$(LIBRARY)(fileno.o) \
	$(LIBRARY)(fillbuf.o) \
	$(LIBRARY)(flushbuf.o) \
	$(LIBRARY)(fopen.o) \
	$(LIBRARY)(fprintf.o) \
	$(LIBRARY)(fputc.o) \
	$(LIBRARY)(fputs.o) \
	$(LIBRARY)(fread.o) \
	$(LIBRARY)(freopen.o) \
	$(LIBRARY)(fscanf.o) \
	$(LIBRARY)(fseek.o) \
	$(LIBRARY)(fsetpos.o) \
	$(LIBRARY)(ftell.o) \
	$(LIBRARY)(fwrite.o) \
	$(LIBRARY)(getc.o) \
	$(LIBRARY)(getchar.o) \
	$(LIBRARY)(gets.o) \
	$(LIBRARY)(icompute.o) \
	$(LIBRARY)(mktemp.o) \
	$(LIBRARY)(perror.o) \
	$(LIBRARY)(printf.o) \
	$(LIBRARY)(putc.o) \
	$(LIBRARY)(putchar.o) \
	$(LIBRARY)(puts.o) \
	$(LIBRARY)(remove.o) \
	$(LIBRARY)(rewind.o) \
	$(LIBRARY)(scanf.o) \
	$(LIBRARY)(setbuf.o) \
	$(LIBRARY)(setvbuf.o) \
	$(LIBRARY)(sprintf.o) \
	$(LIBRARY)(sscanf.o) \
	$(LIBRARY)(tmpfile.o) \
	$(LIBRARY)(tmpnam.o) \
	$(LIBRARY)(ungetc.o) \
	$(LIBRARY)(vfprintf.o) \
	$(LIBRARY)(vprintf.o) \
	$(LIBRARY)(vscanf.o) \
	$(LIBRARY)(vsprintf.o) \
	$(LIBRARY)(vsscanf.o) \
	$(LIBRARY)(fphook.o)

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(clearerr.o):	$(SRC)/clearerr.c
	$(CC1) $(SRC)/clearerr.c

$(LIBRARY)(data.o):	$(SRC)/data.c
	$(CC1) $(SRC)/data.c

$(LIBRARY)(doprnt.o):	$(SRC)/doprnt.c
	$(CC1) $(SRC)/doprnt.c

$(LIBRARY)(doscan.o):	$(SRC)/doscan.c
	$(CC1) $(SRC)/doscan.c

$(LIBRARY)(ecvt.o):	$(SRC)/ecvt.c
	$(CC1) $(SRC)/ecvt.c

$(LIBRARY)(fclose.o):	$(SRC)/fclose.c
	$(CC1) $(SRC)/fclose.c

$(LIBRARY)(feof.o):	$(SRC)/feof.c
	$(CC1) $(SRC)/feof.c

$(LIBRARY)(ferror.o):	$(SRC)/ferror.c
	$(CC1) $(SRC)/ferror.c

$(LIBRARY)(fflush.o):	$(SRC)/fflush.c
	$(CC1) $(SRC)/fflush.c

$(LIBRARY)(fgetc.o):	$(SRC)/fgetc.c
	$(CC1) $(SRC)/fgetc.c

$(LIBRARY)(fgetpos.o):	$(SRC)/fgetpos.c
	$(CC1) $(SRC)/fgetpos.c

$(LIBRARY)(fgets.o):	$(SRC)/fgets.c
	$(CC1) $(SRC)/fgets.c

$(LIBRARY)(fileno.o):	$(SRC)/fileno.c
	$(CC1) $(SRC)/fileno.c

$(LIBRARY)(fillbuf.o):	$(SRC)/fillbuf.c
	$(CC1) $(SRC)/fillbuf.c

$(LIBRARY)(flushbuf.o):	$(SRC)/flushbuf.c
	$(CC1) $(SRC)/flushbuf.c

$(LIBRARY)(fopen.o):	$(SRC)/fopen.c
	$(CC1) $(SRC)/fopen.c

$(LIBRARY)(fprintf.o):	$(SRC)/fprintf.c
	$(CC1) $(SRC)/fprintf.c

$(LIBRARY)(fputc.o):	$(SRC)/fputc.c
	$(CC1) $(SRC)/fputc.c

$(LIBRARY)(fputs.o):	$(SRC)/fputs.c
	$(CC1) $(SRC)/fputs.c

$(LIBRARY)(fread.o):	$(SRC)/fread.c
	$(CC1) $(SRC)/fread.c

$(LIBRARY)(freopen.o):	$(SRC)/freopen.c
	$(CC1) $(SRC)/freopen.c

$(LIBRARY)(fscanf.o):	$(SRC)/fscanf.c
	$(CC1) $(SRC)/fscanf.c

$(LIBRARY)(fseek.o):	$(SRC)/fseek.c
	$(CC1) $(SRC)/fseek.c

$(LIBRARY)(fsetpos.o):	$(SRC)/fsetpos.c
	$(CC1) $(SRC)/fsetpos.c

$(LIBRARY)(ftell.o):	$(SRC)/ftell.c
	$(CC1) $(SRC)/ftell.c

$(LIBRARY)(fwrite.o):	$(SRC)/fwrite.c
	$(CC1) $(SRC)/fwrite.c

$(LIBRARY)(getc.o):	$(SRC)/getc.c
	$(CC1) $(SRC)/getc.c

$(LIBRARY)(getchar.o):	$(SRC)/getchar.c
	$(CC1) $(SRC)/getchar.c

$(LIBRARY)(gets.o):	$(SRC)/gets.c
	$(CC1) $(SRC)/gets.c

$(LIBRARY)(icompute.o):	$(SRC)/icompute.c
	$(CC1) $(SRC)/icompute.c

$(LIBRARY)(mktemp.o):	$(SRC)/mktemp.c
	$(CC1) $(SRC)/mktemp.c

$(LIBRARY)(perror.o):	$(SRC)/perror.c
	$(CC1) $(SRC)/perror.c

$(LIBRARY)(printf.o):	$(SRC)/printf.c
	$(CC1) $(SRC)/printf.c

$(LIBRARY)(putc.o):	$(SRC)/putc.c
	$(CC1) $(SRC)/putc.c

$(LIBRARY)(putchar.o):	$(SRC)/putchar.c
	$(CC1) $(SRC)/putchar.c

$(LIBRARY)(puts.o):	$(SRC)/puts.c
	$(CC1) $(SRC)/puts.c

$(LIBRARY)(remove.o):	$(SRC)/remove.c
	$(CC1) $(SRC)/remove.c

$(LIBRARY)(rewind.o):	$(SRC)/rewind.c
	$(CC1) $(SRC)/rewind.c

$(LIBRARY)(scanf.o):	$(SRC)/scanf.c
	$(CC1) $(SRC)/scanf.c

$(LIBRARY)(setbuf.o):	$(SRC)/setbuf.c
	$(CC1) $(SRC)/setbuf.c

$(LIBRARY)(setvbuf.o):	$(SRC)/setvbuf.c
	$(CC1) $(SRC)/setvbuf.c

$(LIBRARY)(sprintf.o):	$(SRC)/sprintf.c
	$(CC1) $(SRC)/sprintf.c

$(LIBRARY)(sscanf.o):	$(SRC)/sscanf.c
	$(CC1) $(SRC)/sscanf.c

$(LIBRARY)(tmpfile.o):	$(SRC)/tmpfile.c
	$(CC1) $(SRC)/tmpfile.c

$(LIBRARY)(tmpnam.o):	$(SRC)/tmpnam.c
	$(CC1) $(SRC)/tmpnam.c

$(LIBRARY)(ungetc.o):	$(SRC)/ungetc.c
	$(CC1) $(SRC)/ungetc.c

$(LIBRARY)(vfprintf.o):	$(SRC)/vfprintf.c
	$(CC1) $(SRC)/vfprintf.c

$(LIBRARY)(vprintf.o):	$(SRC)/vprintf.c
	$(CC1) $(SRC)/vprintf.c

$(LIBRARY)(vscanf.o):	$(SRC)/vscanf.c
	$(CC1) $(SRC)/vscanf.c

$(LIBRARY)(vsprintf.o):	$(SRC)/vsprintf.c
	$(CC1) $(SRC)/vsprintf.c

$(LIBRARY)(vsscanf.o):	$(SRC)/vsscanf.c
	$(CC1) $(SRC)/vsscanf.c

$(LIBRARY)(fphook.o): 	/usr/src/lib/fphook/fphook.c
	$(CC1) /usr/src/lib/fphook/fphook.c

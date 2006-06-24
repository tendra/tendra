all: parse

parse: parse.adb ada_lex.ads ada_parse.adb
	gnatmake -v -g -gnatoa parse -bargs -A -largs -A

ada_lex.ads: ada_lex.l
	aflex -E ada_lex.l

ada_parse.adb: ada_parse.y
	ayacc 'File=>ada_parse.y Debug=>Off C_Lex=>On, Summary=>On Verbose=>On Error_Recovery=>On'

clean:
	rm -f *.o *.ali parse ada*.ad? *.verbose ada_parse.h *.lis b~parse.ad? b_parse.c

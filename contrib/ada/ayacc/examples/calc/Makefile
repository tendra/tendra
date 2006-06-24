all: driver

driver: driver.adb calc_lex.ads calc.adb
	gnatmake -v -g -gnatoa driver -bargs -A -largs -A

calc_lex.ads: calc_lex.l
	aflex -E calc_lex.l

calc.adb: calc.y
	ayacc 'File=>calc.y Debug=>Off C_Lex=>On Summary=>On Verbose=>On Error_Recovery=>On'

clean:
	rm -f *.o *.ali driver calc*.ad? *.verbose calc.h *.lis b~driver.ad? b_driver.c

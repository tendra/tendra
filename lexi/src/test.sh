#!/bin/sh

lexi -lC99 -a lexer.lxi lexer.lct t.c t.h
mv t.c t0.c 
mv t.h t0.h
./lexi -lC99 -a lexer.lxi lexer.lct t.c t.h
echo "Difference for C generated file from lexer "
diff -u t0.c t.c
echo "Difference for H generated file from lexer "
diff -u t0.h t.h

lexi -lC99 -a -t lct_lex_ -p lexi_lct_ lctlexer.lxi lctlexer.lct t.c t.h
mv t.c t0.c 
mv t.h t0.h
./lexi -lC99 -a -t lct_lex_ -p lexi_lct_ lctlexer.lxi lctlexer.lct t.c t.h
echo "Difference for C generated file from lctlexer "
diff -u t0.c t.c
echo "Difference for H generated file from lctlexer "
diff -u t0.h t.h

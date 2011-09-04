# $Id$

all:: efmt

clean::
	rm efmt

efmt: efmt.c ../error.c ../fmt.c
	${CC} -o efmt efmt.c ../error.c ../fmt.c -I..


# $Id$

all:: efmt

clean::
	rm efmt efmt.o


efmt: ../liberror.a efmt.o
	${CC} -o efmt efmt.o -L.. -lerror


../liberror.a:
	cd .. && ${MAKE} -f makefile.standalone liberror.a


# Makefile for lib/ip.
#
# Note: The oneC_sum.c file is not used if there is an assembly equivalent.

SRC=/usr/src/lib/ip
LIBRARY=$(NAME)
CC1=tcc -Ysystem -c -I$(SRC) -DNDEBUG

all: $(LIBRARY)

OBJECTS	= \
	$(LIBRARY)(ether_line.o) \
	$(LIBRARY)(ethera2n.o) \
	$(LIBRARY)(ethere2a.o) \
	$(LIBRARY)(etherh2n.o) \
	$(LIBRARY)(ethern2h.o) \
	$(LIBRARY)(getdomain.o) \
	$(LIBRARY)(gethnmadr.o) \
	$(LIBRARY)(gethostent.o) \
	$(LIBRARY)(gethostname.o) \
	$(LIBRARY)(getnetent.o) \
	$(LIBRARY)(getnetbyname.o) \
	$(LIBRARY)(getnetbyaddr.o) \
	$(LIBRARY)(getproto.o) \
	$(LIBRARY)(getprotoent.o) \
	$(LIBRARY)(getservent.o) \
	$(LIBRARY)(getsrvbyname.o) \
	$(LIBRARY)(getsrvbyport.o) \
	$(LIBRARY)(hton.o) \
	$(LIBRARY)(inet_addr.o) \
	$(LIBRARY)(inet_network.o) \
	$(LIBRARY)(inet_ntoa.o) \
	$(LIBRARY)(memcspn.o) \
	$(LIBRARY)(rcmd.o) \
	$(LIBRARY)(res_comp.o) \
	$(LIBRARY)(res_init.o) \
	$(LIBRARY)(res_mkquery.o) \
	$(LIBRARY)(res_query.o) \
	$(LIBRARY)(res_send.o) \
	$(LIBRARY)(strcasecmp.o) \

$(LIBRARY):	$(OBJECTS)
	aal cr $@ *.o
	rm *.o

$(LIBRARY)(ether_line.o):	$(SRC)/ether_line.c
	$(CC1) $(SRC)/ether_line.c

$(LIBRARY)(ethera2n.o):	$(SRC)/ethera2n.c
	$(CC1) $(SRC)/ethera2n.c

$(LIBRARY)(ethere2a.o):	$(SRC)/ethere2a.c
	$(CC1) $(SRC)/ethere2a.c

$(LIBRARY)(etherh2n.o):	$(SRC)/etherh2n.c
	$(CC1) $(SRC)/etherh2n.c

$(LIBRARY)(ethern2h.o):	$(SRC)/ethern2h.c
	$(CC1) $(SRC)/ethern2h.c

$(LIBRARY)(getdomain.o):	$(SRC)/getdomain.c
	$(CC1) $(SRC)/getdomain.c

$(LIBRARY)(gethnmadr.o):	$(SRC)/gethnmadr.c
	$(CC1) $(SRC)/gethnmadr.c

$(LIBRARY)(gethostent.o):	$(SRC)/gethostent.c
	$(CC1) $(SRC)/gethostent.c

$(LIBRARY)(gethostname.o):	$(SRC)/gethostname.c
	$(CC1) $(SRC)/gethostname.c

$(LIBRARY)(getnetent.o):	$(SRC)/getnetent.c
	$(CC1) $(SRC)/getnetent.c

$(LIBRARY)(getnetbyname.o):	$(SRC)/getnetbyname.c
	$(CC1) $(SRC)/getnetbyname.c

$(LIBRARY)(getnetbyaddr.o):	$(SRC)/getnetbyaddr.c
	$(CC1) $(SRC)/getnetbyaddr.c

$(LIBRARY)(getproto.o):	$(SRC)/getproto.c
	$(CC1) $(SRC)/getproto.c

$(LIBRARY)(getprotoent.o):	$(SRC)/getprotoent.c
	$(CC1) $(SRC)/getprotoent.c

$(LIBRARY)(getservent.o):	$(SRC)/getservent.c
	$(CC1) $(SRC)/getservent.c

$(LIBRARY)(getsrvbyname.o):	$(SRC)/getsrvbyname.c
	$(CC1) $(SRC)/getsrvbyname.c

$(LIBRARY)(getsrvbyport.o):	$(SRC)/getsrvbyport.c
	$(CC1) $(SRC)/getsrvbyport.c

$(LIBRARY)(hton.o):	$(SRC)/hton.c
	$(CC1) $(SRC)/hton.c

$(LIBRARY)(inet_addr.o):	$(SRC)/inet_addr.c
	$(CC1) $(SRC)/inet_addr.c

$(LIBRARY)(inet_network.o):	$(SRC)/inet_network.c
	$(CC1) $(SRC)/inet_network.c

$(LIBRARY)(inet_ntoa.o):	$(SRC)/inet_ntoa.c
	$(CC1) $(SRC)/inet_ntoa.c

$(LIBRARY)(memcspn.o):	$(SRC)/memcspn.c
	$(CC1) $(SRC)/memcspn.c

$(LIBRARY)(oneC_sum.o):	$(SRC)/oneC_sum.c
	$(CC1) $(SRC)/oneC_sum.c

$(LIBRARY)(rcmd.o):	$(SRC)/rcmd.c
	$(CC1) $(SRC)/rcmd.c

$(LIBRARY)(res_comp.o):	$(SRC)/res_comp.c
	$(CC1) $(SRC)/res_comp.c

$(LIBRARY)(res_init.o):	$(SRC)/res_init.c
	$(CC1) $(SRC)/res_init.c

$(LIBRARY)(res_mkquery.o):	$(SRC)/res_mkquery.c
	$(CC1) $(SRC)/res_mkquery.c

$(LIBRARY)(res_query.o):	$(SRC)/res_query.c
	$(CC1) $(SRC)/res_query.c

$(LIBRARY)(res_send.o):	$(SRC)/res_send.c
	$(CC1) $(SRC)/res_send.c

$(LIBRARY)(strcasecmp.o):	$(SRC)/strcasecmp.c
	$(CC1) $(SRC)/strcasecmp.c

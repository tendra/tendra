all:	sample
	./sample example.l

sample: example.adb sample.adb
	gnatmake -v -g -gnatao sample -bargs -A -largs -A

example.adb: example.l
	aflex example.l

clean:
	rm -f example*.ad? sample *.o *.ali b~sample.ad? b_sample.c

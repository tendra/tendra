MAKE_TDF = ../make_tdf/obj/src/make_tdf
DB = ../tdf/db/def_4_1.db

all: tdf_types.mli tdf_read.ml trans.byte

tdf_types.mli: tdf_types.mli.make_tdf
	$(MAKE_TDF) $(DB) $< $@

tdf_read.ml: tdf_read.ml.make_tdf
	$(MAKE_TDF) $(DB) $< $@

trans.byte: tdf_types.mli tdf_read.ml
	ocamlbuild trans.byte

clean:
	rm -rf tdf_types.mli tdf_read.ml _build trans.byte
	rm -rf tests/*.t tests/*.ll tests/a.out

check: trans.byte
	cd tests; ./compile.sh test_001.c && ./a.out
	@echo Check success!

MAKE_TDF = ../make_tdf/obj/src/make_tdf
DB = ../tdf/db/def_4_1.db

all: tdf_types.mli tdf_read.ml

tdf_types.mli: tdf_types.mli.make_tdf
	$(MAKE_TDF) $(DB) $< $@
	-ocamlc -g -c $@

tdf_read.ml: tdf_read.ml.make_tdf
	$(MAKE_TDF) $(DB) $< $@
	-ocamlc -g -c tdf_read.mli $@

clean:
	rm -rf tdf_types.mli tdf_read.ml a.out *.cmo *.cmi

a.out: all
	ocamlc -g tdf_types.mli tdf_read.mli tdf_read.ml test.ml

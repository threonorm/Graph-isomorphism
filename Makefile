projet:
	gcc -o isomorphisme -O2 main.c isomorphism.c colors.c structs.c graph_gen.c connexity.c graph_io.c
	ocamlc random_iso.ml -o random_iso

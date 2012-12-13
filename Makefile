projet:
	gcc -o isomorphisme -Wall -O2 main.c isomorphism.c colors.c structs.c
	ocamlc random_iso.ml -o random_iso

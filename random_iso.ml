(*Authors : Bréhard Florent - Bourgeat Thomas*)
(*This file is used to generate random isomorph graphs.*)

open Random

(*---------To make Random graph-----*)

let rec appartient e = function
  |t::q-> if t=e then true else appartient e q
  |[]-> false

 let random_graph n =
  let graph = Array.make n [] in
  let compt = ref 0 in
  let a= ref 0 in
  let b= ref 0 in
  while (!compt < (100*n)) do
   a:=(int n);
   b:= !a;
   while (!b = !a) do (b:= (int n);) done;
   if not(appartient (!a) (graph.(!b))) 
   then (incr compt;
        graph.(!a)<- (!b)::(graph.(!a));
        graph.(!b)<- (!a)::(graph.(!b)))
  done;  
  graph

(*-----Basic functions -------*)
let swap i j tab = 
 let aux = tab.(i) in
 tab.(i)<-tab.(j);
 tab.(j)<-aux


let permut n mix =
	let table = Array.make (n) 0 in
	for i=0 to n-1 do
	table.(i)<- i
	done;
	for i=0 to mix do
		let a = (int n) in
		let b= (int n) in
		swap a b table;
	done;
	(fun i-> table.(i))

let rec permut_list f = function
	|t::q-> (f t)::(permut_list f q)
	|[]->[]

(*-------To create the isomorph graph, by permutation f-------*)

let iso_graph f g = 
	let res = Array.make (Array.length g) [] in
	for i=0 to (Array.length g -1) do
	res.(f (i))<-permut_list f (g.(i))
	done;
	res

(*---------Printing functions -------*)

let rec write_list f l= match l with
	|t::q::r-> Format.fprintf f "%d " t; write_list f (q::r)
	|t::q-> Format.fprintf f "%d\n" t
	|_-> assert(false)

let write_graph f graph = 
  let size = Array.length graph in
  Format.fprintf f "%d\n" (size); 
  for i=0 to size -1 do
    let k = List.length graph.(i) in
    Format.fprintf f "%d " k;
    if k <> 0 
      then write_list f (graph.(i))
      else Format.fprintf f "\n"
  done
  
(*----------Body -------------------*)

let main ()=
  if (Array.length (Sys.argv)) <2 
  then failwith("Please enter the size of random graph")
  else 
    let size = int_of_string(Sys.argv.(1)) in
    let a= open_out "graph1" in
    let b= open_out "graph2" in
    let f1= Format.formatter_of_out_channel a in
    let f2= Format.formatter_of_out_channel b in 
    Random.self_init ();
    let graph = random_graph size in
    let perm = permut size size in
    let graph_iso = iso_graph perm graph in
    write_graph f2 graph_iso;
    Format.fprintf f2 "@?";
    write_graph f1 graph;
    Format.fprintf f1 "@?";
    close_out a

let () = main ()

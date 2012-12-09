(*Authors : Bréhard Florent - Bourgeat Thomas*)
(*This file is used to generate random isomorph graphs.*)

open Random


let random_graph n =
  let graph = Array.make n [] in
  let rec list_alea k = match k with
    |0-> []
    |_-> (int(k)+1)::(list_alea (k-1))
  in
  for i=0 to n-1 do
    graph.(i)<- list_alea (int n);
  done;  
  graph

let rec write_list f l= match l with
|t::q::r-> Format.fprintf f "%d " t; write_list f (q::r)
|t::q-> Format.fprintf f "%d\n" t
|_-> assert(false)

let write_graph f graph = 
  let size = Array.length graph in
  Format.fprintf f "%d\n" size; 
  for i=0 to size -1 do
    let k = List.length graph.(i) in
    Format.fprintf f "%d " k;
    if k <> 0 
      then write_list f (graph.(i))
      else Format.fprintf f "\n"
  done
  

let main ()=
  if (Array.length (Sys.argv)) <2 
  then failwith("Please enter the size of random graph")
  else 
    let size = int_of_string(Sys.argv.(1)) in
    let a= open_out "graph1" in
    let f = Format.formatter_of_out_channel a in
    Random.self_init ();
    write_graph f (random_graph size);
    Format.fprintf f "@?";
    close_out a

let () = main ()

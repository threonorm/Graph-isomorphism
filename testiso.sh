#!/bin/sh
for i in `seq 1 100`;
do
    echo $i;
    echo "`./isomorphisme graph1$i graph2$i` $(($i*10))" > $i;
done;
exit 0


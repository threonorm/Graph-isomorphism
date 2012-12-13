#!/bin/sh
for i in `seq 1 100`;
do
    echo $i;
    echo "`./isomorphisme tests/graph1$i tests/graph2$i` $(($i*10))" > $i;
done;
exit 0


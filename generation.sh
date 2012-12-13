#!/bin/sh
for i in `seq 1 10`;
do
    echo $i;
    `./random_iso 1000 $((100*$i)) $i`  ;
done;
exit 0


#!/bin/sh
for i in `seq 2 100`;
do
    echo $i;
    `./random_iso 2000 $((100*$i)) $i`;
done;
exit 0


#!/bin/sh
# http://shellscript.sunone.me/for.html
# http://d.hatena.ne.jp/leetmikeal/20130117/1358423717
 
for i in `seq 1 10`
do
    ./a.out >> log
done
cat log | awk '{m+=$1} END{print m/NR;}'

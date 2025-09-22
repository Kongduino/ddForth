#!/bin/sh
for x in `ls test*fs`
do
    echo "./ddforth -e $x"
    ../bin/ddforth -e $x
done


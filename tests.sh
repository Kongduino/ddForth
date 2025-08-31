#!/bin/sh
    for x in `ls test*fs`
    do
    echo "./ddforth -f $x"
    ./ddforth -f $x
    done


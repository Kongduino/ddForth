#!/bin/sh
    for x in `ls test*fs`
    do
    ./ddforth -f $x
    done


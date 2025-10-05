clear
0 1 2 3 4 5 6 7 8 9 10 s" tag" varray
s" tag" DUP LEN> 0 DO   ." Cell " DUP I I . ." = " swap IX> . CR loop
s" tag" len> DUP 2 / 0 DO
i s" tag" ix>
10 i - 1 - s" tag" IX>
I s" tag" >ix
10 i - 1 - s" tag" >IX
LOOP
CR ." REVERSE\n============\n"
s" tag" DUP LEN> 0 DO   ." Cell " DUP I I . ." = " swap IX> . CR loop


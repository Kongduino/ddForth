: showTagada s" tagada" LEN> 0 do I dup ." cell " . ." = " s" tagada" IX> . cr LOOP CR ;
1 10 s" tagada" array CR ( create an INT array of 10 cells, value 1 )
showTagada
10 0 do I I s" tagada" >IX LOOP  CR
showTagada
10 0 do I 2 * I s" tagada" >IX LOOP  CR
showTagada
33 s" tagada" IX+ 11 s" tagada" +IX
showTagada
: nROT> 0 DO DUP ROT> LOOP CLEAR ;
: n<ROT 0 DO DUP <ROT LOOP CLEAR ;
1 10 s" TT" array s" TT" alist 13 3 s" TT" >IX 3 s" TT" IX> . CR s" TT" alist CR
." <ROT Left rot, ie UP, x 3:" CR
s" TT" 3 n<ROT s" TT" alist CR
." ROT> Right rot, ie DOWN, x 6:" CR
s" TT" 6 nROT>
s" TT" alist

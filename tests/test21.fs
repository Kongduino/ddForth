0 10 s" TABLEAU" array
." Tableau:" cr
10 0 DO randomi 128 MOD I s" TABLEAU" >IX LOOP
s" TABLEAU" alist
: tableauAccu 0 DO I s" TABLEAU" IX> + LOOP ;
0 ( original total ) 5 ( number of "days" ) tableauAccu . CR

0 10 s" TABLEAU" array
." Tableau:" cr
10 0 DO randomi 128 MOD I s" TABLEAU" >IX LOOP
CR s" TABLEAU" alist
: accumul VAR myarray 0 SWAP 0 DO I myarray @ IX> + LOOP ;
10 s" TABLEAU" accumul ." Total: " DUP . CR
5 s" TABLEAU" accumul ." Subtotal: " DUP . cr
." Remainder: " - . cr

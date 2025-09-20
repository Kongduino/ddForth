clear s" Player3 Player2 Player1" SSPLIT s" Players" VARRAY
s" Players" len> DUP . ." players" CR 0 DO 0 4 I s" Players" IX> array LOOP
: SCORE s" Players" IX> >IX ;
0 0 0 3 s" Scores" VARRAY 
-1 VAR scoreGagnant
-1 VAR gagnant
0 BEGIN
  ." \ * Player " DUP 1 + .
  4 0 DO
    RANDOM 6 MOD OVER I SWAP SCORE
  LOOP
  DUP DUP s" Players" IX> ASUM ." Total score: " DUP DUP . CR
  rot swap s" Scores" >IX .S
  DUP scoreGagnant @ > IF
    ." yes " scoreGagnant swap .S !
    DUP gagnant swap !
  then ." no " else
  1 + DUP 3 =
UNTIL
s" Scores" alist

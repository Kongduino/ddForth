clear s" Player3 Player2 Player1" SSPLIT s" Players" VARRAY
s" Players" len> DUP . ." players" CR 0 DO 0 4 I s" Players" IX> array LOOP
: SCORE s" Players" IX> >IX ;
0 BEGIN
  ." \ * Player " DUP 1 + .
  4 0 DO
    RANDOM 6 MOD OVER I SWAP SCORE
  LOOP
  DUP s" Players" IX> ASUM ." Total score: " . CR
  1 + DUP 3 =
UNTIL
( testing imbricated DO...LOOP with EMIT )
CR ." OUTSIDE LOOP" CR
-10 BEGIN
  DUP . DUP -1 * CR
  ." > INSIDE LOOP" CR
  BEGIN
    46 EMIT 1 - DUP 0=
  UNTIL
  DROP CR
  1 + DUP
  0=
UNTIL
. .S CR

: fx DUP 1 >  IF DUP 1 - fx * THEN ELSE ;
12 3 DO I fx . LOOP CR
12 1 DO
  s" ." I' I 1 + - MULTSTR cs
  I DUP INTSTR cs ." ! = " fx . CR
LOOP CR
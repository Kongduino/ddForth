0 10 0 DO
  DUP .
  ." ===> "
  1 + DUP DUP 10 SWAP
  DO
    DUP . 1 +
  LOOP
  DROP CR
LOOP
30 0 DO i -1 * 1 - LOOP 30 .S

: shuffle DUP random swap mod swap DUP random swap mod rot rot dup pick rot rot dup pick rot place swap place ;

10000 0 do shuffle loop s" MyArray" VARRAY
s" MyArray" DUP LEN> 0 DO
  ." Cell " DUP I I . ." = " swap IX> . CR
loop
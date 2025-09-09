s" Hello!" LENSTR 0 DO 0 I 1 + SUBSTR .s CR LOOP CLEAR .S CR
s" Hello!" LENSTR 0 DO LENSTR 1 - I - MIDSTR EMIT LOOP CLEAR CR .S CR
s" Hello!" s" (123)" .S >s s" (456)" .S s< .S .s CLEAR .S CR
s" HeLlO" DUP DUP ." Original string: " .s CR ." UPPERCASE: " UPPERSTR .s CR ." lowercase: " LOWERSTR .s CR

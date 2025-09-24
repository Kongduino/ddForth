s" Hello!" LENSTR 0 DO 0 I 1 + SUBSTR cs CR LOOP CLEAR CR
s" Hello!" LENSTR 0 DO LENSTR 1 - I - MIDSTR EMIT LOOP CLEAR CR
s" Hello!" s" (123)" +STR s" (456)" STR+ cs CLEAR CR
s" HeLlO" DUP DUP ." Original string: " cs CR ." UPPERCASE: " UPPERSTR cs CR ." lowercase: " LOWERSTR cs CR
s" +..." DUP ." .S " cs RANDOM 10 MOD 1 + DUP . ." times as a string, add a + at the end and print:" CR MULTSTR s" +" STR+ cs CR
s" \tfff  " DUP cs 9 . CR LSTRIPSTR DUP cs 10 . CR RSTRIPSTR cs 11 . CR
s" \tfff  " DUP cs 0 . CR STRIPSTR DUP cs 0 . CR
10 0 DO s" Ligne n° " I INTSTR STR+ cs CR LOOP
s" 10" STRINT 10 + . CR
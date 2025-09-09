s" Hello!" LENSTR 0 DO 0 I 1 + SUBSTR .s CR LOOP CLEAR CR
s" Hello!" LENSTR 0 DO LENSTR 1 - I - MIDSTR EMIT LOOP CLEAR CR
s" Hello!" s" (123)" >s s" (456)" s< .s CLEAR CR
s" HeLlO" DUP DUP ." Original string: " .s CR ." UPPERCASE: " UPPERSTR .s CR ." lowercase: " LOWERSTR .s CR
s" +..." DUP ." Stack " .s RANDOM 10 MOD 1 + DUP . ." times as a string, add a + at the end and print:" CR MULTSTR s" +" s< .s CR
s" \tfff  " DUP .s 9 . CR LSTRIPSTR DUP .s 10 . CR RSTRIPSTR .s 11 . CR
s" \tfff  " DUP .s 0 . CR STRIPSTR DUP .s 0 . CR
10 0 DO s" Ligne n° " I INTSTR s< .s CR LOOP
s" 10" STRINT 10 + . CR
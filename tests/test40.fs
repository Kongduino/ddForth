s" No Error|Couldn't initialize curl!|No URL!|Couldn't connect to URL!" 124 csplit 
s" errorMessages" VARRAY

clean
s" http://tagada:8000/data.txt" CURLGETM CR CR CR
DUP 0 <= IF ." Error: " 3 + s" errorMessages" IX> . ." . No data loaded!\n\n" EXIT THEN ELSE CR
 ( ok )
10 csplit
DUP ." Line count: " . CR
DUP 0 DO
	1 i posxy i pick ." Line " i . ." \t"
	9 csplit
	drop swap . ." : " .
LOOP CLEAR CR

# test40(a) test

## Server

Run a Python server: `python3 -m http.server`. It will serve the `data.txt` file.

## Test

Run the test. `test40.fs` will fail, and show the proper error. `test40a` will (should) work, and display the DHT data.


```
% ddforth -f tests/test40a.fs
ddForth v1.2.52
 • Read: s" No Error|Couldn't initialize curl!|No URL!|Couldn't connect to URL!" 124 csplit 
 • Read: s" errorMessages" VARRAY
 • Read: 
 • Read: s" http://127.0.0.1:8000/data.txt" CURLGETM CR CR CR
 • Read: DUP 0 <= IF ." Error: " 3 + s" errorMessages" IX> . ." . No data loaded!\n\n" EXIT THEN DROP ELSE CR
 • Read:  ( ok )
 • Read: 10 csplit
 • Read: DUP ." Line count: " . CR
 • Read: DUP 0 DO
 • Read: 	i pick ." Line " i . ." \t"
 • Read: 	9 csplit
 • Read: 	drop swap . ." : " . CR
 • Read: LOOP CLEAR CR
Read: 13 lines, chunks: 62




Line count: 2 
Line 0 	Temp: 32.5
Line 1 	Humidity: 88
```
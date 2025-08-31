# ddForth

## REGULAR VERSION


```forth
> make clean; make
rm -f ddforth ddforth_debug
g++ -O3 ddforth.cpp -o ddforth
> ./tests.sh
./ddforth -f test.fs
Running code:
	." \"中文也行\"" CR ." ¥Á¥!"
"中文也行" 
¥Á¥! 

./ddforth -f test0.fs
Running code:
	1 2 3 4 5 .S DUP ROT + + / * + 13.22 .S + . CR

+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| 4	|
| 2	| INT.	| 3	|
| 3	| INT.	| 2	|
| 4	| INT.	| 1	|
+-----------------------+

+-----------------------+
| 0	| FLOAT	| 13.220	|
| 1	| INT.	| 1	|
+-----------------------+
14.220000 


./ddforth -f test1.fs
Running code:
	CR ." OUTSIDE LOOP" CR -10 BEGIN DUP . DUP -1 * CR ." > INSIDE LOOP" CR BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP CR 1 + DUP 0= UNTIL . .S CR

OUTSIDE LOOP 
-10 
> INSIDE LOOP 
..........
-9 
> INSIDE LOOP 
.........
-8 
> INSIDE LOOP 
........
-7 
> INSIDE LOOP 
.......
-6 
> INSIDE LOOP 
......
-5 
> INSIDE LOOP 
.....
-4 
> INSIDE LOOP 
....
-3 
> INSIDE LOOP 
...
-2 
> INSIDE LOOP 
..
-1 
> INSIDE LOOP 
.
0 Stack empty! 


./ddforth -f test2.fs
Running code:
	BASE .S 16 ! A5 BASE A ! . CR -13 DUP DUP .S . U. HEX . DEC CR BASE ? .V CR

+-----------------------+
| 0	| INT.	| 0	|
+-----------------------+
165 

+-----------------------+
| 0	| INT.	| -13	|
| 1	| INT.	| -13	|
| 2	| INT.	| -13	|
+-----------------------+
-13 4294967283 fffffff3 
10 
+-------------------------------+
| Num	| Name	| Addr	| Value	|
+-------------------------------+
| 0	| BASE	| 0	|10	|
| 1	| VER.	| 1	|1051	|
+-------------------------------+



./ddforth -f test3.fs
Running code:
	1 2 OVER 1.2 2.1 OVER .S ." Loop and add" CR BEGIN DUP . + DEPTH 1 = UNTIL . CR .S

+-----------------------+
| 0	| FLOAT	| 1.200	|
| 1	| FLOAT	| 2.100	|
| 2	| FLOAT	| 1.200	|
| 3	| INT.	| 1	|
| 4	| INT.	| 2	|
| 5	| INT.	| 1	|
+-----------------------+
Loop and add 
1.200000 3.300000 4.500000 5.500000 7.500000 8.500000 
Stack empty! 

./ddforth -f test4.fs
Running code:
	." Fact\x7e\t\x7eTest" CR 3 BEGIN DUP DUP . ." ! =" FACT U. CR 1 + DUP 10 = UNTIL CR
Fact~	~Test 
3 ! = 6 
4 ! = 24 
5 ! = 120 
6 ! = 720 
7 ! = 5040 
8 ! = 40320 
9 ! = 362880 

./ddforth -f test5.fs
Running code:
	-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR
-10 ..........-9 .........-8 ........-7 .......-6 ......-5 .....-4 ....-3 ...-2 ..-1 .0 Stack empty! 

./ddforth -f test6.fs
Running code:
	: ++ + + ; 1 1 1 .S ++ . CR

+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| 1	|
+-----------------------+
3 


./ddforth -f test7.fs
Running code:
	11 CONST TAGADA 12 VAR TOGODO TOGODO TAGADA .S @ 3 + ! TOGODO ? CR

+-----------------------+
| 0	| INT.	| 256	|
| 1	| INT.	| 2	|
+-----------------------+
14 


./ddforth -f test8.fs
Running code:
	12.12 CONST GAG 21.21 VAR GOG .V GOG GAG @ GOG @ + .S ! .S .V GOG ? CR

+---------------------------------------+
| Num	| Name		| Addr	| Value	|
+---------------------------------------+
| 0/2	| BASE		| 0	|10	|
| 1/2	| VER.		| 1	|1051	|
+---------------------------------------+
| 0/1	| GOG		| 128	|21.21	|
+---------------------------------------+
| 0/1	| GAG		| 384	|12.12	|
+---------------------------------------+

+-----------------------+
| 0	| FLOAT	| 33.330	|
| 1	| INT.	| 128	|
+-----------------------+
Stack empty! 
+---------------------------------------+
| Num	| Name		| Addr	| Value	|
+---------------------------------------+
| 0/2	| BASE		| 0	|10	|
| 1/2	| VER.		| 1	|1051	|
+---------------------------------------+
| 0/1	| GOG		| 128	|33.33	|
+---------------------------------------+
| 0/1	| GAG		| 384	|12.12	|
+---------------------------------------+
33.329998 

```

## DEBUG VERSION

(TL,DR: Boring stuff, See [debug_log.txt](debug_log.txt))

```sh
for x in `ls test*fs`;do;echo "./ddforth_debug  -f $x";./ddforth_debug  -f $x;done > debug_log.txt 
```

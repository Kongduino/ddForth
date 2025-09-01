# ddForth

A minimal implementation of the Forth language in (mostly) C++. When I was a kid – a looooong time ago: the book I still have is based on FORTH-79... – I was fascinated by Forth, and RPN in general. I tried a few times, with various (lack of) success to write my own. Recently I decided to give it another go.

Surprisingly, it went well, beyond expectations, and I can run quite a few of the examples in my book. So I decided to keep pushing. I runs on my computer, as they say, which happens to be a Macbook Pro with an Apple M4 Pro CPU (and a 2018 Mac Mini Intel Core 7!). The compiled binary is small (110 KB on ARM, 85 KB on Intel).

Run `./ddforth "WORDS"` to get the list of words that have been implemented.


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

./ddforth -f test01.fs
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


./ddforth -f test02.fs
Running code:
	BASE .S 16 ! A5 BASE A ! . CR -13 DUP DUP .S . U. HEX . DEC CR BASE ? .V CR

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
+-----------------------+
165 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -13	|
| 1	| INT.	| -13	|
| 2	| INT.	| -13	|
+-----------------------+
-13 4294967283 fffffff3 
10 
+---------------------------------------+
| Num	| Name		| Addr	| Value	|
+---------------------------------------+
| 0/2	| BASE		| 0	|10	|
| 1/2	| VER.		| 1	|1051	|
+---------------------------------------+
+---------------------------------------+



./ddforth -f test03.fs
Running code:
	1 2 OVER 1.2 2.1 OVER .S ." Loop and add" CR BEGIN DUP . + DEPTH 1 = UNTIL . CR .S


	dataStack.size()	6	myInts	3	myFloats	3	myStrings	0
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

./ddforth -f test04.fs
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



./ddforth -f test05.fs
Running code:
	-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR
-10 ..........-9 .........-8 ........-7 .......-6 ......-5 .....-4 ....-3 ...-2 ..-1 .0 Stack empty! 


./ddforth -f test06.fs
Running code:
	: ++ + + ; 1 1 1 .S ++ . CR

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| 1	|
+-----------------------+
3 


./ddforth -f test07.fs
Running code:
	11 CONST TAGADA 12 VAR TOGODO TOGODO TAGADA .S @ 3 + ! TOGODO ? CR

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 256	|
| 1	| INT.	| 2	|
+-----------------------+
14 


./ddforth -f test08.fs
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

	dataStack.size()	2	myInts	1	myFloats	1	myStrings	0
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


./ddforth -f test09.fs
Running code:
	-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR
-10 ..........-9 .........-8 ........-7 .......-6 ......-5 .....-4 ....-3 ...-2 ..-1 .0 Stack empty! 


./ddforth -f test10.fs
Running code:
	0 10 0 DO DUP . ." ===> " 1 + DUP DUP 10 SWAP DO DUP . 1 + LOOP DROP CR LOOP

0 ===>  1 2 3 4 5 6 7 8 9 
1 ===>  2 3 4 5 6 7 8 9 
2 ===>  3 4 5 6 7 8 9 
3 ===>  4 5 6 7 8 9 
4 ===>  5 6 7 8 9 
5 ===>  6 7 8 9 
6 ===>  7 8 9 
7 ===>  8 9 
8 ===>  9 
9 ===>  10 


./ddforth -f test11.fs
Running code:
	CR 5 0 DO I . 5 0 DO I . LOOP CR LOOP

0 0 1 2 3 4 
1 0 1 2 3 4 
2 0 1 2 3 4 
3 0 1 2 3 4 
4 0 1 2 3 4 

```

## DEBUG VERSION

(TL,DR: Boring stuff, See [debug_log.txt](debug_log.txt))

```sh
for x in `ls test*fs`;do;echo "./ddforth_debug  -f $x";./ddforth_debug  -f $x;done > debug_log.txt 
```

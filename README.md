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
	BASE 16 ! A5 BASE A ! . CR -13 DUP DUP .S . U. HEX . DEC CR BASE ? . CR
165 

+-----------------------+
| 0	| INT.	| -13	|
| 1	| INT.	| -13	|
| 2	| INT.	| -13	|
+-----------------------+
-13 4294967283 fffffff3 
10 


./ddforth -f test3.fs
Running code:
	1 2 .S OVER .S CR 1.2 2.1 .S OVER .S CR + + + + DROP .S

+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 1	|
+-----------------------+

+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 2	|
| 2	| INT.	| 1	|
+-----------------------+


+-----------------------+
| 0	| FLOAT	| 2.100	|
| 1	| FLOAT	| 1.200	|
| 2	| INT.	| 1	|
| 3	| INT.	| 2	|
| 4	| INT.	| 1	|
+-----------------------+

+-----------------------+
| 0	| FLOAT	| 1.200	|
| 1	| FLOAT	| 2.100	|
| 2	| FLOAT	| 1.200	|
| 3	| INT.	| 1	|
| 4	| INT.	| 2	|
| 5	| INT.	| 1	|
+-----------------------+


+-----------------------+
libc++abi: terminating due to uncaught exception of type std::out_of_range: vector
| 0	| INT.	| ./tests.sh: line 2: 29797 Abort trap: 6           ./ddforth -f $x
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
```

## DEBUG VERSION

(TL,DR: Boring stuff)

```
> make clean; make debug
rm -f ddforth ddforth_debug
g++ -O3 -DDEBUG ddforth.cpp -o ddforth_debug
> for x in `ls test*fs`;do;echo "./ddforth_debug  -f $x";./ddforth_debug  -f $x;done
./ddforth_debug  -f test.fs
init Adding word 0= with `0 =`
Running code:
	." \"中文也行\"" CR ." ¥Á¥!"
."inside string
 * Adding `."`
中文也行Ending "
ss: "中文也行""
CR * Adding `CR`
."inside string
 * Adding `."`
¥Á¥!Ending "
ss: ¥Á¥!"

[...]

See debug_log.txt


evaluating 'CR' executionPointer: 19
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9 	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19*	| CR	|

```

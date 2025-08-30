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

Evaluating:
." "中文也行"" CR ." ¥Á¥!" 
Stack empty! 
evaluating '."' executionPointer: 0
0*	| ."	|
1 	| "中文也行""	|
2 	| CR	|
3 	| ."	|
4 	| ¥Á¥!"	|

evaluating '"中文也行""' executionPointer: 1
0 	| ."	|
1*	| "中文也行""	|
2 	| CR	|
3 	| ."	|
4 	| ¥Á¥!"	|
"中文也行" 
evaluating 'CR' executionPointer: 2
0 	| ."	|
1 	| "中文也行""	|
2*	| CR	|
3 	| ."	|
4 	| ¥Á¥!"	|


evaluating '."' executionPointer: 3
0 	| ."	|
1 	| "中文也行""	|
2 	| CR	|
3*	| ."	|
4 	| ¥Á¥!"	|

evaluating '¥Á¥!"' executionPointer: 4
0 	| ."	|
1 	| "中文也行""	|
2 	| CR	|
3 	| ."	|
4*	| ¥Á¥!"	|
¥Á¥! 

./ddforth_debug  -f test0.fs
init Adding word 0= with `0 =`
Running code:
	1 2 3 4 5 .S DUP ROT + + / * + 13.22 .S + . CR
1 * Adding `1`
2 * Adding `2`
3 * Adding `3`
4 * Adding `4`
5 * Adding `5`
.S * Adding `.S`
DUP * Adding `DUP`
ROT * Adding `ROT`
+ * Adding `+`
+ * Adding `+`
/ * Adding `/`
* * Adding `*`
+ * Adding `+`
13.22 * Adding `13.22`
.S * Adding `.S`
+ * Adding `+`
. * Adding `.`
CR • Adding `CR`

Evaluating:
1 2 3 4 5 .S DUP ROT + + / * + 13.22 .S + . CR 
Stack empty! 
evaluating '1' executionPointer: 0
0*	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '2' executionPointer: 1
0 	| 1	|
1*	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
lookupUC 2 0= isInteger/10/2 2 is an int 2

evaluating '3' executionPointer: 2
0 	| 1	|
1 	| 2	|
2*	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
lookupUC 3 0= isInteger/10/3 3 is an int 3

evaluating '4' executionPointer: 3
0 	| 1	|
1 	| 2	|
2 	| 3	|
3*	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
lookupUC 4 0= isInteger/10/4 4 is an int 4

evaluating '5' executionPointer: 4
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4*	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
lookupUC 5 0= isInteger/10/5 5 is an int 5

evaluating '.S' executionPointer: 5
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5*	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|

	dataStack.size()	5	myInts	5	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| 4	|
| 2	| INT.	| 3	|
| 3	| INT.	| 2	|
| 4	| INT.	| 1	|
+-----------------------+

evaluating 'DUP' executionPointer: 6
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6*	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|

evaluating 'ROT' executionPointer: 7
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7*	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
handleSWAP: dataStack.size() 6 intCounter 6 userIntegers.size() 6 
evaluating '+' executionPointer: 8
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8*	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
2 INTs 
evaluating '+' executionPointer: 9
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9*	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
2 INTs 
evaluating '/' executionPointer: 10
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10*	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
2 INTs 
evaluating '*' executionPointer: 11
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11*	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
2 INTs 
evaluating '+' executionPointer: 12
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12*	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
2 INTs 
evaluating '13.22' executionPointer: 13
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13*	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|
lookupUC 13.22 0= isInteger/10/13.22 13.22 is not an int.
isFloat: 13.22? 13.22 is an int 5

evaluating '.S' executionPointer: 14
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14*	| .S	|
15 	| +	|
16 	| .	|
17 	| CR	|

	dataStack.size()	2	myInts	1	myFloats	1	myStrings	0
+-----------------------+
| 0	| FLOAT	| 13.220	|
| 1	| INT.	| 1	|
+-----------------------+

evaluating '+' executionPointer: 15
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15*	| +	|
16 	| .	|
17 	| CR	|
1 INT 1 FLOAT 
evaluating '.' executionPointer: 16
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16*	| .	|
17 	| CR	|
handlePRINT: dataStack.size() 1 14.220000 
evaluating 'CR' executionPointer: 17
0 	| 1	|
1 	| 2	|
2 	| 3	|
3 	| 4	|
4 	| 5	|
5 	| .S	|
6 	| DUP	|
7 	| ROT	|
8 	| +	|
9 	| +	|
10 	| /	|
11 	| *	|
12 	| +	|
13 	| 13.22	|
14 	| .S	|
15 	| +	|
16 	| .	|
17*	| CR	|



./ddforth_debug  -f test1.fs
init Adding word 0= with `0 =`
Running code:
	CR ." OUTSIDE LOOP" CR -10 BEGIN DUP . DUP -1 * CR ." > INSIDE LOOP" CR BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP CR 1 + DUP 0= UNTIL . .S CR
CR * Adding `CR`
."inside string
 * Adding `."`
OUTSIDE LOOPEnding "
ss: OUTSIDE LOOP"
CR * Adding `CR`
-10 * Adding `-10`
BEGIN * Adding `BEGIN`
DUP * Adding `DUP`
. * Adding `.`
DUP * Adding `DUP`
-1 * Adding `-1`
* * Adding `*`
CR * Adding `CR`
."inside string
 * Adding `."`
> INSIDE LOOPEnding "
ss: > INSIDE LOOP"
CR * Adding `CR`
BEGIN * Adding `BEGIN`
46 * Adding `46`
EMIT * Adding `EMIT`
1 * Adding `1`
- * Adding `-`
DUP * Adding `DUP`
0= * Adding `0=`
UNTIL * Adding `UNTIL`
DROP * Adding `DROP`
CR * Adding `CR`
1 * Adding `1`
+ * Adding `+`
DUP * Adding `DUP`
0= * Adding `0=`
UNTIL * Adding `UNTIL`
. * Adding `.`
.S * Adding `.S`
CR • Adding `CR`

Evaluating:
CR ." OUTSIDE LOOP" CR -10 BEGIN DUP . DUP -1 * CR ." > INSIDE LOOP" CR BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP CR 1 + DUP 0= UNTIL . .S CR 
Stack empty! 
evaluating 'CR' executionPointer: 0
0*	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 1
0 	| CR	|
1*	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'OUTSIDE LOOP"' executionPointer: 2
0 	| CR	|
1 	| ."	|
2*	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
OUTSIDE LOOP 
evaluating 'CR' executionPointer: 3
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3*	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '-10' executionPointer: 4
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4*	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -10 0= isInteger/10/-10 -10 is an int -10

evaluating 'BEGIN' executionPointer: 5
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5*	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 5

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -10 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 9	|
| 1	| INT.	| 9	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 9	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 8	|
| 1	| INT.	| 8	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 8	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 7	|
| 1	| INT.	| 7	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 7	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| 6	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| 5	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| 4	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| 3	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -10	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -10	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -9	|
| 1	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -9 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 8	|
| 1	| INT.	| 8	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 8	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 7	|
| 1	| INT.	| 7	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 7	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| 6	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| 5	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| 4	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| 3	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -9	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -9	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -8	|
| 1	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -8 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 7	|
| 1	| INT.	| 7	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 7	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| 6	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| 5	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| 4	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| 3	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -8	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -8	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -7	|
| 1	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -7	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -7 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| 6	|
| 2	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
| 1	| INT.	| -7	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| 5	|
| 2	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| -7	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| 4	|
| 2	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| -7	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| 3	|
| 2	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| -7	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -7	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -7	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -7	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -7	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -6	|
| 1	| INT.	| -6	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -6	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -6 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| 5	|
| 2	| INT.	| -6	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
| 1	| INT.	| -6	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| 4	|
| 2	| INT.	| -6	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| -6	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| 3	|
| 2	| INT.	| -6	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| -6	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -6	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -6	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -6	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -6	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -6	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -6	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -5	|
| 1	| INT.	| -5	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -5	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -5 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| 4	|
| 2	| INT.	| -5	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
| 1	| INT.	| -5	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| 3	|
| 2	| INT.	| -5	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| -5	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -5	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -5	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -5	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -5	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -5	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -5	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -4	|
| 1	| INT.	| -4	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -4	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -4 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| 3	|
| 2	| INT.	| -4	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 3	|
| 1	| INT.	| -4	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -4	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -4	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -4	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -4	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -4	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -4	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -3	|
| 1	| INT.	| -3	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -3	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -3 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 2	|
| 2	| INT.	| -3	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| -3	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -3	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -3	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -3	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -3	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -2	|
| 1	| INT.	| -2	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -2	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -2 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| -2	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| -2	|
+-----------------------+
Condition is false
 looping back to 15. Condition: 0

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -2	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -2	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -1	|
| 1	| INT.	| -1	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -1	|
+-----------------------+
Condition is false
 looping back to 5. Condition: 0

evaluating 'DUP' executionPointer: 6
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6*	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '.' executionPointer: 7
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7*	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 2 -1 
evaluating 'DUP' executionPointer: 8
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8*	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '-1' executionPointer: 9
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9*	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC -1 0= isInteger/10/-1 -1 is an int -1

evaluating '*' executionPointer: 10
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10*	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'CR' executionPointer: 11
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11*	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '."' executionPointer: 12
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12*	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '> INSIDE LOOP"' executionPointer: 13
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13*	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
> INSIDE LOOP 
evaluating 'CR' executionPointer: 14
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14*	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating 'BEGIN' executionPointer: 15
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15*	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> BEGIN at 15

evaluating '46' executionPointer: 16
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16*	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 46 0= isInteger/10/46 46 is an int 46

evaluating 'EMIT' executionPointer: 17
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17*	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
.
evaluating '1' executionPointer: 18
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18*	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '-' executionPointer: 19
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19*	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 20
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20*	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 21
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21*	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
| 2	| INT.	| -1	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 22
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22*	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 22. JumpStack size: 2

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| -1	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating 'DROP' executionPointer: 23
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23*	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating 'CR' executionPointer: 24
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24*	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|


evaluating '1' executionPointer: 25
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25*	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 26
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26*	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 27
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27*	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

evaluating '0=' executionPointer: 28
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28*	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|
lookupUC 0= 0= tokenize 0 = 0 * Adding `0`
= • Adding `=`

Evaluating:
0 = 

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
| 1	| INT.	| 0	|
+-----------------------+

evaluating '0' executionPointer: 0
0*	| 0	|
1 	| =	|
lookupUC 0 0= isInteger/10/0 0 is an int 0

evaluating '=' executionPointer: 1
0 	| 0	|
1*	| =	|
2 INTs 0= lookupUC 

evaluating 'UNTIL' executionPointer: 29
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29*	| UNTIL	|
30 	| .	|
31 	| .S	|
32 	| CR	|

--> UNTIL at 29. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 0	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

evaluating '.' executionPointer: 30
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30*	| .	|
31 	| .S	|
32 	| CR	|
handlePRINT: dataStack.size() 1 0 
evaluating '.S' executionPointer: 31
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31*	| .S	|
32 	| CR	|
Stack empty! 
evaluating 'CR' executionPointer: 32
0 	| CR	|
1 	| ."	|
2 	| OUTSIDE LOOP"	|
3 	| CR	|
4 	| -10	|
5 	| BEGIN	|
6 	| DUP	|
7 	| .	|
8 	| DUP	|
9 	| -1	|
10 	| *	|
11 	| CR	|
12 	| ."	|
13 	| > INSIDE LOOP"	|
14 	| CR	|
15 	| BEGIN	|
16 	| 46	|
17 	| EMIT	|
18 	| 1	|
19 	| -	|
20 	| DUP	|
21 	| 0=	|
22 	| UNTIL	|
23 	| DROP	|
24 	| CR	|
25 	| 1	|
26 	| +	|
27 	| DUP	|
28 	| 0=	|
29 	| UNTIL	|
30 	| .	|
31 	| .S	|
32*	| CR	|



./ddforth_debug  -f test2.fs
init Adding word 0= with `0 =`
Running code:
	BASE 16 ! A5 BASE A ! . CR -13 DUP DUP .S . U. HEX . DEC CR BASE ? . CR
BASE * Adding `BASE`
16 * Adding `16`
! * Adding `!`
A5 * Adding `A5`
BASE * Adding `BASE`
A * Adding `A`
! * Adding `!`
. * Adding `.`
CR * Adding `CR`
-13 * Adding `-13`
DUP * Adding `DUP`
DUP * Adding `DUP`
.S * Adding `.S`
. * Adding `.`
U. * Adding `U.`
HEX * Adding `HEX`
. * Adding `.`
DEC * Adding `DEC`
CR * Adding `CR`
BASE * Adding `BASE`
? * Adding `?`
. * Adding `.`
CR • Adding `CR`

Evaluating:
BASE 16 ! A5 BASE A ! . CR -13 DUP DUP .S . U. HEX . DEC CR BASE ? . CR 
Stack empty! 
evaluating 'BASE' executionPointer: 0
0*	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handleBASE 
evaluating '16' executionPointer: 1
0 	| BASE	|
1*	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
lookupUC 16 0= isInteger/10/16 16 is an int 16

evaluating '!' executionPointer: 2
0 	| BASE	|
1 	| 16	|
2*	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handleStore: intCounter 2 dataStack.size() 2 storing 16 into RAM[0] 
evaluating 'A5' executionPointer: 3
0 	| BASE	|
1 	| 16	|
2 	| !	|
3*	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
lookupUC A5 0= isInteger/16/A5 A5 is an int 165

evaluating 'BASE' executionPointer: 4
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4*	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handleBASE 
evaluating 'A' executionPointer: 5
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5*	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
lookupUC A 0= isInteger/16/A A is an int 10

evaluating '!' executionPointer: 6
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6*	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handleStore: intCounter 3 dataStack.size() 3 storing 10 into RAM[0] 
evaluating '.' executionPointer: 7
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7*	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handlePRINT: dataStack.size() 1 165 
evaluating 'CR' executionPointer: 8
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8*	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|


evaluating '-13' executionPointer: 9
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9*	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
lookupUC -13 0= isInteger/10/-13 -13 is an int -13

evaluating 'DUP' executionPointer: 10
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10*	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|

evaluating 'DUP' executionPointer: 11
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11*	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|

evaluating '.S' executionPointer: 12
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12*	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| -13	|
| 1	| INT.	| -13	|
| 2	| INT.	| -13	|
+-----------------------+

evaluating '.' executionPointer: 13
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13*	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handlePRINT: dataStack.size() 3 -13 
evaluating 'U.' executionPointer: 14
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14*	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
4294967283 
evaluating 'HEX' executionPointer: 15
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15*	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handleBASE16 
evaluating '.' executionPointer: 16
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16*	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handlePRINT: dataStack.size() 1  Printing 4294967283 in base 16
f
fffffff3 
evaluating 'DEC' executionPointer: 17
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17*	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handleBASE10 
evaluating 'CR' executionPointer: 18
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18*	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|


evaluating 'BASE' executionPointer: 19
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19*	| BASE	|
20 	| ?	|
21 	| .	|
22 	| CR	|
handleBASE 
evaluating '?' executionPointer: 20
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20*	| ?	|
21 	| .	|
22 	| CR	|
handleRetrieve: dataStack.size() 1 intCounter 1 userIntegers.size() 1 handleRetrieve end 
evaluating '.' executionPointer: 21
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21*	| .	|
22 	| CR	|
handlePRINT: dataStack.size() 1 10 
evaluating 'CR' executionPointer: 22
0 	| BASE	|
1 	| 16	|
2 	| !	|
3 	| A5	|
4 	| BASE	|
5 	| A	|
6 	| !	|
7 	| .	|
8 	| CR	|
9 	| -13	|
10 	| DUP	|
11 	| DUP	|
12 	| .S	|
13 	| .	|
14 	| U.	|
15 	| HEX	|
16 	| .	|
17 	| DEC	|
18 	| CR	|
19 	| BASE	|
20 	| ?	|
21 	| .	|
22*	| CR	|



./ddforth_debug  -f test3.fs
init Adding word 0= with `0 =`
Running code:
	1 2 .S OVER .S CR 1.2 2.1 .S OVER .S CR + + + + DROP .S
1 * Adding `1`
2 * Adding `2`
.S * Adding `.S`
OVER * Adding `OVER`
.S * Adding `.S`
CR * Adding `CR`
1.2 * Adding `1.2`
2.1 * Adding `2.1`
.S * Adding `.S`
OVER * Adding `OVER`
.S * Adding `.S`
CR * Adding `CR`
+ * Adding `+`
+ * Adding `+`
+ * Adding `+`
+ * Adding `+`
DROP * Adding `DROP`
.S • Adding `.S`

Evaluating:
1 2 .S OVER .S CR 1.2 2.1 .S OVER .S CR + + + + DROP .S 
Stack empty! 
evaluating '1' executionPointer: 0
0*	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '2' executionPointer: 1
0 	| 1	|
1*	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
lookupUC 2 0= isInteger/10/2 2 is an int 2

evaluating '.S' executionPointer: 2
0 	| 1	|
1 	| 2	|
2*	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|

	dataStack.size()	2	myInts	2	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 2	|
| 1	| INT.	| 1	|
+-----------------------+

evaluating 'OVER' executionPointer: 3
0 	| 1	|
1 	| 2	|
2 	| .S	|
3*	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|

evaluating '.S' executionPointer: 4
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4*	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 2	|
| 2	| INT.	| 1	|
+-----------------------+

evaluating 'CR' executionPointer: 5
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5*	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|


evaluating '1.2' executionPointer: 6
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6*	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
lookupUC 1.2 0= isInteger/10/1.2 1.2 is not an int.
isFloat: 1.2? 1.2 is an int 2

evaluating '2.1' executionPointer: 7
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7*	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
lookupUC 2.1 0= isInteger/10/2.1 2.1 is not an int.
isFloat: 2.1? 2.1 is an int 2

evaluating '.S' executionPointer: 8
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8*	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|

	dataStack.size()	5	myInts	3	myFloats	2	myStrings	0
+-----------------------+
| 0	| FLOAT	| 2.100	|
| 1	| FLOAT	| 1.200	|
| 2	| INT.	| 1	|
| 3	| INT.	| 2	|
| 4	| INT.	| 1	|
+-----------------------+

evaluating 'OVER' executionPointer: 9
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9*	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
2 FLOATs 
evaluating '.S' executionPointer: 10
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10*	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|

	dataStack.size()	6	myInts	3	myFloats	3	myStrings	0
+-----------------------+
| 0	| FLOAT	| 1.200	|
| 1	| FLOAT	| 2.100	|
| 2	| FLOAT	| 1.200	|
| 3	| INT.	| 1	|
| 4	| INT.	| 2	|
| 5	| INT.	| 1	|
+-----------------------+

evaluating 'CR' executionPointer: 11
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11*	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|


evaluating '+' executionPointer: 12
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12*	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
2 FLOATs 
evaluating '+' executionPointer: 13
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13*	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
2 FLOATs 
evaluating '+' executionPointer: 14
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14*	| +	|
15 	| +	|
16 	| DROP	|
17 	| .S	|
1 INT 1 FLOAT 
evaluating '+' executionPointer: 15
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15*	| +	|
16 	| DROP	|
17 	| .S	|
1 INT 1 FLOAT 
evaluating 'DROP' executionPointer: 16
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16*	| DROP	|
17 	| .S	|

evaluating '.S' executionPointer: 17
0 	| 1	|
1 	| 2	|
2 	| .S	|
3 	| OVER	|
4 	| .S	|
5 	| CR	|
6 	| 1.2	|
7 	| 2.1	|
8 	| .S	|
9 	| OVER	|
10 	| .S	|
11 	| CR	|
12 	| +	|
13 	| +	|
14 	| +	|
15 	| +	|
16 	| DROP	|
17*	| .S	|

	dataStack.size()	1	myInts	0	myFloats	1	myStrings	0
+-----------------------+
libc++abi: terminating due to uncaught exception of type std::out_of_range: vector
| 0	| INT.	| ./ddforth_debug  -f test4.fs
init Adding word 0= with `0 =`
Running code:
	." Fact\x7e\t\x7eTest" CR 3 BEGIN DUP DUP . ." ! =" FACT U. CR 1 + DUP 10 = UNTIL CR
."inside string
 * Adding `."`
FactTestEnding "
ss: Fact~	~Test"
CR * Adding `CR`
3 * Adding `3`
BEGIN * Adding `BEGIN`
DUP * Adding `DUP`
DUP * Adding `DUP`
. * Adding `.`
."inside string
 * Adding `."`
! =Ending "
ss: ! ="
FACT * Adding `FACT`
U. * Adding `U.`
CR * Adding `CR`
1 * Adding `1`
+ * Adding `+`
DUP * Adding `DUP`
10 * Adding `10`
= * Adding `=`
UNTIL * Adding `UNTIL`
CR • Adding `CR`

Evaluating:
." Fact~	~Test" CR 3 BEGIN DUP DUP . ." ! =" FACT U. CR 1 + DUP 10 = UNTIL CR 
Stack empty! 
evaluating '."' executionPointer: 0
0*	| ."	|
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
19 	| CR	|

evaluating 'Fact~	~Test"' executionPointer: 1
0 	| ."	|
1*	| Fact~	~Test"	|
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
19 	| CR	|
Fact~	~Test 
evaluating 'CR' executionPointer: 2
0 	| ."	|
1 	| Fact~	~Test"	|
2*	| CR	|
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
19 	| CR	|


evaluating '3' executionPointer: 3
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3*	| 3	|
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
19 	| CR	|
lookupUC 3 0= isInteger/10/3 3 is an int 3

evaluating 'BEGIN' executionPointer: 4
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4*	| BEGIN	|
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
19 	| CR	|

--> BEGIN at 4

evaluating 'DUP' executionPointer: 5
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5*	| DUP	|
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
19 	| CR	|

evaluating 'DUP' executionPointer: 6
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6*	| DUP	|
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
19 	| CR	|

evaluating '.' executionPointer: 7
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7*	| .	|
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
19 	| CR	|
handlePRINT: dataStack.size() 3 3 
evaluating '."' executionPointer: 8
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8*	| ."	|
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
19 	| CR	|

evaluating '! ="' executionPointer: 9
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9*	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
! = 
evaluating 'FACT' executionPointer: 10
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
10*	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating 'U.' executionPointer: 11
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
11*	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
6 
evaluating 'CR' executionPointer: 12
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
12*	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|


evaluating '1' executionPointer: 13
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
13*	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 14
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
14*	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 15
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
15*	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating '10' executionPointer: 16
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
16*	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 10 0= isInteger/10/10 10 is an int 10

evaluating '=' executionPointer: 17
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
17*	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'UNTIL' executionPointer: 18
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
18*	| UNTIL	|
19 	| CR	|

--> UNTIL at 18. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 4	|
+-----------------------+
Condition is false
 looping back to 4. Condition: 0

evaluating 'DUP' executionPointer: 5
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5*	| DUP	|
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
19 	| CR	|

evaluating 'DUP' executionPointer: 6
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6*	| DUP	|
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
19 	| CR	|

evaluating '.' executionPointer: 7
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7*	| .	|
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
19 	| CR	|
handlePRINT: dataStack.size() 3 4 
evaluating '."' executionPointer: 8
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8*	| ."	|
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
19 	| CR	|

evaluating '! ="' executionPointer: 9
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9*	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
! = 
evaluating 'FACT' executionPointer: 10
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
10*	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating 'U.' executionPointer: 11
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
11*	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
24 
evaluating 'CR' executionPointer: 12
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
12*	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|


evaluating '1' executionPointer: 13
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
13*	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 14
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
14*	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 15
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
15*	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating '10' executionPointer: 16
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
16*	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 10 0= isInteger/10/10 10 is an int 10

evaluating '=' executionPointer: 17
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
17*	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'UNTIL' executionPointer: 18
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
18*	| UNTIL	|
19 	| CR	|

--> UNTIL at 18. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 5	|
+-----------------------+
Condition is false
 looping back to 4. Condition: 0

evaluating 'DUP' executionPointer: 5
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5*	| DUP	|
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
19 	| CR	|

evaluating 'DUP' executionPointer: 6
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6*	| DUP	|
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
19 	| CR	|

evaluating '.' executionPointer: 7
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7*	| .	|
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
19 	| CR	|
handlePRINT: dataStack.size() 3 5 
evaluating '."' executionPointer: 8
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8*	| ."	|
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
19 	| CR	|

evaluating '! ="' executionPointer: 9
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9*	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
! = 
evaluating 'FACT' executionPointer: 10
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
10*	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating 'U.' executionPointer: 11
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
11*	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
120 
evaluating 'CR' executionPointer: 12
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
12*	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|


evaluating '1' executionPointer: 13
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
13*	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 14
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
14*	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 15
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
15*	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating '10' executionPointer: 16
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
16*	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 10 0= isInteger/10/10 10 is an int 10

evaluating '=' executionPointer: 17
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
17*	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'UNTIL' executionPointer: 18
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
18*	| UNTIL	|
19 	| CR	|

--> UNTIL at 18. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 6	|
+-----------------------+
Condition is false
 looping back to 4. Condition: 0

evaluating 'DUP' executionPointer: 5
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5*	| DUP	|
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
19 	| CR	|

evaluating 'DUP' executionPointer: 6
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6*	| DUP	|
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
19 	| CR	|

evaluating '.' executionPointer: 7
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7*	| .	|
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
19 	| CR	|
handlePRINT: dataStack.size() 3 6 
evaluating '."' executionPointer: 8
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8*	| ."	|
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
19 	| CR	|

evaluating '! ="' executionPointer: 9
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9*	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
! = 
evaluating 'FACT' executionPointer: 10
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
10*	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating 'U.' executionPointer: 11
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
11*	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
720 
evaluating 'CR' executionPointer: 12
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
12*	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|


evaluating '1' executionPointer: 13
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
13*	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 14
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
14*	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 15
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
15*	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating '10' executionPointer: 16
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
16*	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 10 0= isInteger/10/10 10 is an int 10

evaluating '=' executionPointer: 17
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
17*	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'UNTIL' executionPointer: 18
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
18*	| UNTIL	|
19 	| CR	|

--> UNTIL at 18. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 7	|
+-----------------------+
Condition is false
 looping back to 4. Condition: 0

evaluating 'DUP' executionPointer: 5
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5*	| DUP	|
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
19 	| CR	|

evaluating 'DUP' executionPointer: 6
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6*	| DUP	|
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
19 	| CR	|

evaluating '.' executionPointer: 7
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7*	| .	|
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
19 	| CR	|
handlePRINT: dataStack.size() 3 7 
evaluating '."' executionPointer: 8
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8*	| ."	|
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
19 	| CR	|

evaluating '! ="' executionPointer: 9
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9*	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
! = 
evaluating 'FACT' executionPointer: 10
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
10*	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating 'U.' executionPointer: 11
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
11*	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
5040 
evaluating 'CR' executionPointer: 12
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
12*	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|


evaluating '1' executionPointer: 13
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
13*	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 14
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
14*	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 15
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
15*	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating '10' executionPointer: 16
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
16*	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 10 0= isInteger/10/10 10 is an int 10

evaluating '=' executionPointer: 17
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
17*	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'UNTIL' executionPointer: 18
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
18*	| UNTIL	|
19 	| CR	|

--> UNTIL at 18. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 8	|
+-----------------------+
Condition is false
 looping back to 4. Condition: 0

evaluating 'DUP' executionPointer: 5
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5*	| DUP	|
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
19 	| CR	|

evaluating 'DUP' executionPointer: 6
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6*	| DUP	|
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
19 	| CR	|

evaluating '.' executionPointer: 7
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7*	| .	|
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
19 	| CR	|
handlePRINT: dataStack.size() 3 8 
evaluating '."' executionPointer: 8
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8*	| ."	|
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
19 	| CR	|

evaluating '! ="' executionPointer: 9
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9*	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
! = 
evaluating 'FACT' executionPointer: 10
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
10*	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating 'U.' executionPointer: 11
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
11*	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
40320 
evaluating 'CR' executionPointer: 12
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
12*	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|


evaluating '1' executionPointer: 13
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
13*	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 14
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
14*	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 15
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
15*	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating '10' executionPointer: 16
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
16*	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 10 0= isInteger/10/10 10 is an int 10

evaluating '=' executionPointer: 17
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
17*	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'UNTIL' executionPointer: 18
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
18*	| UNTIL	|
19 	| CR	|

--> UNTIL at 18. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 9	|
+-----------------------+
Condition is false
 looping back to 4. Condition: 0

evaluating 'DUP' executionPointer: 5
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5*	| DUP	|
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
19 	| CR	|

evaluating 'DUP' executionPointer: 6
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6*	| DUP	|
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
19 	| CR	|

evaluating '.' executionPointer: 7
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7*	| .	|
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
19 	| CR	|
handlePRINT: dataStack.size() 3 9 
evaluating '."' executionPointer: 8
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8*	| ."	|
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
19 	| CR	|

evaluating '! ="' executionPointer: 9
0 	| ."	|
1 	| Fact~	~Test"	|
2 	| CR	|
3 	| 3	|
4 	| BEGIN	|
5 	| DUP	|
6 	| DUP	|
7 	| .	|
8 	| ."	|
9*	| ! ="	|
10 	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
! = 
evaluating 'FACT' executionPointer: 10
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
10*	| FACT	|
11 	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating 'U.' executionPointer: 11
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
11*	| U.	|
12 	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
362880 
evaluating 'CR' executionPointer: 12
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
12*	| CR	|
13 	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|


evaluating '1' executionPointer: 13
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
13*	| 1	|
14 	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 1 0= isInteger/10/1 1 is an int 1

evaluating '+' executionPointer: 14
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
14*	| +	|
15 	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'DUP' executionPointer: 15
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
15*	| DUP	|
16 	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|

evaluating '10' executionPointer: 16
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
16*	| 10	|
17 	| =	|
18 	| UNTIL	|
19 	| CR	|
lookupUC 10 0= isInteger/10/10 10 is an int 10

evaluating '=' executionPointer: 17
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
17*	| =	|
18 	| UNTIL	|
19 	| CR	|
2 INTs 
evaluating 'UNTIL' executionPointer: 18
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
18*	| UNTIL	|
19 	| CR	|

--> UNTIL at 18. JumpStack size: 1

	dataStack.size()	1	myInts	1	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 10	|
+-----------------------+
Condition is true
 Ending BEGIN. Condition: 1

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

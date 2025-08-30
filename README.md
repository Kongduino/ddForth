# ddForth

## REGULAR VERSION


```forth
> make clean; make
rm -f ddforth ddforth_debug
g++ -O3 ddforth.cpp -o ddforth
> ./ddforth 
Running code:
	-10 BEGIN DUP . DUP -1 * BEGIN 46 EMIT 1 - DUP 0= UNTIL DROP 1 + DUP 0= UNTIL . .S CR
-10 ..........-9 .........-8 ........-7 .......-6 ......-5 .....-4 ....-3 ...-2 ..-1 .0 Stack empty! 


> ./ddforth -f test.fs 
Running code:
	." \"中文也行\"" CR ." ¥Á¥!"
"中文也行" 
¥Á¥! 

> ./ddforth -f test0.fs
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


> ./ddforth -f test1.fs
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


> ./ddforth -f test2.fs
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
```

## DEBUG VERSION

```
> make clean; make debug
rm -f ddforth ddforth_debug
g++ -O3 -DDEBUG ddforth.cpp -o ddforth_debug
> ./ddforth_debug -f test0.fs 
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



```

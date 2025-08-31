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
Adding word ? with `@ .`
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


./ddforth_debug  -f test6.fs
init Adding word 0= with `0 =`
Adding word ? with `@ .`
Running code:
	: ++ + + ; 1 1 1 .S ++ . CR
: * Adding `:`
++ * Adding `++`
+ * Adding `+`
+ * Adding `+`
; * Adding `;`
1 * Adding `1`
1 * Adding `1`
1 * Adding `1`
.S * Adding `.S`
++ * Adding `++`
. * Adding `.`
CR • Adding `CR`

Evaluating:
: ++ + + ; 1 1 1 .S ++ . CR 
Stack empty! 
evaluating ':' executionPointer: 0
0*	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5 	| 1	|
6 	| 1	|
7 	| 1	|
8 	| .S	|
9 	| ++	|
10 	| .	|
11 	| CR	|
WORD name: ++: + 2/12 + 3/12 ; 4/12  got a ;! Adding word ++ with `+ + `.

evaluating '1' executionPointer: 5
0 	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5*	| 1	|
6 	| 1	|
7 	| 1	|
8 	| .S	|
9 	| ++	|
10 	| .	|
11 	| CR	|
lookupUC 1 0= ? ++ isInteger/10/1 1 is an int 1

evaluating '1' executionPointer: 6
0 	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5 	| 1	|
6*	| 1	|
7 	| 1	|
8 	| .S	|
9 	| ++	|
10 	| .	|
11 	| CR	|
lookupUC 1 0= ? ++ isInteger/10/1 1 is an int 1

evaluating '1' executionPointer: 7
0 	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5 	| 1	|
6 	| 1	|
7*	| 1	|
8 	| .S	|
9 	| ++	|
10 	| .	|
11 	| CR	|
lookupUC 1 0= ? ++ isInteger/10/1 1 is an int 1

evaluating '.S' executionPointer: 8
0 	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5 	| 1	|
6 	| 1	|
7 	| 1	|
8*	| .S	|
9 	| ++	|
10 	| .	|
11 	| CR	|

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| 1	|
+-----------------------+

evaluating '++' executionPointer: 9
0 	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5 	| 1	|
6 	| 1	|
7 	| 1	|
8 	| .S	|
9*	| ++	|
10 	| .	|
11 	| CR	|
lookupUC ++ 0= ? ++ tokenize + +  + * Adding `+`
+ * Adding `+`

Evaluating:
+ + 

	dataStack.size()	3	myInts	3	myFloats	0	myStrings	0
+-----------------------+
| 0	| INT.	| 1	|
| 1	| INT.	| 1	|
| 2	| INT.	| 1	|
+-----------------------+

evaluating '+' executionPointer: 0
0*	| +	|
1 	| +	|
2 INTs 
evaluating '+' executionPointer: 1
0 	| +	|
1*	| +	|
2 INTs ++ lookupUC 

evaluating '.' executionPointer: 10
0 	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5 	| 1	|
6 	| 1	|
7 	| 1	|
8 	| .S	|
9 	| ++	|
10*	| .	|
11 	| CR	|
handlePRINT: dataStack.size() 1 3 
evaluating 'CR' executionPointer: 11
0 	| :	|
1 	| ++	|
2 	| +	|
3 	| +	|
4 	| ;	|
5 	| 1	|
6 	| 1	|
7 	| 1	|
8 	| .S	|
9 	| ++	|
10 	| .	|
11*	| CR	|

```

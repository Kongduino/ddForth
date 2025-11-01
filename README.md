# ddForth

A minimal implementation of the Forth language in (mostly) C++. When I was a kid – a looooong time ago: the book I still have is based on FORTH-79... – I was fascinated by Forth, and RPN in general. I tried a few times, with various (lack of) success to write my own. Recently I decided to give it another go.

Surprisingly, it went well, beyond expectations, and I can run quite a few of the examples in my book. So I decided to keep pushing. I runs on my computer, as they say, which happens to be a Macbook Pro with an Apple M4 Pro CPU (and a 2018 Mac Mini Intel Core 7!). The compiled binary is still quite small (260 KB on ARM).

The original README was outdated, and possibly confusing. I am trying to rewrite it so that it helps you start with ddForth without losing too much hair. For the language itself, and especially this dialect of Forth, which has a strong accent... see the [Tutorial](Tutorial.md).

## Various versions

Until a while ago I tried developing the main version alongside with:

* An SDL version;
* Various IOT versions, including:
	* A Pico version;
	* A CardPuter version;
	* A couple of esp32 versions
* An IPC socket-based GUI version, which might work out better than the SDL version. But development has been suspended for now.

These are terribly outdated now, and should not be used, really. I will probably make a backup, and remove them from the repo.

## INSTALLING

A bunch of subversions ago, I launched a plugin system, which seems to work well. The development directory is called `plugin`, no surprise here. However, compiled plugins go into `~/.ddForthPlugins/` – at least on Linux and Mac OS X. No idea how to do that on Windows.

Read the plugin directory's [README](plugin/README.md) to build the plugins properly, which you will need to do before building ddForth proper.

### Compiling

```sh~/ddForth$ make install
mkdir -p bin
g++ -O3 -c ddforth.cpp -o bin/ddforth.o
g++ -o bin/ddforth bin/ddforth.o -lcurl
#rm -f bin/*.o
sudo cp bin/ddforth /usr/local/bin/
mkdir -p ~/.ddForthPlugins
cp ./plugin/*.so ~/.ddForthPlugins/
ls -al ~/.ddForthPlugins/
total 2356
drwxrwxr-x  2 kongduino kongduino    4096 Nov  1 14:32 .
drwxr-xr-x 19 kongduino kongduino    4096 Nov  1 15:16 ..
-rwxrwxr-x  1 kongduino kongduino  412944 Nov  1 15:17 ls.so
-rwxrwxr-x  1 kongduino kongduino 1987704 Nov  1 15:17 traversin.so
```

On Linux you might get some (harmless) warnings – I will work on removing them (by solving the issue!). The plugins are copied to `~/.ddForthPlugins/` (which will be created if it doesn't exist yet). This is where ddForth will look for them. Calling a non-existent plugin crashes hard (punishment!) but this will change too.

### Launching

`make install` copies ddForth to `/usr/local/bin/` so it should be available right away:

```sh
$ ddforth 
ddForth v1.2.91


OK 
```

Generally, when code fails, the interpreter tries to be helpful, and shows context (a couple of words before and after the culprit) and the stack – before nuking it. Example:


```
OK s" This is a string" s" \ " splitd 5 strpick cs cr
handleSPICK/2 Stack overflow!
strpick returned false. Aborting!

CONTEXT: 4 to 9
        splitd 5 strpick cs cr         

+-----------------------+
| 0	| INT.	| 4         |
| 1	| STR.	| string	|
| 2	| STR.	| a	        |
| 3	| STR.	| is	    |
| 4	| STR.	| This	    |
+-----------------------+
OK 
```

Yeah dude, there are only 4 chunks...

See the [Tutorial](Tutorial.md), which needs an upgrade, too, and the `tests` directory. There are close to 50 examples so far.



```
	.V WORDS

Variables & Constants
+-----------------------------------------+
| Num     |  VAR Name   | Addr | Value    |
+-----------------------------------------+
|   0/2   | BASE        |    0 |       10 |
|   1/2   | VER.        |    1 |     1156 |
+-----------------------------------------+
+-----------------------------------------+
| Num     | FCONST Name | Addr | Value    |
+-----------------------------------------+
|   0/2   | E           |  385 | 2.718282 |
|   1/2   | PI          |  384 | 3.141593 |
+-----------------------------------------+
Handled in Code:
----------------
 • VAR         (Handled in code)
 • CONST       (Handled in code)
 • : ... ;     (Handled in code)
 • IF...THEN...ELSE (Handled in code)
 • ( THIS IS A COMMENT. ) (Handled in code)

Native Commands:
----------------
WORDS HELP SUPP_ARGS HEXDUMP HELP" + - * / ABS MIN MAX FACT MOD AND OR XOR NOT NEGATE INVERT SQR SQRT SIN COS TAN ASIN ACOS ATAN SINH COSH TANH LOG LOG10 ROUND FLOOR CEIL EXP INT EMIT CHR KEY QKEY LINE U. ." S" C" . CS +STR STR+ LEFTSTR MIDSTR RIGHTSTR LENSTR SUBSTR LOWERSTR UPPERSTR MULTSTR STRIPSTR LSTRIPSTR RSTRIPSTR INTSTR FLOATSTR STRINT STRFLOAT CSPLIT SPLITD SREVERSE DINSERT STRREPLACE SFILL CFILL VARRAY FILSTR SORTSTR RSORTSTR SORTV RSORTV FINDV FORGET DUP DROP SWAP DEPTH CLEAR ROLL STRPICK STRSTORE STRJOIN PICK PLACE SLICER HEX2NUM BASE BIN DEC HEX ! !+ @ CR .S .V WITHIN = S= < <= > >= <> =? >? <? <=? >=? <>? BEGIN UNTIL WHILE AGAIN DO LOOP +LOOP I I' J >R R> EXEC FLOAD INCLUDE FSAVE UOPEN UREADL UREADHEXL UREADRAW UREADHEX UFLUSH UINQ UDISCARDUNTIL UREADHEXUNTIL UREADUNTIL UREADC UCLOSE UWRITE RANDOM RANDOMI IF THEN ELSE EXIT ARRAY ARRAYS >IX IX> LEN> IX+ +IX <ROT ROT> ALIST ASUM POSXY GETXY CLEAN SLEEP DELAY BP DEBUG CONTINUE STEP CURLGETM CURLGETF PLUGIN 

User Commands:
--------------
 • 0=          0 =
 • 0>          0 >
 • 0<          0 <
 • 0<>         0 <>
 • TRUE        1 =
 • FALSE       0 =
 • ?           @ .
 • 1+          1 +
 • 1-          1 -
 • 2+          2 +
 • 2-          2 -
 • 2*          2 *
 • 2/          2 /
 • ++          + +
 • NIP         SWAP DROP
 • TUCK        SWAP OVER
 • -ROT        ROT ROT
 • nip         swap drop
 • tuck        swap over
 • ?DUP        DUP 0= IF THEN DUP ELSE
 • 2DUP        0 PICK 1 PICK
 • 2DROP       DROP DROP
 • 2SWAP       4 roll 4 roll
 • 2OVER       depth 4 - pick depth 4 - pick
 • -rot        rot rot
 • nROT>       0 DO DUP ROT> LOOP CLEAR
 • n<ROT       0 DO DUP <ROT LOOP CLEAR
 • SSPLIT      32 CSPLIT
 • ROT         swap var tagada swap tagada @ s" tagada" forget 
 • OVER        SWAP DUP ROT
 • AGAIN       1 WHILE


Plugin Commands:
--------------
(only when plugins are loaded)
```

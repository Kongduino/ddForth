clear ." Split `"
s" 1"
100 0 DO
  RANDOM 10 MOD INTSTR
  DUP cs
  STR+
LOOP
." ` by: "
RANDOM 10 MOD
DUP .
INTSTR
SPLITD
CR DUP ." Pieces: " . CR
0 DO
  ." * " cs cr
LOOP

1 2 3 4 4 s" ints" VARRAY CR s" ints" alist
1.1 2.2 3.3 4.4 4 s" floats" VARRAY CR s" floats" alist
s" un|deux|trois|quatre" s" |" SPLITD s" strings" VARRAY CR s" strings" alist

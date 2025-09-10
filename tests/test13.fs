( Create a word called average )
: AVERAGE
CR DEPTH DUP VAR COUNT (assign depth as variable COUNT)
1 DO + LOOP (sum up all numbers)
COUNT @ / . (calculate average and print)
;
." Please enter numbers, separated by spaces, to average out:" CR
LINE EXEC ." Average: " AVERAGE
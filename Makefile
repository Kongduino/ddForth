CPP=g++
CFLAGS=-O3

TEST="-10 BEGIN DUP . 1 + DUP 0 <> WHILE . CR 10 DUP U. FACT U."

ddforth: ddforth.cpp
	$(CPP) $(CFLAGS) -g -c ddforth.cpp -o ddforth.o
	$(CPP) -o ddforth ddforth.o $(LDLAGS)

test: ddforth
	./ddforth $(TEST)

clean:
	rm -f ddforth ddforth_debug

debug: ddforth.cpp
	$(CPP) -DDEBUG ddforth.cpp -o ddforth_debug

all: ddforth debug

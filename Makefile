CPP=g++
CFLAGS=-O3

TEST="-10 BEGIN DUP . 1 + DUP 0 <> WHILE . CR 10 DUP U. FACT U."

ddforth: ddforth.cpp
	$(CPP) $(CFLAGS) -g -c ddforth.cpp -o ddforth.o
	$(CPP) -o ddforth ddforth.o $(LDLAGS)
	rm -f *.o

test: ddforth
	./ddforth $(TEST)

tests: ddforth
	cd tests ; ./tests.sh

clean:
	rm -f ddforth ddforth_debug ddforth_SDL ddforth_SDL_debug *.o

debug: ddforth.cpp
	$(CPP) $(CFLAGS) -DDEBUG ddforth.cpp -o ddforth_debug
	rm -f *.o

sdl: ddforth.cpp
	$(CPP) $(CFLAGS) -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	$(CPP) -o ddforth_SDL ddforth.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
	$(CPP) $(CFLAGS) -DDEBUG -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	$(CPP) -o ddforth_SDL_debug ddforth.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
	./in.sh
	rm -f *.o

all: ddforth debug sdl

install: ddforth
	sudo cp ddforth /usr/local/bin/

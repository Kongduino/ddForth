CPP=g++
CFLAGS=-O3

TEST="-10 BEGIN DUP . 1 + DUP 0 <> WHILE . CR 10 DUP U. FACT U."

ddforth: ddforth.cpp
	$(CPP) $(CFLAGS) -g -c ddforth.cpp -o ddforth.o
	$(CPP) -o ddforth ddforth.o $(LDLAGS)

test: ddforth
	./ddforth $(TEST)

clean:
	rm -f ddforth ddforth_debug ddforth_SDL ddforth_SDL_debug

debug: ddforth.cpp
	$(CPP) $(CFLAGS) -DDEBUG ddforth.cpp -o ddforth_debug

sdl: ddforth.cpp
	$(CPP) $(CFLAGS) -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	$(CPP) -o ddforth_SDL ddforth.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
	./in.sh
	$(CPP) $(CFLAGS) -DDEBUG -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	$(CPP) -o ddforth_SDL_debug ddforth.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
	./in_debug.sh

all: ddforth debug sdl

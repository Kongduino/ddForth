CPP=g++
CFLAGS=-O3
CFLAGSMALL=-Oz
LDFLAGS=-lcurl
DYLIB_SUFFIX=so
SHARED_CMD=-shared
TEST="-10 BEGIN DUP . 1 + DUP 0 <> WHILE . CR 10 DUP U. FACT U."

ddforth: ddforth.cpp
	mkdir -p bin
	$(CPP) $(CFLAGS) -c ddforth.cpp -o bin/ddforth.o
	$(CPP) -o bin/ddforth bin/ddforth.o $(LDFLAGS)
	#rm -f bin/*.o

small: ddforth.cpp
	mkdir -p bin
	$(CPP) $(CFLAGSMALL) -c ddforth.cpp -o bin/ddforth.o
	$(CPP) -o bin/ddforth_z bin/ddforth.o $(LDFLAGS)
	rm -f bin/*.o

test: ddforth
	./bin/ddforth $(TEST)

tests: ddforth
	cd tests ; ./tests.sh

clean:
	rm -f bin/dd* *.o

debug: ddforth.cpp
	mkdir -p bin
	$(CPP) $(CFLAGS) -DDEBUG ddforth.cpp -o bin/ddforth_debug
	rm -f bin/*.o

sdl: ddforth.cpp
	mkdir -p bin
	$(CPP) $(CFLAGS) -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	mv *.o bin/
	$(CPP) -o bin/ddforth_SDL bin/ddforth.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
	$(CPP) $(CFLAGS) -DDEBUG -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	mv *.o bin/
	$(CPP) -o bin/ddforth_SDL_debug bin/ddforth.o -L/usr/local/lib -l SDL3 -l SDL3_ttf
	./in.sh
	rm -f bin/*.o

all: ddforth debug sdl small

install: ddforth
	sudo cp bin/ddforth /usr/local/bin/
	mkdir -p ~/.ddForthPlugins
	cp ./plugin/*.$(DYLIB_SUFFIX) ~/.ddForthPlugins/
	ls -al ~/.ddForthPlugins/

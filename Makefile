CPP=g++
CFLAGS=-O3 -I/opt/homebrew/include
CFLAGSMALL=-Oz
LDFLAGS=-lcurl -L/opt/homebrew/opt/curl/lib -L/opt/homebrew/lib
DYLIB_SUFFIX=so
SHARED_CMD=-shared
TEST="-10 BEGIN DUP . 1 + DUP 0 <> WHILE . CR 10 DUP U. FACT U."

.cpp.o:
	$(CC) $(CFLAGS) ../$< -o $@

plugins: plugin/plugin.cpp ddForthPluginsDir
	cd plugin && make clean && make
	cd ../
	cp ./plugin/*.$(DYLIB_SUFFIX) ~/.ddForthPlugins/

ddforth: bin bin/ddforth.o
	mkdir -p bin
	$(CPP) $(CFLAGS) -c ddforth.cpp -o bin/ddforth.o
	$(CPP) -o bin/ddforth bin/ddforth.o $(LDFLAGS)
	#rm -f bin/*.o

bin/ddforth.o : ddforth.cpp

small: bin bin/ddforth.o
	mkdir -p bin
	$(CPP) $(CFLAGSMALL) -c ddforth.cpp -o bin/ddforth.o
	$(CPP) -o bin/ddforth_z bin/ddforth.o $(LDFLAGS)
	rm -f bin/*.o

ddForthPluginsDir:
	mkdir -p ~/.ddForthPlugins/

test: bin/ddforth
	./bin/ddforth $(TEST)

tests: ddforth
	cd tests ; ./tests.sh

clean:
	rm -f bin/dd* *.o
	make -C plugin clean

debug: bin/ddforth.o
	mkdir -p bin
	$(CPP) $(CFLAGS) $(LDFLAGS) -DDEBUG ddforth.cpp -o bin/ddforth_debug
	rm -f bin/*.o

sdl: bin bin/ddforth.o
	mkdir -p bin
	$(CPP) $(CFLAGS) -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	mv *.o bin/
	$(CPP) -o bin/ddforth_SDL bin/ddforth.o $(LDFLAGS) -lSDL3 -lSDL3_ttf
	$(CPP) $(CFLAGS) -DDEBUG -DNEED_SDL -g -c ddforth.cpp -I/usr/local/include/SDL3/ -I/usr/local/include/SDL3_ttf
	mv *.o bin/
	$(CPP) -o bin/ddforth_SDL_debug bin/ddforth.o $(LDFLAGS) -lSDL3 -lSDL3_ttf
	./in.sh
	rm -f bin/*.o

all: plugins ddforth debug sdl small

install: ddforth
	sudo cp bin/ddforth /usr/local/bin/
	mkdir -p ~/.ddForthPlugins
	cp ./plugin/*.$(DYLIB_SUFFIX) ~/.ddForthPlugins/
	ls -al ~/.ddForthPlugins/

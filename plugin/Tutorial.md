# Plugin Tutorial

## Architecture of a plugin

The first thing to keep in mind is that a ddForth plugin lives inside its own little ecosystem, and doesn't have access to ddForth's stack. So it gets fed by ddForth whatever data it needs, and it can send back return values, which will be put on the stack. This is done in `lookupPlugin(string c, bool *r)`.

Let's work through the ls plugin, which is very simple. It has one command, `LS` (the other, `INIT` doesn't need to be called, and shouldn't be, as it is called automatically when the plugin is loaded). Commands are defined in an array of `pluginCommand` structures, which is very similar to the `nativeCommand` structure, except it has one more entry, `string params`, which describes what the command needs on entry.

For ls, the whole command list looks like this:

```c
pluginCommand pluginCommands[] = {
  // handleInit is compulsory, in position 0
  { handleInit, "INIT", "( -- ) Initializes the plugin, if required.", "0" },
  { handleLS, "LS", "( path -- ) Lists file on path", "1S" },
};
int pluginCmdCount = sizeof(pluginCommands) / sizeof(pluginCommand);
```

So we know that we need to pass one string to `handleLS`. Other commands could require a series of parameters, including integers and floats. To make it easier, all params are pushed back, in order, into a `vector<string>`, and decoded properly by each command.

So our `handleLS` command definition looks like this:

`vector<string> handleLS(vector<string> P)`

The first thing to do is to make sure we have the right number of parameters, and extract them:

```
  vector<string> R;
  // path LS
  if (P.size() != 1) {
    R.push_back("false");
    R.push_back("handleLS: Invalid number of args!\n");
    return R;
  }
  string path = P.at(0);
```

Here it is easy. If we needed int parameters we could do something like:

```
  int myNum = std::atoi(P.at(1).c_str());
```

Then the command pushes back (if everything works well) the file names into `vector<string> R`, each prefixed with `S` for string and returns that vector. The contents will be pushed onto the stack, and `true` will be returned.

If an error occurs, the command pushes `"false"` and an error message (as strings). The return values will not be pushed onto the stack, but the message displayed, and `false` will be returned.

### handleInit()

The `handleInit()` command is called when the plugin is loaded, but doesn't _need_ to do anything. If there's no init required, just return an empty `R`. `traversin` needs do do some work before it can be used, so this is where it happens. 

One cool trick with a plugin's return values list is that it can be used to create directly a VARRY. See test48:

```
s" ls" plugin
s" ./" ls
s" .cpp" FILSTR
( Only *.cpp files are now on the stack )
s" myLS" varray s" myLS" sortv
( Let's use this to create a VARRAY: file0 file1 file2 file3 file4 5 s" vName" VARRAY )

s" myLS" len> 0 do
  ( From 0 to length of varray )
  i . ( Prints number )
  i s" myLS" IX> . cr ( Prints line I and CR )
loop
```

A VARRAY called `myLS` is created with the filtered out list of `.cpp` files, and can now be manipulated at will.

Here's test48 and the output:

```
s" ls" plugin
s" ./" ls
s" .cpp" FILSTR
( Only *.cpp files are now on the stack )
s" myLS" varray s" myLS" sortv
( Let's use this to create a VARRAY: file0 file1 file2 file3 file4 5 s" vName" VARRAY )

s" myLS" len> 0 do
  ( From 0 to length of varray )
  i . ( Prints number )
  i s" myLS" IX> . cr ( Prints line I and CR )
loop

% ddforth -f tests/test48.fs 
ddForth v1.2.93
 • Read: s" ls" plugin
 • Read: s" ./" ls
 • Read: s" .cpp" FILSTR
 • Read: ( Only *.cpp files are now on the stack )
 • Read: s" myLS" varray s" myLS" sortv
 • Read: ( Let's use this to create a VARRAY: file0 file1 file2 file3 file4 5 s" vName" VARRAY )
 • Read: 
 • Read: s" myLS" len> 0 do
 • Read:   ( From 0 to length of varray )
 • Read:   i . ( Prints number )
 • Read:   i s" myLS" IX> . cr ( Prints line I and CR )
 • Read: loop
Read: 12 lines, chunks: 29
 • INIT:	( -- ) Initializes the plugin, if required.
   - Arg count: [0] 0
 • LS:	( path -- ) Lists file on path
   - Arg count: [1] 1
   - Arg #0: S
Calling handleInit().
Listing contents of: ./
./ipc.cpp
./incrementVersion.py
./.DS_Store
./LICENSE
./bin
./esp_ddforth
./erase.cpp
./getinmemory.hpp
./ddforth.hpp
./Makefile
./plugin.hpp
./Files.hpp
./myversion.hpp
./Terminal.hpp
./tests
./plugin
./esp32v4_ddforth
./.plugins
./server
./IPC GUI.md
./Numbers.hpp
./Debugger.hpp
./ExtraCommands.hpp
./sdl.cpp
./README.md
./ddforth.cpp
./Strings.hpp
./random.hpp
./Tutorial.md
./Stack.hpp
./USB_UART.hpp
./cardputer_ddforth
./.git
./insert.cpp
./Fonts
./lowercase.py
./assets
./pico_ddforth
./addAll.sh
./sdl_helpers
./in.sh
0 ./ddforth.cpp
1 ./erase.cpp
2 ./insert.cpp
3 ./ipc.cpp
4 ./sdl.cpp


OK 
```
The `ls` command prints everything out, I will remove that in 1.3.0.


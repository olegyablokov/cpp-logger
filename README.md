## Getting started
This is a fast, easy-to-use, thread-safe, standalone C++17 library for logging.

## Usage
To use the logger, do the following:

1. Link the compiled library to your CMake-configured project (read "Build" section below):
```
target_link_libraries(<project_name>, path/to/build/<lib_name>)
```
1. Include this header into your C++ file:
```
 #include "path/to/this/project/logger.h"
```
2. Initialize and start the logger:
```
auto log = Logger::create("test.log", "log");
log->start();
```
3. Write logs:
```
log->write("Log entry categorized as INFO");
log->write("Error message", Logger::MsgType::ERROR);
log->write("Some warning", Logger::MsgType::WARNING);
```
The logger will create a "test.log" file under "./log/\<date\>/" directory and then write something like:
```
[18:52:10:826] INFO:	Log entry categorized as INFO
[18:52:10:827] ERROR:	Error message
[18:52:10:827] WARNING:	Some warning
```

## Build
The project is configured with [CMake](https://cmake.org/). To build the library, do the following:
```
cd path/to/this/project; mkdir build; cd build          # Make a build directory.
cmake ..    		                                # Generate a Makefile.
make                                                    # Build the program.
```

## Tests
Tests are managed with [Catch](https://github.com/catchorg/Catch2). To run tests, execute the following commands:
```
cd path/to/this/project/tests; mkdir build; cd build    # Make a build directory.
cmake ..    		                                # Generate a Makefile.
make                                                    # Build the program.
```
Note that the tests need to be statically linked against a compiled logger library (read "Build" section above to learn how to make the library file).

## License
The library is distributed under MIT License which means you can freely use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the "Software" as described in the [LICENSE file](https://github.com/oyyablokov/cpp-logger/blob/master/LICENSE).

## FAQ
**Q: Cannot build the library. I get errors about filesystem like "fatal error: filesystem: No such file or directory
compilation terminated.". What shall I do?**

**A:** The library uses the std::filesystem which is currently (at the moment of writing this document) not available on many compilers and platforms (for example, MinGW is not supported AFAIK). If possible, consider changing your compiler/platform.
<br><br>
**Q: Is this logger thread-safe?**

**A:** Yes, it is thread-safe: log entries are thread-safely stored in a container and once in a user-defined time interval logger's worker thread locks the container and writes its content to a file, then clears the container. Threads are managed with std::thread.

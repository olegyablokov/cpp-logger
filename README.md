## Getting started
This is a fast, easy-to-use, thread-safe, standalone C++17 library for logging.

## Usage
To use the logger, do the following:

0. Add the logger to your CMake-configured project:
```
add_subdirectory(<path/to/cpp_logger>)
```

1. Include this header into your C++ file:
```
 #include <logger.h>
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
The logger will create a `test.log` file under `./log/\<date\>/` directory and then write something like:
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
If build is successful, the library will appear in the `path/to/this/project/lib` directory.

## Tests
Tests are managed with [Catch](https://github.com/catchorg/Catch2) and are by default excluded from ALL targets. This means if you want to build them, run the commands from the "Build" section but replace the last command with:
```
make logger_tests
```
If build is successful, an executable will appear in the `path/to/this/project/bin` directory.

## License
This project is distributed under MIT License which means you can freely use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the "Software" as described in the [LICENSE file](https://github.com/oyyablokov/cpp-logger/blob/master/LICENSE).

## FAQ
**Q: Cannot build the library. I get errors about filesystem like "fatal error: filesystem: No such file or directory compilation terminated.". What shall I do?**

**A:** The library uses the `std::filesystem` which is currently (at the moment of writing this document) not available on many compilers and platforms (for example, MinGW is not supported AFAIK). If possible, consider upgrading your compiler or changing your compiler/platform.
<br><br>
**Q: Is this logger thread-safe?**

**A:** Yes, it is thread-safe: log entries are thread-safely stored in a container and once in a user-defined time interval logger's worker thread locks the container and writes its content to a file, then clears the container. Threads are managed with `std::thread`.

**Q: I want to use the compiled library directly OR I don't use CMake in my project. Is there a workaround?**

**A:** Yes, you can compile the library and then use it directly. Just link it (in CMake you can do it with `target_link_libraries(<your_project_name>, path/to/<logger_lib>)`) and then include the `path/to/this/project/include/logger.h` header in your code.

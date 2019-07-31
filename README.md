## Getting started
This is my implementation of a multithreading C++ library for logging.



Operating system | Status
---------------- | ----------
Linux            | [![TravisCI](https://img.shields.io/travis/oyyablokov/cpp-logger/develop.svg)](https://travis-ci.org/oyyablokov/cpp-logger)
Windows          | [![AppVeyor](https://img.shields.io/appveyor/ci/oyyablokov/cpp-logger/develop.svg)](https://ci.appveyor.com/project/oyyablokov/cpp-logger)

## Usage
To use the logger, do the following:

1. Add the logger to your CMake-configured project:
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
The project is configured with [CMake](https://cmake.org/). The building process may vary on different platforms and environments, though it follows the same pattern:
```
cd path/to/this/project; mkdir build; cd build          # Make a build directory.
cmake ..    		                                # Generate a Makefile.
make                                                    # Build the program.
```
If build is successful, the library will appear in the `path/to/this/project/lib` directory.

## Tests
Tests are managed with [Catch](https://github.com/catchorg/Catch2) and are by default excluded from ALL targets. It means if you want to build them, run the commands from the "Build" section but replace the last command with:
```
make logger_tests
```
If build is successful, an executable will appear in the `path/to/this/project/bin` directory.

## License
This project is distributed under MIT License which means you can freely use, copy, modify, merge, publish, distribute, sublicense, and/or sell copies of the "Software" as described in the [LICENSE file](https://github.com/oyyablokov/cpp-logger/blob/master/LICENSE).

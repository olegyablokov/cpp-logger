# Copyright (c) 2018 Oleg Yablokov
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
# The above copyright notice and this permission notice shall be included in all
# copies or substantial portions of the Software.
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
# SOFTWARE.

cmake_minimum_required(VERSION 3.11)
project(LoggerTest)

set(CMAKE_CXX_STANDARD 17)

include(${CMAKE_CURRENT_SOURCE_DIR}/../CMakeLists.txt)
message("MY_VAR: ${MY_VAR}")

add_executable(LoggerTest main.cpp logger_tests.cpp)

# Linking against the logger library
set(LoggerLibName "${CMAKE_CURRENT_SOURCE_DIR}/../build/Logger.lib")
if(NOT EXISTS ${LoggerLibName})
	message(FATAL_ERROR "Couldn't find the library file of the logger. Its name is set as: ${LoggerLibName}.\nDid you forget to compile it?")
else() 
	target_link_libraries(LoggerTest ${LoggerLibName})
	message("Logger library successfully loaded.")
endif()

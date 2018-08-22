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
project(logger)

set(CMAKE_CXX_STANDARD 17)

if (WIN32)
    set(LOGGER_TARGET_LIBRARY_NAME "${PROJECT_NAME}.lib")
else() 
    set(LOGGER_TARGET_LIBRARY_NAME "lib${PROJECT_NAME}.a")
endif()

set(LOGGER_SOURCE_FILES
    ${CMAKE_CURRENT_LIST_DIR}/src/logger.cpp
    ${CMAKE_CURRENT_LIST_DIR}/src/logger_impl.cpp
	${CMAKE_CURRENT_LIST_DIR}/src/utility.cpp)
add_library(${PROJECT_NAME} ${LOGGER_SOURCE_FILES})
target_link_libraries(${PROJECT_NAME} stdc++fs pthread)


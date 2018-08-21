cmake_minimum_required(VERSION 3.11)
project(LoggerTest)

set(CMAKE_CXX_STANDARD 17)

if(EXISTS ${CMAKE_CURRENT_SOURCE_DIR}/../build/libLogger.a)
   target_link_libraries(LoggerTest ${CMAKE_CURRENT_SOURCE_DIR}/../build/libLogger.a)
else(message(FATAL_ERROR "Couldn't find the library file of the logger. Did you forget to compile it?"))
endif()

set(SOURCE_FILES 
	main.cpp
	logger_tests.cpp)
add_executable(LoggerTest ${SOURCE_FILES})

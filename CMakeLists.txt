cmake_minimum_required(VERSION 3.11)
project(Logger)

set(CMAKE_CXX_STANDARD 17)

set(SOURCE_FILES
	logger.h
	src/logger.cpp
	src/logger_impl.h
    src/logger_impl.cpp
	src/utility.h)
add_library(Logger ${SOURCE_FILES})
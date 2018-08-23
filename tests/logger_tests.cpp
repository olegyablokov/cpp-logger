#include "catch.hpp"
#include <logger.h>
#include "../src/utility.h"
#include "utility_tests.h"

#include <thread>
#include <chrono>

#include <iostream>

TEST_CASE("Log files can be created in current directory", "[logger]")
{
	auto log = Logger::create("test.log", ""/*, std::chrono:milliseconds(10)*/);
	log->start();
	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	CHECK(file_exists("test.log"));
	CHECK(!file_is_empty("test.log"));

	// clear the working directory
	if (file_exists("test.log")) system((std::string(REMOVE_FILE_CMD) + " test.log").c_str());
}

TEST_CASE("Log files can be created in a subdirectory to the current directory", "[logger]")
{
	auto log = Logger::create("test.log", "dir"/*, std::chrono:milliseconds(10)*/);
	log->start();
	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	CHECK(file_exists("dir/test.log"));
	CHECK(!file_is_empty("dir/test.log"));

	// clear the working directory
	if (file_exists("dir/test.log")) system((std::string(REMOVE_FILE_CMD) + " dir/test.log").c_str());
}

TEST_CASE("Log files can be created in a directory with absolute path", "[logger]")
{
	std::string dir;
#ifdef __linux__
	dir = "~";
#elif _WIN32
	//dir = "C:\Users\%USERNAME%";
#endif

	auto log = Logger::create("test.log", dir/*, std::chrono:milliseconds(10)*/);
	log->start();
	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	CHECK(file_exists(dir + "/test.log"));
	CHECK(!file_is_empty(dir + "/test.log"));

	// clear the working directory
	if (file_exists(dir + "/test.log")) system((std::string(REMOVE_FILE_CMD) + " " + dir + "/test.log").c_str());
}

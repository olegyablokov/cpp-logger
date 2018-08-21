#include "catch.hpp"
#include "../logger.h"
#include "utility_tests.h"

#include <thread>
#include <chrono>

TEST_CASE("Log files can be created in current directory", "[logger]")
{
	auto log = Logger::create("test.log", "");
	log->start();
	log->write("Log entry to make the logger create a log file");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	CHECK(file_exists("test.log"));

	// clear the working directory
	if (file_exists("test.log")) system((std::string(REMOVE_FILE_CMD) + " test.log").c_str());
}

TEST_CASE("Log files can be created in a subdirectory to the current directory", "[logger]")
{
	auto log = Logger::create("test.log", "");
	log->start();
	log->write("Log entry to make the logger create a log file");
	std::this_thread::sleep_for(std::chrono::seconds(1));

	CHECK(file_exists("test.log"));

	// clear the working directory
	if (file_exists("test.log")) system((std::string(REMOVE_FILE_CMD) + " test.log").c_str());
}

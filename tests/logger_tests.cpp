#include "catch.hpp"
#include <logger.h>
#include "../src/utility.h"
#include "utility_tests.h"

#include <thread>
#include <chrono>
#include <filesystem>

#include <iostream>

TEST_CASE("Log files can be created in current directory", "[filesystem]")
{
	std::string file_path = logger_impl::get_current_date() + "/";
	std::string file_full_name = file_path + "test.log";

	auto log = Logger::create("test.log", "", std::chrono::milliseconds(10));
	log->start();
	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	CHECK(std::filesystem::exists(file_full_name));
	CHECK(!file_is_empty(file_full_name));

	// delete temporary files
	std::filesystem::remove(file_full_name);
	std::filesystem::remove(file_path);
}

TEST_CASE("Log files can be created in a subdirectory to the current directory", "[filesystem]")
{
	std::string file_path = "log/" + logger_impl::get_current_date() + "/";
	std::string file_full_name = file_path + "test.log";

	auto log = Logger::create("test.log", "log", std::chrono::milliseconds(10));
	log->start();
	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	CHECK(std::filesystem::exists(file_full_name));
	CHECK(!file_is_empty(file_full_name));

	// delete temporary files
	std::filesystem::remove(file_full_name);
	std::filesystem::remove("log/" + logger_impl::get_current_date());
	std::filesystem::remove("log/");
}

TEST_CASE("Log files can be created in a directory with absolute path", "[filesystem]")
{
	std::string file_path = std::filesystem::temp_directory_path().string() + "/" + logger_impl::get_current_date() + "/";
	std::string file_full_name = file_path + "test.log";
	
	auto log = Logger::create("test.log", std::filesystem::temp_directory_path().string(), std::chrono::milliseconds(10));
	log->start();
	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	CHECK(std::filesystem::exists(file_full_name));
	CHECK(!file_is_empty(file_full_name));

	// delete temporary files
	std::filesystem::remove(file_full_name);
	std::filesystem::remove(file_path);
}

TEST_CASE("Logging can be stopped and resumed", "[logger]")
{
	std::string file_path = logger_impl::get_current_date() + "/";
	std::string file_full_name = file_path + "test.log";

	auto log = Logger::create("test.log", "", std::chrono::milliseconds(10));
	log->start();
	log->stop();

	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	CHECK(!std::filesystem::exists(file_full_name));

	log->start();
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	CHECK(!std::filesystem::exists(file_full_name));

	log->write("Test log entry");
	std::this_thread::sleep_for(std::chrono::milliseconds(50));

	CHECK(std::filesystem::exists(file_full_name));
	CHECK(!file_is_empty(file_full_name));

	// delete temporary files
	std::filesystem::remove(file_full_name);
	std::filesystem::remove(file_path);
}

TEST_CASE("All log messages passed to Logger before calling stop are written to file", "[logger]")
{
	std::string file_path = logger_impl::get_current_date() + "/";
	std::string file_full_name = file_path + "test.log";

	auto log = Logger::create("test.log", "", std::chrono::milliseconds(50));
	log->start();
	std::this_thread::sleep_for(std::chrono::milliseconds(25)); // wait for logger thread to go into sleep
	log->write("Test log entry");
	log->stop();
	std::this_thread::sleep_for(std::chrono::milliseconds(100));

	CHECK(std::filesystem::exists(file_full_name));
	CHECK(!file_is_empty(file_full_name));

	// delete temporary files
	std::filesystem::remove(file_full_name);
	std::filesystem::remove(file_path);
}

TEST_CASE("Logger can be safely terminated while it is working", "[logger]")
{
	std::string file_path = logger_impl::get_current_date() + "/";
	std::string file_full_name = file_path + "test.log";

	auto log = Logger::create("test.log", "", std::chrono::milliseconds(50));
	log->start();
	for (int i = 0; i < 1000; ++i) log->write(std::to_string(i));
	std::this_thread::sleep_for(std::chrono::milliseconds(100));
	delete log;

	CHECK(std::filesystem::exists(file_full_name));
	CHECK(!file_is_empty(file_full_name));

	// delete temporary files
	std::filesystem::remove(file_full_name);
	std::filesystem::remove(file_path);
}

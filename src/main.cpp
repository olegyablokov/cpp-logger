#include "../logger.h"

#include <iostream>
#include <chrono>
#include <thread>
#include <chrono>
#include <iomanip>
#include <ctime>

int main()
{
	auto log = Logger::create("test.log", "log");
	log->start();

	for (size_t i = 0; i < 1; i++)
	{
		log->write("Log entry categorized as INFO");
		log->write("Error message", Logger::MsgType::ERROR);
		log->write("Some warning", Logger::MsgType::WARNING);
		std::this_thread::sleep_for(std::chrono::milliseconds(100));
	}

	std::this_thread::sleep_for(std::chrono::seconds(42));
	return 0;
}

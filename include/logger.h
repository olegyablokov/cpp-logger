/*
Copyright (c) 2018 Oleg Yablokov
Permission is hereby granted, free of charge, to any person obtaining a copy
of this software and associated documentation files (the "Software"), to deal
in the Software without restriction, including without limitation the rights
to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
copies of the Software, and to permit persons to whom the Software is
furnished to do so, subject to the following conditions:
The above copyright notice and this permission notice shall be included in all
copies or substantial portions of the Software.
THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
SOFTWARE.
**/

#pragma once
#include "logger_settings.h"

/**
* @brief The interface class for logging.
* @note Don't try to call its constructor directly as this class provides no implementation. Instead, use the static Logger* Logger::create(...) method.
*/
class Logger
{
public:
	/**
	* @brief Message type written in a log file along with the message.
	* @note If you want to add your own types, don't forget to update the logger_impl::get_msg_type_name(...) function in utility.cpp.
	*/
	enum MsgType
	{
		INFO,
		DEBUG,
		WARNING,
		FATAL,
		TRACE,
		ERROR,
		ALERT,
		CRITICAL,
		NOTICE
	};

	virtual ~Logger() {};

	/**
	* @brief The factory method of this class. Use it to create your own logger object.
	* @note The logger won't start until the start() method is called.
	*/
	static Logger* create(const std::string& log_name = "name.log",
		const std::string& log_dir = ".",
		std::chrono::milliseconds logging_freq = std::chrono::milliseconds(500));

	/**
	* @brief The method for writing a log entry. 
	* @note Log files are created only when there is something to write into them.
	* @note If the logger is stopped (is_started() == false) all the messages passed to this method are dropped.
	*/
	virtual void write(const std::string& msg, MsgType&& type = MsgType::INFO) = 0;

	/**
	* @brief The method which starts logging or resumes it if it has been stopped with the stop() method.
	*/
	virtual void start() = 0;

	/**
	* @brief The method which stops logging. 
	* @note The logger will write all the messages which had been given to it before this method was called.
	* @note This method is blocking: it will not return until logging is stopped.
	*/
	virtual void stop() = 0;

	/**
	* @brief The method which returns true if logging is enabled and false otherwise.
	*/
	virtual bool is_running() const noexcept = 0;

	virtual LoggerSettings get_settings() const noexcept = 0;

protected:
	Logger(const std::string& log_name = "name.log",
		const std::string& log_dir = ".",
		std::chrono::milliseconds logging_freq = std::chrono::milliseconds(500)) {};
};

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

#include "utility.h"

#include <chrono>
#include <set>
#include <sstream>
#include <filesystem>

namespace logger_impl
{
	std::string get_msg_type_name(const Logger::MsgType& type)
	{
		if (type == Logger::MsgType::INFO) return "INFO";
		else if (type == Logger::MsgType::DEBUG) return "DEBUG";
		else if (type == Logger::MsgType::WARNING) return "WARNING";
		else if (type == Logger::MsgType::FATAL) return "FATAL";
		else if (type == Logger::MsgType::TRACE) return "TRACE";
		else if (type == Logger::MsgType::ERROR) return "ERROR";
		else if (type == Logger::MsgType::ALERT) return "ALERT";
		else if (type == Logger::MsgType::CRITICAL) return "CRITICAL";
		else if (type == Logger::MsgType::NOTICE) return "NOTICE";
		else throw(std::logic_error("Unknown Logger::MsgType. Did you forget to register it in logger_impl::get_msg_type_name(...)?"));
	}

	std::string get_current_date()
	{
		std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
		std::time_t time_now_t = std::chrono::system_clock::to_time_t(time_now);
		std::tm now_tm = *std::localtime(&time_now_t);

		std::stringstream ss;
		ss << std::put_time(&now_tm, "%Y.%m.%d");
		return ss.str();
	}

	std::string get_current_time()
	{
		auto now = std::chrono::system_clock::now();
		auto seconds = std::chrono::time_point_cast<std::chrono::seconds>(now);
		auto fraction = now - seconds;
		time_t cnow = std::chrono::system_clock::to_time_t(now);
		auto milliseconds = std::chrono::duration_cast<std::chrono::milliseconds>(fraction).count();
		std::string ms_str;
		if (milliseconds < 10) ms_str = "00" + std::to_string(milliseconds);
		else if (milliseconds < 100) ms_str = "0" + std::to_string(milliseconds);
		else ms_str = std::to_string(milliseconds);

		std::chrono::time_point<std::chrono::system_clock> time_now = std::chrono::system_clock::now();
		std::time_t time_now_t = std::chrono::system_clock::to_time_t(time_now);
		std::tm now_tm = *std::localtime(&time_now_t);

		std::stringstream ss;
		ss << std::put_time(&now_tm, "[%H:%M:%S:") << ms_str << "]";

		return ss.str();
	}

	bool str_contains_one_of_symbols(const std::string& str, const std::string& symbols)
	{
		std::set<char> symbols_set;
		for (auto& c : symbols) symbols_set.insert(c);
		bool is_in = false;
		for (auto& c : str)
		{
			is_in = (symbols_set.find(c) != symbols_set.end());
			if (is_in) break;
		};
		return is_in;
	}

	bool pathname_is_valid(const std::string& name)
	{
		if ((name.length() > _MAX_PATH) || (str_contains_one_of_symbols(name, "\\:*?\"<>|"))) return false;
		else return true;
	}

	bool filename_is_valid(const std::string& name)
	{
		if ((name.length() > _MAX_PATH) || (str_contains_one_of_symbols(name, "\\:*?\"<>|/"))) return false;
		else return true;
	}
}
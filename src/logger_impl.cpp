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

#include "logger_impl.h"
#include "utility.h"

#include <filesystem>
#include <fstream>

namespace logger_impl
{
	LoggerImpl::LoggerImpl(const std::string& log_name, const std::string& log_dir, std::chrono::milliseconds logging_freq) :
		Logger(log_name, log_dir, logging_freq), m_LoggerSettings{ log_name, log_dir, logging_freq }
	{
		if (log_dir == "") m_LoggerSettings.log_dir = ".";
		std::string test_dir = m_LoggerSettings.log_dir + "/" + get_current_date();
		if (filename_is_valid(test_dir)) throw std::invalid_argument("Filename \"" + test_dir + "\" is not valid");
		if (filename_is_valid(log_name)) throw std::invalid_argument("Filename \"" + log_name + "\" is not valid");

	};

	void LoggerImpl::write(const std::string& msg, MsgType&& type)
	{
		std::lock_guard<std::mutex> lock(m_WriteMutex);
		m_LogEntries.push(LogEntry{ msg, type, get_current_time(), get_current_date() });
	}

	void LoggerImpl::start() noexcept
	{
		m_IsStarted.store(true);
		m_WriterThread.reset(new std::thread(&logger_impl::LoggerImpl::run, this));
	}	

	void LoggerImpl::stop() noexcept
	{
		m_IsStarted.store(false);
		m_WriterThread->join();
		m_WriterThread.reset();
	}

	bool LoggerImpl::is_started() const noexcept
	{
		return m_IsStarted.load();
	}

	LoggerSettings LoggerImpl::get_settings() const noexcept
	{
		return m_LoggerSettings;
	}

	void LoggerImpl::run()
	{
		std::string prev_dir, prev_file_name;
		std::string cur_dir, cur_file_name;
		std::string log_msgs;
		while (m_IsStarted.load())
		{
			while (!m_LogEntries.empty())
			{
				std::lock_guard<std::mutex> lock(m_WriteMutex);

				auto const& entry = m_LogEntries.front();
				cur_dir = m_LoggerSettings.log_dir + "/" + entry.date;
				cur_file_name = cur_dir + "/" + m_LoggerSettings.log_name;

				if (cur_file_name == prev_file_name || prev_file_name == "")
				{
				}
				else
				{
					std::filesystem::create_directories(prev_dir);
					std::ofstream file(prev_file_name.c_str(), std::ofstream::app);
					file << log_msgs;
					file.close();
					log_msgs = "";
				}
				log_msgs += entry.time + " " + get_msg_type_name(entry.type) + ":\t" + entry.msg + "\n";

				prev_dir = cur_dir;
				prev_file_name = cur_file_name;
				m_LogEntries.pop();
			}
			std::this_thread::sleep_for(m_LoggerSettings.logging_freq);
		}
	}
}

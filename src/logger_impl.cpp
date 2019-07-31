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
		else std::filesystem::create_directories(m_LoggerSettings.log_dir);
		m_IsRunning.store(false);
	}

	LoggerImpl::~LoggerImpl()
	{
		stop();
	}

	void LoggerImpl::write(const std::string& msg, MsgType&& type)
	{
		if (m_IsRunning.load())
		{
			std::lock_guard<std::mutex> lock(m_WriteMutex);
			m_LogEntries.push(LogEntry{ msg, type, get_current_time(), get_current_date() });
		}
	}

	void LoggerImpl::start()
	{
		if (!m_IsRunning.load())
		{
			m_IsRunning.store(true);
			m_WriterThread.reset(new std::thread(&logger_impl::LoggerImpl::run, this));
		}
	}	

	void LoggerImpl::stop()
	{
		if (m_IsRunning.load())
		{
			m_IsRunning.store(false);
			m_WriterThread->join();
			m_WriterThread.reset();
		}
	}

	bool LoggerImpl::is_running() const noexcept
	{
		return m_IsRunning.load();
	}

	LoggerSettings LoggerImpl::get_settings() const noexcept
	{
		return m_LoggerSettings;
	}

	void LoggerImpl::run()
	{
		while (m_IsRunning.load())
		{
			flush_log_entries_to_file();
			std::this_thread::sleep_for(m_LoggerSettings.logging_freq);
		}
		flush_log_entries_to_file();
	}

	void LoggerImpl::flush_log_entries_to_file()
	{
		std::lock_guard<std::mutex> lock(m_WriteMutex);
		std::string dir, file_name;
		std::string prev_date;
		std::string log_msgs;

		while (!m_LogEntries.empty())
		{
			auto const& entry = m_LogEntries.front();
			log_msgs += entry.time + " " + get_msg_type_name(entry.type) + ":\t" + entry.msg + "\n";

			dir = m_LoggerSettings.log_dir + "/" + entry.date;
			file_name = dir + "/" + m_LoggerSettings.log_name;

			if (m_LogEntries.size() == 1 || prev_date == entry.date)
			{ // flush log_msgs into file
				std::filesystem::create_directories(dir);
				std::ofstream file(file_name.c_str(), std::ofstream::app);
				file << log_msgs;
				file.close();
				log_msgs = "";
			}

			prev_date = entry.date;
			m_LogEntries.pop();
		}
	}
}

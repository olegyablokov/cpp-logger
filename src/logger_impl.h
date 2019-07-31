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
#include <logger.h>

#include <memory>
#include <atomic>
#include <mutex>
#include <string>
#include <thread>
#include <queue>
#include <chrono>

namespace logger_impl
{
	struct LogEntry
	{
		std::string msg;
		Logger::MsgType type;
		std::string time;
		std::string date;
	};

	class LoggerImpl : public Logger
	{
	public:
		LoggerImpl(const std::string& log_name = "name.log",
			const std::string& log_dir = ".",
			std::chrono::milliseconds logging_freq = std::chrono::milliseconds(500));
		virtual ~LoggerImpl();

		virtual void write(const std::string& msg, MsgType&& type = MsgType::INFO) override;
		virtual void start() override;
		virtual void stop() override;
		virtual bool is_running() const noexcept override;

		virtual LoggerSettings get_settings() const noexcept override;

	private:
		void run();
		void flush_log_entries_to_file();
		
		std::unique_ptr<std::thread> m_WriterThread;
		std::mutex m_WriteMutex;
		std::queue<LogEntry> m_LogEntries;
		std::atomic<bool> m_IsRunning;
		LoggerSettings m_LoggerSettings;
	};
}

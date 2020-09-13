#include <modeco/IostreamLoggerSink.h>
#include <iostream>

namespace mco {

	void IostreamLoggerSink::Output(const std::string& message, LogSeverity severity) {
		std::lock_guard<std::mutex> lock(mutex);

		// add color before messages
		switch(severity) {
			case LogSeverity::Warning:
				std::cout << "\033[33;1m";
				break;

			case LogSeverity::Error:
				std::cout << "\033[31;1m";
				break;

			// we don't color these
			case LogSeverity::Verbose:
			case LogSeverity::Info:
			default:
				break;
		}

		std::cout << message << "\033[0m" << '\n';
	}
	
} // namespace mco
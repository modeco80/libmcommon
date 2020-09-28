#include <modeco/Logger.h>
#include <ctime>
#include <chrono>

#if defined(DOPT_ASSERT)
	#include <iostream>
#endif

namespace mco {

	/**
	 * The output sink that the mcommon logger will use across all channels.
	 */
	Sink* Logger::LoggerSink = nullptr;

	/**
	 * Whether or not verbose/debug messages should be allowed across all channels.
	 */
	bool Logger::AllowVerbose = false;

	// static functions

	Logger Logger::CreateLogger(const std::string& channel) {
		Logger logger;
		logger.channel_name = channel;

		return logger;
	}

	void Logger::SetSink(Sink* sink) {
		Logger::LoggerSink = sink;
	}

	void Logger::SetAllowVerbose(bool allow) {
		Logger::AllowVerbose = allow;
	}

	std::string Logger::TimestampString() {
		std::time_t t = std::chrono::system_clock::to_time_t(std::chrono::system_clock::now());
		std::string ts = std::string(std::ctime(&t));

		ts.back() = ']';
		ts.insert(ts.begin(), '[');

		return ts;
	}

#if defined(DOPT_ASSERT)
	// Sink that does nothing to make it so the program should run
	struct DebugNullSink : public Sink {
		void Output(const std::string& str, LogSeverity ls) {
		}
	};
#endif

	void Logger::DoBaseFormatting(std::ostringstream& oss, LogSeverity ls) {
		// Odd place to put this but meh
#if defined(DOPT_ASSERT)
		if(!Logger::LoggerSink) {
			static DebugNullSink safe;
			// output a console message warning that the sink wasn't set
			std::cout << "USAGE ERROR: Sink wasn't set!!!\n";
			std::cout << "The application will crash if built without the DOPT_ASSERT define.\n";
			std::cout << "A null sink has been set that won't output anything\n";
			std::cout << "but will let the application successfully run.\n";
			std::cout << "Check if a Logger::SetSink call was commented out or not made!\n";

			// then set our (debug only) safe sink as the sink to use. This will let the program run
			// but isn't useful at all for any logging purposes.
			Logger::SetSink(&safe);
			return;
		}
#endif

		oss << TimestampString() << " [" << channel_name << "/";

		switch(ls) {
			case LogSeverity::Info:
				oss << "INFO] ";
				break;

			case LogSeverity::Warning:
				oss << "WARN] ";
				break;

			case LogSeverity::Error:
				oss << "ERROR] ";
				break;

			// we don't color for these
			case LogSeverity::Verbose:
				oss << "VERBOSE] ";
				break;

			default:
				break;
		}
	}

	Logger::Logger() {
	}

	Logger::Logger(Logger&& c) {
		this->channel_name = c.channel_name;
	}

} // namespace mco
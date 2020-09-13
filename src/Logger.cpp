#include <modeco/Logger.h>
#include <ctime>
#include <chrono>

namespace mco {

	/**
	 * The output sink that the mcommon logger will use across all channels.
	 * If null, then the logger will not attempt to access the sink.
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

	void Logger::DoBaseFormatting(std::ostringstream& oss, LogSeverity ls) {
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
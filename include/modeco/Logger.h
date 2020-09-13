#pragma once

#include <sstream>
#include <stdexcept>
#include <string>
#include <modeco/types.h>
#include <modeco/source_location.h>

namespace mco {

	/**
	 * Log reporting serverity.
	 */
	enum class LogSeverity : byte {
		/**
		 * A verbose message. Should only be emitted
		 * if Logger::AllowVerbose == true.
		 */
		Verbose,
		/**
		 * An informational message. This can be used to report information to the user.
		 */
		Info,

		/**
		 * An message that can be used to warn the user of a condition that may be wrong.
		 */
		Warning,

		/**
		 * An message that can be used to warn the user of a condition that is definitely wrong.
		 */
		Error
	};

	/**
	 * Logger sink.
	 */
	struct Sink {
		/**
		 * Output somewhere arbitrary.
		 */
		virtual void Output(const std::string& message, LogSeverity severity) = 0;
	};

	struct Logger {
		
		/**
		 * Create a logger with a user-specified channel name.
		 * 
		 * \param[in] channel The channel name to use. Can be anything.
		 */
		static Logger CreateLogger(const std::string& channel);

		/**
		 * Set the sink used for all loggers to this sink.
		 */
		static void SetSink(Sink* sink);
		
		static void SetAllowVerbose(bool allow);


		template <typename... Args>
		inline void info(Args... args) {
			if(!Logger::LoggerSink)
				return;

			std::ostringstream ss;
			DoBaseFormatting(ss, LogSeverity::Info);

			((ss << std::forward<Args>(args)), ...);

			LoggerSink->Output(ss.str(), LogSeverity::Info);

			ss.clear();
		}

		template <typename... Args>
		inline void warn(Args... args) {
			if(!Logger::LoggerSink)
				return;

			std::ostringstream ss;
			DoBaseFormatting(ss, LogSeverity::Warning);

			((ss << std::forward<Args>(args)), ...);

			LoggerSink->Output(ss.str(), LogSeverity::Warning);
			ss.clear();
		}

		template <typename... Args>
		inline void error(mco::source_location loc, Args... args) {
			if(!Logger::LoggerSink)
				return;

			std::ostringstream ss;
			DoBaseFormatting(ss, LogSeverity::Error);

			((ss << std::forward<Args>(args)), ...);

			ss << " (" << loc.file_name() << ':' << loc.line() << ')';

			LoggerSink->Output(ss.str(), LogSeverity::Error);

			ss.clear();
		}

		template <typename... Args>
		inline void verbose(mco::source_location loc, Args... args) {
			if(!Logger::LoggerSink || !Logger::AllowVerbose)
				return;

			std::ostringstream ss;
			DoBaseFormatting(ss, LogSeverity::Verbose);

			((ss << std::forward<Args>(args)), ...);

			ss << " (" << loc.file_name() << ':' << loc.line() << ')';

			LoggerSink->Output(ss.str(), LogSeverity::Verbose);

			ss.clear();
		}

// I wish there was a better way to do this, but there doesn't reliably seem to be unless I make all of these structs
// that get their own deduction guides, which is slightly (very) excessive. 
// Feel free to undef this kludge if it ends up breaking your own code.. sorry!
#define error(...) error(mco::source_location::current(), ##__VA_ARGS__)
#define verbose(...) verbose(mco::source_location::current(), ##__VA_ARGS__)

		// log exceptions with stable formatting
		inline void except(std::exception_ptr exception, mco::source_location loc = mco::source_location::current()) {
			if(!Logger::LoggerSink)
				return;

			try {
				// If the exception_ptr passed in was valid,
				// rethrow it here so we can catch details ourselves.
				if(exception)
					std::rethrow_exception(exception);

			} catch(std::exception& ex) {
				std::ostringstream ss;
				DoBaseFormatting(ss, LogSeverity::Error);

				ss << "Exception thrown: " << ex.what() << " (" << loc.file_name() << ':' << loc.line() << ')';

				LoggerSink->Output(ss.str(), LogSeverity::Error);
				ss.clear();
			}
		}

		// move constructor
		Logger(Logger&& c);


	   private:
	   
		void DoBaseFormatting(std::ostringstream& oss, LogSeverity ls);

		Logger();

		static Sink* LoggerSink;
		static bool AllowVerbose;

		static std::string TimestampString();

		/**
		 * The channel name that the logger will use.
		 */
		std::string channel_name;
	};

} // namespace mco
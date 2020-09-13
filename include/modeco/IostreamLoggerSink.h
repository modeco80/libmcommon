#pragma once
#include <modeco/Logger.h>	
#include <mutex>


namespace mco {
	
	struct IostreamLoggerSink : public Sink {
		
		void Output(const std::string& message, LogSeverity severity);
		
	   private:
		/**
		 * Mutex lock.
		 */
		std::mutex mutex;
	};
	
	
} // namespace mco
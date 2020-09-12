#include <modeco/Logger.h>
#include <iostream>
#include <mutex>

// this may become a default sink...
/** 
 * A basic stdout sink for the mcommon logger.
 */
struct StdoutSink : public mco::Sink {
	
	void Output(const std::string& message, mco::LogSeverity severity) {
		std::lock_guard<std::mutex> lock(mutex);
		
		// add color before messages
		switch(severity) {
			
			case mco::LogSeverity::Warning:
				std::cout << "\033[33;1m";
				break;
				
			case mco::LogSeverity::Error:
				std::cout << "\033[31;1m";
				break;
			
			// we don't color these
			case mco::LogSeverity::Verbose:
			case mco::LogSeverity::Info:
			default:
				break;
		}
		
		std::cout << message << "\033[0m" << '\n';
	}
	
private:
	/**
	 * Mutex lock.
	 */
	std::mutex mutex;
};

// create the sink and the logger.
static StdoutSink theSink;
static mco::Logger logger = mco::Logger::CreateChannel("Main");


int main() {
	// set the sink to our stdout sink
	// any operations before this range will end up doing nothing (safe)
	mco::Logger::SetSink(&theSink);
	
	
	// ugh.. i wish there was a better way to do this!
	
	logger.info("Hello World!");
	logger.warn("hmm. Something may be fucky wucky uwu");
	logger.error("something is fucky wucky.. uh oh fucko boingo!!!!");
	
	try {
		int i = 32;
		if(i == 32)
			throw std::runtime_error("i is an invalid value");
	} catch(std::exception& ex) {
		// log the exception
		// NOTE: We use exception_ptr because we want this to be generic in a catchall 2
		logger.except(std::current_exception());
	}
	
	logger.info("End of logger tests.");
	return 0;
}
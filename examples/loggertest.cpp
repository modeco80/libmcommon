#include <modeco/Logger.h>
#include <modeco/IostreamLoggerSink.h>
#include <mutex>

static mco::IostreamLoggerSink theSink;
mco::Logger logger = mco::Logger::CreateLogger("Main");
mco::Logger other_logger = mco::Logger::CreateLogger("Other Subsystem");

int main() {
	
	// set the sink to the default iostream sink
	// (Comment out this line and build in debug mode or add #define DOPT_ASSERT to see what happens?)
	mco::Logger::SetSink(&theSink);
	// allow verbose messages.
	mco::Logger::SetAllowVerbose(true);
	
	// log some messages here
	
	logger.info("Hello World!");
	logger.warn("hmm. Something may be fucky wucky uwu");
	logger.error("something is fucky wucky.. uh oh fucko boingo!!!!");

	other_logger.info("other subsystem says something");
	
	logger.verbose("this message should be printed if Logger::SetAllowVerbose(true) worked");
	other_logger.verbose("so should this one");

	try {
		int i = 32;
		if(i == 32)
			throw std::runtime_error("i is in fact 32");
	} catch(std::exception& ex) {
		// log the exception
		// NOTE: We use exception_ptr because we want this to be generic in a catchall too
		logger.except(std::current_exception());
	}

	logger.info("End of logger tests.");
	return 0;
}
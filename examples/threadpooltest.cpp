#include <modeco/Logger.h>
#include <modeco/IostreamLoggerSink.h>
#include <modeco/ThreadPool.h>
#include <mutex>

static mco::IostreamLoggerSink theSink;
mco::Logger logger = mco::Logger::CreateLogger("Main");


int test_waiting()  {
	std::this_thread::sleep_for(std::chrono::milliseconds(10000));
	return 38 + 4;
}

int main() {
	// set the sink to the default iostream sink
	mco::Logger::SetSink(&theSink);
	mco::ThreadPool pool;
	
	auto fut = pool.AddTask(&test_waiting);
	
	logger.info("waiting for this task...");
	
	logger.info("Value is ", fut.get());
	

	logger.info("End of thread pool tests.");
	return 0;
}
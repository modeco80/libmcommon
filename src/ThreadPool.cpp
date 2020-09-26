#include <modeco/ThreadPool.h>

namespace mco {
	constexpr std::size_t DefaultWorkerCount = 4;

	ThreadPool::ThreadPool() {
		Spawn(DefaultWorkerCount);
	}

	ThreadPool::ThreadPool(std::size_t numOfWorkers) {
		Spawn(numOfWorkers);
	}

	ThreadPool::~ThreadPool() {
		{
			std::unique_lock<std::mutex> lock(queue_lock);
			stop = true;
		}
		cond.notify_all();

		for(auto& worker : worker_threads)
			worker.join();
	}

	void ThreadPool::Spawn(std::size_t numOfWorkers) {
		for(auto i = 0u; i < numOfWorkers; ++i) {
			worker_threads.emplace_back(std::thread(&ThreadPool::WorkerThreadFunction, this));
		}
	}

	void ThreadPool::WorkerThreadFunction() {
		while(true) {
			std::packaged_task<void()> task;

			{
				std::unique_lock<std::mutex> lock(queue_lock);

				cond.wait(lock, [this] {
					return stop || !tasks.empty();
				});

				if(stop && tasks.empty())
					return;

				task = std::move(tasks.front());
				tasks.pop();
			}

			// Spawn the task in this thread.
			task();
		}
	}
} // namespace mco
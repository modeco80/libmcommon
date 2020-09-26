#include <modeco/types.h>
#include <functional>
#include <future>
#include <queue>

namespace mco {
	
	/**
	 * A simple thread pool.
	 */
	struct ThreadPool {
		
		/**
		 * Constructor that spawns a default-defined amount of workers.
		 */
		ThreadPool();
		
		/**
		 * Constructor spawning \ref numOfWorkers workers.
		 *
		 * \param[in] numOfWorkers Number or workers to spawn.
		 */
		ThreadPool(std::size_t numOfWorkers);
		
		/**
		 * Add a task. Returns the future return type.
		 */
		template <class F, class... Args>
		inline decltype(auto) AddTask(F&& f, Args&&... args) {
			typedef std::invoke_result_t<F, Args...> return_type;
			
			std::packaged_task<return_type()> task(std::bind(std::forward<F>(f), std::forward<Args>(args)...));
			auto future = task.get_future();
			
			// empace task into the queue
			{
				std::unique_lock<std::mutex> lk(queue_lock);
				tasks.emplace(std::move(task));
			}
			cond.notify_one();
			return future;
		}
		
		/**
		 * Stops thread pool and joins all threads.
		 */
		~ThreadPool();
		
	private:
	
		// TODO This could be a public API but meh
		/**
		 * Spawns \ref numOfWorkers workers.
		 *
		 * \param[in] numOfWorkers Number or workers to spawn.
		 */
		void Spawn(std::size_t numOfWorkers);
		
	
		/**
		 * Every worker thread gets this function.
		 */
		void WorkerThreadFunction();
	
		/**
		 * Worker threads.
		 */
		std::vector<std::thread> worker_threads;
		
		std::queue<std::packaged_task<void()>> tasks;
		
		std::mutex queue_lock;
		std::condition_variable cond;
		
		bool stop;
	};
	
}
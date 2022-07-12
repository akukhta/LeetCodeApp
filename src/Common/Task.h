#pragma once
#include <future>
#include <thread>

template <class RetFuture>
class Task
{
public:
	Task() = default;
	
	void setTask(std::future<RetFuture> task)
	{
		currentTask = std::future<RetFuture>(std::move(task));
	}

	void executeTask()
	{
		std::thread t([this]() 
			{
				isDone.store(false);
				
				if (preCb)
				{
					preCb();
				}
				
				currentTask.wait();
				isDone.store(true);

				if (postCb)
				{
					postCb();
				}
			});

		t.detach();
	}


	RetFuture getResult()
	{
		while (!isDone.load())
		{
			std::this_thread::sleep_for(std::chrono::milliseconds(1));
		}

		return currentTask.get();
	}

	void setPreCallBack(std::function<void()> &&preCb)
	{
		this->preCb = std::function<void()>(std::move(preCb));
	}

	void setPostCallBack(std::function<void()> &&postCb)
	{
		this->postCb = std::function<void()>(std::move(postCb));
	}

private:
	std::future<RetFuture> currentTask;
	std::atomic<bool> isDone;
	std::function<void()> preCb;
	std::function<void()> postCb;
};

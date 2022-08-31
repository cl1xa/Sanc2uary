#include "thread_pool.hpp"

namespace big
{
	thread_pool::thread_pool() : m_accept_jobs(true)
	{
		this->m_managing_thread = thread(&thread_pool::create, this);

		g_thread_pool = this;
	}

	thread_pool::~thread_pool()
	{
		g_thread_pool = nullptr;
	}

	void thread_pool::create()
	{
		const uint32_t thread_count = thread::hardware_concurrency();

		LOG(G3LOG_DEBUG) << xorstr_("Allocating ") << thread_count << xorstr_(" threads in thread pool.");
		this->m_thread_pool.reserve(thread_count);

		for (uint32_t i = 0; i < thread_count; i++)
			this->m_thread_pool.emplace_back(thread(&thread_pool::run, this));
	}

	void thread_pool::destroy()
	{
		this->m_managing_thread.join();
		{
			unique_lock lock(m_lock);
			this->m_accept_jobs = false;
		}
		this->m_data_condition.notify_all();

		for (auto& thread : m_thread_pool)
			thread.join();

		m_thread_pool.clear();
	}

	void thread_pool::push(function<void()> func)
	{
		if (func)
		{
			{
				unique_lock lock(this->m_lock);
				this->m_job_stack.push(move(func));
			}
			this->m_data_condition.notify_all();
		}
	}

	void thread_pool::run()
	{
		for (;;)
		{
			unique_lock lock(this->m_lock);

			this->m_data_condition.wait(lock, [this]()
				{
					return !this->m_job_stack.empty() || !this->m_accept_jobs;
				});

			if (!this->m_accept_jobs) break;
			if (this->m_job_stack.empty()) continue;

			function<void()> job = move(this->m_job_stack.top());

			this->m_job_stack.pop();
			lock.unlock();

			try
			{
				invoke(move(job));
			}
			catch (const exception& e)
			{
				LOG(WARNING) << "Exception thrown while executing job in thread:" << endl << e.what();
			}
		}

		LOG(G3LOG_DEBUG) << "Thread " << this_thread::get_id() << " exiting...";
	}
}
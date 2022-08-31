#include "common.hpp"
#include "fiber_pool.hpp"
#include "script.hpp"
#include "script_mgr.hpp"

namespace big
{
	fiber_pool::fiber_pool(size_t num_fibers)
	{
		for (size_t i = 0; i < num_fibers; ++i)
		{
			g_script_mgr.add_script(make_unique<script>(&fiber_func));
		}

		g_fiber_pool = this;
	}

	fiber_pool::~fiber_pool()
	{
		g_fiber_pool = nullptr;
	}

	void fiber_pool::queue_job(function<void()> func)
	{
		if (func)
		{
			lock_guard lock(m_mutex);
			m_jobs.push(move(func));
		}
	}

	void fiber_pool::fiber_tick()
	{
		unique_lock lock(m_mutex);

		if (!m_jobs.empty())
		{
			auto job = move(m_jobs.top());

			m_jobs.pop();
			lock.unlock();

			invoke(move(job));
		}
	}

	void fiber_pool::fiber_func()
	{
		while (true)
		{
			g_fiber_pool->fiber_tick();
			script::get_current()->yield();
		}
	}
}
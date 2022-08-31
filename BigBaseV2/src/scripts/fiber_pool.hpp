#pragma once
#include "common.hpp"

namespace big
{
	class fiber_pool
	{
	public:
		explicit fiber_pool(size_t num_fibers);
		~fiber_pool();

		void queue_job(function<void()> func);

		void fiber_tick();
		static void fiber_func();

	private:
		recursive_mutex m_mutex;
		stack<function<void()>> m_jobs;
	};

	inline fiber_pool* g_fiber_pool{};
}
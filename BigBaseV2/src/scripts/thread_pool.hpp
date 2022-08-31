#pragma once

namespace big
{
	class thread_pool
	{
		atomic<bool> m_accept_jobs;
		condition_variable m_data_condition;

		stack<function<void()>> m_job_stack;
		mutex m_lock;
		vector<thread> m_thread_pool;

		thread m_managing_thread;

	public:
		thread_pool();
		~thread_pool();

		void destroy();
		void push(function<void()> func);
	private:
		void create();
		void done();
		void run();
	};

	inline thread_pool* g_thread_pool{};
}
#pragma once

#include "logger.hpp"

using namespace std::chrono;

namespace big
{
	class benchmark
	{
	public:
		explicit benchmark(string name = xorstr_("")) : 
			m_start(high_resolution_clock::now()), m_name(name) {}

		void get_runtime()
		{
			auto now = high_resolution_clock::now();
			auto milliseconds_elapsed = duration_cast<milliseconds>(now - m_start);
			auto microseconds_elapsed = duration_cast<microseconds>(now - m_start);

			LOG(G3LOG_DEBUG) << m_name << xorstr_(" finished with a resulting time of: ") << milliseconds_elapsed.count() << xorstr_("ms ") << microseconds_elapsed.count() % 1000 << xorstr_("us");
		}

		void reset()
		{
			m_start = high_resolution_clock::now();
		}

	private:
		high_resolution_clock::time_point m_start;
		string m_name;
	};
}

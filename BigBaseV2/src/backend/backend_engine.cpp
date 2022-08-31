#include "backend.hpp"

namespace big
{
	void backend_engine::engine_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_engine::update_pointers();
			backend_engine::hud_transition_state();

		} QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_engine::no_idle_kick();

		} QUEUE_JOB_END_CLAUSE
	}

	void backend_engine::engine_loop()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				backend_engine::engine_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

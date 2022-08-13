#include "backend.hpp"
#include "common.hpp"
#include "script_mgr.hpp"
#include "fiber_pool.hpp"
#include "script_global.hpp"

namespace big
{
	void backend_engine::engine_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_engine::update_pointers();
			backend_engine::hud_transition_state();
			backend_engine::no_idle_kick();

		} QUEUE_JOB_END_CLAUSE
	}

	void backend_engine::script_func()
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

#include "features/features.hpp"

namespace big
{
	void features_engine::engine_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			features_engine::update_globals();
			features_engine::update_pointers();
			features_engine::hud_transition_state();

		} QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			features_engine::no_idle_kick();

		} QUEUE_JOB_END_CLAUSE
	}

	void features_engine::engine_loop()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				features_engine::engine_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

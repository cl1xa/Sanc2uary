#include "features/features.hpp"

namespace big
{
	void features_engine::engine_calls()
	{
		features_engine::update_globals();

		features_engine::update_pointers();

		features_engine::hud_transition_state();

		features_engine::no_idle_kick();
	}

	void features_engine::engine_loop()
	{
		while (g_running)
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

#include "backend/backend.hpp"

namespace big
{
	void backend_engine::engine_calls()
	{
		backend_engine::update_globals();

		backend_engine::update_pointers();

		backend_engine::hud_transition_state();

		backend_engine::no_idle_kick();
	}

	void backend_engine::engine_loop()
	{
		while (g_running)
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

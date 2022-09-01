#include "backend/backend.hpp"

namespace big
{
	void backend_utility::utility_calls()
	{
		backend_utility::keep_player_clean();

		backend_utility::no_ragdoll();
	}

	void backend_utility::utility_loop()
	{
		while (g_running)
		{
			TRY_CLAUSE
			{
				backend_utility::utility_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

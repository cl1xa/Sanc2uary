#include "backend/backend.hpp"

namespace big
{
	void backend_playercheats::player_calls()
	{
		backend_playercheats::no_police();

		backend_playercheats::player_god();

		backend_playercheats::infinite_ammo();

		backend_playercheats::noclip();
	}

	void backend_playercheats::player_loop()
	{
		while (g_running)
		{
			TRY_CLAUSE
			{
				backend_playercheats::player_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

#include "features/features.hpp"

namespace big
{
	void features_player::player_calls()
	{
		features_player::no_police();

		features_player::player_god();

		features_player::keep_player_clean();

		features_player::infinite_ammo();
	}

	void features_player::player_loop()
	{
		while (g_running)
		{
			TRY_CLAUSE
			{
				features_player::player_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

#include "backend/backend.hpp"

namespace big
{
	void backend_player::keep_player_clean()
	{
		if (g_config.cheats.player.keep_player_clean)
		{
			PED::CLEAR_PED_BLOOD_DAMAGE(globals::local_ped);
			PED::CLEAR_PED_WETNESS(globals::local_ped);
			PED::CLEAR_PED_ENV_DIRT(globals::local_ped);
			PED::RESET_PED_VISIBLE_DAMAGE(globals::local_ped);
		}
	}
}
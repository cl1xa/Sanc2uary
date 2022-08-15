#include "backend/backend.hpp"

namespace big
{
	void backend_player::keep_player_clean()
	{
		if (g_config.cheats.player.keep_player_clean)
		{
			const Ped local_ped = PLAYER::PLAYER_PED_ID();

			PED::CLEAR_PED_BLOOD_DAMAGE(local_ped);
			PED::CLEAR_PED_WETNESS(local_ped);
			PED::CLEAR_PED_ENV_DIRT(local_ped);
			PED::RESET_PED_VISIBLE_DAMAGE(local_ped);
		}
	}
}
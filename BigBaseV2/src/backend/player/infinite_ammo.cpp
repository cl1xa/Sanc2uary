#include "backend/backend.hpp"

namespace big
{
	void backend_player::infinite_ammo()
	{ 
		const Ped local_ped = PLAYER::PLAYER_PED_ID();

		if (g_config.cheats.player.infinite_ammo)
		{
			WEAPON::SET_PED_INFINITE_AMMO(local_ped, true, NULL);
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(local_ped, true);
		}
		else
		{
			WEAPON::SET_PED_INFINITE_AMMO(local_ped, false, NULL);
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(local_ped, false);
		}
	}
}
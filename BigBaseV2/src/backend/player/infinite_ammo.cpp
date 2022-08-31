#include "backend/backend.hpp"

namespace big
{
	void backend_player::infinite_ammo()
	{ 
		if (g_config.cheats.player.infinite_ammo)
		{
			WEAPON::SET_PED_INFINITE_AMMO(globals::local_ped, true, NULL);
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(globals::local_ped, true);
		}
		else
		{
			WEAPON::SET_PED_INFINITE_AMMO(globals::local_ped, false, NULL);
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(globals::local_ped, false);
		}
	}
}
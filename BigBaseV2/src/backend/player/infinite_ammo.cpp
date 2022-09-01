#include "backend/backend.hpp"

namespace big
{
	void backend_playercheats::infinite_ammo()
	{ 
		WEAPON::SET_PED_INFINITE_AMMO(globals::local_ped, g_config.cheats.player.infinite_ammo, NULL);
		WEAPON::SET_PED_INFINITE_AMMO_CLIP(globals::local_ped, g_config.cheats.player.infinite_ammo);
	}
}
#include "backend/backend.hpp"

namespace big
{
	static bool LastInfiniteAmmo = false;

	void backend_player::infinite_ammo()
	{ 
		bool InfiniteAmmo = g_config.cheats.player.infinite_ammo;
		const Ped ped = PLAYER::PLAYER_PED_ID();

		if (InfiniteAmmo 
			|| (!InfiniteAmmo && InfiniteAmmo != LastInfiniteAmmo))
		{
			WEAPON::SET_PED_INFINITE_AMMO(ped, g_config.cheats.player.infinite_ammo, NULL);
			WEAPON::SET_PED_INFINITE_AMMO_CLIP(ped, g_config.cheats.player.infinite_ammo);

			LastInfiniteAmmo = g_config.cheats.player.infinite_ammo;
		}
	}
}
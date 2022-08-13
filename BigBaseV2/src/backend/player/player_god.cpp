#include "backend/backend.hpp"

namespace big
{
	static bool LastGodmode = false;

	void backend_player::player_god()
	{
		bool Godmode = g_config.cheats.player.player_god;
		const Ped ped = PLAYER::PLAYER_PED_ID();

		if (Godmode 
			|| (!Godmode && Godmode != LastGodmode))
		{
			ENTITY::SET_ENTITY_INVINCIBLE(PLAYER::PLAYER_PED_ID(), g_config.cheats.player.player_god);
			PED::CLEAR_PED_BLOOD_DAMAGE(ped);
			PED::CLEAR_PED_WETNESS(ped);
			PED::CLEAR_PED_ENV_DIRT(ped);
			PED::RESET_PED_VISIBLE_DAMAGE(ped);

			LastGodmode = g_config.cheats.player.player_god;
		}
	}
}
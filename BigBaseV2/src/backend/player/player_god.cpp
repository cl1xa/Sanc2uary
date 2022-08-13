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
			PED::SET_PED_CONFIG_FLAG(ped, 32, g_config.cheats.player.player_god);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, g_config.cheats.player.player_god);

			PED::SET_PED_CAN_RAGDOLL(ped, g_config.cheats.player.player_god);
			ENTITY::SET_ENTITY_INVINCIBLE(ped, g_config.cheats.player.player_god);
			PED::CLEAR_PED_BLOOD_DAMAGE(ped);
			PED::CLEAR_PED_WETNESS(ped);
			PED::CLEAR_PED_ENV_DIRT(ped);
			PED::RESET_PED_VISIBLE_DAMAGE(ped);

			LastGodmode = g_config.cheats.player.player_god;
		}
	}
}
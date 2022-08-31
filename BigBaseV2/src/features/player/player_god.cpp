#include "features/features.hpp"

namespace big
{
	static bool LastGodmode = false;

	void features_player::player_god()
	{
		if (g_config.cheats.player.player_god)
		{
			PED::SET_PED_CONFIG_FLAG(globals::local_ped, 32, false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(globals::local_ped, false);

			PED::SET_PED_CAN_RAGDOLL(globals::local_ped, false);
			ENTITY::SET_ENTITY_INVINCIBLE(globals::local_ped, true);

			PED::CLEAR_PED_BLOOD_DAMAGE(globals::local_ped);
			PED::CLEAR_PED_WETNESS(globals::local_ped);
			PED::CLEAR_PED_ENV_DIRT(globals::local_ped);
			PED::RESET_PED_VISIBLE_DAMAGE(globals::local_ped);
		}
		else
		{
			PED::SET_PED_CONFIG_FLAG(globals::local_ped, 32, true);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(globals::local_ped, true);

			PED::SET_PED_CAN_RAGDOLL(globals::local_ped, true);
			ENTITY::SET_ENTITY_INVINCIBLE(globals::local_ped, false);
		}
	}
}
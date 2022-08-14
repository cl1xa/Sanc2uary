#include "backend/backend.hpp"

namespace big
{
	static bool LastGodmode = false;

	void backend_player::player_god()
	{
		const Ped ped = PLAYER::PLAYER_PED_ID();

		if (g_config.cheats.player.player_god)
		{
			PED::SET_PED_CONFIG_FLAG(ped, 32, false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, false);

			PED::SET_PED_CAN_RAGDOLL(ped, false);
			ENTITY::SET_ENTITY_INVINCIBLE(ped, true);
			PED::CLEAR_PED_BLOOD_DAMAGE(ped);
			PED::CLEAR_PED_WETNESS(ped);
			PED::CLEAR_PED_ENV_DIRT(ped);
			PED::RESET_PED_VISIBLE_DAMAGE(ped);
		}
		else
		{
			PED::SET_PED_CONFIG_FLAG(ped, 32, true);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(ped, true);

			PED::SET_PED_CAN_RAGDOLL(ped, true);
			ENTITY::SET_ENTITY_INVINCIBLE(ped, false);
		}
	}
}
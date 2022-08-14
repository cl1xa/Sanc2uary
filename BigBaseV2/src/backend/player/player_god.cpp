#include "backend/backend.hpp"

namespace big
{
	static bool LastGodmode = false;

	void backend_player::player_god()
	{
		const Ped local_ped = PLAYER::PLAYER_PED_ID();

		if (g_config.cheats.player.player_god)
		{
			PED::SET_PED_CONFIG_FLAG(local_ped, 32, false);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(local_ped, false);

			PED::SET_PED_CAN_RAGDOLL(local_ped, false);
			ENTITY::SET_ENTITY_INVINCIBLE(local_ped, true);

			PED::CLEAR_PED_BLOOD_DAMAGE(local_ped);
			PED::CLEAR_PED_WETNESS(local_ped);
			PED::CLEAR_PED_ENV_DIRT(local_ped);
			PED::RESET_PED_VISIBLE_DAMAGE(local_ped);
		}
		else
		{
			PED::SET_PED_CONFIG_FLAG(local_ped, 32, true);
			PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(local_ped, true);

			PED::SET_PED_CAN_RAGDOLL(local_ped, true);
			ENTITY::SET_ENTITY_INVINCIBLE(local_ped, false);
		}
	}
}
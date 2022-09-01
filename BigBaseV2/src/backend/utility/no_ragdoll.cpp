#include "backend/backend.hpp"

namespace big
{
	int seatbelt = 32;

	void backend_utility::no_ragdoll()
	{
		PED::SET_PED_CAN_RAGDOLL(globals::local_ped, !g_config.utility.no_ragdoll);

		PED::SET_PED_CONFIG_FLAG(globals::local_ped, seatbelt, !g_config.utility.no_ragdoll);
		PED::SET_PED_CAN_BE_KNOCKED_OFF_VEHICLE(globals::local_ped, !g_config.utility.no_ragdoll);
	}
}
#include "backend/backend.hpp"

namespace big
{
	void backend_vehicle::automatic_repair()
	{
		if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(globals::local_vehicle)
			&& (int)ePedTask::TASK_DRIVING
			&& entity::take_control_of(globals::local_vehicle))
		{
			if (!g_config.cheats.vehicle.automatic_repair)
				return;

			vehicle::repair(globals::local_vehicle);
		}
	}
}
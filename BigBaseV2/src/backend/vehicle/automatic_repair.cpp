#include "backend/backend.hpp"

namespace big
{
	void backend_vehicle::automatic_repair()
	{
		const Ped local_ped = PLAYER::PLAYER_PED_ID();
		const Vehicle local_vehicle = PED::GET_VEHICLE_PED_IS_USING(local_ped);

		if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(local_vehicle) 
			&& (int)ePedTask::TASK_DRIVING
			&& entity::take_control_of(local_vehicle))
		{
			if (!g_config.cheats.vehicle.automatic_repair)
				return;

			vehicle::repair(local_vehicle);
		}
	}
}
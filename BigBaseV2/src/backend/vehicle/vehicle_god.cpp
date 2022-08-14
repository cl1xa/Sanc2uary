#include "backend/backend.hpp"

namespace big
{
	void backend_vehicle::vehicle_god()
	{
		const Ped local_ped = PLAYER::PLAYER_PED_ID();
		const Vehicle local_vehicle = PED::GET_VEHICLE_PED_IS_USING(local_ped);

		if (g_config.cheats.vehicle.vehicle_god 
			&& (int)ePedTask::TASK_DRIVING 
			&& entity::take_control_of(local_vehicle))
		{
			VEHICLE::_SET_DISABLE_VEHICLE_WINDOW_COLLISIONS(local_vehicle, true);
			ENTITY::SET_ENTITY_INVINCIBLE(local_vehicle, true);
		}
		else
		{
			VEHICLE::_SET_DISABLE_VEHICLE_WINDOW_COLLISIONS(local_vehicle, false);
			ENTITY::SET_ENTITY_INVINCIBLE(local_vehicle, false);
		}	
	}
}
#include "backend/backend.hpp"

namespace big
{
	void backend_vehicle::vehicle_god()
	{
		if (g_config.cheats.vehicle.vehicle_god 
			&& (int)ePedTask::TASK_DRIVING 
			&& entity::take_control_of(globals::local_vehicle))
		{
			VEHICLE::_SET_DISABLE_VEHICLE_WINDOW_COLLISIONS(globals::local_vehicle, true);
			ENTITY::SET_ENTITY_INVINCIBLE(globals::local_vehicle, true);
		}
		else
		{
			VEHICLE::_SET_DISABLE_VEHICLE_WINDOW_COLLISIONS(globals::local_vehicle, false);
			ENTITY::SET_ENTITY_INVINCIBLE(globals::local_vehicle, false);
		}	
	}
}
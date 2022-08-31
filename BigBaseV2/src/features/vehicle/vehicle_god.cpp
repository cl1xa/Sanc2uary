#include "features/features.hpp"


namespace big
{
	void features_vehicle::vehicle_god()
	{
		if (g_config.cheats.vehicle.vehicle_god && vehicle::owns_vehicle(globals::local_vehicle))
		{
			VEHICLE::_SET_DISABLE_VEHICLE_WINDOW_COLLISIONS(globals::local_vehicle, true);
			ENTITY::SET_ENTITY_INVINCIBLE(globals::local_vehicle, true);
		}
		else
		{
			//Duplicate check is stupid and sloppy. Lol.
			if (vehicle::owns_vehicle(globals::local_vehicle))
			{
				VEHICLE::_SET_DISABLE_VEHICLE_WINDOW_COLLISIONS(globals::local_vehicle, false);
				ENTITY::SET_ENTITY_INVINCIBLE(globals::local_vehicle, false);
			}
		}	
	}
}
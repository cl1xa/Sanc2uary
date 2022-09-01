#include "backend/backend.hpp"

namespace big
{
	void backend_vehiclecheats::automatic_repair()
	{
		if (!g_config.cheats.vehicle.automatic_repair)
			return;

		if ((VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(globals::local_vehicle) || !VEHICLE::ARE_ALL_VEHICLE_WINDOWS_INTACT(globals::local_vehicle)) && 
			vehicle::owns_vehicle(globals::local_vehicle))
		{
			vehicle::repair(globals::local_vehicle);
		}
	}
}
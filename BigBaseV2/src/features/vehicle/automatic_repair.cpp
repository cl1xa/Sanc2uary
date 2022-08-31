#include "features/features.hpp"

namespace big
{
	void features_vehicle::automatic_repair()
	{
		if (!g_config.cheats.vehicle.automatic_repair)
			return;

		if (VEHICLE::GET_DOES_VEHICLE_HAVE_DAMAGE_DECALS(globals::local_vehicle) && 
			vehicle::owns_vehicle(globals::local_vehicle))
		{
			vehicle::repair(globals::local_vehicle);
		}
	}
}
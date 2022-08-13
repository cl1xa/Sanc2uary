#include "backend/backend.hpp"

namespace big
{
	static bool LastVehicleGodmode = false;

	void backend_vehicle::vehicle_god()
	{
		bool VehicleGodmode = g_config.cheats.vehicle.vehicle_god;
		const Ped ped = PLAYER::PLAYER_PED_ID();
		const Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

		if (VehicleGodmode 
			|| (!VehicleGodmode && VehicleGodmode != LastVehicleGodmode))
		{
			ENTITY::SET_ENTITY_INVINCIBLE(vehicle, g_config.cheats.vehicle.vehicle_god);

			LastVehicleGodmode = g_config.cheats.vehicle.vehicle_god;
		}
	}
}
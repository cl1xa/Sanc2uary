#include "backend/backend.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void backend_vehicle::automatic_repair()
	{
		static ULONGLONG tick_1 = 0;
		ULONGLONG now = GetTickCount64();

		const Player player = PLAYER::PLAYER_ID();
		const Ped ped = PLAYER::PLAYER_PED_ID();

		const Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

		if (now - tick_1 > 50) //Delay to prevent vehicle seizures
		{
			if (g_config.cheats.vehicle.automatic_repair
				&& vehicle::owns_vehicle())
			{
				vehicle::repair(vehicle);
			}

			tick_1 = now;
		}
	}
}
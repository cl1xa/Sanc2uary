#include "backend/backend.hpp"
#include "util/vehicle.hpp"

namespace big
{
	void backend_vehicle::horn_boost()
	{
		const Player player = PLAYER::PLAYER_ID();
		const Ped ped = PLAYER::PLAYER_PED_ID();
		const Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

		if (g_config.cheats.vehicle.horn_boost
			&& PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN)
			&& PLAYER::IS_PLAYER_PRESSING_HORN(player)
			&& vehicle::owns_vehicle()
			&& entity::take_control_of(vehicle))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(vehicle, 79);
		}
	}
}
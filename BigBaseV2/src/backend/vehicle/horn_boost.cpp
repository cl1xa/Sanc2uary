#include "backend/backend.hpp"

namespace big
{
	void backend_vehicle::horn_boost()
	{
		const Ped local_ped = PLAYER::PLAYER_PED_ID();
		const Vehicle local_vehicle = PED::GET_VEHICLE_PED_IS_USING(local_ped);

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN)
			&& (int)ePedTask::TASK_DRIVING
			&& entity::take_control_of(local_vehicle))
		{
			if (!g_config.cheats.vehicle.horn_boost)
				return;
			
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(local_vehicle, 79);
		}
	}
}
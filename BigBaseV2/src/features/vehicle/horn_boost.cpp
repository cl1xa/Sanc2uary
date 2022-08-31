#include "features/features.hpp"


namespace big
{
	void features_vehicle::horn_boost()
	{
		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN)
			&& (int)ePedTask::TASK_DRIVING
			&& entity::take_control_of(globals::local_vehicle))
		{
			if (!g_config.cheats.vehicle.horn_boost)
				return;
			
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(globals::local_vehicle, 79);
		}
	}
}
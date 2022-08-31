#include "features/features.hpp"


namespace big
{
	void features_vehicle::horn_boost()
	{
		if (!g_config.cheats.vehicle.horn_boost)
			return;

		if (PAD::IS_CONTROL_PRESSED(0, (int)ControllerInputs::INPUT_VEH_HORN)
			&& vehicle::owns_vehicle(globals::local_vehicle))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(globals::local_vehicle, 79);
		}
	}
}
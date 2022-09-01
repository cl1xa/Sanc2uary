#include "backend/backend.hpp"

namespace big
{
	int none = 0;
	float new_speed = 79;

	void backend_vehiclecheats::horn_boost()
	{
		if (!g_config.cheats.vehicle.horn_boost)
			return;

		if (PAD::IS_CONTROL_PRESSED(none, (int)ControllerInputs::INPUT_VEH_HORN)
			&& vehicle::owns_vehicle(globals::local_vehicle))
		{
			VEHICLE::SET_VEHICLE_FORWARD_SPEED(globals::local_vehicle, new_speed);
		}
	}
}
#include "backend/backend.hpp"

namespace big
{
	void backend_vehiclecheats::vehicle_god() { ENTITY::SET_ENTITY_INVINCIBLE(globals::local_vehicle, g_config.cheats.vehicle.vehicle_god); }
}
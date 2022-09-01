#include "backend/backend.hpp"

namespace big
{
	void backend_engine::update_globals()
	{
		globals::local_player = PLAYER::PLAYER_ID();

		globals::local_ped = PLAYER::PLAYER_PED_ID();

		globals::local_vehicle = PED::GET_VEHICLE_PED_IS_USING(globals::local_ped);
	}
}
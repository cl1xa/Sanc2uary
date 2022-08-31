#pragma once

namespace big::globals
{
	const Player local_player = PLAYER::PLAYER_ID();

	const Ped local_ped = PLAYER::PLAYER_PED_ID();

	const Vehicle local_vehicle = PED::GET_VEHICLE_PED_IS_USING(local_ped);
}
#pragma once
#include "misc.hpp"
#include "entity.hpp"
#include "teleport.hpp"
#include "math.hpp"
#include "gta/enums.hpp"
#include "script_global.hpp"

namespace big::vehicle
{
	inline auto vehicle_global = script_global(1585857);
	inline auto mechanic_global = script_global(2815059);

	inline Vehicle get_personal_vehicle()
	{
		return *mechanic_global.at(298).as<Vehicle*>();
	}

	inline void go_into_personal_vehicle()
	{
		*script_global(2671449).at(8).as<int*>() = 1;
	}

	inline bool owns_vehicle()
	{
		Ped ped = PLAYER::PLAYER_PED_ID();
		Vehicle vehicle = PED::GET_VEHICLE_PED_IS_USING(ped);

		return PED::IS_PED_IN_ANY_VEHICLE(ped, FALSE) && NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(vehicle);
	}

	inline bool repair(Vehicle veh)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh) || !entity::take_control_of(veh))
			return false;

		VEHICLE::SET_VEHICLE_FIXED(veh);
		VEHICLE::SET_VEHICLE_DEFORMATION_FIXED(veh);
		VEHICLE::SET_VEHICLE_DIRT_LEVEL(veh, 0.f);

		return true;
	}

	inline void bring(Vehicle veh, Vector3 location, bool put_in = true, int seatIdx = -1)
	{
		if (!ENTITY::IS_ENTITY_A_VEHICLE(veh)) 
			return g_notification_service->push_error("Vehicle cheats", "Vehicle is damaged or does not exist");

		auto vecVehicleLocation = ENTITY::GET_ENTITY_COORDS(veh, true);

		teleport::load_ground_at_3dcoord(vecVehicleLocation);

		if (!entity::take_control_of(veh))
			return g_notification_service->push_warning("Vehicle cheats", "Failed to take control of remote vehicle.");

		auto ped = PLAYER::PLAYER_PED_ID();

		ENTITY::SET_ENTITY_COORDS(veh, location.x, location.y, location.z + 1.f, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_HEADING(veh, ENTITY::GET_ENTITY_HEADING(ped));

		if (put_in)
		{
			for (size_t i = 0; i < 100 && math::distance_between_vectors(location, ENTITY::GET_ENTITY_COORDS(veh, true)) > 10; i++)
				script::get_current()->yield();

			auto driver_ped = VEHICLE::GET_PED_IN_VEHICLE_SEAT(veh, -1, false);

			if (driver_ped != 0)
			{
				if (PED::GET_PED_TYPE(driver_ped) == ePedType::PED_TYPE_NETWORK_PLAYER)
					TASK::CLEAR_PED_TASKS_IMMEDIATELY(driver_ped);
				else
					entity::delete_entity(driver_ped);
			}

			PED::SET_PED_INTO_VEHICLE(ped, veh, seatIdx);
		}
	}

	inline bool fix_index(int veh_idx, bool spawn_veh = false)
	{
		bool can_be_fixed = misc::has_bits_set(vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::HAS_INSURANCE);

		if (can_be_fixed)
		{
			misc::clear_bits(vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::DESTROYED | eVehicleFlags::IMPOUNDED | eVehicleFlags::UNK2);

			if (spawn_veh)
				misc::set_bits(vehicle_global.at(veh_idx, 142).at(103).as<int*>(), eVehicleFlags::TRIGGER_SPAWN_TOGGLE | eVehicleFlags::SPAWN_AT_MORS_MUTUAL);
		}

		return can_be_fixed;
	}

	inline int fix_all()
	{
		int fixed_count = 0;

		const int arr_size = *vehicle_global.as<int*>();

		for (int i = 0; i < arr_size; i++)
			if (fix_index(i, true))
				fixed_count++;

		return fixed_count;
	}
}
#pragma once

namespace big::entity
{
	inline void delete_entity(Entity ent)
	{
		ENTITY::DETACH_ENTITY(ent, 1, 1);
		ENTITY::SET_ENTITY_VISIBLE(ent, false, false);
		NETWORK::_NETWORK_SET_ENTITY_INVISIBLE_TO_NETWORK(ent, true);
		ENTITY::SET_ENTITY_COORDS_NO_OFFSET(ent, 0, 0, 0, 0, 0, 0);
		ENTITY::SET_ENTITY_AS_MISSION_ENTITY(ent, 1, 1);
		ENTITY::SET_ENTITY_AS_NO_LONGER_NEEDED(&ent);
		ENTITY::DELETE_ENTITY(&ent);
	}

	inline bool take_control_of(Entity ent)
	{
		if (NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent))
			return true;

		for (uint8_t i = 0; !NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent) && i < 250; i++)
		{
			NETWORK::NETWORK_REQUEST_CONTROL_OF_ENTITY(ent);

			script::get_current()->yield(15ms);
		}

		if (!NETWORK::NETWORK_HAS_CONTROL_OF_ENTITY(ent))
			return false;

		int netHandle = NETWORK::NETWORK_GET_NETWORK_ID_FROM_ENTITY(ent);

		NETWORK::SET_NETWORK_ID_CAN_MIGRATE(netHandle, true);

		return true;
	}

	/*namespace water
	{
		inline float* get_water_collision_ptr(CNavigation* nav)
		{
			auto nav_addr = (uint64_t)nav;
			return (float*)(*(uint64_t*)(nav_addr + 0x10) + 0x54);
		}

		inline void reset_ped_oxygen_time(CPed* ped)
		{
			auto ped_addr = (uint64_t)ped;
			*(float*)(*(uint64_t*)(ped_addr + 0x10C0) + 0x278) = 0;
		}
	}*/
}
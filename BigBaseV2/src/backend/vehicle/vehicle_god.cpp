#include "backend/backend.hpp"
#include "util/entity.hpp"

namespace big
{
	static bool LastVehicleGodmode = false;
	static float last_water_collistion_strength = 0;

	void backend_vehicle::vehicle_god()
	{
		if (g_local_player == nullptr || g_local_player->m_vehicle == nullptr || g_local_player->m_ped_task_flag)
			return;

		/*float* water_collision_ptr = nullptr;
		if (g_local_player->m_vehicle->m_navigation != nullptr)
			water_collision_ptr = entity::water::get_water_collision_ptr(g_local_player->m_vehicle->m_navigation);*/

		if (g_config.cheats.vehicle.vehicle_god && g_local_player->m_ped_task_flag && (int)ePedTask::TASK_DRIVING)
		{
			g_local_player->m_vehicle->m_deform_god = 0x8C;

			/*entity::water::reset_ped_oxygen_time(g_local_player);

			if (water_collision_ptr != nullptr && *water_collision_ptr != 0.f)
			{
				last_water_collistion_strength = *water_collision_ptr;
				*water_collision_ptr = 0;
			}*/
		}
		else
		{
			g_local_player->m_vehicle->m_deform_god = 0x9C;

			/*if (last_water_collistion_strength != 0 && water_collision_ptr != nullptr)
			{
				*water_collision_ptr = last_water_collistion_strength;
				last_water_collistion_strength = 0;
			}*/
		}
	}
}
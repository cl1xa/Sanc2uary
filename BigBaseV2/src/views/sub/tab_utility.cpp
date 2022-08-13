#include "views/view.hpp"
#include "fiber_pool.hpp"

namespace big
{
	void view_sub::tab_utility()
	{
		if (ImGui::Button(xorstr_("Suicide")))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);

			} QUEUE_JOB_END_CLAUSE

				g_notification_service->push(xorstr_("Utility"), xorstr_("Killed local player"));
		}

		if (ImGui::Button(xorstr_("Skip Cutscene")))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();

			} QUEUE_JOB_END_CLAUSE

				g_notification_service->push(xorstr_("Utility"), xorstr_("Skipped current cutscene"));
		}

		if (ImGui::Button(xorstr_("Clean Player")))
		{
			QUEUE_JOB_BEGIN_CLAUSE()
			{
				Ped ped = PLAYER::PLAYER_PED_ID();

				PED::CLEAR_PED_BLOOD_DAMAGE(ped);
				PED::CLEAR_PED_WETNESS(ped);
				PED::CLEAR_PED_ENV_DIRT(ped);
				PED::RESET_PED_VISIBLE_DAMAGE(ped);

			} QUEUE_JOB_END_CLAUSE

				g_notification_service->push(xorstr_("Utility"), xorstr_("Cleaned local player"));
		}
	}
}
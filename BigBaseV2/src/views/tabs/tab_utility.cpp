#include "views/view.hpp"
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
	}
}
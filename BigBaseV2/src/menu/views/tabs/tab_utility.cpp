#include "menu/views/view.hpp"

namespace big
{
	void view_sub::tab_utility()
	{

		queue_button(xorstr_("Suicide"), []
			{
				ENTITY::SET_ENTITY_HEALTH(PLAYER::PLAYER_PED_ID(), 0, 0);

				g_notification_service->push(xorstr_("Utility"), xorstr_("Killed local player"));
			});

		queue_button(xorstr_("Skip cutscene"), []
			{
				CUTSCENE::STOP_CUTSCENE_IMMEDIATELY();

				g_notification_service->push(xorstr_("Utility"), xorstr_("Skipped current cutscene"));
			});
	}
}
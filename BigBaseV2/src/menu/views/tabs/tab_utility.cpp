#include "menu/views/view.hpp"

namespace big
{
	void view_sub::tab_utility()
	{
		ImGui::Checkbox(xorstr_("Keep player clean"), &g_config.cheats.player.keep_player_clean);

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

		queue_button(xorstr_("Clear weather"), []
			{
				MISC::SET_OVERRIDE_WEATHER(xorstr_("EXTRASUNNY"));

				g_notification_service->push(xorstr_("Player cheats"), xorstr_("Cleared local weather"));
			});
	}
}
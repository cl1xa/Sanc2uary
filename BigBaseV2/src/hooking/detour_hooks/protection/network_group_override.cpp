#include "hooking/hooking.hpp"

namespace big
{
	void hooks::network_group_override(int64_t a1, int64_t a2, int64_t a3)
	{
		if (g_config.protection.crash.script_world_state)
		{
			if (a2 == 0 && (a3 == 103 || a3 == 0))
			{
				g_notification_service->push_warning(xorstr_("Protection"), xorstr_("Corrected unwanted data in SCRIPT_WORLD_STATE_EVENT"));

				return;
			}
		}

		return g_hooking->m_network_group_override_hook.get_original<decltype(&network_group_override)>()(a1, a2, a3);
	}
}
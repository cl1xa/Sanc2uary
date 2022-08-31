#include "hooking/hooking.hpp"

namespace big
{
	void hooks::get_network_event_data(int64_t unk, rage::CEventNetwork* net_event)
	{
		switch (net_event->get_type())
		{
			//CEventNetworkRemovedFromSessionDueToComplaints
			case 161: 
			{
				//g_notification_service->push_error(xorstr_("Session error"), xorstr_("Desynced from session host"));

				if (g_config.settings.notify_debug)
					LOG(WARNING) << xorstr_("Desynced from session host");

				break;
			}
		}

		return g_hooking->m_get_network_event_data_hook.get_original<decltype(&get_network_event_data)>()(unk, net_event);
	}
}
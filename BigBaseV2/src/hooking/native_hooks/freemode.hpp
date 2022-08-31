#pragma once

namespace big::freemode
{
	inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
	{
		if (g_config.settings.notify_debug)
			g_notification_service->push(xorstr_("NETWORK_BAIL"), xorstr_("!NETWORK_BAIL TRIGGERED!"), true);

		src->set_return_value<BOOL>(FALSE);
	};

	//Session switching optimization #1
	inline void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
	{
		LOG(G3LOG_DEBUG) << xorstr_("!NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA TRIGGERED!");

		if (g_config.misc.optimize_loading)
			src->set_return_value<BOOL>(TRUE);
	}
}
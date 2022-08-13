#pragma once
#include "gta/structs.hpp"

namespace big::freemode
{
	inline void NETWORK_BAIL(rage::scrNativeCallContext* src)
	{
		if (g_config.settings.notify_debug)
			g_notification_service->push(xorstr_("NETWORK_BAIL"), xorstr_("!NETWORK_BAIL TRIGGERED!"), true);

		src->set_return_value<BOOL>(FALSE);
	};

	inline void NETWORK_CAN_BAIL(rage::scrNativeCallContext* src)
	{
		if (g_config.settings.notify_debug)
			g_notification_service->push(xorstr_("NETWORK_CAN_BAIL"), xorstr_("!NETWORK_CAN_BAIL TRIGGERED!"), true);

		src->set_return_value<BOOL>(FALSE);
	}

	//Session switching optimization #1
	//https://github.com/Yimura/YimMenu/discussions/143
	inline void NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA(rage::scrNativeCallContext* src)
	{
		LOG(G3LOG_DEBUG) << xorstr_("!NETWORK_HAS_RECEIVED_HOST_BROADCAST_DATA TRIGGERED!");

		if (g_config.misc.optimize_loading)
			src->set_return_value<BOOL>(TRUE);

	}
}
#pragma once
#include "native_hooks.hpp"
#include "script_global.hpp"

namespace big::shop_controller
{
	inline void SET_WARNING_MESSAGE_WITH_HEADER(rage::scrNativeCallContext* src)
	{
		if (g_config.protection.other.rate_limit)
		{
			if (auto entry_line = src->get_arg<const char*>(1); !strcmp(entry_line, "CTALERT_F_2"))
			{
				g_notification_service->push_error(xorstr_("Rate Limit"), xorstr_("Online rate limit reached. Whatever you're doing, do it less"));

				*script_global(4535606).as<int*>() = 0;

				return;
			}

			HUD::SET_WARNING_MESSAGE_WITH_HEADER(
				src->get_arg<const char*>(0),
				src->get_arg<const char*>(1),
				src->get_arg<int>(2),
				src->get_arg<const char*>(3),
				src->get_arg<BOOL>(4),
				src->get_arg<Any>(5),
				src->get_arg<Any*>(6),
				src->get_arg<Any*>(7),
				src->get_arg<BOOL>(8),
				src->get_arg<Any>(9)
			);
		}
	}
}
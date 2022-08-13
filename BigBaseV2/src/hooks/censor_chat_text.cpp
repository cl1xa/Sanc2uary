#include "gta/joaat.hpp"
#include "hooking.hpp"
#include "natives.hpp"
#include "script_global.hpp"

namespace big
{
	int hooks::censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text)
	{
		if (g_config.protection.other.uncensor_chat)
		{
			LOG(INFO) << fmt::format("[{} | {}] Unfiltered string: {}", chat_menu, reinterpret_cast<void*>(output_text), user_text);
			return -1; //Returns uncensored text
		}

		return g_hooking->m_censor_chat_text_hook.get_original<decltype(&censor_chat_text)>()(chat_menu, user_text, output_text);
	}
}
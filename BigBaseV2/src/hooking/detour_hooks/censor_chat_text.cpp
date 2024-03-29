#include "hooking/hooking.hpp"

namespace big
{
	int uncensor_chat = -1;

	int hooks::censor_chat_text(__int64 chat_menu, const char* user_text, const char** output_text)
	{
		if (g_config.misc.uncensor_chat)
		{
			LOG(INFO) << fmt::format(xorstr_("[{} | {}] Unfiltered string: {}"), chat_menu, reinterpret_cast<void*>(output_text), user_text);

			return uncensor_chat; //Returns uncensored text
		}

		return g_hooking->m_censor_chat_text_hook.get_original<decltype(&censor_chat_text)>()(chat_menu, user_text, output_text); //Returns censored text
	}
}
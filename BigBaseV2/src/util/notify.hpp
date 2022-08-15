#pragma once
#include "network/CNetGamePlayer.hpp"
#include "script.hpp"

using namespace std;

namespace big::notify
{
	//Displays notification text above the map
	inline void above_map(string_view text)
	{
		//Ghetto
		string in = text.data();
		const auto out = (fmt::format(xorstr_("{}"), in)).c_str();

		HUD::SET_TEXT_OUTLINE();
		HUD::BEGIN_TEXT_COMMAND_THEFEED_POST(xorstr_("STRING"));

		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(out);
		HUD::END_TEXT_COMMAND_THEFEED_POST_TICKER(false, false);
	}

	//Shows a busy spinner till the value at the address equals the value passed or if timeout is hit
	inline void busy_spinner(string_view text, int* address, int value, int timeout = 15)
	{
		//Ghetto
		string in = text.data();
		const auto out = (fmt::format(xorstr_("{}"), in)).c_str();

		HUD::BEGIN_TEXT_COMMAND_BUSYSPINNER_ON(xorstr_("STRING"));
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(out);
		HUD::END_TEXT_COMMAND_BUSYSPINNER_ON(3);

		for (size_t i = 0; *address != value && i < (size_t)timeout * 100; i++)
			script::get_current()->yield(chrono::steady_clock::duration(10));
		
		HUD::BUSYSPINNER_OFF();
	}

	//Depricated. Will keep as it may be useful in the future.
	/*inline void display_help_text(string_view text)
	{
		string in = text.data();
		const auto out = (fmt::format(xorstr_("{}"), in)).c_str();

		HUD::BEGIN_TEXT_COMMAND_DISPLAY_HELP("STRING");
		HUD::ADD_TEXT_COMPONENT_SUBSTRING_PLAYER_NAME(out);
		HUD::END_TEXT_COMMAND_DISPLAY_HELP(0, 0, 1, -1);
	}*/
}
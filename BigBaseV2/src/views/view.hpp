#pragma once
#include "imgui.h"
#include "pointers.hpp"
#include "script.hpp"

namespace big
{
	class view_main
	{
	public:
		static void notifications();
		static void root();

		static void always()
		{
			notifications();
		}
	};

	class view_sub
	{
	public:
		static void tab_protection();
		static void tab_misc();
		static void tab_utility();
		static void tab_cheats();
		static void tab_recovery();
		static void tab_network();
		static void tab_settings();
	};
}
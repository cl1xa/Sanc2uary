#pragma once
#include "common.hpp"

namespace big
{
	class menu
	{
	public:
		void dx_init();
		void dx_on_tick();
		void always_draw();

		void script_init();
		void script_on_tick();
		static void script_func();

	public:
		bool m_opened{};
	};

	inline menu g_gui;
}

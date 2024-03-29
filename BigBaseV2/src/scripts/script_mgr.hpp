#pragma once
#include "common.hpp"
#include "script.hpp"

namespace big
{
	using script_list = vector<unique_ptr<script>>;

	class script_mgr
	{
	public:
		explicit script_mgr() = default;
		~script_mgr() = default;

		void add_script(unique_ptr<script> script);
		void remove_all_scripts();

		script_list& scripts();

		void tick();

	private:
		void tick_internal();

	private:
		recursive_mutex m_mutex;
		script_list m_scripts;
	};

	inline script_mgr g_script_mgr;
}
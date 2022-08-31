#include "common.hpp"
#include "gta/array.hpp"
#include "gta/script_thread.hpp"
#include "gta/tls_context.hpp"
#include "misc/gta_util.hpp"
#include "invoker.hpp"
#include "pointers.hpp"
#include "script_mgr.hpp"

namespace big
{
	void script_mgr::add_script(unique_ptr<script> script)
	{
		lock_guard lock(m_mutex);
		m_scripts.push_back(move(script));
	}

	void script_mgr::remove_all_scripts()
	{
		lock_guard lock(m_mutex);
		m_scripts.clear();
	}

	script_list& script_mgr::scripts()
	{
		return m_scripts;
	}

	void script_mgr::tick()
	{
		gta_util::execute_as_script(RAGE_JOAAT("main_persistent"), mem_fn(&script_mgr::tick_internal), this);
	}

	void script_mgr::tick_internal()
	{
		static bool ensure_main_fiber = (ConvertThreadToFiber(nullptr), true);
		static bool ensure_native_handlers = (g_native_invoker.cache_handlers(), true);

		lock_guard lock(m_mutex);

		for (auto const& script : m_scripts)
			if (script->is_enabled())
				script->tick();
	}
}
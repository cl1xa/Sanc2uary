
#include "scripts/fiber_pool.hpp"

namespace big
{
	inline bool queue_button(const std::string_view text) 
	{
		return ImGui::Button(text.data());
	}

	inline void queue_button(const std::string_view text, std::function<void()> cb) 
	{
		if (queue_button(text)) 
			g_fiber_pool->queue_job(cb);
	}
}
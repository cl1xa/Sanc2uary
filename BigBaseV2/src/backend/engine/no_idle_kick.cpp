#include "backend/backend.hpp"

namespace big
{
	int tick = 0;

	void backend_engine::no_idle_kick()
	{
		if (g_config.protection.other.idle)
		{
			*script_global(1648034).at(1156).as<int*>() = tick;
			*script_global(1648034).at(1172).as<int*>() = tick;
		}
	}
}

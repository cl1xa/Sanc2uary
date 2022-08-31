#include "features/features.hpp"

namespace big
{
	void features_engine::no_idle_kick()
	{
		if (g_config.protection.other.idle)
		{
			*script_global(1648034).at(1156).as<int*>() = 0;
			*script_global(1648034).at(1172).as<int*>() = 0;
		}
	}
}

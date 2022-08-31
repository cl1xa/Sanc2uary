#include "features/features.hpp"

namespace big
{
	void features_vehicle::vehicle_calls()
	{
		features_vehicle::vehicle_god();

		features_vehicle::horn_boost();

		features_vehicle::automatic_repair();
	}

	void features_vehicle::vehicle_loop()
	{
		while (g_running)
		{
			TRY_CLAUSE
			{
				features_vehicle::vehicle_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

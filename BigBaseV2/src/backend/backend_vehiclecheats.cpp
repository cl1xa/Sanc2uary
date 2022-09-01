#include "backend/backend.hpp"

namespace big
{
	void backend_vehiclecheats::vehicle_calls()
	{
		backend_vehiclecheats::vehicle_god();

		backend_vehiclecheats::horn_boost();

		backend_vehiclecheats::automatic_repair();
	}

	void backend_vehiclecheats::vehicle_loop()
	{
		while (g_running)
		{
			TRY_CLAUSE
			{
				backend_vehiclecheats::vehicle_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}
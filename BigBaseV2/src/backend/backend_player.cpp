#include "backend.hpp"

namespace big
{
	void backend_player::player_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			backend_player::player_god();
			backend_player::no_police();
			backend_player::infinite_ammo();

		} QUEUE_JOB_END_CLAUSE
	}

	void backend_player::player_loop()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				backend_player::player_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

#include "features/features.hpp"

namespace big
{
	void features_player::player_calls()
	{
		QUEUE_JOB_BEGIN_CLAUSE()
		{
			features_player::no_police();

		} QUEUE_JOB_END_CLAUSE

		QUEUE_JOB_BEGIN_CLAUSE()
		{
			features_player::player_god();
			features_player::keep_player_clean();
			features_player::infinite_ammo();

		} QUEUE_JOB_END_CLAUSE
	}

	void features_player::player_loop()
	{
		while (true)
		{
			TRY_CLAUSE
			{
				features_player::player_calls();
			}
			EXCEPT_CLAUSE

			script::get_current()->yield();
		}
	}
}

#pragma once

namespace big::math
{
	inline float distance_between_vectors(Vector3 a, Vector3 b)
	{
		return (float)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}
}
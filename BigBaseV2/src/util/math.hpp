#pragma once

namespace big::math
{
	inline constexpr auto ColorFromBytes = [](uint8_t r, uint8_t g, uint8_t b)
	{
		return ImVec4((float)r / 255.0f, (float)g / 255.0f, (float)b / 255.0f, 1.0f);
	};

	inline float distance_between_vectors(Vector3 a, Vector3 b)
	{
		return (float)sqrt(pow((a.x - b.x), 2) + pow((a.y - b.y), 2) + pow((a.z - b.z), 2));
	}

	inline void clear_bit(int* address, int pos) { *address &= ~(1 << pos); }

	inline void clear_bits(int* address, int bits) { *address &= ~(bits); }

	inline bool has_bit_set(int* address, int pos) { return *address & 1 << pos; }

	inline bool has_bits_set(int* address, int bits) { return (*address & bits) == bits; }

	inline void set_bit(int* address, int pos) { *address |= 1 << pos; }

	inline void set_bits(int* address, int bits) { *address |= bits; }
}
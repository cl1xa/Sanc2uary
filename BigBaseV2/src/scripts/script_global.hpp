#pragma once
#include "common.hpp"

namespace big
{
	class script_global
	{
	public:
		explicit script_global(size_t index);

		script_global at(ptrdiff_t index);
		script_global at(ptrdiff_t index, size_t size);

		template <typename T>
		enable_if_t<std::is_pointer_v<T>, T> as()
		{
			return static_cast<T>(get());
		}

		template <typename T>
		enable_if_t<std::is_lvalue_reference_v<T>, T> as()
		{
			return *static_cast<add_pointer_t<remove_reference_t<T>>>(get());
		}

	private:
		void *get();
		size_t m_index;
	};
}

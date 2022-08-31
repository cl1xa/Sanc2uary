#pragma once
#include "common.hpp"

namespace big
{
	class script_local
	{
	public:
		explicit script_local(rage::scrThread* thread, size_t index);
		explicit script_local(PVOID stack, size_t index);

		script_local at(ptrdiff_t index);
		script_local at(ptrdiff_t index, size_t size);

		template <typename T>
		enable_if_t<is_pointer_v<T>, T> as()
		{
			return static_cast<T>(get());
		}

		template <typename T>
		enable_if_t<is_lvalue_reference_v<T>, T> as()
		{
			return *static_cast<add_pointer_t<remove_reference_t<T>>>(get());
		}

	private:
		void* get();
		size_t m_index;
		PVOID m_stack;
	};
}
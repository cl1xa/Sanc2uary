#pragma once
#include "common.hpp"
#include "gta/data/fwddec.hpp"
#include "gta/data/rage/joaat.hpp"
#include "gta/natives.hpp"
#include "hooking/vmt_hook.hpp"

namespace big
{
	class script_hook
	{
	public:
		explicit script_hook(rage::joaat_t script_hash, unordered_map<rage::scrNativeHash, rage::scrNativeHandler> native_replacements);
		~script_hook();

		void ensure();

	private:
		void hook_instance(rage::scrProgram* program);

		static void scrprogram_dtor(rage::scrProgram* this_, bool free_memory);
		static unordered_map<rage::scrProgram*, script_hook*> s_map;

		rage::joaat_t m_script_hash;
		rage::scrProgram* m_program;
		unique_ptr<vmt_hook> m_vmt_hook;
		unordered_map<rage::scrNativeHash, rage::scrNativeHandler> m_native_replacements;
		unordered_map<rage::scrNativeHash, rage::scrNativeHandler*> m_native_handler_ptrs;
	};
}
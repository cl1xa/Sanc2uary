#include "common.hpp"
#include "detour_hook.hpp"
#include "logger.hpp"
#include "memory/handle.hpp"
#include <..\MinHook\include\MinHook.h>

namespace big
{
	detour_hook::detour_hook(::string name, void* target, void* detour) :m_name(::move(name)), m_target(target), m_detour(detour)
	{
		fix_hook_address();

		if (auto status = MH_CreateHook(m_target, m_detour, &m_original); status == MH_OK)
			LOG(INFO) << fmt::format(xorstr_("Created hook: {}"), m_name);
		else
			throw ::runtime_error(fmt::format(xorstr_("Failed to create hook '{}' at 0x{:X} (error: {})"), m_name, uintptr_t(m_target), MH_StatusToString(status)));
	}

	detour_hook::~detour_hook() noexcept
	{
		if (m_target)
			MH_RemoveHook(m_target);

		LOG(INFO) << fmt::format(xorstr_("Removed hook: {}"), m_name);
	}

	void detour_hook::enable()
	{
		if (auto status = MH_EnableHook(m_target); status == MH_OK)
			LOG(INFO) << fmt::format(xorstr_("Enabled hook: {}"), m_name);
		else
			throw ::runtime_error(fmt::format(xorstr_("Failed to enable hook 0x{:X} ({})"), uintptr_t(m_target), MH_StatusToString(status)));
	}

	void detour_hook::disable()
	{
		if (auto status = MH_DisableHook(m_target); status == MH_OK)
			LOG(INFO) << fmt::format(xorstr_("Disabled hook: {}"), m_name);
		else
			LOG(WARNING) << fmt::format(xorstr_("Failed to disable hook: {}"), m_name);
	}

	DWORD exp_handler(PEXCEPTION_POINTERS exp, ::string const& name)
	{
		return exp->ExceptionRecord->ExceptionCode == STATUS_ACCESS_VIOLATION ? EXCEPTION_EXECUTE_HANDLER : EXCEPTION_CONTINUE_SEARCH;
	}

	void detour_hook::fix_hook_address()
	{
		__try
		{
			auto ptr = memory::handle(m_target);

			while (ptr.as<::uint8_t&>() == 0xE9)
				ptr = ptr.add(1).rip();

			m_target = ptr.as<void*>();
		}
		__except (exp_handler(GetExceptionInformation(), m_name))
		{
			[this]()
			{
				throw ::runtime_error(fmt::format(xorstr_("Failed to fix hook address for '{}'"), m_name));
			}();
		}
	}
}
#pragma once

#include <SDKDDKVer.h>
#include <Windows.h>
#include <D3D11.h>
#include <wrl/client.h>

#include <cinttypes>
#include <cstddef>
#include <cstdint>

#include <chrono>
#include <ctime>

#include <filesystem>
#include <fstream>
#include <iostream>
#include <iomanip>

#include <atomic>
#include <mutex>
#include <thread>

#include <memory>
#include <new>

#include <sstream>
#include <string>
#include <string_view>

#include <algorithm>
#include <functional>
#include <utility>

#include <stack>
#include <vector>

#include <typeinfo>
#include <type_traits>

#include <exception>
#include <stdexcept>

#include <any>
#include <optional>
#include <variant>

#define FMT_HEADER_ONLY
#include <fmt/format.h>
#include <nlohmann/json.hpp>

#include "logger.hpp"

#include "file_manager/config.hpp"
#include "gta/natives.hpp"

#include "services/notification_service.hpp"
#include "util/notify.hpp"

#include "anti_tamper/xorstr.hpp"
#include "gta/data/ped/CPed.hpp"
#include "gta/data/enums.hpp"

#include "gta/data/rage/joaat.hpp"

using namespace std;
using namespace big::notify;

namespace big
{
	using namespace std::chrono_literals;
	
	template <typename T>
	using comptr = Microsoft::WRL::ComPtr<T>;

	inline HMODULE g_hmodule{};
	inline HANDLE g_main_thread{};
	inline DWORD g_main_thread_id{};
	inline std::atomic_bool g_running{ false };

	inline CPed* g_local_player;
}
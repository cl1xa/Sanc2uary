#pragma once
#include "imgui.h"

namespace big
{
	enum class NotificationType 
	{
		INFO,
		SUCCESS,
		WARNING,
		DANGER,
	};

	struct notification
	{
		NotificationType type;
		const std::string title;
		const std::string message;
		const std::chrono::time_point<std::chrono::system_clock> created_on;
		const float destroy_in;
		float alpha;
	};

	class notification_service final
	{
		std::unordered_map<std::size_t, notification> notifications;

	public:
		notification_service();
		virtual ~notification_service();

		void push(notification);
		void push(std::string, std::string, bool debug = false);
		void push_warning(std::string, std::string);
		void push_error(std::string, std::string);
		std::vector<notification> get();

		std::map<NotificationType, ImVec4> notification_colors = 
		{
			{NotificationType::INFO, ImVec4(0.1f, 0.1f, 0.1f, 1.00f)},
			{NotificationType::SUCCESS, ImVec4(0.29f, 0.69f, 0.34f, 1.00f)},
			{NotificationType::WARNING,  ImVec4(0.69f, 0.29f , 0.29f, 1.00f) },
			{NotificationType::DANGER, ImVec4(0.69f, 0.29f , 0.29f, 1.00f)},
		};
	};

	inline notification_service* g_notification_service{};
}
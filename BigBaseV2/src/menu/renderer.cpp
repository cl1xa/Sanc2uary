#include "common.hpp"
#include "file_manager/file_manager.hpp"
#include "views/font.hpp"
#include "menu/menu.hpp"
#include "hooking/pointers.hpp"
#include "renderer.hpp"
#include <imgui.h>
#include <backends/imgui_impl_dx11.h>
#include <backends/imgui_impl_win32.h>
#include <imgui_internal.h>

IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

namespace big
{
	renderer::renderer() :
		m_dxgi_swapchain(*g_pointers->m_swapchain)
	{
		void *d3d_device{};

		if (SUCCEEDED(m_dxgi_swapchain->GetDevice(__uuidof(ID3D11Device), &d3d_device)))
			m_d3d_device.Attach(static_cast<ID3D11Device*>(d3d_device));
		else
			throw std::runtime_error(xorstr_("Failed to get D3D device."));

		m_d3d_device->GetImmediateContext(m_d3d_device_context.GetAddressOf());

		auto file_path = g_file_manager->get_project_file(xorstr_("./imgui.ini")).get_path();
		
		ImGuiContext* ctx = ImGui::CreateContext();

		static std::string path = file_path.make_preferred().string();
		ctx->IO.IniFilename = path.c_str();

		ImGui_ImplDX11_Init(m_d3d_device.Get(), m_d3d_device_context.Get());
		ImGui_ImplWin32_Init(g_pointers->m_hwnd);

		ImFontConfig font_cfg{};
		font_cfg.FontDataOwnedByAtlas = false;
		std::strcpy(font_cfg.Name, xorstr_("Storopia"));

		m_font = ImGui::GetIO().Fonts->AddFontFromMemoryTTF(const_cast<std::uint8_t*>(font_rubik), sizeof(font_rubik), 20.f, &font_cfg);

		g_gui.dx_init();
		g_renderer = this;
	}

	renderer::~renderer()
	{
		ImGui_ImplWin32_Shutdown();
		ImGui_ImplDX11_Shutdown();
		ImGui::DestroyContext();

		g_renderer = nullptr;
	}

	void renderer::on_present()
	{
		if (g_gui.m_opened)
		{
			ImGui::GetIO().MouseDrawCursor = true;
			ImGui::GetIO().ConfigFlags &= ~ImGuiConfigFlags_NoMouse;
		}
		else
		{
			ImGui::GetIO().MouseDrawCursor = false;
			ImGui::GetIO().ConfigFlags |= ImGuiConfigFlags_NoMouse;
		}

		ImGui_ImplDX11_NewFrame();
		ImGui_ImplWin32_NewFrame();
		ImGui::NewFrame();

		g_gui.always_draw();

		if (g_gui.m_opened)
			g_gui.dx_on_tick();

		ImGui::Render();
		ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
	}

	void renderer::pre_reset()
	{
		ImGui_ImplDX11_InvalidateDeviceObjects();
	}

	void renderer::post_reset()
	{
		ImGui_ImplDX11_CreateDeviceObjects();
	}

	void renderer::wndproc(HWND hwnd, UINT msg, WPARAM wparam, LPARAM lparam)
	{
		//Persist and restore the cursor position between menu instances.
		static POINT cursor_coords{};

		if (msg == WM_KEYUP && (wparam == VK_DELETE || wparam == VK_INSERT))
		{
			if (g_gui.m_opened)
				GetCursorPos(&cursor_coords);
			else if (cursor_coords.x + cursor_coords.y != 0)
				SetCursorPos(cursor_coords.x, cursor_coords.y);

			g_gui.m_opened ^= true;
		}

		if (g_gui.m_opened)
			ImGui_ImplWin32_WndProcHandler(hwnd, msg, wparam, lparam);
	}
}

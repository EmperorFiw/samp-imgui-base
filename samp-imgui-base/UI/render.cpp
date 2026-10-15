#include "render.h"

namespace UI
{
    static bool g_bInitialised = false;
    static ImFont* g_pBoldFont = nullptr;

    void Initialize(HWND hWnd, IDirect3DDevice9* pDevice)
    {
        if (!g_bInitialised) {
            ImGui::CreateContext();
            ImGui_ImplWin32_Init(hWnd);
            ImGui_ImplDX9_Init(pDevice);

            ImGuiIO& io = ImGui::GetIO();
            io.MouseDrawCursor = false;
            io.ConfigFlags |= ImGuiConfigFlags_NoMouseCursorChange;

            ImFontConfig font_config;

            font_config.PixelSnapH = true;
            io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahomabd.ttf", 18.0f, &font_config, io.Fonts->GetGlyphRangesDefault());
            font_config.MergeMode = true;
            io.Fonts->AddFontFromFileTTF("C:\\Windows\\Fonts\\Tahomabd.ttf", 18.0f, &font_config, io.Fonts->GetGlyphRangesThai());

            io.Fonts->Build();

            g_bInitialised = true;
        }
    }

    void Render()
    {
        if (!g_bInitialised) return;

        ImGui_ImplDX9_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        ImGui::SetNextWindowPos(ImVec2(10.0f, 10.0f), ImGuiCond_Always);

        ImGuiWindowFlags window_flags =
            ImGuiWindowFlags_NoTitleBar |
            ImGuiWindowFlags_NoResize |
            ImGuiWindowFlags_NoMove |
            ImGuiWindowFlags_NoScrollbar |
            ImGuiWindowFlags_NoInputs |
            ImGuiWindowFlags_NoSavedSettings |
            ImGuiWindowFlags_NoBackground;

        if (ImGui::Begin("##Overlay", nullptr, window_flags))
        {
            ImGui::TextColored(ImVec4(1.0f, 0.0f, 0.0f, 1.0f), "[SA-MP ImGui Base] รองรับภาษาไทย");
        }
        ImGui::End();

        ImGui::Render();
        ImGui_ImplDX9_RenderDrawData(ImGui::GetDrawData());
    }

    void Shutdown()
    {
        if (!g_bInitialised) return;

        ImGui_ImplDX9_Shutdown();
        ImGui_ImplWin32_Shutdown();
        ImGui::DestroyContext();
        g_bInitialised = false;
    }
}
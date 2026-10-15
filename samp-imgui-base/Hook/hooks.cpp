#include "hooks.h"

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(HWND hWnd, UINT msg, WPARAM wParam, LPARAM lParam);

typedef HRESULT(APIENTRY* EndScene_t)(LPDIRECT3DDEVICE9 pDevice);
typedef HRESULT(APIENTRY* Reset_t)(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters);

namespace Hooks
{
    static EndScene_t oEndScene = nullptr;
    static Reset_t oReset = nullptr;
    static WNDPROC oWndProc = nullptr;

    static HWND g_hWnd = NULL;

    static LRESULT CALLBACK hkWndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
    {
        if (ImGui_ImplWin32_WndProcHandler(hWnd, uMsg, wParam, lParam))
            return true;

        return CallWindowProc(oWndProc, hWnd, uMsg, wParam, lParam);
    }

    static HRESULT APIENTRY hkEndScene(LPDIRECT3DDEVICE9 pDevice)
    {
        if (!g_hWnd)
        {
            D3DDEVICE_CREATION_PARAMETERS params;
            pDevice->GetCreationParameters(&params);
            g_hWnd = params.hFocusWindow;

            if (g_hWnd)
            {
                oWndProc = (WNDPROC)SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG_PTR)hkWndProc);
                UI::Initialize(g_hWnd, pDevice);
            }
        }

        UI::Render();

        return oEndScene(pDevice);
    }

    static HRESULT APIENTRY hkReset(LPDIRECT3DDEVICE9 pDevice, D3DPRESENT_PARAMETERS* pPresentationParameters)
    {
        ImGui_ImplDX9_InvalidateDeviceObjects();

        HRESULT hr = oReset(pDevice, pPresentationParameters);

        if (SUCCEEDED(hr))
        {
            ImGui_ImplDX9_CreateDeviceObjects();
        }

        return hr;
    }

    bool Initialize()
    {
        while (*(DWORD*)0xC97C28 == NULL)
        {
            Sleep(100);
        }

        void** vTableDevice = *(void***)(*(DWORD*)0xC97C28);
        if (!vTableDevice) return false;

        if (MH_Initialize() != MH_OK) return false;

        void* pResetTarget = vTableDevice[16];
        void* pEndSceneTarget = vTableDevice[42];

        if (MH_CreateHook(pResetTarget, &hkReset, reinterpret_cast<LPVOID*>(&oReset)) != MH_OK)
            return false;

        if (MH_CreateHook(pEndSceneTarget, &hkEndScene, reinterpret_cast<LPVOID*>(&oEndScene)) != MH_OK)
            return false;

        return MH_EnableHook(MH_ALL_HOOKS) == MH_OK;
    }

    void Restore()
    {
        if (oWndProc && g_hWnd)
        {
            SetWindowLongPtr(g_hWnd, GWLP_WNDPROC, (LONG_PTR)oWndProc);
            oWndProc = nullptr;
        }

        MH_DisableHook(MH_ALL_HOOKS);
        MH_Uninitialize();

        UI::Shutdown();
    }
}
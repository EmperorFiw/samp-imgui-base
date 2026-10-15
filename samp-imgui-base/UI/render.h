#pragma once
#include "../main.h"

namespace UI
{
    void Initialize(HWND hWnd, IDirect3DDevice9* pDevice);
    void Render();
    void Shutdown();
}
#include "main.h"
#include <cstdio>
#include <cstdarg>

uintptr_t g_SAMP = 0;
HMODULE g_hModule = NULL;

void AddMessageToChat(D3DCOLOR dwColor, const char* szMsg, ...)
{
    if (!g_SAMP || !szMsg) return;

    void* pChat = *(void**)(g_SAMP + SAMP037_CHAT_INFO_OFFSET);
    if (!pChat) return;

    char tmp[512] = { 0 };
    va_list ap;
    va_start(ap, szMsg);
    vsnprintf(tmp, sizeof(tmp) - 1, szMsg, ap);
    va_end(ap);

    typedef void(__thiscall* ChatAddMsg_t)(void* pThis, int nType, const char* szText, const char* szPrefix, DWORD dwColor, DWORD dwPrefixColor);
    ChatAddMsg_t ChatAddMsg = (ChatAddMsg_t)(g_SAMP + SAMP_FUNC_ADDTOCHATWND);

    ChatAddMsg(pChat, 8, tmp, NULL, dwColor, 0);
}

DWORD WINAPI MainThread(LPVOID lpParam)
{
    while (!g_SAMP)
    {
        g_SAMP = (uintptr_t)GetModuleHandleA("samp.dll");
        Sleep(100);
    }
    while (*(void**)(g_SAMP + SAMP037_CHAT_INPUT_INFO_OFFSET) == nullptr)
    {
        Sleep(100);
    }
    if (Hooks::Initialize())
    {
        AddMessageToChat(D3DCOLOR_RGBA(0, 255, 0, 255), "[SA-MP ImGui Base] Loaded successfully!");
    }

    return 0;
}

BOOL APIENTRY DllMain(HMODULE hModule, DWORD ul_reason_for_call, LPVOID lpReserved)
{
    switch (ul_reason_for_call)
    {
    case DLL_PROCESS_ATTACH:
        g_hModule = hModule;
        DisableThreadLibraryCalls(hModule);
        CreateThread(NULL, 0, (LPTHREAD_START_ROUTINE)MainThread, hModule, 0, NULL);
        break;

    case DLL_PROCESS_DETACH:
        Hooks::Restore();
        break;
    }
    return TRUE;
}
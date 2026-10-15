#pragma once
#include <windows.h>
#include <d3d9.h>
#include <cstdio>
#include <cstdarg>

#include <minhook/MinHook.h>
#include <imgui/imgui.h>
#include <imgui/imgui_impl_dx9.h>
#include <imgui/imgui_impl_win32.h>

#include "Hook/hooks.h"
#include "UI/render.h"

#define SAMP037_CHAT_INPUT_INFO_OFFSET				0x21A0E8
#define SAMP037_CHAT_INFO_OFFSET					0x21A0E4
#define SAMP_FUNC_ADDTOCHATWND						0x064010

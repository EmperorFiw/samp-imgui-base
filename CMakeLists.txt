cmake_minimum_required(VERSION 3.20)

project(samp_imgui_base LANGUAGES CXX)

set(SAMP_IMGUI_BASE_DIR "${CMAKE_CURRENT_SOURCE_DIR}/samp-imgui-base")
set(IMGUI_DIR "${SAMP_IMGUI_BASE_DIR}/include/imgui")
set(MINHOOK_LIBRARY "${SAMP_IMGUI_BASE_DIR}/lib/MinHook-x86.lib")

if(NOT WIN32)
    message(FATAL_ERROR "samp-imgui-base requires Windows and Direct3D 9.")
endif()

if(NOT CMAKE_SIZEOF_VOID_P EQUAL 4)
    message(FATAL_ERROR "Only 32-bit x86 is supported. Configure with -A Win32.")
endif()

if(NOT EXISTS "${MINHOOK_LIBRARY}")
    message(FATAL_ERROR "Bundled MinHook library not found: ${MINHOOK_LIBRARY}")
endif()

set(APP_SOURCES
    "${SAMP_IMGUI_BASE_DIR}/main.cpp"
    "${SAMP_IMGUI_BASE_DIR}/main.h"
    "${SAMP_IMGUI_BASE_DIR}/Hook/hooks.cpp"
    "${SAMP_IMGUI_BASE_DIR}/Hook/hooks.h"
    "${SAMP_IMGUI_BASE_DIR}/UI/render.cpp"
    "${SAMP_IMGUI_BASE_DIR}/UI/render.h"
)

set(IMGUI_SOURCES
    "${IMGUI_DIR}/imgui.cpp"
    "${IMGUI_DIR}/imgui_draw.cpp"
    "${IMGUI_DIR}/imgui_tables.cpp"
    "${IMGUI_DIR}/imgui_widgets.cpp"
    "${IMGUI_DIR}/imgui_impl_dx9.cpp"
    "${IMGUI_DIR}/imgui_impl_win32.cpp"
    "${IMGUI_DIR}/imgui.h"
    "${IMGUI_DIR}/imgui_internal.h"
    "${IMGUI_DIR}/imgui_impl_dx9.h"
    "${IMGUI_DIR}/imgui_impl_win32.h"
    "${IMGUI_DIR}/imconfig.h"
    "${IMGUI_DIR}/imstb_rectpack.h"
    "${IMGUI_DIR}/imstb_textedit.h"
    "${IMGUI_DIR}/imstb_truetype.h"
)

add_library(samp-imgui-base SHARED ${APP_SOURCES} ${IMGUI_SOURCES}
    "${SAMP_IMGUI_BASE_DIR}/include/minhook/MinHook.h")

source_group(TREE "${SAMP_IMGUI_BASE_DIR}" FILES ${APP_SOURCES} ${IMGUI_SOURCES}
    "${SAMP_IMGUI_BASE_DIR}/include/minhook/MinHook.h")

target_compile_features(samp-imgui-base PRIVATE cxx_std_20)
target_include_directories(samp-imgui-base PRIVATE "${SAMP_IMGUI_BASE_DIR}/include")
target_compile_definitions(samp-imgui-base PRIVATE
    WIN32 _WINDOWS _USRDLL SAMPIMGUIBASE_EXPORTS UNICODE _UNICODE)

target_link_libraries(samp-imgui-base PRIVATE "${MINHOOK_LIBRARY}" d3d9)

set_target_properties(samp-imgui-base PROPERTIES
    PREFIX ""
    SUFFIX ".asi"
    OUTPUT_NAME "samp-imgui-base")

if(MSVC)
    target_compile_options(samp-imgui-base PRIVATE /W3 /permissive- /sdl)
    target_link_options(samp-imgui-base PRIVATE /SUBSYSTEM:WINDOWS /MANIFESTUAC:NO)
endif()
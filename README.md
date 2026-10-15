# SA-MP ImGui Base

โปรเจกต์ตั้งต้นสำหรับปลั๊กอิน `.asi` ของ SA-MP ใช้ [Dear ImGui](https://github.com/ocornut/imgui) วาด overlay ผ่าน Direct3D 9 และใช้ [MinHook](https://github.com/TsudaKageyu/minhook) ติดตั้ง hook

## ความต้องการของระบบ

| รายการ | เวอร์ชัน |
|---|---|
| Visual Studio | 2022 ขึ้นไป (workload **Desktop development with C++**) |
| CMake | 3.20 ขึ้นไป |
| Toolset | MSVC v143 |
| สถาปัตยกรรม | x86 (32-bit) |

## การ Build

Clone repository แล้วเข้าไปยังโฟลเดอร์โปรเจกต์:

```powershell
git clone https://github.com/EmperorFiw/samp-imgui-base.git
cd samp-imgui-base
```

จากนั้น build ด้วย CMake:

```powershell
cmake -B build -A Win32
cmake --build build --config Release
```

ไฟล์ผลลัพธ์คือ `samp-imgui-base.asi` อยู่ที่ `build/Release/`

สำหรับ Debug ให้เปลี่ยน configuration:

```powershell
cmake --build build --config Debug
```

## การใช้งาน

คัดลอกไฟล์ `samp-imgui-base.asi` ไปไว้ในโฟลเดอร์ติดตั้งเกม GTA:SA ที่มี ASI Loader อยู่แล้ว

## โครงสร้างโปรเจกต์

```text
.
├── CMakeLists.txt
└── samp-imgui-base/
    ├── main.cpp, main.h      # จุดเริ่มต้นของปลั๊กอิน
    ├── Hook/                 # ติดตั้งและถอด Direct3D hook
    ├── UI/                   # เริ่มต้นและวาด ImGui overlay
    ├── include/
    │   ├── imgui/            # Dear ImGui และ backend Win32 / DirectX 9
    │   └── minhook/          # MinHook.h
    └── lib/
        └── MinHook-x86.lib
```

## เครดิต

- [Dear ImGui](https://github.com/ocornut/imgui) โดย Omar Cornut และผู้ร่วมพัฒนา
- [MinHook](https://github.com/TsudaKageyu/minhook) โดย Tsuda Kageyu และผู้ร่วมพัฒนา
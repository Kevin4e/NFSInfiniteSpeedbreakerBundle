#define WIN32_LEAN_AND_MEAN

#include <windows.h>

inline void Init() noexcept
{
    *reinterpret_cast<unsigned char*>(0xB4D86C) = 1;
}

extern "C" __declspec(dllexport) void InitializeASI() {
    // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
    // A few tweaks and simplified condition for clarity; logic unchanged, there were a few redundant operations

    IMAGE_NT_HEADERS* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(0x400108);

    if (nt->OptionalHeader.AddressOfEntryPoint == 0x47E926)
        Init();

    else
        MessageBoxA(nullptr, "This .exe is not supported.\nPlease use v1.4 NFSC.exe (6,88 MB (7.217.152 bytes)).", "NFSC Infinite Speedbreaker by Kevin4e", MB_ICONERROR);
}
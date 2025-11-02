#define WIN32_LEAN_AND_MEAN

#include <windows.h>

inline void Init() noexcept
{
    *reinterpret_cast<unsigned char*>(0x988E1C) = 1;
}

extern "C" __declspec(dllexport) void InitializeASI() {
    // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
    // A few tweaks and simplified condition for clarity; logic unchanged, there were a few redundant operations

    IMAGE_NT_HEADERS* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(0x400108);

    if (nt->OptionalHeader.AddressOfEntryPoint == 0x3C4040)
        Init();

    else
        MessageBoxA(nullptr, "This .exe is not supported.\nPlease use v1.3 speed.exe (5.75 MB (6.029.312 bytes)).", "NFSMW Infinite Speedbreaker by Kevin4e", MB_ICONERROR);
}
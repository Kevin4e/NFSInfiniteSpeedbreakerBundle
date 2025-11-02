#define WIN32_LEAN_AND_MEAN

#include <windows.h>
#include <cstring>

inline void Init() noexcept
{
    DWORD originalProtection;
    if (!VirtualProtect(reinterpret_cast<void*>(0x7BA4F1), 1, PAGE_EXECUTE_READWRITE, &originalProtection)) return;

    std::memset(reinterpret_cast<void*>(0x7BA4F1), 0xEB, 1); // Make 'jmp' instead of 'ja'

    FlushInstructionCache(GetCurrentProcess(), reinterpret_cast<void*>(0x7BA4F1), 1);

    DWORD temp;
    VirtualProtect(reinterpret_cast<void*>(0x7BA4F1), 1, originalProtection, &temp);
}

extern "C" __declspec(dllexport) void InitializeASI() {
    // Check if .exe file is compatible - Thanks to thelink2012 and MWisBest
    // A few tweaks and simplified condition for clarity; logic unchanged, there were a few redundant operations

    IMAGE_NT_HEADERS* nt = reinterpret_cast<IMAGE_NT_HEADERS*>(0x400118);

    if (nt->OptionalHeader.AddressOfEntryPoint == 0x4AEC55)
        Init();

    else
        MessageBoxA(nullptr, "This .exe is not supported.\nPlease use v1.0.0.1 nfs.exe (10,0 MB (10.584.064 bytes)).", "NFSUC Infinite Speedbreaker by Kevin4e", MB_ICONERROR);
}
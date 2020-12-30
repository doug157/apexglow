#include "includes.h"

typedef char(*t_sub2F3A80)();
t_sub2F3A80 r_sub2F3A80 = nullptr;

char h_sub2F3A80()
{
	auto result = r_sub2F3A80();
	apex::highlight_loop();
	return result;
}

BOOL APIENTRY DllMain(HMODULE hModule,
	DWORD ul_reason_for_call,
	LPVOID lpReserved)
{
	if (ul_reason_for_call == DLL_PROCESS_ATTACH)
	{
		AllocConsole();
		FILE* file = nullptr;
		freopen_s(&file, "CONOUT$", "w", stdout);
		ShowWindow(GetConsoleWindow(), SW_SHOW);

		r_sub2F3A80 = (t_sub2F3A80)((std::byte*)GetModuleHandleW(nullptr) + 0x2F3A80);

		if (DetourTransactionBegin() != NO_ERROR ||
			DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
			DetourAttach(&(PVOID&)r_sub2F3A80, h_sub2F3A80) != NO_ERROR ||
			DetourTransactionCommit() != NO_ERROR)
			return FALSE;
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		if (DetourTransactionBegin() != NO_ERROR ||
			DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
			DetourDetach(&(PVOID&)r_sub2F3A80, h_sub2F3A80) != NO_ERROR ||
			DetourTransactionCommit() != NO_ERROR)
			return FALSE;
	}
	return TRUE;
}


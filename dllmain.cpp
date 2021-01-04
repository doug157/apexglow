#include "includes.h"

typedef char(*tSub2F3A80)();
tSub2F3A80 rSub2F3A80 = nullptr;

char hSub2F3A80()
{
	auto result = rSub2F3A80();
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

		rSub2F3A80 = (tSub2F3A80)((std::byte*)GetModuleHandleW(nullptr) + 0x2F3A80);

		if (DetourTransactionBegin() != NO_ERROR ||
			DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
			DetourAttach(&(PVOID&)rSub2F3A80, hSub2F3A80) != NO_ERROR ||
			DetourTransactionCommit() != NO_ERROR)
			return FALSE;
	}
	else if (ul_reason_for_call == DLL_PROCESS_DETACH)
	{
		if (DetourTransactionBegin() != NO_ERROR ||
			DetourUpdateThread(GetCurrentThread()) != NO_ERROR ||
			DetourDetach(&(PVOID&)rSub2F3A80, hSub2F3A80) != NO_ERROR ||
			DetourTransactionCommit() != NO_ERROR)
			return FALSE;
	}
	return TRUE;
}


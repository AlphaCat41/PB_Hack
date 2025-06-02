// dllmain.cpp : Defines the entry point for the DLL application.
#include "pch.h"
#include "DIPHook.h"

void InitConsole () {

	AllocConsole ();
	FILE* stream;
	freopen_s (&stream, "CONOUT$", "w", stdout);
	freopen_s (&stream, "CONOUT$", "w", stderr);
	freopen_s (&stream, "CONIN$", "r", stdin);

	std::cout.clear ();
	std::cerr.clear ();
	std::cin.clear ();
}

DWORD_PTR* GetVTableAddress () {
	IDirect3D9* pD3D = Direct3DCreate9 (D3D_SDK_VERSION);
	if (!pD3D) return nullptr;

	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.Windowed = TRUE;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.hDeviceWindow = GetForegroundWindow ();

	IDirect3DDevice9* pDevice = nullptr;
	if (FAILED (pD3D->CreateDevice (D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL,
		d3dpp.hDeviceWindow,
		D3DCREATE_SOFTWARE_VERTEXPROCESSING,
		&d3dpp, &pDevice))) {
		std::cout << "[ERROR] Failed to create Direct3D device." << std::endl;
		pD3D->Release ();
		return nullptr;
	}

	DWORD_PTR* vTable = *reinterpret_cast<DWORD_PTR**>(pDevice);
	pDevice->Release ();
	pD3D->Release ();
	return vTable;
}

DWORD WINAPI SetupHook (LPVOID lpParam) {
	InitConsole ();
	MH_Initialize ();

	DWORD_PTR* vTable = GetVTableAddress ();
	if (!vTable) return 1;

	void* pDIP = (void*)vTable[82];


	if (MH_CreateHook (pDIP, &hkDrawIndexedPrimitive, reinterpret_cast<void**>(&oDrawIndexedPrimitive)) != MH_OK) {
		std::cout << "[ERROR] Failed to create DIP hook." << std::endl;
		return 1;
	}

	if (MH_EnableHook (pDIP) != MH_OK) {
		std::cout << "[ERROR] Failed to enable DIP hook." << std::endl;
		return 1;
	}

	return 0; // Return a DWORD value as required by LPTHREAD_START_ROUTINE
}

BOOL APIENTRY DllMain (HMODULE hModule,
	DWORD  ul_reason_for_call,
	LPVOID lpReserved
) {
	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:
		DisableThreadLibraryCalls (hModule); // Prevent unnecessary thread notifications
		CreateThread (NULL, 0, SetupHook, NULL, 0, NULL);
		break;

	case DLL_THREAD_ATTACH:
	case DLL_THREAD_DETACH:
	case DLL_PROCESS_DETACH:
		break;
	}
	return TRUE;
}


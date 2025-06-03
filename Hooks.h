#pragma once
#include "pch.h"

typedef void (__stdcall* CalcDamage_t) (int param_1, void* param_2, void* param_3, int param_4);
CalcDamage_t oCalcDamage = nullptr;

void __stdcall hkCalcDamage (int param_1, void* param_2, void* param_3, int param_4) {
	oCalcDamage (param_1, param_2, param_3, param_4);
	float* x1_56 = (float*)(param_1 + 0x38);
	float* x1_76 = (float*)(param_1 + 0x4C);
	float* x4_36 = (float*)(param_4 + 0x24);
	std::cout << "x1_56: " << *x1_56 << ", x1_76: " << *x1_76 << ", x4_36: " << x4_36 << std::endl;

	*x1_56 = 999.0f;
	*x1_76 = 0.0f;
	if (param_4) {
		*x4_36 = 999.0f;
	}
}

typedef float* (__fastcall* GetPositionFn)(void* thisptr);
GetPositionFn oGetPosition = nullptr;

float* __fastcall hkGetPosition (void* thisptr) {
	float* pos = oGetPosition (thisptr);
	std::cout << "[HOOKED] X: " << pos[0]
		<< " Y: " << pos[1]
		<< " Z: " << pos[2] << std::endl;

	return pos;
}
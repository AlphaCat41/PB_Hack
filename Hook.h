#pragma once
#include "pch.h"

typedef void (__thiscall* CalcDamage_t) (int param_1, float* param_2, float* param_3, int param_4);
CalcDamage_t oCalcDamage = nullptr;

void __fastcall hkCalcDamage (int param_1, float* param_2, float* param_3, int param_4) {
	std::cout << "hkCalcDamage called with params: "
		<< param_1 << ", "
		<< param_2 << ", "
		<< param_3 << ", "
		<< param_4 << std::endl;
	oCalcDamage (param_1, param_2, param_3, param_4);
}

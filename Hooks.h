#pragma once
#include "pch.h"

typedef void (__stdcall* CalcDamage_t) (int param_1, void* param_2, void* param_3, int param_4);
CalcDamage_t oCalcDamage = nullptr;
// 0x3fb049
void __stdcall hkCalcDamage (int param_1, void* param_2, void* param_3, int param_4) {
	oCalcDamage (param_1, param_2, param_3, param_4);
	float* base_dmg = (float*)(param_1 + 0x38);
	float* def_rate = (float*)(param_1 + 0x4C);
	float* dmg = (float*)(param_4 + 0x24);
	//param_3 = player who is killing
	std::cout << param_1 << ", " << param_2 << ", " << param_3 << ", " << param_4 << std::endl;

	*base_dmg = 999.0f;
	*def_rate = 0.0f;
	if (param_4) {
		*dmg = 999.0f;
	}
}

typedef void (__thiscall* tOnHit)(int param_1, int param_2, void* param_3);
tOnHit oOnHit = nullptr;
// 0x3ffade
void __fastcall hkOnHit (int thisPtr, void* edx, int param_2, void* param_3) {
	// ป้องกัน pointer null
	float* damagePtr = (float*)(param_2 + 0x38);
	if (damagePtr) {
		float originalDamage = *damagePtr;

		// แก้ไขค่าความเสียหายตรงนี้ (เช่น ลดให้เหลือ 1)
		*damagePtr = 200.0f;
		std::cout << "Original Damage: " << originalDamage << ", Modified Damage: " << *damagePtr << std::endl;
	}
	oOnHit (thisPtr, param_2, param_3);
}
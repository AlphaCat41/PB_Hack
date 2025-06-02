#pragma once
#include "pch.h"

typedef void (__cdecl* GetPositionFn)(float* outPos);
GetPositionFn oGetPosition = nullptr;

void __cdecl hkGetPosition (float* outPos) {
	std::cout << "hkGetPosition called!" << std::endl;
	std::cout << outPos[0] << std::endl;

	oGetPosition (outPos);
}

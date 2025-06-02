#pragma once
#include "pch.h"

typedef HRESULT (APIENTRY* DIP_t)(LPDIRECT3DDEVICE9, D3DPRIMITIVETYPE, INT, UINT, UINT, UINT, UINT);
DIP_t oDrawIndexedPrimitive = nullptr;

LPDIRECT3DTEXTURE9 yellowTex = nullptr;
UINT targetStride = 44; // ต้องหา stride ของโมเดลศัตรูเอง

void CreateYellowTexture (LPDIRECT3DDEVICE9 pDevice) {
	if (!yellowTex) {
		// สร้าง texture สีเหลือง (1x1 pixel)
		D3DXCreateTexture (pDevice, 1, 1, 1, 0, D3DFMT_A8R8G8B8,
			D3DPOOL_MANAGED, &yellowTex);
		D3DLOCKED_RECT rect;
		if (SUCCEEDED (yellowTex->LockRect (0, &rect, nullptr, 0))) {
			DWORD* color = (DWORD*)rect.pBits;
			*color = D3DCOLOR_ARGB (255, 255, 255, 0); // สีเหลือง
			yellowTex->UnlockRect (0);
		}
	}
}
HRESULT APIENTRY hkDrawIndexedPrimitive (LPDIRECT3DDEVICE9 pDevice,
	D3DPRIMITIVETYPE Type,
	INT BaseVertexIndex,
	UINT MinVertexIndex,
	UINT NumVertices,
	UINT StartIndex,
	UINT PrimitiveCount) {

	D3DVERTEXBUFFER_DESC desc;
	LPDIRECT3DVERTEXBUFFER9 pVB = nullptr;
	UINT stride, offset;

	if (SUCCEEDED (pDevice->GetStreamSource (0, &pVB, &offset, &stride)) && pVB) {
		pVB->Release ();
	}

	if (stride == targetStride) {
		IDirect3DBaseTexture9* oldTexture = nullptr;
		pDevice->GetTexture (0, &oldTexture);

		CreateYellowTexture (pDevice);
		pDevice->SetRenderState (D3DRS_ZENABLE, FALSE);
		pDevice->SetTexture (0, yellowTex);

		oDrawIndexedPrimitive (pDevice, Type, BaseVertexIndex, MinVertexIndex, NumVertices, StartIndex, PrimitiveCount);

		pDevice->SetTexture (0, oldTexture);
		if (oldTexture) oldTexture->Release ();
		pDevice->SetRenderState (D3DRS_ZENABLE, TRUE);


	}

	return oDrawIndexedPrimitive (pDevice, Type, BaseVertexIndex, MinVertexIndex,
		NumVertices, StartIndex, PrimitiveCount);
}
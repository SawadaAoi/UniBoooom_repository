/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	ポリゴン集合体管理定義
	------------------------------------
	MeshBuffer.h
	------------------------------------
	作成者　佐々木先生

	変更履歴
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __MESH_BUFFER_H__	//MeshBuffer.hインクルードガード
#define __MESH_BUFFER_H__

#include "DirectX.h"

class MeshBuffer
{
public:
	struct Description
	{
		const void* pVtx;
		UINT vtxSize;
		UINT vtxCount;
		bool isWrite;
		const void* pIdx;
		UINT idxSize;
		UINT idxCount;
		D3D11_PRIMITIVE_TOPOLOGY topology;
	};
public:
	MeshBuffer(const Description& desc);
	~MeshBuffer();

	void Draw(int count = 0);
	HRESULT Write(void* pVtx);

	Description GetDesc();

private:
	HRESULT CreateVertexBuffer(const void* pIdx, UINT size, UINT count, bool isWrite);
	HRESULT CreateIndexBuffer(const void* pVtx, UINT size, UINT count);

private:
	ID3D11Buffer* m_pVtxBuffer;
	ID3D11Buffer* m_pIdxBuffer;
	Description m_desc;

};

#endif	//!__MESH_BUFFER_H__
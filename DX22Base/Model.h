/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	モデル定義
	------------------------------------
	Model.h
	------------------------------------
	作成者

	変更履歴
	・2024/01/20 コメント改修 takagi
	・2024/01/21 コメント改修 takagi

========================================== */

#ifndef __MODEL_H__	//Model.hインクルードガード
#define __MODEL_H__

#include <DirectXMath.h>
#include <vector>
#include "Shader.h"
#include "MeshBuffer.h"

class Model
{
public:
	enum Flip
	{
		None,	// DirectX準拠(反転する
		XFlip,	// Maya準拠
		ZFlip	// DirectX準拠(Mayaから180回転した状態
	};
public:
	struct Vertex
	{
		DirectX::XMFLOAT3 pos;
		DirectX::XMFLOAT3 normal;
		DirectX::XMFLOAT2 uv;
		DirectX::XMFLOAT4 color;
	};
	using Vertices = std::vector<Vertex>;
	using Indices = std::vector<unsigned long>;
	struct Material
	{
		DirectX::XMFLOAT4 diffuse;
		DirectX::XMFLOAT4 ambient;
		DirectX::XMFLOAT4 specular;
		Texture* pTexture;
	};
	using Materials = std::vector<Material>;
	struct Mesh
	{
		Vertices vertices;
		Indices indices;
		unsigned int materialID;
		std::vector<uint32_t> boneID;
		MeshBuffer* pMesh;
	};
	using Meshes = std::vector<Mesh>;

public:
	Model();
	~Model();
	void SetVertexShader(VertexShader* vs);
	void SetPixelShader(PixelShader* ps);

	const Mesh* GetMesh(unsigned int index);
	unsigned int GetMeshNum();

#ifdef _DEBUG
	static std::string GetError();
#endif

public:
	bool Load(const char* file, float scale = 1.0f, Flip flip = Flip::None);
	void Draw();
	void Reset();

private:
	void MakeMesh(const void* ptr, float scale, Flip flip);
	void MakeMaterial(const void* ptr, std::string directory);

private:
	static VertexShader* m_pDefVS;
	static PixelShader* m_pDefPS;
	static unsigned int m_shaderRef;
#ifdef _DEBUG
	static std::string m_errorStr;
#endif

private:
	Meshes m_meshes;
	Materials m_materials;
	VertexShader* m_pVS;
	PixelShader* m_pPS;
};


#endif	//!__MODEL_H__
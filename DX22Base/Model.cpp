/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	���f������
	------------------------------------
	Model.cpp
	------------------------------------
	�쐬��

	�ύX����
	�E2024/01/21 �R�����g���C�E_model.cpp�̓��e�ړ� takagi

========================================== */

#include "Model.h"
#include "DirectXTex/TextureLoad.h"

#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#if _MSC_VER >= 1930
#ifdef _DEBUG
#pragma comment(lib, "assimp-vc143-mtd.lib")
#else
#pragma comment(lib, "assimp-vc143-mt.lib")
#endif
#elif _MSC_VER >= 1920
#ifdef _DEBUG
#pragma comment(lib, "assimp-vc142-mtd.lib")
#else
#pragma comment(lib, "assimp-vc142-mt.lib")
#endif
#elif _MSC_VER >= 1910
#ifdef _DEBUG
#pragma comment(lib, "assimp-vc141-mtd.lib")
#else
#pragma comment(lib, "assimp-vc141-mt.lib")
#endif
#endif

VertexShader* Model::m_pDefVS = nullptr;
PixelShader* Model::m_pDefPS = nullptr;
unsigned int Model::m_shaderRef = 0;
#ifdef _DEBUG
std::string Model::m_errorStr = "";
#endif

//--- �v���g�^�C�v�錾
void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps);

Model::Model()
{
	if (m_shaderRef == 0)
	{
		MakeModelDefaultShader(&m_pDefVS, &m_pDefPS);
	}
	m_pVS = m_pDefVS;
	m_pPS = m_pDefPS;
	++m_shaderRef;
}
Model::~Model()
{
	Reset();
	--m_shaderRef;
	if (m_shaderRef <= 0)
	{
		delete m_pDefPS;
		delete m_pDefVS;
	}
}

void Model::SetVertexShader(VertexShader* vs)
{
	m_pVS = vs;
}
void Model::SetPixelShader(PixelShader* ps)
{
	m_pPS = ps;
}
const Model::Mesh* Model::GetMesh(unsigned int index)
{
	if (index >= GetMeshNum())
	{
		return &m_meshes[index];
	}
	return nullptr;
}
uint32_t Model::GetMeshNum()
{
	return static_cast<uint32_t>(m_meshes.size());
}
#ifdef _DEBUG
std::string Model::GetError()
{
	return m_errorStr;
}
#endif

void MakeModelDefaultShader(VertexShader** vs, PixelShader** ps)
{
	const char* ModelVS = R"EOT(
struct VS_IN {
	float3 pos : POSITION0;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
struct VS_OUT {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
VS_OUT main(VS_IN vin) {
	VS_OUT vout;
	vout.pos = float4(vin.pos, 1.0f);
	vout.pos.z += 0.5f;
	vout.pos.y -= 0.8f;
	vout.normal = vin.normal;
	vout.uv = vin.uv;
	return vout;
})EOT";
	const char* ModelPS = R"EOT(
struct PS_IN {
	float4 pos : SV_POSITION;
	float3 normal : NORMAL0;
	float2 uv : TEXCOORD0;
};
Texture2D tex : register(t0);
SamplerState samp : register(s0);
float4 main(PS_IN pin) : SV_TARGET
{
	return tex.Sample(samp, pin.uv);
})EOT";
	*vs = new VertexShader();
	(*vs)->Compile(ModelVS);
	*ps = new PixelShader();
	(*ps)->Compile(ModelPS);
}

bool Model::Load(const char* file, float scale, Flip flip)
{
#ifdef _DEBUG
	m_errorStr = "";
#endif
	Reset();

	// assimp�̐ݒ�
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_JoinIdenticalVertices;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_FlipUVs;
	flag |= aiProcess_PreTransformVertices;
	if (flip == Flip::XFlip)  flag |= aiProcess_MakeLeftHanded;
	// assimp�œǂݍ���
	const aiScene* pScene = importer.ReadFile(file, flag);
	if (!pScene) {
		m_errorStr = importer.GetErrorString();
		return false;
	}

	// �f�B���N�g���̓ǂݎ��
	std::string directory = file;
	auto strIt = directory.begin();
	while (strIt != directory.end()) {
		if (*strIt == '/')
			*strIt = '\\';
		++strIt;
	}
	directory = directory.substr(0, directory.find_last_of('\\') + 1);

	// ���b�V���쐬
	MakeMesh(pScene, scale, flip);
	// �}�e���A���̍쐬
	MakeMaterial(pScene, directory);

	return true;
}

void Model::Draw()
{
	m_pVS->Bind();
	m_pPS->Bind();
	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		m_pPS->SetTexture(0,m_materials[m_meshes[i].materialID].pTexture);
		m_meshes[i].pMesh->Draw();
	}
}

void Model::Reset()
{
	auto meshIt = m_meshes.begin();
	while (meshIt != m_meshes.end())
	{
		if(meshIt->pMesh) delete meshIt->pMesh;
		++meshIt;
	}

	auto matIt = m_materials.begin();
	while (matIt != m_materials.end())
	{
		if (matIt->pTexture) delete matIt->pTexture;
		++matIt;
	}
}

void Model::MakeMesh(const void* ptr, float scale, Flip flip)
{
	// ���O����
	aiVector3D zero3(0.0f, 0.0f, 0.0f);
	aiColor4D one4(1.0f, 1.0f, 1.0f, 1.0f);
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	float zflip = flip == Flip::ZFlip ? -1.0f : 1.0f;
	int idx1 = flip != Flip::None ? 2 : 1;
	int idx2 = flip != Flip::None ? 1 : 2;

	// ���b�V���̍쐬
	m_meshes.resize(pScene->mNumMeshes);
	for (unsigned int i = 0; i < m_meshes.size(); ++i)
	{
		// ���_�̍쐬
		m_meshes[i].vertices.resize(pScene->mMeshes[i]->mNumVertices);
		for (unsigned int j = 0; j < m_meshes[i].vertices.size(); ++j) {
			//--- ���f���f�[�^����l�̎擾
			// ���W
			aiVector3D pos = pScene->mMeshes[i]->mVertices[j];
			// �@���i������
			aiVector3D normal = pScene->mMeshes[i]->HasNormals() ? pScene->mMeshes[i]->mNormals[j] : zero3;
			// UV(1�̃��b�V���ɕ����̃e�N�X�`�����\��t������ׁA�e�N�X�`���̖����ɉ�����UV���ݒ肳��Ă���
			aiVector3D uv = pScene->mMeshes[i]->HasTextureCoords(0) ?
				pScene->mMeshes[i]->mTextureCoords[0][j] : zero3;
			// ���_�ɐݒ肳��Ă���F
			aiColor4D color = pScene->mMeshes[i]->HasVertexColors(0) ? pScene->mMeshes[i]->mColors[0][j] : one4;
			//--- �l��ݒ�
			m_meshes[i].vertices[j] = {
				DirectX::XMFLOAT3(pos.x * scale * zflip, pos.y * scale, pos.z * scale),
				DirectX::XMFLOAT3(normal.x, normal.y, normal.z),
				DirectX::XMFLOAT2(uv.x, uv.y),
				DirectX::XMFLOAT4(color.r, color.g, color.b, color.a)
			};
		}

		// �C���f�b�N�X�̍쐬
		// mNumFaces�̓|���S���̐���\��(�P�|���S���łR�C���f�b�N�X
		m_meshes[i].indices.resize(pScene->mMeshes[i]->mNumFaces * 3);	// �C���f�b�N�X�̕K�v�����m��
		for (unsigned int j = 0; j < pScene->mMeshes[i]->mNumFaces; ++j) {
			aiFace face = pScene->mMeshes[i]->mFaces[j];
			int idx = j * 3;
			m_meshes[i].indices[idx + 0] = face.mIndices[0];
			m_meshes[i].indices[idx + 1] = face.mIndices[idx1];
			m_meshes[i].indices[idx + 2] = face.mIndices[idx2];
		}

		// �}�e���A���̊��蓖��
		m_meshes[i].materialID = pScene->mMeshes[i]->mMaterialIndex;

		// ���b�V�������ɒ��_�o�b�t�@�쐬
		MeshBuffer::Description desc = {};
		desc.pVtx = m_meshes[i].vertices.data();
		desc.vtxSize = sizeof(Vertex);
		desc.vtxCount = m_meshes[i].vertices.size();
		desc.pIdx = m_meshes[i].indices.data();
		desc.idxSize = sizeof(unsigned long);
		desc.idxCount = m_meshes[i].indices.size();
		desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_meshes[i].pMesh = new MeshBuffer(desc);
	}
}
void Model::MakeMaterial(const void* ptr, std::string directory)
{
	// ���O����
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);

	// �}�e���A���̍쐬
	m_materials.resize(pScene->mNumMaterials);
	for (unsigned int i = 0; i < m_materials.size(); ++i)
	{
		// �e��p�����[�^�[
		aiColor3D color(0.0f, 0.0f, 0.0f);
		float shininess;

		//�g�U���̎擾
		m_materials[i].diffuse = pScene->mMaterials[i]->Get(AI_MATKEY_COLOR_DIFFUSE, color) == AI_SUCCESS ?
			DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f) : DirectX::XMFLOAT4(1.0f, 1.0f, 1.0f, 1.0f);
		//�����̎擾
		m_materials[i].ambient = pScene->mMaterials[i]->Get(AI_MATKEY_COLOR_AMBIENT, color) == AI_SUCCESS ?
			DirectX::XMFLOAT4(color.r, color.g, color.b, 1.0f) : DirectX::XMFLOAT4(0.3f, 0.3f, 0.3f, 1.0f);
		//���˂̋������擾
		shininess = pScene->mMaterials[i]->Get(AI_MATKEY_SHININESS, shininess) == AI_SUCCESS ? shininess : 0.0f;
		//���ˌ��̎擾
		m_materials[i].specular = pScene->mMaterials[i]->Get(AI_MATKEY_COLOR_SPECULAR, color) == AI_SUCCESS ?
			DirectX::XMFLOAT4(color.r, color.g, color.b, shininess) : DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, shininess);

		// �e�N�X�`��
		HRESULT hr;
		aiString path;
		if (pScene->mMaterials[i]->Get(AI_MATKEY_TEXTURE_DIFFUSE(0), path) == AI_SUCCESS)
		{
			// �e�N�X�`���̈�m��
			m_materials[i].pTexture = new Texture;
			// ���̂܂ܒT��
			hr = m_materials[i].pTexture->Create(path.C_Str());
			// ���f���Ɠ����K�w��T��
			if (FAILED(hr))
			{
				// �p�X����t�@�C�����̂ݎ擾
				std::string fullPath = path.C_Str();
				std::string::iterator strIt = fullPath.begin();
				while (strIt != fullPath.end())
				{
					if (*strIt == '/')
						*strIt = '\\';
					++strIt;
				}
				size_t find = fullPath.find_last_of("\\");
				std::string fileName = fullPath;
				if (find != std::string::npos)
					fileName = fileName.substr(find + 1);
				// �e�N�X�`���̓Ǎ�
				hr = m_materials[i].pTexture->Create((directory + fileName).c_str());
			}
			// �e�N�X�`����������Ȃ�����
			if (FAILED(hr)) {
				delete m_materials[i].pTexture;
				m_materials[i].pTexture = nullptr;
				m_errorStr += path.C_Str();
			}
		}
		else {
			m_materials[i].pTexture = nullptr;
		}
	}
}
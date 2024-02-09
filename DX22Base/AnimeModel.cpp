#include "AnimeModel.h"
#include "DirectXTex/TextureLoad.h"
#include <algorithm>
#include <assimp/Importer.hpp>
#include <assimp/scene.h>
#include <assimp/postprocess.h>

#ifdef _DEBUG
#include "Line.h"
#endif

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

// static�����o�ϐ���`
VertexShader*	AnimeModel::m_pDefVS = nullptr;
PixelShader*	AnimeModel::m_pDefPS = nullptr;
unsigned int	AnimeModel::m_shaderRef = 0;
#ifdef _DEBUG
std::string		AnimeModel::m_errorStr = "";
#endif

/*
* @brief assimp���̍s���XMMATRIX�^�ɕϊ�
* @param[in] M assimp�̍s��
* @return �ϊ���̍s��
*/
DirectX::XMMATRIX GetMatrixFromAssimpMatrix(aiMatrix4x4 M)
{
	return DirectX::XMMatrixSet(
		M.a1, M.b1, M.c1, M.d1,
		M.a2, M.b2, M.c2, M.d2,
		M.a3, M.b3, M.c3, M.d3,
		M.a4, M.b4, M.c4, M.d4
	);
}

/*
* @brief �f�t�H���g�̃V�F�[�_�[���쐬
* @param[out] vs ���_�V�F�[�_�[�i�[��
* @param[out] ps �s�N�Z���V�F�[�_�[�i�[��
*/
void MakeAnimeModelDefaultShader(VertexShader** vs, PixelShader** ps)
{
	const char* AnimeModelVS = R"EOT(
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
	const char* AnimeModelPS = R"EOT(
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
	(*vs)->Compile(AnimeModelVS);
	*ps = new PixelShader();
	(*ps)->Compile(AnimeModelPS);
}



/*
* @brief �R���X�g���N�^
*/
AnimeModel::AnimeModel()
	: m_loadScale(1.0f)
	, m_loadFlip(None)
	, m_playNo(ANIME_NONE)
	, m_blendNo(ANIME_NONE)
	, m_parametric{ ANIME_NONE, ANIME_NONE }
	, m_blendTime(0.0f)
	, m_blendTotalTime(0.0f)
	, m_parametricBlend(0.0f)
{
	// �f�t�H���g�V�F�[�_�[�̓K�p
	if (m_shaderRef == 0)
	{
		MakeAnimeModelDefaultShader(&m_pDefVS, &m_pDefPS);
	}
	m_pVS = m_pDefVS;
	m_pPS = m_pDefPS;
	++m_shaderRef;
}

/*
* @brief �f�X�g���N�^
*/
AnimeModel::~AnimeModel()
{
	Reset();
	--m_shaderRef;
	if (m_shaderRef <= 0)
	{
		delete m_pDefPS;
		delete m_pDefVS;
	}
}

/*
* @brief �����f�[�^�폜
*/
void AnimeModel::Reset()
{
	auto meshIt = m_meshes.begin();
	while (meshIt != m_meshes.end())
	{
		if (meshIt->pMesh) delete meshIt->pMesh;
		++meshIt;
	}

	auto matIt = m_materials.begin();
	while (matIt != m_materials.end())
	{
		if (matIt->pTexture) delete matIt->pTexture;
		++matIt;
	}
}

/*
* @brief ���_�V�F�[�_�[�ݒ�
*/
void AnimeModel::SetVertexShader(VertexShader* vs)
{
	m_pVS = vs;
}

/*
* @brief �s�N�Z���V�F�[�_�[�ݒ�
*/
void AnimeModel::SetPixelShader(PixelShader* ps)
{
	m_pPS = ps;
}

/*
* @brief ���f���f�[�^�ǂݍ���
* @param[in] file �ǂݍ��ރ��f���t�@�C���ւ̃p�X
* @param[in] scale ���f���̃T�C�Y�ύX
* @param[in] flip ���]�ݒ�
* @return �ǂݍ��݌���
*/
bool AnimeModel::Load(const char* file, float scale, Flip flip)
{
#ifdef _DEBUG
	m_errorStr = "";
#endif
	Reset();

	// assimp�̐ݒ�
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_FlipUVs;
	if (flip == Flip::XFlip)  flag |= aiProcess_MakeLeftHanded;

	// assimp�œǂݍ���
	const aiScene* pScene = importer.ReadFile(file, flag);
	if (!pScene) {
		m_errorStr = importer.GetErrorString();
		return false;
	}

	// �ǂݍ��ݎ��̐ݒ��ۑ�
	m_loadScale = scale;
	m_loadFlip = flip;

	// �f�B���N�g���̓ǂݎ��
	std::string directory = file;
	auto strIt = directory.begin();
	while (strIt != directory.end()) {
		if (*strIt == '/')
			*strIt = '\\';
		++strIt;
	}
	directory = directory.substr(0, directory.find_last_of('\\') + 1);

	// �m�[�h�̍쐬
	MakeBoneNodes(pScene);
	// ���b�V���쐬
	MakeMesh(pScene, scale, flip);
	// �}�e���A���̍쐬
	MakeMaterial(pScene, directory);

	return true;
}

/*
* @brief �`��
* @param[in] order �`�揇��
* @param[in] func ���b�V���`��R�[���o�b�N
*/
void AnimeModel::Draw(const std::vector<UINT>* order, std::function<void(int)> func)
{
	// �V�F�[�_�[�ݒ�
	m_pVS->Bind();
	m_pPS->Bind();

	// �`�搔�ݒ�
	size_t drawNum = m_meshes.size();
	if (order)
	{
		drawNum = order->size();
	}

	// �`��
	for (UINT i = 0; i < drawNum; ++i)
	{
		// ���b�V���ԍ��ݒ�
		UINT meshNo = i;
		if (order)
		{
			meshNo = (*order)[i];
		}

		// �`��R�[���o�b�N
		if (func)
		{
			func(meshNo);
		}
		else
		{
			m_pPS->SetTexture(0, m_materials[m_meshes[meshNo].materialID].pTexture);
		}

		// �`��
		m_meshes[meshNo].pMesh->Draw();
	}
}

/*
* @brief ���b�V�����擾
* @param[in] index ���b�V���ԍ�
* @return �Y�����b�V�����
*/
const AnimeModel::Mesh* AnimeModel::GetMesh(unsigned int index)
{
	if (index < GetMeshNum())
	{
		return &m_meshes[index];
	}
	return nullptr;
}

/*
* @brief ���b�V�����擾
*/
uint32_t AnimeModel::GetMeshNum()
{
	return static_cast<uint32_t>(m_meshes.size());
}

/*
* @brief �}�e���A�����擾
* @param[in] index �}�e���A���ԍ�
* @return �Y���}�e���A�����
*/
const AnimeModel::Material* AnimeModel::GetMaterial(unsigned int index)
{
	if (index < GetMaterialNum())
	{
		return &m_materials[index];
	}
	return nullptr;
}

/*
* @brief �}�e���A�����擾
*/
uint32_t AnimeModel::GetMaterialNum()
{
	return static_cast<uint32_t>(m_materials.size());
}

/*
* @brief �A�j���[�V������̕ϊ��s��擾
* @param[in] index �{�[���ԍ�
* @return �Y���{�[���̕ϊ��s��
*/
DirectX::XMMATRIX AnimeModel::GetBone(NodeIndex index)
{
	if (index < m_nodes.size())
	{
		return m_nodes[index].mat;
	}
	return DirectX::XMMatrixIdentity();
}

/*
* @brief �A�j���[�V�������擾
* @param[in] no �A�j���ԍ�
* @return �Y���A�j���[�V�������
*/
const AnimeModel::Animation* AnimeModel::GetAnimation(AnimeNo no)
{
	if (AnimeNoCheck(no))
	{
		return &m_animes[no];
	}
	return nullptr;
}


/*
* @brief �A�j���[�V�����ǂݍ���
* @param[in] file �ǂݍ��ރA�j���[�V�����t�@�C���ւ̃p�X
* @return �����Ŋ��蓖�Ă�ꂽ�A�j���[�V�����ԍ�
*/
AnimeModel::AnimeNo AnimeModel::AddAnimation(const char* file)
{
#ifdef _DEBUG
	m_errorStr = "";
#endif

	// assimp�̐ݒ�
	Assimp::Importer importer;
	int flag = 0;
	flag |= aiProcess_Triangulate;
	flag |= aiProcess_FlipUVs;
	if (m_loadFlip == Flip::XFlip)  flag |= aiProcess_MakeLeftHanded;

	// assimp�œǂݍ���
	const aiScene* pScene = importer.ReadFile(file, flag);
	if (!pScene)
	{
#ifdef _DEBUG
		m_errorStr += importer.GetErrorString();
#endif
		return ANIME_NONE;
	}

	// �A�j���[�V�����`�F�b�N
	if (!pScene->HasAnimations())
	{
#ifdef _DEBUG
		m_errorStr += "no animation.";
#endif
		return ANIME_NONE;
	}

	// �A�j���[�V�����f�[�^�m��
	aiAnimation* assimpAnime = pScene->mAnimations[0];
	m_animes.push_back(Animation());
	Animation& anime = m_animes.back();

	// �A�j���[�V�����ݒ�
	float animeFrame = static_cast<float>(assimpAnime->mTicksPerSecond);
	anime.totalTime = static_cast<float>(assimpAnime->mDuration) / animeFrame;
	anime.channels.resize(assimpAnime->mNumChannels);
	Channels::iterator channelIt = anime.channels.begin();
	while (channelIt != anime.channels.end())
	{
		// �Ή�����`�����l��(�{�[��)��T��
		uint32_t channelIdx = static_cast<uint32_t>(channelIt - anime.channels.begin());
		aiNodeAnim* assimpChannel = assimpAnime->mChannels[channelIdx];
		AnimeModel::Nodes::iterator nodeIt = std::find_if(m_nodes.begin(), m_nodes.end(),
			[assimpChannel](Node& node) {
			return node.name == assimpChannel->mNodeName.data;
		});
		if (nodeIt == m_nodes.end())
		{
			channelIt->index = INDEX_NONE;
			++channelIt;
			continue;
		}

		// �e�L�[�̒l��ݒ�
		channelIt->index = static_cast<NodeIndex>(nodeIt - m_nodes.begin());
		Timeline& timeline = channelIt->timeline;

		// ��xXMVECTOR�^�Ŋi�[
		using XMVectorKey = std::pair<float, DirectX::XMVECTOR>;
		using XMVectorKeys = std::map<float, DirectX::XMVECTOR>;
		XMVectorKeys keys[3];
		// �ʒu
		for (UINT i = 0; i < assimpChannel->mNumPositionKeys; ++i)
		{
			aiVectorKey& key = assimpChannel->mPositionKeys[i];
			keys[0].insert(XMVectorKey(static_cast<float>(key.mTime) / animeFrame,
				DirectX::XMVectorSet(key.mValue.x, key.mValue.y, key.mValue.z, 0.0f)
			));
		}
		// ��]
		for (UINT i = 0; i < assimpChannel->mNumRotationKeys; ++i)
		{
			aiQuatKey& key = assimpChannel->mRotationKeys[i];
			keys[1].insert(XMVectorKey(static_cast<float>(key.mTime) / animeFrame,
				DirectX::XMVectorSet(key.mValue.x, key.mValue.y, key.mValue.z, key.mValue.w)));
		}
		// �g�k
		for (UINT i = 0; i < assimpChannel->mNumScalingKeys; ++i)
		{
			aiVectorKey& key = assimpChannel->mScalingKeys[i];
			keys[2].insert(XMVectorKey(static_cast<float>(key.mTime) / animeFrame,
				DirectX::XMVectorSet(key.mValue.x, key.mValue.y, key.mValue.z, 0.0f)));
		}

		// �e�^�C�����C���̐擪�̎Q�Ƃ�ݒ�
		XMVectorKeys::iterator it[] = { keys[0].begin(), keys[1].begin(), keys[2].begin() };
		for (int i = 0; i < 3; ++i)
		{
			// �L�[��������Ȃ��ꍇ�́A�Q�ƏI��
			if (keys[i].size() == 1)
				++it[i];
		}

		// �e�v�f���Ƃ̃^�C�����C���ł͂Ȃ��A���ׂĂ̕ϊ����܂߂��^�C�����C���̍쐬
		while (it[0] != keys[0].end() && it[1] != keys[1].end() && it[2] != keys[2].end())
		{
			// ����̎Q�ƈʒu�ň�ԏ��������Ԃ��擾
			float time = anime.totalTime;
			for (int i = 0; i < 3; ++i)
			{
				if (it[i] != keys[i].end())
				{
					time = std::min(it[i]->first, time);
				}
			}

			// ���ԂɊ�Â��ĕ�Ԓl���v�Z
			DirectX::XMVECTOR result[3];
			for (int i = 0; i < 3; ++i)
			{
				// �擪�̃L�[��菬�������Ԃł���΁A�擪�̒l��ݒ�
				if (time < keys[i].begin()->first)
				{
					result[i] = keys[i].begin()->second;
				}
				// �ŏI�L�[���傫�����Ԃł���΁A�ŏI�̒l��ݒ�
				else if (keys[i].rbegin()->first <= time)
				{
					result[i] = keys[i].rbegin()->second;
					it[i] = keys[i].end();
				}
				// �L�[���m�ɋ��܂ꂽ���Ԃł���΁A��Ԓl���v�Z
				else
				{
					// �Q�Ƃ��Ă��鎞�ԂƓ����ł���΁A���̎Q�ƂփL�[��i�߂�
					if (it[i]->first <= time)
					{
						++it[i];
					}

					// ��Ԓl�̌v�Z
					XMVectorKeys::iterator prev = it[i];
					--prev;
					float rate = (time - prev->first) / (it[i]->first - prev->first);
					result[i] = DirectX::XMVectorLerp(prev->second, it[i]->second, rate);
				}
			}

			// �w�莞�ԂɊ�Â����L�[��ǉ�
			Transform transform;
			DirectX::XMStoreFloat3(&transform.translate, result[0]);
			DirectX::XMStoreFloat4(&transform.quaternion, result[1]);
			DirectX::XMStoreFloat3(&transform.scale, result[2]);
			timeline.insert(Key(time, transform));
		}

		++channelIt;
	}

	// �A�j���ԍ���Ԃ�
	return static_cast<AnimeNo>(m_animes.size() - 1);
}

/*
* @brief �A�j���[�V�����̍X�V����
* @param[in] tick �A�j���[�V�����o�ߎ���
*/
void AnimeModel::Step(float tick)
{
	// �A�j���[�V�����̍Đ��m�F
	if (m_playNo == ANIME_NONE) { return; }

	//--- �A�j���[�V�����s��̍X�V
	// �p�����g���b�N
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		CalcAnime(PARAMETRIC0, m_parametric[0]);
		CalcAnime(PARAMETRIC1, m_parametric[1]);
	}
	// ���C���A�j��
	if (m_playNo != ANIME_NONE && m_playNo != PARAMETRIC_ANIME)
	{
		CalcAnime(MAIN, m_playNo);
	}
	// �u�����h�A�j��
	if (m_blendNo != ANIME_NONE && m_blendNo != PARAMETRIC_ANIME)
	{
		CalcAnime(BLEND, m_blendNo);
	}

	// �A�j���[�V�����s��Ɋ�Â��č��s����X�V
	CalcBones(0, DirectX::XMMatrixScaling(m_loadScale, m_loadScale, m_loadScale));

	//--- �A�j���[�V�����̎��ԍX�V
	// ���C���A�j��
	UpdateAnime(m_playNo, tick);
	// �u�����h�A�j��
	if (m_blendNo != ANIME_NONE)
	{
		UpdateAnime(m_blendNo, tick);
		m_blendTime += tick;
		if (m_blendTime <= m_blendTime)
		{
			// �u�����h�A�j���̎����I��
			m_blendTime = 0.0f;
			m_blendTotalTime = 0.0f;
			m_playNo = m_blendNo;
			m_blendNo = ANIME_NONE;
		}
	}
	// �p�����g���b�N
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		UpdateAnime(m_parametric[0], tick);
		UpdateAnime(m_parametric[1], tick);
	}
}

/*
* @brief �A�j���[�V�����Đ�
* @param[in] no �Đ�����A�j���[�V�����ԍ�
* @param[in] loop ���[�v�Đ��t���O
* @param[in] speed �Đ����x
*/
void AnimeModel::Play(AnimeNo no, bool loop, float speed)
{
	// �Đ��`�F�b�N
	if (!AnimeNoCheck(no)) { return; }
	if (m_playNo == no) { return; }

	// �����A�j���[�V�������`�F�b�N
	if (no != PARAMETRIC_ANIME)
	{
		// �ʏ�̏�����
		InitAnime(no);
		m_animes[no].isLoop = loop;
		m_animes[no].speed = speed;
	}
	else
	{
		// �����A�j���[�V�����̌��ɂȂ��Ă���A�j���[�V������������
		InitAnime(m_parametric[0]);
		InitAnime(m_parametric[1]);
		m_animes[m_parametric[0]].isLoop = loop;
		m_animes[m_parametric[1]].isLoop = loop;
		SetParametricBlend(0.0f);
	}

	// �Đ��A�j���[�V�����̐ݒ�
	m_playNo = no;
}

/*
* @brief �u�����h�Đ�
* @param[in] no �A�j���[�V�����ԍ�
* @param[in] blendTime �u�����h�Ɋ|���鎞��
* @param[in] loop ���[�v�t���O
* @param[in] speed �Đ����x
*/
void AnimeModel::PlayBlend(AnimeNo no, float blendTime, bool loop, float speed)
{
	// �Đ��`�F�b�N
	if (!AnimeNoCheck(no)) { return; }

	// �����A�j���[�V�������`�F�b�N
	if (no != PARAMETRIC_ANIME)
	{
		InitAnime(no);
		m_animes[no].isLoop = loop;
		m_animes[no].speed = speed;
	}
	else
	{
		// �����A�j���[�V�����̌��ɂȂ��Ă���A�j���[�V������������
		InitAnime(m_parametric[0]);
		InitAnime(m_parametric[1]);
		m_animes[m_parametric[0]].isLoop = loop;
		m_animes[m_parametric[1]].isLoop = loop;
		SetParametricBlend(0.0f);
	}

	// �u�����h�̐ݒ�
	m_blendTime = 0.0f;
	m_blendTotalTime = blendTime;
	m_blendNo = no;
}

/*
* @brief �������A�j���[�V�����̐ݒ�
* @param[in] no1 �������A�j��1
* @param[in] no2 �������A�j��2
*/
void AnimeModel::SetParametric(AnimeNo no1, AnimeNo no2)
{
	// �A�j���[�V�����`�F�b�N
	if (!AnimeNoCheck(no1)) { return; }
	if (!AnimeNoCheck(no2)) { return; }

	// �����ݒ�
	m_parametric[0] = no1;
	m_parametric[1] = no2;
	SetParametricBlend(0.0f);
}

/*
* @brief �A�j���[�V�����̍��������ݒ�
* @param[in] blendRate ��������
*/
void AnimeModel::SetParametricBlend(float blendRate)
{
	// �������A�j�����ݒ肳��Ă��邩�m�F
	if (m_parametric[0] == ANIME_NONE || m_parametric[1] == ANIME_NONE) return;

	// ���������ݒ�
	m_parametricBlend = blendRate;

	// �����Ɋ�Â��ăA�j���[�V�����̍Đ����x��ݒ�
	Animation& anime1 = m_animes[m_parametric[0]];
	Animation& anime2 = m_animes[m_parametric[1]];
	float blendTotalTime = anime1.totalTime * (1.0f - m_parametricBlend) + anime2.totalTime * m_parametricBlend;
	anime1.speed = anime1.totalTime / blendTotalTime;
	anime2.speed = anime2.totalTime / blendTotalTime;
}

/*
* @brief �A�j���[�V�����̍Đ����Ԃ�ύX
* @param[in] no �ύX����A�j��
* @param[in] time �V�����Đ�����
*/
void AnimeModel::SetAnimationTime(AnimeNo no, float time)
{
	// �A�j���[�V�����`�F�b�N
	if (!AnimeNoCheck(no)) { return; }

	// �Đ����ԕύX
	Animation& anime = m_animes[no];
	anime.nowTime = time;
	while (anime.nowTime >= anime.totalTime)
	{
		anime.nowTime -= anime.totalTime;
	}
}

/*
* @brief �A�j���[�V�����̍Đ����x��ύX(�V�c�ǉ�)
* @param[in] no �ύX����A�j��
* @param[in] speed �V�����Đ����x
*/
void AnimeModel::SetAnimationSpeed(AnimeNo no, float speed)
{
	// �A�j���[�V�����`�F�b�N
	if (!AnimeNoCheck(no)) { return; }

	m_animes[no].speed = speed;
}

/*
* @brief �Đ��t���O�̎擾
* @param[in] no ���ׂ�A�j���ԍ�
* @return ���ݍĐ����Ȃ�true
*/
bool AnimeModel::IsPlay(AnimeNo no)
{
	// �A�j���[�V�����`�F�b�N
	if (!AnimeNoCheck(no)) { return false; }

	// �p�����g���b�N�͍������̃A�j������ɔ��f
	if (no == PARAMETRIC_ANIME) { no = m_parametric[0]; }

	// �Đ����Ԃ̔���
	if (m_animes[no].totalTime < m_animes[no].nowTime) { return false; }

	// ���ꂼ��̍Đ��ԍ��ɐݒ肳��Ă��邩�m�F
	if (m_playNo == no) { return true; }
	if (m_blendNo == no) { return true; }
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		if (m_parametric[0] == no) { return true; }
		if (m_parametric[1] == no) { return true; }
	}

	// �Đ����łȂ�
	return false;
}

/*
* @brief �Đ����̔ԍ��̎擾
* @return �A�j���ԍ�
*/
AnimeModel::AnimeNo AnimeModel::GetPlayNo()
{
	return m_playNo;
}

/*
* @brief �Đ����̃u�����h�A�j���̎擾
* @return �A�j���ԍ�
*/
AnimeModel::AnimeNo AnimeModel::GetBlendNo()
{
	return m_blendNo;
}


#ifdef _DEBUG

/*
* @brief �G���[���b�Z�[�W�擾
* @returnn �G���[���b�Z�[�W
*/
std::string AnimeModel::GetError()
{
	return m_errorStr;
}

/*
* @brief �{�[���f�o�b�O�`��
*/
void AnimeModel::DrawBone()
{
	// �ċA����
	std::function<void(int, DirectX::XMFLOAT3)> FuncDrawBone =
		[&FuncDrawBone, this](int idx, DirectX::XMFLOAT3 parent)
	{
		// �e�m�[�h���猻�݈ʒu�܂ŕ`��
		DirectX::XMFLOAT3 pos;
		DirectX::XMStoreFloat3(&pos, DirectX::XMVector3TransformCoord(DirectX::XMVectorZero(), m_nodes[idx].mat));
		CLine::Add(parent, pos, DirectX::XMFLOAT4(1.0f, 0.0f, 0.0f, 1.0f));

		// �q�m�[�h�̕`��
		auto it = m_nodes[idx].children.begin();
		while (it != m_nodes[idx].children.end())
		{
			FuncDrawBone(*it, pos);
			++it;
		}
	};

	// �`����s
	FuncDrawBone(0, DirectX::XMFLOAT3());
	CLine::Draw();
}

#endif


void AnimeModel::MakeBoneNodes(const void* ptr)
{
	// �ċA������Assimp�̃m�[�h����ǂݎ��
	std::function<NodeIndex(aiNode*, NodeIndex, DirectX::XMMATRIX mat)> FuncAssimpNodeConvert =
		[&FuncAssimpNodeConvert, this](aiNode* assimpNode, NodeIndex parent, DirectX::XMMATRIX mat)
	{
		DirectX::XMMATRIX transform = GetMatrixFromAssimpMatrix(assimpNode->mTransformation);
		std::string name = assimpNode->mName.data;
		if (name.find("$AssimpFbx") != std::string::npos)
		{
			mat = transform * mat;
			return FuncAssimpNodeConvert(assimpNode->mChildren[0], parent, mat);
		}
		else
		{
			// Assimp�̃m�[�h�������f���N���X�֊i�[
			Node node;
			node.name = assimpNode->mName.data;
			node.parent = parent;
			node.children.resize(assimpNode->mNumChildren);
			node.mat = mat;

			// �m�[�h���X�g�ɒǉ�
			m_nodes.push_back(node);
			NodeIndex nodeIndex = static_cast<NodeIndex>(m_nodes.size() - 1);

			// �q�v�f�����l�ɕϊ�
			for (UINT i = 0; i < assimpNode->mNumChildren; ++i)
			{
				m_nodes[nodeIndex].children[i] = FuncAssimpNodeConvert(
					assimpNode->mChildren[i], nodeIndex, DirectX::XMMatrixIdentity());
			}
			return nodeIndex;
		}
	};

	// �m�[�h�쐬
	m_nodes.clear();
	FuncAssimpNodeConvert(reinterpret_cast<const aiScene*>(ptr)->mRootNode, INDEX_NONE, DirectX::XMMatrixIdentity());

	// �A�j���[�V�����v�Z�̈�ɁA�m�[�h�����̏����f�[�^���쐬
	Transform init = {
		DirectX::XMFLOAT3(0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT4(0.0f, 0.0f, 0.0f, 0.0f),
		DirectX::XMFLOAT3(1.0f, 1.0f, 1.0f)
	};
	for (int i = 0; i < MAX_TRANSFORM; ++i)
	{
		m_nodeTransform[i].resize(m_nodes.size(), init);
	}
}

void AnimeModel::MakeWeight(const void* ptr, int meshIdx)
{
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);

	// ���b�V���ɑΉ�����{�[�������邩
	aiMesh* assimpMesh = pScene->mMeshes[meshIdx];
	Mesh& mesh = m_meshes[meshIdx];
	if (assimpMesh->HasBones())
	{
		// ���b�V���Ɋ��蓖�Ă��Ă���{�[���̈�m��
		mesh.bones.resize(assimpMesh->mNumBones);
		for (auto boneIt = mesh.bones.begin(); boneIt != mesh.bones.end(); ++boneIt)
		{
			UINT boneIdx = static_cast<UINT>(boneIt - mesh.bones.begin());
			aiBone* assimpBone = assimpMesh->mBones[boneIdx];
			// �\�z�ς݂̃{�[���m�[�h����Y���m�[�h���擾
			std::string boneName = assimpBone->mName.data;
			auto nodeIt = std::find_if(m_nodes.begin(), m_nodes.end(),
				[boneName](const Node& val) {
				return val.name == boneName;
			});
			// ���b�V���Ɋ��蓖�Ă��Ă���{�[�����A�m�[�h�ɑ��݂��Ȃ�
			if (nodeIt == m_nodes.end())
			{
				boneIt->index = INDEX_NONE;
				continue;
			}

			// ���b�V���̃{�[���ƃm�[�h�̕R�Â�
			boneIt->index = static_cast<NodeIndex>(nodeIt - m_nodes.begin());
			boneIt->invOffset = GetMatrixFromAssimpMatrix(assimpBone->mOffsetMatrix);
			boneIt->invOffset.r[3].m128_f32[0] *= m_loadScale;
			boneIt->invOffset.r[3].m128_f32[1] *= m_loadScale;
			boneIt->invOffset.r[3].m128_f32[2] *= m_loadScale;
			boneIt->invOffset =
				DirectX::XMMatrixScaling(m_loadFlip == ZFlipUseAnime ? -1.0f : 1.0f, 1.0f, 1.0f) *
				boneIt->invOffset *
				DirectX::XMMatrixScaling(1.f / m_loadScale, 1.f / m_loadScale, 1.f / m_loadScale);

			// �E�F�C�g�̐ݒ�
			UINT weightNum = assimpBone->mNumWeights;
			for (UINT i = 0; i < weightNum; ++i)
			{
				aiVertexWeight weight = assimpBone->mWeights[i];
				Vertex& vtx = mesh.vertices[weight.mVertexId];
				for (int j = 0; j < 4; ++j)
				{
					if (vtx.weight[j] <= 0.0f)
					{
						vtx.index[j] = boneIdx;
						vtx.weight[j] = weight.mWeight;
						break;
					}
				}
			}
		}
	}
	else
	{
		// ���b�V���̐e�m�[�h���g�����X�t�H�[�����Ƃ��Čv�Z
		std::string nodeName = assimpMesh->mName.data;
		auto nodeIt = std::find_if(m_nodes.begin(), m_nodes.end(),
			[nodeName](const Node& val) {
			return val.name == nodeName;
		});
		if (nodeIt == m_nodes.end())
		{
			return;	// �{�[���f�[�^�Ȃ�
		}

		// ���b�V���łȂ��e�m�[�h���ċA�T��
		std::function<int(int)> FuncFindNode =
			[&FuncFindNode, this, pScene](NodeIndex parent)
		{
			std::string name = m_nodes[parent].name;
			for (UINT i = 0; i < pScene->mNumMeshes; ++i)
			{
				if (name == pScene->mMeshes[i]->mName.data)
				{
					return FuncFindNode(m_nodes[parent].parent);
				}
			}
			return parent;
		};

		Bone bone;
		bone.index = FuncFindNode(nodeIt->parent);
		bone.invOffset = DirectX::XMMatrixInverse(nullptr, m_nodes[bone.index].mat);
		for (auto vtxIt = mesh.vertices.begin(); vtxIt != mesh.vertices.end(); ++vtxIt)
		{
			vtxIt->weight[0] = 1.0f;
		}

		mesh.bones.resize(1);
		mesh.bones[0] = bone;
	}
}



bool AnimeModel::AnimeNoCheck(AnimeNo no)
{
	// �p�����g���b�N�A�j���[�V�����m�F
	if (no == PARAMETRIC_ANIME)
	{
		// �p�����g���b�N�̃A�j���[�V�����������������ݒ肳��Ă��邩
		return
			m_parametric[0] != ANIME_NONE &&
			m_parametric[1] != ANIME_NONE;
	}
	else
	{
		// ���Ȃ��A�j���[�V�����ԍ����ǂ���
		return 0 <= no && no < m_animes.size();
	}
}
void AnimeModel::InitAnime(AnimeNo no)
{
	// �A�j���̐ݒ�Ȃ��A�p�����g���b�N�Őݒ肳��Ă���Ȃ珉�������Ȃ�
	if (no == ANIME_NONE || no == PARAMETRIC_ANIME) { return; }

	Animation& anime = m_animes[no];
	anime.nowTime = 0.0f;
	anime.speed = 1.0f;
	anime.isLoop = false;
}
void AnimeModel::CalcAnime(AnimeTransform kind, AnimeNo no)
{
	Animation& anime = m_animes[no];
	Channels::iterator channelIt = anime.channels.begin();
	while (channelIt != anime.channels.end())
	{
		// ��v����{�[�����Ȃ���΃X�L�b�v
		Timeline& timeline = channelIt->timeline;
		if (channelIt->index == INDEX_NONE || timeline.empty())
		{
			++channelIt;
			continue;
		}

		//--- �Y���m�[�h�̎p�����A�j���[�V�����ōX�V
		Transform& transform = m_nodeTransform[kind][channelIt->index];
		if (timeline.size() <= 1)
		{
			// �L�[��������Ȃ��̂Œl�����̂܂܎g�p
			transform = channelIt->timeline[0];
		}
		else
		{
			Timeline::iterator startIt = timeline.begin();
			if (anime.nowTime <= startIt->first)
			{
				// �擪�L�[�����O�̎��ԂȂ�A�擪�̒l���g�p
				transform = startIt->second;
			}
			else if (timeline.rbegin()->first <= anime.nowTime)
			{
				// �ŏI�L�[������̎��ԂȂ�A�Ō�̒l���g�p
				transform = timeline.rbegin()->second;
			}
			else
			{
				// �w�肳�ꂽ���Ԃ�����2�̃L�[����A��Ԃ��ꂽ�l���v�Z
				Timeline::iterator nextIt = timeline.upper_bound(anime.nowTime);
				startIt = nextIt;
				--startIt;
				float rate = (anime.nowTime - startIt->first) / (nextIt->first - startIt->first);
				LerpTransform(&transform, startIt->second, nextIt->second, rate);
			}
		}

		++channelIt;
	}
}
void AnimeModel::UpdateAnime(AnimeNo no, float tick)
{
	if (no == PARAMETRIC_ANIME) { return; }

	Animation& anime = m_animes[no];
	anime.nowTime += anime.speed * tick;
	if (anime.isLoop)
	{
		while (anime.nowTime >= anime.totalTime)
		{
			anime.nowTime -= anime.totalTime;
		}
	}
}
void AnimeModel::CalcBones(NodeIndex index, const DirectX::XMMATRIX parent)
{
	//--- �A�j���[�V�������Ƃ̃p�����[�^������
	Transform transform;
	// �p�����g���b�N
	if (m_playNo == PARAMETRIC_ANIME || m_blendNo == PARAMETRIC_ANIME)
	{
		LerpTransform(&transform, m_nodeTransform[PARAMETRIC0][index], m_nodeTransform[PARAMETRIC1][index], m_parametricBlend);
		if (m_playNo == PARAMETRIC_ANIME)
		{
			m_nodeTransform[MAIN][index] = transform;
		}
		if (m_blendNo == PARAMETRIC_ANIME)
		{
			m_nodeTransform[BLEND][index] = transform;
		}
	}
	// �u�����h�A�j��
	if (m_blendNo != ANIME_NONE)
	{
		LerpTransform(&transform, m_nodeTransform[MAIN][index], m_nodeTransform[BLEND][index], m_blendTime / m_blendTotalTime);
	}
	else
	{
		// ���C���A�j���̂�
		transform = m_nodeTransform[MAIN][index];
	}

	// �Y���m�[�h�̎p���s����v�Z
	Node& node = m_nodes[index];
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslationFromVector(DirectX::XMLoadFloat3(&transform.translate));
	DirectX::XMMATRIX R = DirectX::XMMatrixRotationQuaternion(DirectX::XMLoadFloat4(&transform.quaternion));
	DirectX::XMMATRIX S = DirectX::XMMatrixScalingFromVector(DirectX::XMLoadFloat3(&transform.scale));
	node.mat = (S * R * T) * parent;

	// �q�v�f�̎p�����X�V
	Children::iterator it = node.children.begin();
	while (it != node.children.end())
	{
		CalcBones(*it, node.mat);
		++it;
	}
}

void AnimeModel::LerpTransform(Transform* pOut, const Transform& a, const Transform& b, float rate)
{
	DirectX::XMVECTOR vec[][2] = {
		{ DirectX::XMLoadFloat3(&a.translate),	DirectX::XMLoadFloat3(&b.translate) },
		{ DirectX::XMLoadFloat4(&a.quaternion),	DirectX::XMLoadFloat4(&b.quaternion) },
		{ DirectX::XMLoadFloat3(&a.scale),		DirectX::XMLoadFloat3(&b.scale) },
	};
	for (int i = 0; i < 3; ++i)
	{
		vec[i][0] = DirectX::XMVectorLerp(vec[i][0], vec[i][1], rate);
	}
	DirectX::XMStoreFloat3(&pOut->translate, vec[0][0]);
	DirectX::XMStoreFloat4(&pOut->quaternion, vec[1][0]);
	DirectX::XMStoreFloat3(&pOut->scale, vec[2][0]);
}

void AnimeModel::MakeMesh(const void* ptr, float scale, Flip flip)
{
	// ���O����
	aiVector3D zero3(0.0f, 0.0f, 0.0f);
	aiColor4D one4(1.0f, 1.0f, 1.0f, 1.0f);
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);
	float zflip = (flip == Flip::ZFlip || flip == Flip::ZFlipUseAnime) ? -1.0f : 1.0f;
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
				DirectX::XMFLOAT4(color.r, color.g, color.b, color.a),
			};
		}

		//�d�ݕt��
		MakeWeight(pScene, i);

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
		desc.vtxCount = UINT(m_meshes[i].vertices.size());
		desc.pIdx = m_meshes[i].indices.data();
		desc.idxSize = sizeof(unsigned long);
		desc.idxCount = UINT(m_meshes[i].indices.size());
		desc.topology = D3D11_PRIMITIVE_TOPOLOGY_TRIANGLELIST;
		m_meshes[i].pMesh = new MeshBuffer(desc);
	}
}
void AnimeModel::MakeMaterial(const void* ptr, std::string directory)
{
	// ���O����
	const aiScene* pScene = reinterpret_cast<const aiScene*>(ptr);

	// �}�e���A���̍쐬
	m_materials.resize(pScene->mNumMaterials);
	for (unsigned int i = 0; i < m_materials.size(); ++i)
	{
		// �e��p�����[�^�[
		//=========================================
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

		//=========================================

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
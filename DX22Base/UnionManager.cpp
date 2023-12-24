/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	UNION�Ǘ�����
	------------------------------------
	UnionManager.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/19 ���� takagi
	�E2023/12/24 �T�C�Y�E�t���[���ύX takagi

========================================== */

// =============== �C���N���[�h ===================
#include "UnionManager.h"	//���g�̃w�b�_
#include "CameraDef.h"		//�^���J����
#include "Slime_2.h"		//�����Ώ�
#include "Slime_3.h"		//�����Ώ�
#include "Slime_4.h"		//�����Ώ�

#if _DEBUG
#include <Windows.h>		//���b�Z�[�W�{�b�N�X�p
#endif

// =============== �萔��` =====================
const std::string VS_PASS("Assets/Shader/VsUnionManager.cso");				//�e�N�X�`���̃p�X��
const std::string PS_PASS("Assets/Shader/PsUnionManager.cso");				//�e�N�X�`���̃p�X��
const std::string TEX_PASS_SLIME2("Assets/Texture/Union/Union_Green.png");	//�e�N�X�`���̃p�X��
const std::string TEX_PASS_SLIME3("Assets/Texture/Union/Union_Yellow.png");	//�e�N�X�`���̃p�X��
const std::string TEX_PASS_SLIME4("Assets/Texture/Union/Union_Red.png");	//�e�N�X�`���̃p�X��
const TPos3d<float> INIT_POS(640.0f, 360.0f, 0.0f);						//�ʒu������
const TTriType<float> INIT_SCALE(4000.0f, 4000.0f, 0.0f);				//�����g�k
const TTriType<float> INIT_RADIAN(0.0f);								//������]
const TTriType<int> FRAME_FADE_MAX(100, 60, 70);						//�t�F�[�h�ɂ�����t���[����	x:�A�E�g, y:�X�g�b�v, z:�C��
const int FRAME_MIN(0);													//�t�F�[�h���Ԃ̍ŏ�
const int FRAME_OUT_PATTERN_1_FIN(50);									//�t�F�[�h�A�E�g�J�n����g�k�����܂�܂ł̃t���[����
const int FRAME_OUT_PATTERN_2_FIN(80);									//�t�F�[�h�A�E�g�J�n����g�k�����܂�I���܂ł̃t���[����
const float SCALE_OUT_MIN(500.0f);										//�t�F�[�h�A�E�g�ŏ��T�C�Y	uv�̓s����A�l���傫�����T�C�Y���������Ȃ�
const float SCALE_IN_MIN(600.0f);										//�t�F�[�h�C���ŏ��T�C�Y	uv�̓s����A�l���傫�����T�C�Y���������Ȃ�
const float SCALE_OUT_STAY(10.0f);										//�t�F�[�h�A�E�g�g�k���ꎞ���܂�Ƃ��̃T�C�Y
const float SCALE_OUT_MAX(0.0f);										//�t�F�[�h�ő�T�C�Y	uv�̓s����A�l�����������T�C�Y���傫���Ȃ�
const float SCALE_IN_MAX(0.0f);											//�t�F�[�h�ő�T�C�Y	uv�̓s����A�l�����������T�C�Y���傫���Ȃ�
const float ROTATE_ACCEL_RATE(8.0f);									//�p���x��������
const std::map<size_t, TTriType<float>>MAP_SCALE = {
	{ typeid(CSlime_2).hash_code(), {1272.0f * 0.003f, 636.0f * 0.003f, 0.0f} },	//�X���C��2�a���p
	{ typeid(CSlime_3).hash_code(), {1272.0f * 0.004f, 636.0f * 0.004f, 0.0f} },	//�X���C��3�a���p
	{ typeid(CSlime_4).hash_code(), {1272.0f * 0.005f, 636.0f * 0.005f, 0.0f} },	//�X���C��4�a���p
};	//UNION�̑傫��
const std::map<size_t, int>MAP_FRAME = {
	{ typeid(CSlime_2).hash_code(), 60 },	//�X���C��2�a���p
	{ typeid(CSlime_3).hash_code(), 90 },	//�X���C��3�a���p
	{ typeid(CSlime_4).hash_code(), 120 },	//�X���C��4�a���p
};	//UNION�\������

// =============== �O���[�o���ϐ��錾 =====================
int CUnionManager::ms_nCntUnionManager;					//���g�̐�����
std::map<size_t, Texture*> CUnionManager::ms_pTexture;	//�e�N�X�`�����

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�������ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CUnionManager::CUnionManager()
	:m_ucFlag(0x00)		//�t���O
	,m_pCamera(nullptr)	//�J����
{
	// =============== �ÓI�쐬 ===================
	if (0 == ms_nCntUnionManager)	//���݁A���ɂ��̃N���X���쐬����Ă��Ȃ���
	{
		// =============== �e�N�X�`�����Z�b�g ===================
		if (ms_pTexture.size() > 0)	//�܂��R���e�i�Ɏc���Ă��鎞
		{
			for (auto Iterator = ms_pTexture.begin(); Iterator != ms_pTexture.end();)
			{
				if (Iterator->second)	//�k���`�F�b�N
				{
					SAFE_DELETE(Iterator->second);	//�폜
				}
				Iterator = ms_pTexture.erase(Iterator);	//�C�e���[�^�폜
			}
		}

		// =============== �e�N�X�`���쐬 ===================
		ms_pTexture.insert(std::pair<size_t, Texture*>(typeid(CSlime_2).hash_code(), new Texture));	//�R���e�i�i�[
#if _DEBUG
		if (FAILED(ms_pTexture.at(typeid(CSlime_2).hash_code())->Create(TEX_PASS_SLIME2.c_str())))	//�V�K�e�N�X�`���o�^
		{
			std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";					//�G���[�ӏ�
			MessageBox(nullptr, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", ErrorSpot.c_str(), MB_OK);	//�G���[�ʒm
		}
#else
		ms_pTexture.at(typeid(CSlime_2).hash_code())->Create(TEX_PASS_SLIME2.c_str());	//�V�K�e�N�X�`���o�^
#endif
		ms_pTexture.insert(std::pair<size_t, Texture*>(typeid(CSlime_3).hash_code(), new Texture));	//�R���e�i�i�[
#if _DEBUG
		if (FAILED(ms_pTexture.at(typeid(CSlime_3).hash_code())->Create(TEX_PASS_SLIME3.c_str())))	//�V�K�e�N�X�`���o�^
		{
			std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";					//�G���[�ӏ�
			MessageBox(nullptr, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", ErrorSpot.c_str(), MB_OK);	//�G���[�ʒm
		}
#else
		ms_pTexture.at(typeid(CSlime_3).hash_code())->Create(TEX_PASS_SLIME3.c_str());	//�V�K�e�N�X�`���o�^
#endif
		ms_pTexture.insert(std::pair<size_t, Texture*>(typeid(CSlime_4).hash_code(), new Texture));	//�R���e�i�i�[
#if _DEBUG
		if (FAILED(ms_pTexture.at(typeid(CSlime_4).hash_code())->Create(TEX_PASS_SLIME4.c_str())))	//�V�K�e�N�X�`���o�^
		{
			std::string ErrorSpot = typeid(*this).name(); ErrorSpot += "->Error";					//�G���[�ӏ�
			MessageBox(nullptr, "�e�N�X�`���̓ǂݍ��݂Ɏ��s���܂���", ErrorSpot.c_str(), MB_OK);	//�G���[�ʒm
		}
#else
		ms_pTexture.at(typeid(CSlime_4).hash_code())->Create(TEX_PASS_SLIME4.c_str());	//�V�K�e�N�X�`���o�^
#endif
	}
}

/* ========================================
	�R�s�[�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R�s�[���ɍs������
	-------------------------------------
	����1�Fconst CUnionManager & Obj�F�R�s�[���̎Q��
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
//CUnionManager::CUnionManager(const CUnionManager & Obj)
//{
//}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�j�����ɍs������
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
CUnionManager::~CUnionManager()
{
	// =============== �I�� ===================
	ms_nCntUnionManager--;				//���g�̐��J�E���g
	for (auto Iterator = m_pUnion.end(); Iterator != m_pUnion.begin();)
	{
		if (*--Iterator)	//�k���`�F�b�N
		{
			SAFE_DELETE(*Iterator);	//�폜
		}
		Iterator = m_pUnion.erase(Iterator);	//�C�e���[�^�폜
	}
	if (ms_nCntUnionManager == 0)
	{
		for (auto Iterator = ms_pTexture.begin(); Iterator != ms_pTexture.end();)
		{
			if (Iterator->second)	//�k���`�F�b�N
			{
				SAFE_DELETE(Iterator->second);	//�폜
			}
			Iterator = ms_pTexture.erase(Iterator);	//�C�e���[�^�폜
		}
	}
}

/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�X�V����
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CUnionManager::Update()
{
	// =============== �폜 ===================
	for (auto Iterator = m_pUnion.begin(); Iterator != m_pUnion.end();)
	{
		if (*Iterator)	//�k���`�F�b�N
		{
			(*Iterator)->Update();	//�X�V
			if ((*Iterator)->IsFin())	//��ڂ��I��������
			{
				SAFE_DELETE(*Iterator);					//�폜
				Iterator = m_pUnion.erase(Iterator);	//�C�e���[�^�폜
			}
			else
			{
				Iterator++;	//�C�e���[�^����
			}
		}
	}
}

/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�`�揈��
	-------------------------------------
	����1�F�Ȃ�
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CUnionManager::Draw()
{
	// =============== �`�� ===================
	for (auto Iterator = m_pUnion.begin(); Iterator != m_pUnion.end(); Iterator++)
	{
		if (*Iterator)	//�k���`�F�b�N
		{
			(*Iterator)->Draw();	//�`��
		}
	}
}

/* ========================================
	�J�����Z�b�g�֐�
	-------------------------------------
	���e�F�J�����̓o�^
	-------------------------------------
	����1�FCCamera * pCamera�F�J����
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CUnionManager::SetCamera(CCamera * pCamera)
{
	// =============== ������ ===================
	m_pCamera = pCamera;	//�J����������
}

/* ========================================
	UNION�����֐�
	-------------------------------------
	���e�F�����̃N���X�ɂ��킹��UNION�𐶐�
	-------------------------------------
	����1�Fconst size_t & HashTypeId�F�^�̃n�b�V���R�[�h
	����2�Fconst TPos3d<float> & fPos�F�^�̃n�b�V���R�[�h
	-------------------------------------
	�ߒl�F�Ȃ�
=========================================== */
void CUnionManager::MakeUnion(const size_t & HashTypeId, const TPos3d<float> & fPos)
{
	// =============== ���� ===================
	if (ms_pTexture.find(HashTypeId) == ms_pTexture.end() || MAP_SCALE.find(HashTypeId) == MAP_SCALE.end())
	{
		// =============== �I�� ===================
		return;	//�������f
	}
	
	// =============== �ϐ��錾 ===================
	CUnion* Temp = new CUnion(MAP_FRAME.at(HashTypeId));	//�o�^���������

	// =============== ���o�^ ===================
	Temp->SetTexture(ms_pTexture.at(HashTypeId));	//�e�N�X�`���o�^
	Temp->SetPos(fPos);								//�ʒu�o�^
	Temp->SetSize(MAP_SCALE.at(HashTypeId));		//�傫���o�^
	Temp->SetCamera(m_pCamera);						//�J�����Z�b�^

	// =============== �R���e�i�o�^ ===================
	m_pUnion.push_back(Temp);	//UNION�ǉ�
}
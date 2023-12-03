/* ========================================
	HEW/UniBoooom!!
	---------------------------------------
	��������cpp
	---------------------------------------
	Explosion.cpp

	TeiUon

	�ύX����
	�E2023/11/03 cpp�쐬 Tei
	�E2023/11/05 ����cpp�̏����ݒ� Tei
	�E2023/11/06 �����̃��f���ݒ�A�`��A�ʒu
	�E2023/11/06 bool�̐ݒ�Ǝ擾�֐����� Tei
	�E2023/11/08 �ϐ��A�֐��̕ύX Sawada
	�E2023/11/10 ���̃I�u�W�F�N�g�Ɠ���J�����Ńr���[�ƃv���W�F�N�V�������Z�b�g�ł���悤�ɂ��� Yamashita
	�E2023/11/10 �����̑傫�������X�ɑ傫���Ȃ�悤�ɕύX Sawada
	�E2023/11/11 parameter�p�w�b�_�ǉ� Suzumura
	�E2023/11/13 �X���C�����x���ɂ���Ĕ��j�̖c��݂̑��x�̒������ł���悤�ɕύX Suzumura
	�E2023/11/14 SphereInfo�̕ύX�ɑΉ� Takagi
	�E2023/11/15 Object�N���X���p�������̂ŏC���@yamamoto
	�E2023/11/20 �R���{���z��Y�����̒ǉ� Sawada
	�E2023/11/21 �����l�̐ݒ�ƁA�x�������̒ǉ� Sawada
	�E2023/11/21 �{�X�Ɉ�x�G�������𔻒�p�̊֐����� Suzumura

	�E2023/11/21 DisplayAddTime�̒���BoooomUI�̕\�����ԏ����ǉ� Tei

======================================== */

// =============== �C���N���[�h ===================
#include "Explosion.h"			//���g�̃w�b�_�[
#include "Geometry.h"			//��Ԃɂ�����`��̒��ۃN���X��`�̃w�b�_�[
#include "Sphere.h"				//����`�̃w�b�_�[
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "DirectWrite.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
//const float MAX_DISPLAY_TIME = 3.0f * 60;	// ���������b��
const float EXPAND_QUICK_RATE = 0.2f;   // �c���������� 
const int DELAY_TIME = 0.5f * 60;
#endif
const float EXPLODE_STANDARD_SIZE = 0.15f;
const float EXPLODE_STANDARD_ONE_FRAME = 1.38 * 60.0;

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F�������W(x,y,z)
	����2�F�����T�C�Y(x,y,z)
	����3�F��������
	����4�F�R���{�z��̈ʒu(�Y����)
	����5�F�x���t���O
	-------------------------------------
	�ߒl�F����
=========================================== */
CExplosion::CExplosion(TPos3d<float> fPos, float fSize, float fTime, int comboNum, bool delayFlg, int nDamage, Effekseer::EffectRef explodeEffect, const CCamera* pCamera)
	: m_fSizeAdd(0.0f)
	, m_nDelFrame(0)
	, m_bDelFlg(false)
	, m_fExplodeTime(fTime)	// ���������Ԃ��Z�b�g����
	, m_fMaxSize(fSize)		// �ő�T�C�Y���Z�b�g����
	, m_dComboNum(comboNum)
	, m_bDelayFlg(delayFlg)
	, m_dDelayCnt(0)
	, m_fDamage(0)
	, m_pCamera(nullptr)
	, m_bBossTouched(false)
{
	//�����I�u�W�F�N�g������
	m_Sphere.fRadius = fSize / 2;	// �����蔻����Z�b�g����
	m_3dModel = new CSphere();
	m_Transform.fPos = fPos;		// �X���C���������ꏊ�ɐ�������
	m_fExplodeTime = fTime;		// ���������Ԃ��Z�b�g����
	m_fMaxSize = fSize;			// �ő�T�C�Y���Z�b�g����
	m_fDamage = (float)nDamage;		// �^����_���[�W�ʂ��Z�b�g����
	m_pCamera = pCamera;		//�J�������Z�b�g
	TPos3d<float> cameraPos = m_pCamera->GetPos();
	m_cameraPos = { cameraPos.x, cameraPos.y, cameraPos.z };
	m_explodeEffect = explodeEffect;
	m_efcHnadle = LibEffekseer::GetManager()->Play(m_explodeEffect, fPos.x, fPos.y, fPos.z);
	LibEffekseer::GetManager()->SetScale(m_efcHnadle,EXPLODE_STANDARD_SIZE * fSize, EXPLODE_STANDARD_SIZE * fSize, EXPLODE_STANDARD_SIZE * fSize);
	LibEffekseer::GetManager()->SetSpeed(m_efcHnadle, EXPLODE_STANDARD_ONE_FRAME / fTime);
	LibEffekseer::GetManager()->SetModelRenderer(m_efcHnadle, EXPLODE_STANDARD_ONE_FRAME / fTime);

}

/* ========================================
	�f�X�g���N�^�֐�
	-------------------------------------
	���e�F�f�X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
CExplosion::~CExplosion()
{

	SAFE_DELETE(m_3dModel);	// ���������
}


/* ========================================
	�X�V�֐�
	-------------------------------------
	���e�F�������̍X�V����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CExplosion::Update()
{
	// �����x���������L���ȏꍇ
	if (m_bDelayFlg)
	{
		Delay();	// �x������
		return;
	}

	DisplayTimeAdd();
}



/* ========================================
	�`��֐�
	-------------------------------------
	���e�F�����̕`�揈��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CExplosion::Draw()
{
	m_3dModel->SetWorld(m_Transform.GetWorldMatrixSRT());

	m_3dModel->SetView(m_pCamera->GetViewMatrix());
	m_3dModel->SetProjection(m_pCamera->GetProjectionMatrix());

	//m_3dModel->Draw();	// ������3D���f���̕`��
	m_pCamera->GetInverseViewMatrix();
	m_pCamera->GetProjectionMatrix();
	//�G�t�F�N�g�̕`��
	TPos3d<float> cameraPos = m_pCamera->GetPos();						//�J�������W���擾
	DirectX::XMFLOAT3 fCameraPos(cameraPos.x, cameraPos.y, cameraPos.z);	//XMFLOAT3�ɕϊ�
	LibEffekseer::SetViewPosition(fCameraPos);								//�J�������W���Z�b�g
	LibEffekseer::SetCameraMatrix(m_pCamera->GetViewWithoutTranspose(), m_pCamera->GetProjectionWithoutTranspose());	//�]�u�O��view��projection���Z�b�g

	Effekseer::Vector3D vec = LibEffekseer::GetManager()->GetLocation(m_efcHnadle);
	std::string txt = "X = " + std::to_string(vec.X) + "\nY = " + std::to_string(vec.Y) + "\nZ = " + std::to_string(vec.Z);
	DirectWrite::DrawString(txt, DirectX::XMFLOAT2(0.0f,200.0f));
}


/* ========================================
	�����\���J�E���g���Z�����֐�
	-------------------------------------
	���e�F�����\���J�E���g�����Z���Ĉ��b����������I���t���O���I���ɂ���
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CExplosion::DisplayTimeAdd()
{
	m_nDelFrame++;	// �t���[�����Z

	// ���b���܂ő傫������
	if (m_nDelFrame <= m_fExplodeTime )
	{
		// m_fTime�Ɋ�Â���m_fSizeAdd������
		m_fSizeAdd = m_fMaxSize / m_fExplodeTime / EXPAND_QUICK_RATE;

		// �ő�T�C�Y�ɂȂ�܂�Size�����Z
		if (m_Transform.fScale.y < m_fMaxSize)
		{
			m_Transform.fScale += m_fSizeAdd;
		}

	}
	// ���b�����Ԃ��o������
	if (m_fExplodeTime <= m_nDelFrame)
	{
		m_bDelFlg = true;	// �폜�t���O�𗧂Ă�
	}

	
	m_Sphere.fRadius = m_Transform.fScale.y / 2;	// �����蔻����Z�b�g����
}


/* ========================================
	�{�X�ɂӂꂽ���Ƃ�m�点��֐�
	-------------------------------------
	���e�F�{�X�ƐڐG���t���O��on
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CExplosion::BossTouched()
{
	m_bBossTouched = true;
}

/* ========================================
	���W�ݒ菈���֐�
	-------------------------------------
	���e�F�����̔�����x�点��
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
void CExplosion::Delay()
{
	m_dDelayCnt++;

	// �x���b�����o������
	if (m_dDelayCnt >= DELAY_TIME)
	{
		m_bDelayFlg = false;	// �x���t���O���I�t�ɂ���
	}
}

/* ========================================
	�폜�t���O�擾�����֐�
	-------------------------------------
	���e�F�폜�t���O���擾����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�폜�t���O(bool)
=========================================== */
bool CExplosion::GetDelFlg()
{
	return m_bDelFlg;
}

/* ========================================
	�R���{�z��ԍ��擾�����֐�
	-------------------------------------
	���e�F�R���{�z��ԍ����擾����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�R���{�z��ԍ�(int)
=========================================== */
int CExplosion::GetComboNum()
{
	return m_dComboNum;
}

/* ========================================
	�_���[�W�ʎ擾�����֐�
	-------------------------------------
	���e�F�^����_���[�W���擾����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�_���[�W��(int)
=========================================== */
int CExplosion::GetDamage()
{
	return (int)m_fDamage;
}

/* ========================================
	���ɓ������Ă��邩�擾�����֐�
	-------------------------------------
	���e�F���Ƀ{�X�Ƃ������Ă��邩�ǂ������擾����
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F�ڐG�t���O(bool)
=========================================== */
bool CExplosion::GetBossTouched()
{
	return m_bBossTouched;
}

/* ========================================
	�J�������Z�b�g�֐�
	----------------------------------------
	���e�F�`�揈���Ŏg�p����J�������Z�b�g
	----------------------------------------
	����1�F�Ȃ�
	----------------------------------------
	�ߒl�F�Ȃ�
======================================== */
void CExplosion::SetCamera(const CCamera * pCamera)
{
	m_pCamera = pCamera;
}




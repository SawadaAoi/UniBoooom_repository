/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�Q�[���V�[���pcpp
	------------------------------------
	GameScene.cpp
	------------------------------------
	�쐬�� �V�c����

	�ύX����
	�E2023/11/08 �R�����g�ǉ��A���ʂȉӏ����폜�@�V�c����
	�E2023/11/09 �J�����̗l�X����`�F�b�N�B���C�����玲���D��B�n�ʒǉ��B ���؏x��
	�E2023/11/10 �J�������X���C���Ɣ����ɂ��n���悤�ɂ����Eline�̃��������[�N�΍� ���؏x��
	�E2023/11/17 �U���@�\�Ăяo���f�o�b�O���[�h�ǉ� takagi
	�E2023/11/18 BGM�̍Đ� yamashita
	�E2023/11/18 �������X���C���̓���ɕ\������X�R�A�ǉ��@yamamoto
	�E2023/11/18~20 �t�F�[�h������ ���؏x��
	�E2023/11/21 �t�F�[�h�X�V�Ăяo�� ���؏x��
	�E2023/11/21 �R���{�p�̃����o�ϐ���ǉ� Sawada
	�E2023/11/21 ������BoooomUI�\�����邽�߂̏�����ǉ�
	�E2023/11/23 �g�[�^���X�R�A�\���ǉ��@yamamoto
	�E2023/11/27 �񕜃A�C�e���̒ǉ� Sawada
	�E2023/11/29 UI��1�̃I�u�W�F�N�g�ɂ܂Ƃ߂� Sawada

========================================== */

// =============== �f�o�b�O���[�h ===================
#define USE_CAMERA_VIBRATION (true)
#define MODE_COORD_AXIS (true)			//���W���f�����ǂ���
#define MODE_GROUND (false)				//���W���f�����ǂ���
#if _DEBUG
#define TRY_USE_HIT_STOP (true)
#endif
#define USE_FADE_GAME (true)	//�t�F�[�h����

#if USE_FADE_GAME
#include "Fade.h"
#endif

#if USE_CAMERA_VIBRATION
#include "Input.h"
#endif

#if TRY_USE_HIT_STOP
#include "HitStop.h"
#include "Input.h"
#endif


// =============== �C���N���[�h ===================
#include "SceneGame.h"
#include "Geometry.h"
#include "Model.h"
#include "CameraDebug.h"
#include "CameraChase.h"
#include "Pos3d.h"
#include "Box.h"
#include "Line.h"
#include "Defines.h"
#include "GameParameter.h"


// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const float BGM_VOLUME = 0.02f;
#endif

/* ========================================
	�R���X�g���N�^�֐�
	-------------------------------------
	���e�F�R���X�g���N�^
	-------------------------------------
	����1�F����
	-------------------------------------
	�ߒl�F����
=========================================== */
SceneGame::SceneGame()
{
	// ���_�V�F�[�_�̓Ǎ�
	m_pVs = new VertexShader();
	if (FAILED(m_pVs->Load("Assets/shader/VS_Model.cso"))) {
		MessageBox(nullptr, "VS_Model.cso", "Error", MB_OK);
	}

	// �����_�[�^�[�Q�b�g�A�[�x�o�b�t�@�̐ݒ�
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�

#if MODE_COORD_AXIS
	// �����̕\��
	CLine::Init();
#endif

#if MODE_GROUND
	m_pBox = new CBox();
#endif

	m_pCollision		= new CCOLLISION();
	m_pPlayer			= new CPlayer();
	m_pCamera			= new CCameraChase(m_pPlayer->GetPosAddress());
	m_pFloor			= new CFloor(m_pPlayer->GetPosAddress());	// �n�ʐ���
	m_pHealItemMng		= new CHealItemManager();	// �񕜃A�C�e���}�l�[�W���[
	m_pExplosionMng		= new CExplosionManager();	// �����}�l�[�W���[����
	m_pSlimeMng			= new CSlimeManager();

	m_pUIStageMng		= new CUIStageManager(m_pPlayer, m_pCamera, m_pSlimeMng);	// UI�}�l�[�W���[����


	
	//�I�u�W�F�N�g��UI�̃Z�b�g
	m_pSlimeMng->SetScoreOHMng(m_pUIStageMng->GetScoreMng());
	m_pExplosionMng->SetCombo(m_pUIStageMng->GetCombo());
	m_pSlimeMng->SetExplosionMng(m_pExplosionMng);
	m_pSlimeMng->SetHealMng(m_pHealItemMng);
	// �e�I�u�W�F�N�g�̃J�����[�Z�b�g
	m_pPlayer->SetCamera(m_pCamera);
	m_pSlimeMng->SetCamera(m_pCamera);
	m_pExplosionMng->SetCamera(m_pCamera);
	m_pFloor->SetCamera(m_pCamera);
	m_pHealItemMng->SetCamera(m_pCamera);

#if USE_FADE_GAME
	m_pFade = new CFade(m_pCamera);
#endif

	LoadSound();
	//BGM�̍Đ�
	m_pSpeaker = CSound::PlaySound(m_pBGM);		//BGM�̍Đ�
	m_pSpeaker->SetVolume(BGM_VOLUME);			//���ʂ̐ݒ�


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
SceneGame::~SceneGame()
{
	if (m_pSpeaker)
	{
		m_pSpeaker->Stop();
		m_pSpeaker->DestroyVoice();
	}
	SAFE_DELETE(m_pUIStageMng);
	SAFE_DELETE(m_pHealItemMng);
	SAFE_DELETE(m_pFade);
	SAFE_DELETE(m_pExplosionMng);
	SAFE_DELETE(m_pSlimeMng);	// �X���C���}�l�[�W���[�폜
	SAFE_DELETE(m_pFloor);
	SAFE_DELETE(m_pCamera);
	SAFE_DELETE(m_pPlayer);
	SAFE_DELETE(m_pCollision);

#if MODE_COORD_AXIS
	// �����̕\��
	CLine::Uninit();
#endif
	SAFE_DELETE(m_pVs);

	//SAFE_DELETE(m_pDirectWrite);

}


/* ========================================
   �X�V�����֐�
   -------------------------------------
   ���e�F�X�V����
   -------------------------------------
   ����1�F�e�B�b�N��?(���g�p)
   -------------------------------------
   �ߒl�F����
=========================================== */
void SceneGame::Update(float tick)
{

#if TRY_USE_HIT_STOP
	CHitStop::Update();	//�q�b�g�X�g�b�v�X�V
	//Effect�X�V�A���̑��K�v�Ȃ���
	if (CHitStop::IsStop())	//�X�g�b�v����
	{
		return;	//�������f
	}
#endif
#if USE_CAMERA_VIBRATION
	if (IsKeyTrigger('1'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_WEAK);
	}
	if (IsKeyTrigger('2'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_UP_DOWN_STRONG);
	}
	if (IsKeyTrigger('3'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_SIDE_WEAK);
	}
	if (IsKeyTrigger('4'))
	{
		m_pCamera->UpFlag(CCamera::E_BIT_FLAG_VIBRATION_SIDE_STRONG);
	}
#endif
#if TRY_USE_HIT_STOP
	if (IsKeyTrigger('Z'))
	{
		CHitStop::UpFlag(CHitStop::E_BIT_FLAG_STOP_SOFT);	//�t���O�I��
	}
#endif
	m_pCamera->Update();
	m_pPlayer->Update();
	m_pSlimeMng->SetPlayerPos(m_pPlayer->GetPos());

	SceneGameCollision();
	// �X���C���}�l�[�W���[�X�V
	m_pFloor->Update();
	m_pSlimeMng->Update(m_pExplosionMng);
	m_pExplosionMng->Update();
	m_pHealItemMng->Update();
	// UI�}�l�[�W���[�X�V
	m_pUIStageMng->Update();

#if USE_FADE_GAME
	m_pFade->Update();
#endif
}

/* ========================================
   �`�揈���֐�
   -------------------------------------
   ���e�F�`�揈��
   -------------------------------------
   ����1�F����
   -------------------------------------
   �ߒl�F����
=========================================== */
void SceneGame::Draw()
{
#if MODE_COORD_AXIS
	// �����̕\��
	CLine::SetView(m_pCamera->GetViewMatrix());
	CLine::SetProjection(m_pCamera->GetProjectionMatrix());
	// �O���b�h
	DirectX::XMFLOAT4 lineColor(0.5f, 0.5f, 0.5f, 1.0f);
	float size = DEBUG_GRID_NUM * DEBUG_GRID_MARGIN;
	for (int i = 1; i <= DEBUG_GRID_NUM; ++i)
	{
		float grid = i * DEBUG_GRID_MARGIN;
		DirectX::XMFLOAT3 pos[2] = {
			DirectX::XMFLOAT3(grid, 0.0f, size),
			DirectX::XMFLOAT3(grid, 0.0f,-size),
		};
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = pos[1].x = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].x = size;
		pos[1].x = -size;
		pos[0].z = pos[1].z = grid;
		CLine::Add(pos[0], pos[1], lineColor);
		pos[0].z = pos[1].z = -grid;
		CLine::Add(pos[0], pos[1], lineColor);
	}
	// ��
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(size, 0, 0), DirectX::XMFLOAT4(1, 0, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, size, 0), DirectX::XMFLOAT4(0, 1, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, size), DirectX::XMFLOAT4(0, 0, 1, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(-size, 0, 0), DirectX::XMFLOAT4(0, 0, 0, 1));
	CLine::Add(DirectX::XMFLOAT3(0, 0, 0), DirectX::XMFLOAT3(0, 0, -size), DirectX::XMFLOAT4(0, 0, 0, 1));

	CLine::Draw();
#endif

#if MODE_GROUND
	DirectX::XMFLOAT4X4 mat[3];

	//Geometory�p�̕ϊ��s���ݒ�
	DirectX::XMMATRIX T = DirectX::XMMatrixTranslation(0.0f, -0.5f * 0.1f, 0.0f);	//�O���b�h�������ɗ���悤�Ɉړ�
	DirectX::XMMATRIX S = DirectX::XMMatrixScaling(100.0f, 0.1f, 100.0f);		//�n�ʂƂȂ�悤�ɁA�O�㍶�E�ɍL���㉺�ɋ���
	DirectX::XMMATRIX world = S * T;											//�S�Ă̍s�����ɂ܂Ƃ߂�
	world = DirectX::XMMatrixTranspose(world);
	DirectX::XMStoreFloat4x4(&mat[0], world);	//mat��fMat�Ɋi�[
	m_pBox->SetWorld(mat[0]);	//�{�b�N�X�ɕϊ��s���ݒ�

	//Geometory�p�̕ϊ��s���ݒ�
	mat[1] = m_pCamera->GetViewMatrix();
	mat[2] = m_pCamera->GetProjectionMatrix();

	m_pBox->SetView(mat[1]);		//�{�b�N�X�ɕϊ��s���ݒ�
	m_pBox->SetProjection(mat[2]);	//�{�b�N�X�ɕϊ��s���ݒ�

	//// �s����V�F�[�_�[�� 
	//m_pVs->WriteBuffer(0, mat);

	m_pBox->Draw();
#endif
	
	RenderTarget* pRTV = GetDefaultRTV();	//�f�t�H���g�Ŏg�p���Ă���RenderTargetView�̎擾
	DepthStencil* pDSV = GetDefaultDSV();	//�f�t�H���g�Ŏg�p���Ă���DepthStencilView�̎擾
	SetRenderTargets(1, &pRTV, pDSV);		//DSV��null����2D�\���ɂȂ�
	//���̕`��
	m_pFloor->Draw();
	m_pHealItemMng->Draw();
	// �X���C���}�l�[�W���[�`��
	m_pSlimeMng->Draw();
	m_pPlayer->Draw();
	
	//�����}�l�[�W���[�`��
	m_pExplosionMng->Draw();
	


	//UI�̕`��
	SetRenderTargets(1, &pRTV, nullptr);
	m_pUIStageMng->Draw();



#if USE_FADE_GAME
	m_pFade->Draw();
#endif
}

/* ========================================
   �T�E���h�t�@�C���ǂݍ��݊֐�
   -------------------------------------
   ���e�F�T�E���h�t�@�C���̓ǂݍ���
   -------------------------------------
   ����1�F����
   -------------------------------------
   �ߒl�F����
=========================================== */
void SceneGame::LoadSound()
{
	m_pBGM = CSound::LoadSound("Assets/Sound/BGM/BGM_maou.mp3", true);		//BGM�̓ǂݍ���
	m_pSEHitHammer = CSound::LoadSound("Assets/Sound/SE/Smash.mp3");		//SE�̓ǂݍ���
}
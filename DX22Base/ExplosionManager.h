/* ========================================
   HEW/UniBoooom!!
   ---------------------------------------
   �����Ǘ��w�b�_�[
   ---------------------------------------
   ExplosionManager.h

   �쐬�� �A �F��

   �ύX����
	�E2023/11/06 �����}�l�[�W���[�N���X�쐬 tei
	�E2023/11/09 �����z���Ԃ������̒ǉ� sawada
	�E2023/11/10 ���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g����悤�ɂ��� yamashita
	�E2023/11/13 Create�֐��̈�����time��ǉ� Suzumura
	�E2023/11/18 �T�E���h�p�̃����o�ϐ���ǉ� yamashita
	�E2023/11/20 �R���{���@�\�ǉ� Sawada
	�E2023/11/21 �R���{���@�\�̈ꕔ���R���{�N���X�Ɉړ� Sawada

========================================== */
#ifndef __EXPLOSION_MANAGER_H__	//ExplosionManager.h�C���N���[�h�K�[�h
#define __EXPLOSION_MANAGER_H__

// =============== �C���N���[�h ===================
#include "Explosion.h"			//���������w�b�_�[
#include "GameParameter.h"		//�萔��`�p�w�b�_�[
#include "SlimeBase.h"
#include "Sound.h"
#include "Combo.h"

// =============== �萔��` =======================
#if MODE_GAME_PARAMETER
#else
const int MAX_EXPLOSION_NUM = 20;	//�ő唚����
const float EXPLODE_BASE_RATIO = 1.5f;			// �X���C���̔����ڐG�ł̔����̑傫���̃x�[�X
const float MAX_SIZE_EXPLODE = 5.0f;			// �X���C��4���m�̔����̑傫��
const float LEVEL_1_EXPLODE_TIME = 0.5f * 60.0f;	// �X���C��_1�̔���������
const float LEVEL_2_EXPLODE_TIME = 1.0f * 60.0f;	// �X���C��_2�̔���������
const float LEVEL_3_EXPLODE_TIME = 2.0f * 60.0f;	// �X���C��_3�̔���������
const float LEVEL_4_EXPLODE_TIME = 3.0f * 60.0f;	// �X���C��_4�̔���������

#endif
// =============== �N���X��` =====================
class CExplosionManager
{
public:
	// ===�����o�֐��錾===
	CExplosionManager();		//�R���X�g���N�^
	~CExplosionManager();		//�f�X�g���N�^

	void Update();		 		//�X�V�֐�
	void Draw();		 		//�`��֐�
	
	void Create(TTriType<float> pos,float size, float time);   	//���������֐�
	void Create(TTriType<float> pos,float size, float time, int comboNum);   	//���������֐�
	void DeleteCheck();							   				// ���Ԃ�蔚�����폜�֐�
	void ComboEndCheck();										// �����̘A�����r�؂ꂽ���`�F�b�N����
	void SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize);					//�X���C���̃��x���ɉ����Ĕ�����ύX
	void SwitchExplode(E_SLIME_LEVEL slimeLevel, TPos3d<float> pos, TTriType<float> slimeSize, int comboNum);					//�X���C���̃��x���ɉ����Ĕ�����ύX



	CExplosion* GetExplosionPtr(int num);
	
	void SetCamera(const CCamera* pCamera);	//���̃I�u�W�F�N�g�Ɠ���̃J�������Z�b�g
	void SetCombo(CCombo* pCombo);


private:
	// ===�����o�ϐ��錾===
	CExplosion* m_pExplosion[MAX_EXPLOSION_NUM];	// �����̔z��
	CCombo* m_pCombo;								// �R���{�����p
	const CCamera* m_pCamera;
	XAUDIO2_BUFFER* m_pSEExplode;
	IXAudio2SourceVoice* m_pSEExplodeSpeaker;


};

#endif // __EXPLOSION_MANAGER_H__
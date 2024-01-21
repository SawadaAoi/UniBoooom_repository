/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��1��`
	------------------------------------
	Slime_Boss_1.h
	------------------------------------
	�쐬��	suzumura

	�ύX����
	�E2023/11/17 �N���X�쐬 suzumura
	�E2023/11/23 �ˌ������̒ǉ� suzumura
	�E2024/01/20 ���t�@�N�^�����O takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SLIME_BOSS_1_H__	//Slime_Boss_1.h�C���N���[�h�K�[�h
#define __SLIME_BOSS_1_H__

// =============== �C���N���[�h ===================
#include "Slime_BossBase.h"

// =============== �񋓒�` ===================
enum E_BOSS_1_STATE
{
	NORMAL = 0,
	CHARGE,
	ASSAULT
};

// =============== �N���X��` =====================
class CSlime_Boss_1 :
	public CSlime_BossBase
{
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Boss_1();
	CSlime_Boss_1(TPos3d<float> pos, VertexShader* pVS, Model* pModel);
	~CSlime_Boss_1();

	void Update() override;

	void NormalMove() override;
	void SetNormalSpeed() override;
	void SetMaxHp() override;

	void Charge(TPos3d<float> playerPos, TPos3d<float> movePos);	// ���ߊ֐�
	void Assault();	// �ˌ��֐�

private:
	void ResetAssault();
	// ===�����o�ϐ�===
	int m_nFrame;		// Update���ň����t���[��


	float m_assaultDistancePlayer;	// �ˌ����̃v���C���[�Ԃ̋�����ۑ�
	TPos3d<float> m_assaultMovePos;	// �ˌ�����MovePos��ۑ�
};


#endif	//!__SLIME_BOSS_1_H__
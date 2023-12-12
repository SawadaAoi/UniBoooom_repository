/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�{�X�X���C��2.h
	------------------------------------
	Slime_Boss_2.h
	------------------------------------
	�쐬��	�V�c����

	�ύX����
	�E2023/12/11 �N���X�쐬 Sawada

========================================== */
#ifndef __SLIME_BOSS_2__H__
#define __SLIME_BOSS_2__H__

// =============== �C���N���[�h ===================
#include "Slime_BossBase.h"



// =============== �N���X��` =====================
class CSlime_Boss_2 :
	public CSlime_BossBase
{
public:
	// =============== �񋓒�` ===================
	enum MOVE_STATE
	{
		MOVE_NORMAL = 0,
		MOVE_JUMP,
		MOVE_TARGET_SHADOW,
		MOVE_DROP,

		MOVE_MAX,
	};
public:
	// ===�v���g�^�C�v�錾===
	CSlime_Boss_2();
	CSlime_Boss_2(TPos3d<float> pos, VertexShader* pVS, Model* pModel1, Model* pModel2);
	~CSlime_Boss_2();

	void Update(tagTransform3d playerTransform) override;
	void NormalMove(tagTransform3d playerTransform) override;

	void MoveJump();
	void MoveTargetShadow();
	void MoveDrop();

	void SetNormalSpeed() override;
	void SetMaxHp() override;


private:
	// ===�����o�ϐ�===
	int m_nMoveCnt[MOVE_MAX];		// �ړ������̃t���[�����Z�l



	float m_assaultDistancePlayer;	// �ˌ����̃v���C���[�Ԃ̋�����ۑ�
	TPos3d<float> m_assaultMovePos;	// �ˌ�����MovePos��ۑ�
	Model* m_StateModels[2];
};


#endif //__SLIME_BOSS_2__H__

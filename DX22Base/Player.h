/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	player�p�w�b�_
	------------------------------------
	player.h
	------------------------------------
	�쐬��
		�R�{�M��
	�ύX����
	�E2023/11/03 h,�쐬 �R�{�M��
	�E2023/11/06 �_���[�W�����ǉ�,�R�����g�ǉ� �R�{�M��
	�E2023/11/08 Pos.h���C���N���[�h /�R�����C
	�E2023/11/08 �����蔻��p�̋���m_sphere��ǉ� /�R�����C
	�E2023/11/08 �v���C���[���W������ϐ���TTriType����TPos�ɕύX /�R�����C
	�E2023/11/09 GetPosAddress�ǉ��A�J�����ǉ� ���؏x��
	�E2023/11/09 �v���C���[�̖��G���Ԃ��J�E���g�̕ϐ��Ɩ��G��Ԃ̃t���O��ǉ� �R�����C
	�E2023/11/09 �v���C���[�̖��G��Ԃ��擾����Q�b�g�֐���ǉ� �R�����C
	
========================================== */

#ifndef __PLAYER_H__
#define __PLAYER_H_

// =============== �C���N���[�h ===================
#include "Shader.h"
#include "hammer.h"
#include "Geometry.h"
#include "SphereInfo.h"
#include "Pos3d.h"
#include "Camera.h"
// =============== �N���X��` =====================
class CPlayer
{
public:
	// ===�v���g�^�C�v�錾===
	CPlayer();		//�R���X�g���N�^
	~CPlayer();		//�f�X�g���N�^

	void Update();	//�X�V
	void Draw();	//�`��
	void Damage();	//���g��HP�����炷
	void Move();	//�ړ��֐�
	void ControllerMove();	// �R���g���[���p����


	// �Q�b�g�֐�
	CSphereInfo::Sphere GetPlayerSphere();	//�����蔻�����邽�߃Q�b�^�[
	CSphereInfo::Sphere GetHammerSphere();	//�����蔻�����邽�߃Q�b�^�[
	TPos3d<float> GetPos();	//�v���C���[�̍��W���擾
	TPos3d<float>* GetPosAddress() { return &m_pos; }
	CHammer* GetHammer() { return m_pHammer; }
	bool GetCollide();							//�����蔻�肪���邩�̊m�F
	// �Z�b�g�֐�
	void SetCamera(const CCamera* pCamera);
	bool GetHammerFlg();

private:
	// ===�����o�ϐ��錾=====
	DirectX::XMMATRIX m_T;				//�ʒu
	DirectX::XMMATRIX m_S;				//�g�k
	DirectX::XMMATRIX m_Ry;				//��]
	//TTriType<float> m_playerPosition;	//�v���C���[�̈ʒu
	TPos3d<float> m_pos;					//�v���C���[�̍��W
	CSphereInfo::Sphere m_sphere;		//�v���C���[�̓����蔻��p�̋���
	TTriType<float> m_playerForward;	// �v���C���[�̏����i�s����
	float m_playerRotation;				// �v���C���[�̉�]�p�x
	int m_nHp;							//�v���C���[�̗̑�
	bool m_bHammer;						//�U�������ǂ����̃t���O
	int m_nNoDamageCnt;					//�v���C���[�̖��G���Ԃ��J�E���g
	bool m_bCollide;					//�v���C���[�̖��G��Ԃ̃t���O(�����蔻���OFF)
	CHammer* m_pHammer;					//�n���}�[�N���X�̃|�C���^(�v���C���[���Ǘ�����)
	CGeometry* m_pPlayerGeo;			//�v���C���[�����\������W�I���g���[
	const CCamera* m_pCamera;			//�v���C���[��Ǐ]����J����
	CGeometry* m_pGameOver;				//�Q�[���I�[�o�[�����\������W�I���g���[

};


#endif // !__PLAYER_H__




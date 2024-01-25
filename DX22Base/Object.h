/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�I�u�W�F�N�g��`
	------------------------------------
	Object.h
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2024/01/18 �쐬 takagi
	�E2024/01/21 �R�����g���C�E���t�@�N�^�����O�E�ĉ���� takagi
	�E2024/01/22 Draw()�֐�const���E���Ή� takagi

========================================== */

#ifndef __OBJECT_H__	//Object.h�C���N���[�h�K�[�h
#define __OBJECT_H__

// =============== �C���N���[�h ===================
#include "Transform3d.h"	//�����o�̃w�b�_
#include "Camera.h"			//�����o�̃w�b�_
#include "Shader.h"			//�V�F�[�_�[�g�p
#include "Sound.h"			//���Đ�

// =============== �N���X��` =====================
class CObject
{
private:
	// ===�萔��`===========
	const TPos3d<float> INIT_POS = { 0.0f, 0.0f, 0.0f };		//�����ʒu
	const TTriType<float> INIT_SCALE = { 1.0f, 1.0f, 1.0f };	//�����g�k
	const TTriType<float> INIT_RADIAN = 0.0f;					//������]
public:
	// ===�v���g�^�C�v�錾===
	CObject();															//�R���X�g���N�^
	CObject(const CObject& Obj);										//�R�s�[�R���X�g���N�^
	virtual ~CObject();													//�f�X�g���N�^
	virtual void Update() = 0;											//�X�V
	virtual void Draw() const = 0;										//�`��
	virtual TPos3d<float> GetPos() const final;							//�ʒu�Q�b�^
	virtual const float& GetPosZ() const final;							//Z���W�Q�b�^
	virtual void SetPos(const TPos3d<float>& fPos) final;				//�ʒu�Z�b�^
	virtual void SetSize(const TTriType<float>& fScale) final;			//�傫���Z�b�^
	virtual void SetRotate(const TTriType<float>& fRotate) final;		//��]�Z�b�^
	virtual void SetTransform(const tagTransform3d& Transform) final;	//���[���h���W�Z�b�^
	virtual void SetCamera(const CCamera* pCamera);						//�J�����Z�b�^
	virtual void PlaySe(const std::map<int, XAUDIO2_BUFFER*>& pSe,
		const int& nKey, const float& fVolume = 1.0f);					//SE�����o�^
	virtual void SetVertexShader(VertexShader* pVs) = 0;				//���_�V�F�[�_�Z�b�^
	virtual void SetPixelShader(PixelShader* pPs) = 0;					//�s�N�Z���V�F�[�_�Z�b�^
	//void* operator new(size_t _Size);									//"new"���Z�q�I�[�o�[���[�h
	//void operator delete(void* pPointer);								//"delete"���Z�q�I�[�o�[���[�h
protected:
	// ===�����o�ϐ��錾=====
	tagTransform3d m_Transform;	//���[���h���W
	std::map<int, IXAudio2SourceVoice*> m_pListener;	//���Đ���(�e�V�[���Œ�`����SE�̗񋓂��L�[�Ƃ���)
	const CCamera* m_pCamera;							//�J�����ǐ�
	static const CCamera* ms_pCameraDef;				//�^���J����
private:
	static int ms_nCntObject;	//���g�̐�����
	unsigned int m_unMyNum;		//�I�u�W�F�N�g�ԍ�(ObjectDrawer�p)
};	//�I�u�W�F�N�g

#endif	//!__OBJECT_H__
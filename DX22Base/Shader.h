/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�V�F�[�_�[��`
	------------------------------------
	Shader.h
	------------------------------------
	�쐬�ҁ@���X�ؐ搶

	�ύX����
	�E2024/01/21 �R�����g���C takagi
	�E2024/01/23 WriteBuffer��void*����const�� takagi

========================================== */

#ifndef __SHADER_H__	//Shader.h�C���N���[�h�K�[�h
#define __SHADER_H__

#include "DirectX.h"
#include "Texture.h"
#include <string>
#include <map>
#include <vector>

// �V�F�[�_�[�̊�{�N���X
class Shader
{
protected:
	enum Kind
	{
		Vertex,
		Pixel
	};
protected:
	Shader(Kind kind);
public:
	virtual ~Shader();
public:
	// �V�F�[�_�[�t�@�C��(*.cso)��ǂݍ��ޏ���
	HRESULT Load(const char* pFileName);
	// �����񂩂�V�F�[�_���R���p�C��
	HRESULT Compile(const char* pCode);


	// �萔�̏�������
	void WriteBuffer(UINT slot, const void* pData);
	// �e�N�X�`���̐ݒ�
	void SetTexture(UINT slot, Texture* tex);
	void SetSampler(UINT slot, D3D11_SAMPLER_DESC* pSampDsc);
	// �V�F�[�_�[��`��Ɏg�p
	virtual void Bind(void) = 0;

private:
	HRESULT Make(void* pData, UINT size);
protected:
	// �V�F�[�_�[�t�@�C����ǂݍ��񂾌�A�V�F�[�_�[�̎�ޕʂɏ������s��
	virtual HRESULT MakeShader(void* pData, UINT size) = 0;

private:
	Kind m_kind;
protected:
	std::vector<ID3D11Buffer*> m_pBuffers;
	std::vector<ID3D11ShaderResourceView*> m_pTextures;
	std::vector<ID3D11SamplerState*> m_pSampler;
};

//----------
// ���_�V�F�[�_
class VertexShader : public Shader
{
public:
	VertexShader();
	~VertexShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);

private:
	ID3D11VertexShader* m_pVS;
	ID3D11InputLayout* m_pInputLayout;
};
//----------
// �s�N�Z���V�F�[�_
class PixelShader : public Shader
{
public:
	PixelShader();
	~PixelShader();
	void Bind(void);
protected:
	HRESULT MakeShader(void* pData, UINT size);
private:
	ID3D11PixelShader* m_pPS;
};

#endif	//!__SHADER_H__
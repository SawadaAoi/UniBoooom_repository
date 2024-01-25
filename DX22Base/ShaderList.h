/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�����V�F�[�_�[��`
	------------------------------------
	ShaderList.h
	------------------------------------
	�쐬�ҁ@���X�ؐ搶

	�ύX����
	�E2024/01/20 �R�����g���C takagi
	�E2024/01/21 �R�����g���C takagi

========================================== */

#ifndef __SHADER_LIST_H__	//ShaderList.h�C���N���[�h�K�[�h
#define __SHADER_LIST_H__

#include "Shader.h"
#include "AnimeModel.h"


class ShaderList
{
	// ��`
public:
	enum VSKind
	{
		VS_WORLD,
		VS_ANIME,
		VS_KIND_MAX
	};
	enum PSKind
	{
		PS_LAMBERT,
		PS_SPECULAR,
		PS_TOON,
		PS_FOG,
		PS_KIND_MAX
	};


public:
	ShaderList();
	~ShaderList();

	static void Init();
	static void Uninit();

	// �V�F�[�_�[�擾
	static VertexShader* GetVS(VSKind vs);
	static PixelShader* GetPS(PSKind ps);

	// �萔�o�b�t�@�ւ̐ݒ�
	static void SetWVP(const DirectX::XMFLOAT4X4* wvp);
	static void SetBones(DirectX::XMFLOAT4X4* bones200);
	static void SetMaterial(const AnimeModel::Material& material);
	static void SetLight(DirectX::XMFLOAT4 color, DirectX::XMFLOAT3 dir);
	static void SetCameraPos(const DirectX::XMFLOAT3 pos);
	static void SetFog(DirectX::XMFLOAT4 color, float start, float range);
	
private:
	static void MakeWorldVS();
	static void MakeAnimeVS();
	static void MakeLambertPS();
	static void MakeSpecularPS();
	static void MakeToonPS();
	static void MakeFogPS();

private:
	static VertexShader* m_pVS[VS_KIND_MAX];
	static PixelShader* m_pPS[PS_KIND_MAX];
	
};

#endif	//!__SHADER_LIST_H__
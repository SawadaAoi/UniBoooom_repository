#include "CameraBase.h"


CameraBase::CameraBase()
	: m_pos(0.0f,0.0f,-3.0f)
	, m_look(0.0f, 0.0f, 0.0f)
	, m_up(0.0f, 1.0f, 0.0f)
	, m_fovy(DirectX::XMConvertToRadians(60.0f))
	, m_aspect(16.0f/9.0f)
	, m_near(0.3f)
	,m_far(100.0f)
{

}

CameraBase::~CameraBase()
{
}


DirectX::XMFLOAT4X4 CameraBase::GetViewMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX view;
	view = DirectX::XMMatrixLookAtLH(
		DirectX::XMVectorSet(m_pos.x, m_pos.y, m_pos.z, 0.0f),		 // カメラの位置
		DirectX::XMVectorSet(m_look.x, m_look.y, m_look.z, 0.0f),	 // カメラが注目している位置
		DirectX::XMVectorSet(m_up.x, m_up.y, m_up.z, 0.0f));		 // カメラの上方向
	DirectX::XMStoreFloat4x4(&mat, view);
	return mat;
}

DirectX::XMFLOAT4X4 CameraBase::GetProjectionMatrix()
{
	DirectX::XMFLOAT4X4 mat;
	DirectX::XMMATRIX proj;
	proj= DirectX::XMMatrixPerspectiveFovLH(
		m_fovy,	// 縦方向の画角
		m_aspect,						// アスペクト比
		m_near,								// 画面に写り始める距離
		m_far);
	DirectX::XMStoreFloat4x4(&mat, proj);
	return mat;
}
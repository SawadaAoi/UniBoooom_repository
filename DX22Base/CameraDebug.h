#pragma once
#include "Input.h"
#include "CameraBase.h"

class CameraDebug :
	public CameraBase
{
public:
	CameraDebug();
	~CameraDebug();
	void Update();

};
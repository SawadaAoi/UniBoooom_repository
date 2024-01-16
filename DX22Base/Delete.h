/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	�폜�}�N������
	------------------------------------
	Delete.cpp
	------------------------------------
	�쐬��	takagi

	�ύX����
	�E2023/12/27 DirectX.h����}�N����`�ړ�
	�E2024/01/11 �C�e���[�^�폜�ǉ�

========================================== */

#ifndef __DELETE_H__	//Delete.h�C���N���[�h�K�[�h
#define __DELETE_H__

// =============== �萔�E�}�N����` ===================
#if !defined SAFE_DELETE	//��`�ς̂Ƃ���`���Ȃ�
#define SAFE_DELETE(p) do{if(p){delete p; p = nullptr;}}while(0)												//�|�C���^�P�̍폜
#endif	//!SAFE_DELETE
#if !defined SAFE_DELETE_ARRAY	//��`�ς̂Ƃ���`���Ȃ�
#define SAFE_DELETE_ARRAY(p) do{if(p){delete[] p; p = nullptr;}}while(0)										//�|�C���^�z��폜
#endif	//!SAFE_DELETE_ARRAY
#if !defined SAFE_RELEASE	//��`�ς̂Ƃ���`���Ȃ�
#define SAFE_RELEASE(p) do{if(p){p->Release(); p = nullptr;}}while(0)											//Release()�֐��Ăяo��
#endif	//!SAFE_RELEASE
#if !defined SAFE_DELETE_CONTAINER	//��`�ς̂Ƃ���`���Ȃ�
#define SAFE_DELETE_CONTAINER(container) do{for(auto iterator = container.end(); iterator != container.begin();) \
	{--iterator; iterator = container.erase(iterator);}}while(0)												//��|�C���^�R���e�i�폜
#endif	//!SAFE_DELETE_CONTAINER
#if !defined SAFE_DELETE_POINTER_VECTOR	//��`�ς̂Ƃ���`���Ȃ�
#define SAFE_DELETE_POINTER_VECTOR(vector) do{for(auto iterator = vector.end(); iterator != vector.begin();) \
	{if(*(--iterator)){delete (*iterator); (*iterator) = nullptr;}iterator = vector.erase(iterator);}}while(0)	//�|�C���^�z��R���e�i�폜
#endif	//!SAFE_DELETE_POINTER_VECTOR
#if !defined SAFE_DELETE_POINTER_MAP	//��`�ς̂Ƃ���`���Ȃ�
#define SAFE_DELETE_POINTER_MAP(map) do{for(auto iterator = map.end(); iterator != map.begin();) \
	{if((--iterator)->second){delete (iterator->second); (iterator->second) = nullptr;}iterator = map.erase(iterator);} \
	}while(0)																									//�|�C���^�A�z�R���e�i�폜
#endif	//!SAFE_DELETE_POINTER_MAP

#endif	//!__DELETE_H__
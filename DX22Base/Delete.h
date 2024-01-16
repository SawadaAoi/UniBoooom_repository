/* ========================================
	HEW/UniBoooom!!
	------------------------------------
	削除マクロ実装
	------------------------------------
	Delete.cpp
	------------------------------------
	作成者	takagi

	変更履歴
	・2023/12/27 DirectX.hからマクロ定義移動
	・2024/01/11 イテレータ削除追加

========================================== */

#ifndef __DELETE_H__	//Delete.hインクルードガード
#define __DELETE_H__

// =============== 定数・マクロ定義 ===================
#if !defined SAFE_DELETE	//定義済のとき定義しない
#define SAFE_DELETE(p) do{if(p){delete p; p = nullptr;}}while(0)												//ポインタ単体削除
#endif	//!SAFE_DELETE
#if !defined SAFE_DELETE_ARRAY	//定義済のとき定義しない
#define SAFE_DELETE_ARRAY(p) do{if(p){delete[] p; p = nullptr;}}while(0)										//ポインタ配列削除
#endif	//!SAFE_DELETE_ARRAY
#if !defined SAFE_RELEASE	//定義済のとき定義しない
#define SAFE_RELEASE(p) do{if(p){p->Release(); p = nullptr;}}while(0)											//Release()関数呼び出し
#endif	//!SAFE_RELEASE
#if !defined SAFE_DELETE_CONTAINER	//定義済のとき定義しない
#define SAFE_DELETE_CONTAINER(container) do{for(auto iterator = container.end(); iterator != container.begin();) \
	{--iterator; iterator = container.erase(iterator);}}while(0)												//非ポインタコンテナ削除
#endif	//!SAFE_DELETE_CONTAINER
#if !defined SAFE_DELETE_POINTER_VECTOR	//定義済のとき定義しない
#define SAFE_DELETE_POINTER_VECTOR(vector) do{for(auto iterator = vector.end(); iterator != vector.begin();) \
	{if(*(--iterator)){delete (*iterator); (*iterator) = nullptr;}iterator = vector.erase(iterator);}}while(0)	//ポインタ配列コンテナ削除
#endif	//!SAFE_DELETE_POINTER_VECTOR
#if !defined SAFE_DELETE_POINTER_MAP	//定義済のとき定義しない
#define SAFE_DELETE_POINTER_MAP(map) do{for(auto iterator = map.end(); iterator != map.begin();) \
	{if((--iterator)->second){delete (iterator->second); (iterator->second) = nullptr;}iterator = map.erase(iterator);} \
	}while(0)																									//ポインタ連想コンテナ削除
#endif	//!SAFE_DELETE_POINTER_MAP

#endif	//!__DELETE_H__
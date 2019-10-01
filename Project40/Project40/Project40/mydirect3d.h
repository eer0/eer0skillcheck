/*======================================================================================================
		windowsの表示  [mydirect3d.h]
																					Author:コ　笠
																					Date:2019/6/5
--------------------------------------------------------------------------------------------------------

======================================================================================================*/


#ifndef _MYDIRECT3D_H_	// ２重インクルード防止のマクロ定義
#define _MYDIRECT3D_H_

#include <windows.h>
#include <d3d9.h>


bool MyDirect3D_Init(HWND hWnd);
void MyDirect3D_Uninit(void);
//void MyDirect3D_Update(void);
//void MyDirect3D_Draw(void);
LPDIRECT3DDEVICE9 GetDevice(void);

#endif


#ifndef _DEBUG_H_	// ２重インクルード防止のマクロ定義
#define _DEBUG_H_

#include <d3d9.h>
#include <d3dx9.h>

void Debug_Init(void);
void Debug_Uninit(void);
void Debug_Begin(void);
void Debug_End(void);
void Debug_DrawCircle(float x,float y,float radius);
void Debug_SetColor(D3DCOLOR color);






#endif//_DEBUG_H

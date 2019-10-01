#ifndef _SPRITE_H_	// ２重インクルード防止のマクロ定義
#define _SPRITE_H_
#include <d3d9.h>
#include <d3dx9.h>

void Sprite_Draw(int textureId, float dx, float dy);
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h);
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h,float angle);
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z );
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z, bool isright);
void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, int g_FadeAlpha);
void Sprite_Draw(int textureId, float dx, float dy, D3DCOLOR color);



void Sprite_Init(void);
void Sprite_UnInit(void);
//void Sprite_SetColor(D3DCOLOR color);










#endif
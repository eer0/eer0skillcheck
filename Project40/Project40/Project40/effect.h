#ifndef _effect_H_	// ２重インクルード防止のマクロ定義
#define _effect_H_

#define effect_MAX (10000)

#include <d3d9.h>
#include <d3dx9.h>

typedef struct effect_tag
{
	D3DXVECTOR2 position;
	int lifeFrame;
	int spawnFrame;
	D3DCOLOR color;

}effect;

void effect_Init();

void effect_Update();

void effect_Draw();

void effect_UnInit();

void effect_Create(float x, float y,D3DCOLOR color, int lifeFrame);

#endif//_effect_H_

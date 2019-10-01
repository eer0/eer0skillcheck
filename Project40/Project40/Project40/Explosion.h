#ifndef _EXPLOSION_H_	// ２重インクルード防止のマクロ定義
#define _EXPLOSION_H_

#define EXPLOSION_MAX (100)

#include <d3d9.h>
#include <d3dx9.h>

typedef struct Explosion_tag
{
	D3DXVECTOR2 position;
	int Animationcount;
	bool bUse;

}Explosion;

void Explosion_Init();

void Explosion_Update();

void Explosion_Draw();

void Explosion_UnInit();

void Explosion_Create(float x, float y);

#endif//_EXPLOSION_H_
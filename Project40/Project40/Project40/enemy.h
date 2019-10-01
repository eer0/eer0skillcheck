#ifndef _ENEMY_H_	// ２重インクルード防止のマクロ定義
#define _ENEMY_H_

#define ENEMY_MAX (1000)

#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"

typedef struct Enemy_tag
{
	//種類　速度ベクトル
	D3DXVECTOR2 position;
	Circle collision;
	bool used;
}Enemy;

void Enemy_Init();

void Enemy_Update();

void Enemy_Draw();

void Enemy_UnInit();

void Enemy_Create(float x, float y);

bool Enemy_IsUsed(int index);

void Enemy_Destroy(int index);

Circle* Enemy_GetCollision(int index);

Enemy* GetEnemyPosition(void);

#endif//_ENEMY_H_

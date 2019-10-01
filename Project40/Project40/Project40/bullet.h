#ifndef _BULLET_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _BULLET_H_

#define BULLET_MAX (1024)

#include <d3d9.h>
#include <d3dx9.h>
#include "collision.h"

typedef struct Bullet_tag
{
	//��ށ@���x�x�N�g��
	D3DXVECTOR2 position;
	Circle collision;
	bool used;
}Bullet;

void Bullet_Init();

void Bullet_Update();

void Bullet_Draw();

void Bullet_UnInit();

void Bullet_Create(float x,float y);

bool Bullet_IsUsed(int index);

void Bullet_Destroy(int index);

Circle* Bullet_GetCollision(int index);


#endif//__BULLET_H_


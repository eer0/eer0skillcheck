#ifndef _COLLISION_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _COLLISION_H_

#include <d3d9.h>
#include <d3dx9.h>

typedef struct Circle_tag
{
	D3DXVECTOR2 position;
	float radius;
}Circle;


bool Circle_Circle(Circle*pA,Circle*pB);

#endif//_COLLISION_H_


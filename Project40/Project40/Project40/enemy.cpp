#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "mydirect3d.h"
#include "enemy.h"
#include "collision.h"
#include "Debug.h"

#define ENEMY_MAX (1000)
//�O���[�o���ϐ�
static int tex_Enemy;
static Enemy g_Enemy[ENEMY_MAX] = {};
static float speed = 7.0f;




void Enemy_Init()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		g_Enemy[i].used = false;
		g_Enemy[i].collision.radius = 40;
	}
	tex_Enemy = Texture_SetLoadFile("Accet\\texture\\teki.png", 197, 134);
}



void Enemy_Update()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemy[i].used) {
			continue;//�������Ȃ�
		}
		//�e�̍��W�̍X�V
		D3DXVECTOR2 dir(0.0f, 0.0f);
		dir += D3DXVECTOR2(0.0f, 1.0f);

		D3DXVec2Normalize(&dir, &dir);//�x�N�g���̐��K��
		D3DXVECTOR2 vecSpeed = dir * speed;
		g_Enemy[i].position += vecSpeed;
		g_Enemy[i].collision.position = g_Enemy[i].position;

		//�e����ʊO������

		//if (g_Enemy_Position.y < -34)
		//{
			//Enemy_flag = false;
		//}
		if (g_Enemy[i].position.y > SCREEN_HEIGHT + 34)
		{
			g_Enemy[i].used = false;
		}

		/*if (g_Enemy_Position.x < 89)
		{
			g_Enemy_Position.x = 89;
		}
		if (g_Enemy_Position.x > SCREEN_WIDTH - 89)
		{
			g_Enemy_Position.x = SCREEN_WIDTH - 89;
		}
		if (g_Enemy_Position.y < 67)
		{
			g_Enemy_Position.y = 67;
		}
		if (g_Enemy_Position.y > SCREEN_HEIGHT - 67)
		{
			g_Enemy_Position.y = SCREEN_HEIGHT - 67;
		}
		*/
	}
}




void Enemy_Draw()
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (g_Enemy[i].used)
		{
			Sprite_Draw(tex_Enemy, g_Enemy[i].position.x, g_Enemy[i].position.y, 0, 0, 197, 134, 0, g_Enemy[i].position.x, g_Enemy[i].position.y, 0.5, 0.5, 1);
			Debug_DrawCircle(g_Enemy[i].position.x, g_Enemy[i].position.y, 40);
		}
	}
}




void Enemy_UnInit()
{
	
}




void Enemy_Create(float x, float y)//�e�̈�ԏ��߂ɍ��W
{
	for (int i = 0; i < ENEMY_MAX; i++)
	{
		if (!g_Enemy[i].used)
		{
			//���g�p�̂Ƃ���ō��
			g_Enemy[i].used = true;
			g_Enemy[i].position.x = x;
			g_Enemy[i].position.y = y;
			break;
		}

	}
}

bool Enemy_IsUsed(int index)
{

	return g_Enemy[index].used;

}

void Enemy_Destroy(int index)
{

	g_Enemy[index].used = false;


}

Circle* Enemy_GetCollision(int index)
{
	return &g_Enemy[index].collision;
}

Enemy* GetEnemyPosition(void)
{
	return &g_Enemy[0];
}

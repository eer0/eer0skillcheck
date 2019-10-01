#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "mydirect3d.h"
#include "bullet.h"
#include "collision.h"
#include "effect.h"


//グローバル変数
static int tex_Bullet;
static Bullet g_Bullets[BULLET_MAX] = {};
static float speed = 10.0f;

void Bullet_Init()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		g_Bullets[i].used = false;
		g_Bullets[i].collision.radius = 11;
	}
	
	tex_Bullet = Texture_SetLoadFile("Accet\\texture\\tama.png", 21, 59);
    
}



void Bullet_Update()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!g_Bullets[i].used) {
			continue;
		}
		//弾の座標の更新
		D3DXVECTOR2 dir(0.0f, 0.0f);
		dir -= D3DXVECTOR2(0.0f, 1.0f);
		D3DXVec2Normalize(&dir, &dir);//ベクトルの正規化
		D3DXVECTOR2 vecSpeed = dir * speed;
		g_Bullets[i].position += vecSpeed;
		g_Bullets[i].collision.position = g_Bullets[i].position;
		effect_Create(g_Bullets[i].position.x, g_Bullets[i].position.y + 20, D3DCOLOR_RGBA(0, 0, 255, 255), 10);

		//弾が画面外だった
		if (g_Bullets[i].position.x < -11)
		{
			g_Bullets[i].used = false;
		}
		if (g_Bullets[i].position.x > SCREEN_WIDTH + 11)
		{
			g_Bullets[i].used = false;
		}
		if (g_Bullets[i].position.y < -30)
		{
			g_Bullets[i].used = false;
		}
		if (g_Bullets[i].position.y > SCREEN_HEIGHT + 30)
		{
			g_Bullets[i].used = false;
		}
	}
}




void Bullet_Draw()
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (g_Bullets[i].used)
		{
			Sprite_Draw(tex_Bullet, g_Bullets[i].position.x, g_Bullets[i].position.y, 0, 0, 21, 59, 0, g_Bullets[i].position.x, g_Bullets[i].position.y, 1, 1, 1);
		}
	}
}




void Bullet_UnInit()
{
	
}




void Bullet_Create(float x, float y)//弾の一番初めに座標
{
	for (int i = 0; i < BULLET_MAX; i++)
	{
		if (!g_Bullets[i].used)
		{
			//未使用のところで作る
			g_Bullets[i].used = true;
			g_Bullets[i].position.x = x;
			g_Bullets[i].position.y = y;
			break;
		}
		
	}
}


bool Bullet_IsUsed(int index)
{
	
	return g_Bullets[index].used;
	
}

void Bullet_Destroy(int index)
{
	
	g_Bullets[index].used = false;
	
	 
}

Circle* Bullet_GetCollision(int index)
{
	return &g_Bullets[index].collision;
}
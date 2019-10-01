#include "Explosion.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "texture.h"
#include "sprite.h"


//グローバル変数
static int tex_Explosion;
static Explosion g_Explosion [EXPLOSION_MAX];



void Explosion_Init() 
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//フラグをoffにする
		g_Explosion[i].bUse = false;
		//座標の初期化
		g_Explosion[i].position.x = 0.0f;
		g_Explosion[i].position.y = 0.0f;
	}
	//テクスチャ
	tex_Explosion = Texture_SetLoadFile("Accet\\texture\\explosion.tga", 1024, 1024);
}

void Explosion_Update()
{
	//アニメーションの更新(フラグがonたっら)
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].bUse)
		{
			g_Explosion[i].Animationcount++;
			//フラグoff（アニメーションが終わったら)
			if (g_Explosion[i].Animationcount >= 16)
			{
				g_Explosion[i].bUse = false;
				g_Explosion[i].Animationcount = 0;
			}
		}
	}
	
}

void Explosion_Draw()
{
	
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//フラグがon
		if (g_Explosion[i].bUse)
		{
	        //爆発を描く
			Sprite_Draw(tex_Explosion, g_Explosion[i].position.x, g_Explosion[i].position.y, g_Explosion[i].Animationcount  % 4 * 256, g_Explosion[i].Animationcount / 4 * 256, 256, 256, 1, g_Explosion[i].position.x, g_Explosion[i].position.y, 0.3,0.3,0.3);
		}

	}
	
}

void Explosion_UnInit()
{
	
}

void Explosion_Create(float x, float y)//爆発の一番初めに座標
{
	for (int i = 0; i < EXPLOSION_MAX; i++)

	{
		if (!g_Explosion[i].bUse)
		{
			g_Explosion[i].bUse = true;
			g_Explosion[i].position.x = x;
			g_Explosion[i].position.y = y;
			g_Explosion[i].Animationcount = 0;
			break;
		}
		              
	}
}
#include "main.h"
#include "explosion.h"
#include "block.h"
#include "sprite.h"
#include "texture.h"
#include"ball.h"

unsigned int	g_ExplosionTexture;
EXPLOSION g_Explosion[EXPLOSION_MAX];

EXPLOSION *GetExplosion()
{//    &g_Explosion[0]どちらでもいい
	return g_Explosion;
}

void InitExplosion()
{

	g_ExplosionTexture = LoadTexture("rom:/explosion.tga");

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		g_Explosion[i].isUse = false;
	}


}

void UninitExplosion()
{
	UnloadTexture(g_ExplosionTexture);
}

void UpdateExplosion()
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].isUse)
		{
			
			g_Explosion[i].frame++;

			//  切り替える絵の数(生きてるフレーム数)   x*y         4*4
			if (g_Explosion[i].frame >= 16)
			{
				g_Explosion[i].isUse = false;
			}
			
		}
	}
}

void DrawExplosion()
{
	SetTexture(g_ExplosionTexture);

	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].isUse)
		{
			DrawSprite(g_Explosion[i].pos.x, g_Explosion[i].pos.y, 200.0f, 200.0f,
				//       %4=1~3   texture横向分成4份（1.0f/4)    texture纵向分成4份（1.0f/4)变成一
			g_Explosion[i].frame % 4 * 0.25f, g_Explosion[i].frame / 4 * 0.25f,
			//(1.0f/4) (1.0f/4)
			0.25f, 0.25f, MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));


		}

	}
}

void SetExplosion(Float2 pos)
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (!g_Explosion[i].isUse)
		{
			g_Explosion[i].pos= pos;
			g_Explosion[i].frame = 0;
			g_Explosion[i].isUse = true;
			break;
		}
	}
}
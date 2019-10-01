#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "ball.h"
#include "player.h"
#include "block.h"
#include"explosion.h"
#include"score.h"
#include"result.h"
#include"title.h"

// オブジェクト変数
BALL g_Ball;

int block_max = 64;
BALL *GetBall()
{//    &g_Explosion[0]どちらでもいい
	return &g_Ball;
}


void InitBall()
{

	g_Ball.tex = LoadTexture("rom:/ball.tga");

	g_Ball.pos.x = 0.0f;
	g_Ball.pos.y = 150.0f;

	g_Ball.sp.x = BALL_SP_X;
	g_Ball.sp.y = BALL_SP_Y;
}



void UninitBall()
{

	UnloadTexture(g_Ball.tex);

}


void UpdateBall()
{
	// プレイヤーの座標取得
	PLAYER *pPlayer = GetPlayer();
	// ボールの座標更新
	g_Ball.pos.x += g_Ball.sp.x;
	g_Ball.pos.y += g_Ball.sp.y;

	// スピード制限(元々の速度の5倍までいける)
	if (g_Ball.sp.y > BALL_SP_Y * 2.0f)
	{
		g_Ball.sp.y = BALL_SP_Y * 2.0f;
	}

	// プレイヤーとの衝突判定
	if ((pPlayer->pos.y - PLAYER_HAIGHT / 2) <= (g_Ball.pos.y + BALL_SIZE / 2) &&
		(pPlayer->pos.y + PLAYER_HAIGHT / 2) >= (g_Ball.pos.y - BALL_SIZE / 2) &&
		(pPlayer->pos.x - PLAYER_WIDTH / 2) <= (g_Ball.pos.x + BALL_SIZE / 2) &&
		(pPlayer->pos.x + PLAYER_WIDTH / 2) >= (g_Ball.pos.x - BALL_SIZE / 2))
	{
		g_Ball.sp.y *= -1.0f;
	}

	// 壁との衝突判定
	if (g_Ball.pos.x < -500.0f + 60.0f ||
		g_Ball.pos.x > 500.0f - 60.0f)
	{
		g_Ball.sp.x *= -1.0f;
	}

	// 天井との衝突判定
	if (g_Ball.pos.y - BALL_SIZE/2 < -1 * SCREEN_HEIGHT / 2 + 64.0f)
	{
		g_Ball.sp.y *= -1.0f;
	}

	// 地面との衝突判定
	if (g_Ball.pos.y + BALL_SIZE/2 > SCREEN_HEIGHT / 2)
	{
		g_Ball.sp.y = -1.0f * BALL_SP_Y;
		AddScore(-10);
	}

	BLOCK *block = GetBlock();
	
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		EXPLOSION *explosion = GetExplosion();
		if ((block + i)->isUse) {
			
			if (block[i].Position.y - 32.0f - 32.0f < g_Ball.pos.y&&
				g_Ball.pos.y < block[i].Position.y + 25.0f + 25.0f&&
				block[i].Position.x - 50.0f < g_Ball.pos.x&&
				g_Ball.pos.x < block[i].Position.x + 50.0f )
			{
				bool hit = false;

				if (g_Ball.sp.y > 0.0f)
				{
					g_Ball.sp.y *= -1.0f;
					hit = true;
				
				}
				else if (g_Ball.sp.y < 0.0f)
				{
					if (g_Ball.pos.y > block[i].Position.y + 25.0f)
					{
						g_Ball.sp.y *= -1.0f;
						hit = true;
					
					}
				}

				if (g_Ball.sp.x > 0.0f)
				{
					if (g_Ball.pos.x < block[i].Position.x - 50.0f)
					{
						g_Ball.sp.x *= -1.0f;
						hit = true;
						explosion[i].isUse = true;
					}
				}
				else if (g_Ball.sp.x < 0.0f)
				{
					if (g_Ball.tex > block[i].Position.x + 50.0f)
					{
						g_Ball.sp.x *= -1.0f;
						hit = true;
				      
					}
				}
				if (hit)
				{
					block[i].isUse = false;
					SetExplosion((block + i)->Position);
					AddScore(10);
					block_max += -1;
					if (block_max<= 0)
					{
						SetScene(SCENE_RESULT);
						block_max = 64;
					}
				}
			}
		}
	}
	
}



void DrawBall()
{

	SetTexture(g_Ball.tex);

	DrawSprite(g_Ball.pos.x, g_Ball.pos.y, 64.0f, 64.0f,
						0.0f, 0.0f, 1.0f, 1.0f,
						MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}


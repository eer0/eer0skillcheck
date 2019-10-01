#include "game.h"
#include "player.h"
#include "bullet.h"
#include "enemy.h"
#include "EnemyGenerater.h"
#include "Judgement.h"
#include "explosion.h"
#include "number.h"
#include "score.h"
#include "sound.h"
#include "sprite.h"
#include "common.h"
#include "texture.h"
#include "input.h"
#include "fade.h"
#include "effect.h"

static int g_score=0;
unsigned int g_GameTexture;
bool end = false;
int k = 0;

void Game_Init()
{
	g_GameTexture = Texture_SetLoadFile("Accet\\texture\\yuzhou.jpg", SCREEN_WIDTH, SCREEN_HEIGHT);
	Player_Init();
	Bullet_Init();
	EnemyGenerater_Init();
	Enemy_Init();
	Explosion_Init();
	Number_Init();
	effect_Init();
}

void Game_Update()
{
	
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		end = true;
	}
	if (end && !Fade_IsFade())
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
		end = false;
		SetScene(SCENE_RESULT);
		StopSound();
	}


	Player_Update();
	Bullet_Update();
	EnemyGenerater_Update();
	Enemy_Update();
	Judgement_Update();
    Explosion_Update();
	effect_Update();
	/*if ( end && !Fade_IsFade())
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
		end = false;
		g_score = 0;
		SetScene(SCENE_RESULT);
	}*/
}


void Game_Draw()
{
	Sprite_Draw(g_GameTexture , SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
	score_Draw(g_score, 1250, 50, 7,true,false);
	Bullet_Draw();
	Player_Draw();
	Enemy_Draw();
	Explosion_Draw();
	effect_Draw();
}

void Game_UnInit()
{
	Player_UnInit();
	Bullet_UnInit();
	EnemyGenerater_UnInit();
	Enemy_UnInit();
	Explosion_UnInit();
	effect_UnInit();
}

void Addscore(int n)
{
	g_score += n;
}
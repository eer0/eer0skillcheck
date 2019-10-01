#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "explosion.h"
#include "score.h"
#include "game.h"
#include "result.h"
#include "fade.h"
#include "sound.h"
#include "input.h"



unsigned int g_ResultTexture;
bool ispush1 = false;

void InitResult()
{

	g_ResultTexture = Texture_SetLoadFile("Accet\\texture\\gg.jpg", SCREEN_WIDTH, SCREEN_HEIGHT);
}


void UninitResult()
{
	
}


void UpdateResult()
{

	if (Keyboard_IsTrigger(DIK_SPACE))
	{

		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		ispush1 = true;

	}

	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		ispush1 = true;
	}

	if (ispush1 && !Fade_IsFade())
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
		ispush1 = false;
		SetScene(SCENE_TITLE);
	}
}


void DrawResult()
{

	Sprite_Draw(g_ResultTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH , SCREEN_HEIGHT );
}
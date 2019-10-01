
#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "explosion.h"
#include "score.h"
#include "title.h"
#include "fade.h"
#include "sound.h"
#include "input.h"


unsigned int g_TitleTexture;
bool ispush = false;


void InitTitle()
{
	g_TitleTexture = Texture_SetLoadFile("Accet\\texture\\feiji123.png", SCREEN_WIDTH/2, SCREEN_HEIGHT);
}


void UninitTitle()
{
	
}


void UpdateTitle()
{
	if (Keyboard_IsTrigger(DIK_SPACE))
	{
		
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		ispush = true;
		
	}

	if (Keyboard_IsTrigger(DIK_RETURN))
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 0), true);
		ispush = true;
	}

	if(ispush&&!Fade_IsFade())
	{
		Fade_Start(30, D3DCOLOR_RGBA(0, 0, 0, 255), false);
		PlaySound(SOUND_LABEL_BGM000);
		ispush = false;
		SetScene(SCENE_GAME);
	}
	
}


void DrawTitle()
{
	Sprite_Draw(g_TitleTexture, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2, 0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);

}

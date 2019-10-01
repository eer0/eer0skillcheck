#include "main.h"
#include "controller.h"
#include "texture.h"
#include"explosion.h"
#include"score.h"
#include "sprite.h"
#include"fade.h"

unsigned int g_TitleTexture;


void InitTitle()
{
	g_TitleTexture = LoadTexture("rom:/title.tga");
}


void UninitTitle()
{
	UnloadTexture(g_TitleTexture);
}


void UpdateTitle()
{
	if (GetControllerTrigger(NpadButton::Plus::Index))
	{
		SetFade(SCENE_GAME);
	}
	
}


void DrawTitle()
{
	SetTexture(g_TitleTexture);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}
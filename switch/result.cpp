#include "main.h"
#include "controller.h"
#include "texture.h"
#include"score.h"
#include "sprite.h"
#include"fade.h"

unsigned int g_ResultTexture;


void InitResult()
{
	g_ResultTexture = LoadTexture("rom:/result.tga");
}


void UninitResult()
{
	UnloadTexture(g_ResultTexture);
}


void UpdateResult()
{
	if (GetControllerTrigger(NpadButton::Plus::Index))
	{
		
		SetFade(SCENE_TITLE);
	}
	

}


void DrawResult()
{
	SetTexture(g_ResultTexture);

	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}
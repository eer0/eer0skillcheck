
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"

FADE_STATE g_FadeState;
SCENE g_FadeNextScene;
float g_FadeAlpha;

void InitFade()
{
	g_FadeState = FADE_STATE_NONE;
	g_FadeNextScene = SCENE_NONE;
	g_FadeAlpha = 0.0f;
}

void UninitFade()
{

}

void UpdateFade()
{
	if (g_FadeState == FADE_STATE_OUT)
	{
		if (g_FadeAlpha >= 1.0f)
		{
			g_FadeAlpha = 1.0f;
			g_FadeState = FADE_STATE_IN;
			SetScene(g_FadeNextScene);
		}
		//20.0f‚Ífade-out‚Ì’x‚³
		g_FadeAlpha += 1.0f / 20.0f;
	}

	else if(g_FadeState == FADE_STATE_IN)
	{
		if (g_FadeAlpha <= 0.0f)
		{
			g_FadeAlpha = 0.0f;
			g_FadeState = FADE_STATE_NONE;
		}
		//20.0f‚Ífade-in‚Ì’x‚³
		g_FadeAlpha -= 1.0f / 20.0f;
	}
}

void DrawFade()
{
	if (g_FadeState == FADE_STATE_NONE)
	{
		return;
	}

	SetTexture(0);
	DrawSprite(0.0f, 0.0f, SCREEN_WIDTH, SCREEN_HEIGHT,
		0.0f, 0.0f, 1.0f, 1.0f,
		MakeFloat4(0.0f, 0.0f, 0.0f, g_FadeAlpha));

}

void SetFade(SCENE Scene)
{
	g_FadeNextScene = Scene;
	g_FadeState = FADE_STATE_OUT;
	//g_FadeState = FADE_STATE_IN;
	//g_FadeState = FADE_STATE_NONE;
}


FADE_STATE GetFadeState()
{
	return  g_FadeState;
}
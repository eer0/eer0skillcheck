#pragma once


enum FADE_STATE
{
	FADE_STATE_NONE = 0,
	FADE_STATE_IN,
	FADE_STATE_OUT
};

void InitFade();
void UninitFade();
void UpdateFade();
void DrawFade();

void SetFade(SCENE Scene);


FADE_STATE GetFadeState();

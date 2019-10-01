#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "bg.h"
#include "player.h"
#include "ball.h"
#include "block.h"
#include "explosion.h"
#include"score.h"
#include"game.h"
#include"title.h"
#include"result.h"
#include"fade.h"

void Init();
void Uninit();
void Update();
void Draw();

SCENE g_Scene = SCENE_NONE;

extern "C" void nnMain()
{
	Init();

    while( true )
	{
		Update();
		Draw();
	}

	Uninit();
}


void Init()
{
	InitSystem();
	InitController();
	InitFade();

	SetScene(SCENE_TITLE);
	

}


void Uninit()
{
	SetScene(SCENE_NONE);

	UninitController();
	UninitFade();
	UninitSystem();
	
}


void Update()
{
	UpdateController();
	UpdateFade();

	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		UpdateTitle();
		break;
	case SCENE_GAME:
		UpdateGame();
		break;
	case SCENE_RESULT:
		UpdateResult();
		break;
	default:break;
	}


	
}


void Draw()
{
	glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
	glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		DrawTitle();
		break;
	case SCENE_GAME:
		DrawGame();
		break;
	case SCENE_RESULT:
		DrawResult();
		break;
	default:break;
	}

	DrawFade();
	SwapBuffers();


}



void SetScene(SCENE Scene)
{
	switch (g_Scene)
	{
	case SCENE_NONE:
			break;
	case SCENE_TITLE:
		UninitTitle();
		break;
	case SCENE_GAME:
		UninitGame();
		break;
	case SCENE_RESULT:
		UninitResult();
		break;
	default:break;
	}

	g_Scene = Scene;

	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:
		InitTitle();
		break;
	case SCENE_GAME:
		InitGame();
		break;
	case SCENE_RESULT:
		InitResult();
		break;
	default:break;
	}

}
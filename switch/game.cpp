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
#include"fade.h"


void InitGame()
{

	InitBG();
	InitPlayer();
	InitScore();
	InitBall();
	InitBlock();
	InitExplosion();
}

void UninitGame()
{
	
	UninitBG();
	UninitPlayer();
	UninitScore();
	UninitBall();
	UninitBlock();
	UninitExplosion();
}

void UpdateGame()
{
	
	UpdateBG();
	UpdatePlayer();
	UpdateScore();
	UpdateBall();
	UpdateBlock();
	UpdateExplosion();
	
	if (GetControllerTrigger(NpadButton::Minus::Index))
	{

		SetFade(SCENE_TITLE);
	}
	

}
void DrawGame()
{

	DrawBG();
	DrawPlayer();
	DrawScore();
	DrawBall();
	DrawBlock();
	DrawExplosion();
}
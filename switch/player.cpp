
#include "main.h"
#include "controller.h"
#include "texture.h"
#include "sprite.h"
#include "player.h"
#include "block.h"

unsigned int	g_PlayerTexture;
PLAYER			g_Player;


void InitPlayer()
{

	g_PlayerTexture = LoadTexture("rom:/player.tga");

	g_Player.pos.x = 0.0f;
	g_Player.pos.y = 450.0f;
}



void UninitPlayer()
{

	UnloadTexture(g_PlayerTexture);

}


void UpdatePlayer()
{

	// ボタン
	if (GetControllerPress(NpadButton::Left::Index))
		g_Player.pos.x += -20.0f;
	if (GetControllerPress(NpadButton::Right::Index))
		g_Player.pos.x += 20.0f;


	// アナログスティック
	Float2 stick;
	stick = GetControllerLeftStick();

	g_Player.pos.x += stick.x * 20.0f;
	


	// タッチスクリーン
	if (GetControllerTouchScreen())
	{
		Float2 touch;
		touch = GetControllerTouchScreenPosition();
		g_Player.pos = touch;
	}



	// 加速度センサー
	if (GetControllerPress(NpadButton::A::Index))
	{
		Float3 acc;
		acc = GetControllerRightAcceleration();

		g_Player.pos.x += acc.x * 10.0f;
		g_Player.pos.y += -acc.y * 10.0f;
	}



	// ジャイロセンサー
	if (GetControllerPress(NpadButton::B::Index))
	{
		Float3 angle;
		angle = GetControllerRightAngle();

		g_Player.pos.x = angle.z * 1000.0f;
	}



	// 振動
	if (GetControllerPress(NpadButton::Y::Index))
	{
		SetControllerLeftVibration(5);
	}
	if (GetControllerPress(NpadButton::X::Index))
	{
		SetControllerRightVibration(5);
	}


	BLOCK *block = GetBlock();
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Player.pos.y + 30.0f <block[i].Position.y)
		{
			g_Player.pos.y = block[i].Position.y-30.0f;
		}
	}
	

	if (g_Player.pos.x < -500.0f + 100.0f)
		g_Player.pos.x = -500.0f + 100.0f;

	if (g_Player.pos.x > 500.0f - 100.0f)
		g_Player.pos.x = 500.0f - 100.0f;

	if (g_Player.pos.y > 540.0f - 30.0f)
		g_Player.pos.y = 540.0f - 30.0f;

	if (g_Player.pos.y < -442.0f - 30.0f)
		g_Player.pos.y = -442.0f - 30.0f;


}



void DrawPlayer()
{

	SetTexture(g_PlayerTexture);

	DrawSprite(g_Player.pos.x, g_Player.pos.y,PLAYER_WIDTH, PLAYER_HAIGHT,
						0.0f, 0.0f, 1.0f, 1.0f,
						MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

}

PLAYER *GetPlayer()
{
	return &g_Player;
}
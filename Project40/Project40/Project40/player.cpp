#include "player.h"
#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "mydirect3d.h"
#include "bullet.h"
#include "sound.h"
#include "effect.h"

static int tex_player;
static bool isright = true;
static bool shot = false;
static float maru = 0.0f;
static float henka = 1.0f;
static float maru_speed = 0.0f;
static float speed = 9.0f;
static int frame = 0;
D3DXVECTOR2 g_Player_Position(0.0f, 0.0f);

void Player_Init()
{
	g_Player_Position = { SCREEN_WIDTH / 2,SCREEN_HEIGHT / 2 };
	tex_player = Texture_SetLoadFile("Accet\\texture\\feiji.png", 318, 87);
}

void Player_Update()
{
	//キー入力の更新
	Keyboard_Update();
	
	D3DXVECTOR2 dir(0.0f, 0.0f);
	
	if (Keyboard_IsPress(DIK_W))
	{
		dir -= D3DXVECTOR2(0.0f, 1.0f);
		//dir.y-=1;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		dir += D3DXVECTOR2(1.0f, 0.0f);
		//dir.x+=1;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		dir += D3DXVECTOR2(0.0f, 1.0f);
		//dir.y+=1;
	}
	if (Keyboard_IsPress(DIK_A))
	{
		dir -= D3DXVECTOR2(1.0f, 0.0f);
		//dir.x-=1;
	}

	/*if (Keyboard_IsPress(DIK_A))
	{
		position_player.x -= hspeed;
		isright = false;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		position_player.x += hspeed;
		isright = true;
	}
	if (Keyboard_IsPress(DIK_W))
	{
		position_player.y -= vspeed;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		position_player.y += vspeed;
	}*/

	shot = false;
	if (Keyboard_IsPress(DIK_J))
	{
		shot = true;
	}
	else
	{
		
	}
	if (shot)
	{
		
		if (frame % 20 == 0)
		{
			Bullet_Create(g_Player_Position.x, g_Player_Position.y);
			
			//PlaySound(SOUND_LABEL_SE_SHOT);
			
		}
		frame += 1;
	}

	if (Keyboard_IsPress(DIK_SPACE))
	{
		maru_speed += 0.03f;
	}
	maru += maru_speed;
	maru_speed *= 0.98f;

	if (Keyboard_IsPress(DIK_UP))
	{
		henka += 0.03f;
	}
	if (Keyboard_IsPress(DIK_DOWN))
	{
		henka -= 0.03f;
	}
	if (henka < 0.0f)
	{
		henka = 0.0f;
	}


	if (g_Player_Position.x < 38)
	{
		g_Player_Position.x = 38;
	}
	//g_Player_Position.x = MAX(g_Player_Position.x,38);
	if (g_Player_Position.x > SCREEN_WIDTH - 38)
	{
		g_Player_Position.x = SCREEN_WIDTH - 38;
	}
	if (g_Player_Position.y < 43)
	{
		g_Player_Position.y = 43;
	}
	if (g_Player_Position.y > SCREEN_HEIGHT - 43)
	{
		g_Player_Position.y = SCREEN_HEIGHT - 43;
	}

	D3DXVec2Normalize(&dir, &dir);//ベクトルの正規化
	D3DXVECTOR2 vecSpeed = dir * speed;
	g_Player_Position += vecSpeed;
	effect_Create(g_Player_Position.x, g_Player_Position.y+20, D3DCOLOR_RGBA(255, 0, 0, 255), 10);

}

void Player_Draw()
{
	Sprite_Draw(tex_player , g_Player_Position.x, g_Player_Position.y, 118, 0, 78, 86, 0, g_Player_Position.x, g_Player_Position.y, 1, 1, henka, isright);
}

void Player_UnInit()
{
	
}


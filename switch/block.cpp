
#include "main.h"
#include "texture.h"
#include "sprite.h"
#include "block.h"
#include"explosion.h"


unsigned int	g_BlockTexture;

BLOCK			g_Block[BLOCK_MAX];

void InitBlock()
{

	g_BlockTexture = LoadTexture("rom:/block.tga");

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		g_Block[i].isUse = false;
	}


	for (int y = 0; y < 8; y++)
	{
		for (int x = 0; x < 8; x++)
		{
			SetBlock(-350.0f + x * 100.0f, -355.0f + y * 50.0f, y / 2);
		}
	}
}



void UninitBlock()
{

	UnloadTexture(g_BlockTexture);

}


void UpdateBlock()
{
	int blockCount = 0;

	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].isUse == true)
			blockCount++;
	}
	

}



void DrawBlock()
{

	SetTexture(g_BlockTexture);


	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].isUse == true)
		{
			DrawSprite(g_Block[i].Position.x, g_Block[i].Position.y, 100.0f, 64.0f,
				0.0f, g_Block[i].Type * 0.25f, 1.0f, 0.25f,
				MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));
		}
	}
}


void SetBlock(float x, float y, int type)
{
	for (int i = 0; i < BLOCK_MAX; i++)
	{
		if (g_Block[i].isUse == false)
		{
			g_Block[i].Position.x = x;
			g_Block[i].Position.y = y;
			g_Block[i].Type = type;
			g_Block[i].isUse = true;
			break;
		}
	}

}


BLOCK *GetBlock()
{
	return g_Block;
}
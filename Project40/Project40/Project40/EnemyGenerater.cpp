#include "input.h"
#include "texture.h"
#include "sprite.h"
#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <Windows.h>
#include "mydirect3d.h"
#include "EnemyGenerater.h"
#include "enemy.h"
#include "sound.h"

static int genalateCounter = 0;
static int frameCounter = 0;//‰Šú‰»‚Å‚à0‘ã“ü‚í‚·‚ê‚¸‚É

void EnemyGenerater_Init()
{

}

void EnemyGenerater_Update()
{
	if (frameCounter % 60 == 0)
	{
		//“G”­¶II
		switch (genalateCounter % 3)
		{
		case 0:
			Enemy_Create(128.0f, -34.0f);
			//Enemy_Create(250.0f, -34.0f);
			//Enemy_Create(628.0f, -34.0f);
			Enemy_Create(500.0f, -34.0f);
			break;

		case 1:
			Enemy_Create(128.0f, -34.0f);
			//Enemy_Create(250.0f, -34.0f);
			//Enemy_Create(628.0f, -34.0f);
			Enemy_Create(500.0f, -34.0f);
			break;

		case 2:
			Enemy_Create(1000.0f, -34.0f);
			//Enemy_Create(900.0f, -34.0f);
			Enemy_Create(800.0f, -34.0f);
			break;
		}
		genalateCounter++;
	}
	frameCounter++;
}


void EnemyGenerater_UnInit()
{
	
}
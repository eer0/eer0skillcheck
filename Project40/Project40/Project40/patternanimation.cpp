#include "patternanimation.h"
#include "texture.h"
#include "mydirect3d.h"
#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "sprite.h"

#define COCO_WALK_R_PATTERN_MAX (10)//最大パタン

static int tex_coco;
static LPDIRECT3DDEVICE9 g_pDevice = NULL;

void PatternAnim_Init(void)
{
	tex_coco = Texture_SetLoadFile("Accet\\texture\\runningman100.png", 700, 400);
}


void PatternAnim_Draw(float dx, float dy, int frameCount, float angle, float cx, float cy, float x, float y, float z, bool isright)
{
	//                       待ちフレーム
	int pattern = frameCount /  8 % (COCO_WALK_R_PATTERN_MAX );  //最大パタン数
	//　　　　　　　フレームカウンター
	//int pattern1 = frameCount / 8 / (COCO_WALK_R_PATTERN_MAX );


	//ココ右向き描画
	Sprite_Draw(tex_coco, dx, dy, pattern%5*140, pattern/5*200, 140, 200,  angle,  cx,  cy,  x,  y, z,isright);
}
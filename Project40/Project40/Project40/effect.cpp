#include "effect.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "texture.h"
#include "sprite.h"
#include "mydirect3d.h"


//グローバル変数
static int tex_effect;
static effect g_effect[effect_MAX];
static int g_EffectFrameCount = 0;


void effect_Init()
{
	for (int i = 0; i < effect_MAX; i++)
	{
		g_effect[i].lifeFrame = 0;
		g_effect[i].spawnFrame = -1;
		//座標の初期化
	
	}
	g_EffectFrameCount = 0;
	//テクスチャ
	tex_effect = Texture_SetLoadFile("Accet\\texture\\effect000.jpg", 40, 40);
}

void effect_Update()
{
	
	//アニメーションの更新(フラグがonたっら)
	for (int i = 0; i < effect_MAX; i++)
	{
		if (g_effect[i].lifeFrame > 0)
		{
			int elapsedFrame = g_EffectFrameCount - g_effect[i].spawnFrame;
			float rate = elapsedFrame / (float)g_effect[i].lifeFrame;
			if (rate > 1.0f)
			{
				rate = 1.0f;
				g_effect[i].lifeFrame = 0;
				g_effect[i].spawnFrame = -1;
				continue;
			}
			//αは各色成分と乗算される
			D3DXCOLOR color = g_effect[i].color;
			color.a = 1.0f - rate;
			g_effect[i].color = color;
		}
	}
	g_EffectFrameCount++;
}

void effect_Draw()
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	// レンダーステート(加算合成処理)
    // 色 = (SRC色 * SRCアルファ) + (DEST色 * (1.0)アルファ)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// αデスティネーションカラーの指定(1.0)

	for (int i = 0; i < effect_MAX; i++)
	{
		//生きてたら
		if (g_effect[i].lifeFrame > 0)
		{
			//effectを描く
			
			Sprite_Draw(tex_effect, g_effect[i].position.x, g_effect[i].position.y,g_effect[i].color);
		}
	}
	// レンダーステート(通常ブレンド処理)
    // 色 = (SRC色 * SRCアルファ) + (DEST色 * (1.0 - SRC)アルファ)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// ブレンディング処理(デフォルト)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// αソースカラーの指定
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// αデスティネーションカラーの指定(1.0 - SRC)

}

void effect_UnInit()
{

}

void effect_Create(float x, float y,D3DCOLOR color,int lifeFrame)//※エフェクトの拡大率をいれられると良い
{
	for (int i = 0; i < effect_MAX; i++)

	{
		if (g_effect[i].lifeFrame > 0)//使っているところだったら
		{
			continue;
		}
		g_effect[i].position.x = x;
		g_effect[i].position.y = y;
		g_effect[i].lifeFrame = lifeFrame;
		g_effect[i].spawnFrame = g_EffectFrameCount;
		g_effect[i].color = color;
		//大きさ
		break;
		

	}
}
#include "common.h"
#include "texture.h"
#include "sprite.h"
#include "fade.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "mydirect3d.h"


//グローバル変数
//FADE_STATE g_FadeState;
//SCENE g_FadeNextScene;
//static float g_FadeAlpha;
//unsigned int g_FadeTexture;
bool g_bFadeOut = false;
bool g_bFade = false;
int g_FadeFrame = 0;
int g_FadeFrameCount = 0;
int g_FadeStartFrame = 0;
D3DCOLOR g_FadeColor = 0;


typedef struct FadeVertex_tag
{
	D3DXVECTOR4 position;//頂点座標
	D3DCOLOR color;//頂点の形に色を追加する

}FadeVertex;
//FVFの宣言
#define FVF_FADE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE) //XとYとZとRHWをもつ頂点データを表す


//初期化
void Fade_Init()
{
	bool g_bFade = false;
	int g_FadeFrameCount = 0;

}

void Fade_Uninit()
{

}

void Fade_Update()
{
	if (g_bFade)
	{
		int elapsedFrame = g_FadeFrameCount - g_FadeStartFrame;
		float rate = elapsedFrame / (float)g_FadeFrame;//比率
		float alpha = 0;

		if (elapsedFrame >= g_FadeFrame)
		{
			g_bFade = false;
			rate = 1.0f;
		}

		if (g_bFadeOut)//不透明になる
		{
			alpha = rate;
		}
		else//透明になる
		{
			alpha = 1.0f - rate;
		}
		//一行で書く:alpha=g_bFadeOut?rate:1.0f-rate;
		D3DXCOLOR color = g_FadeColor;
		color.a = alpha;
		g_FadeColor = color;
	
	}

	g_FadeFrameCount++;

	
	
}

void Fade_Draw()
{
	//ポリゴン描画　SetTextureにはNULL
	//フェードインが終了してたらポリゴン描かない 
	//フェードアウト            ポリゴン描く
	//if (!g_bFadeOut && !g_bFade)
	//{
	//	return;
	//}
	D3DXCOLOR color = g_FadeColor;
	if (color.a <= 0.0001f)
	{
		return;
	}


	
	FadeVertex v[]{
		{D3DXVECTOR4(0.0f,SCREEN_HEIGHT,0.0f,1.0f),g_FadeColor},
		{D3DXVECTOR4(0.0f,0.0f,0.0f,1.0f),g_FadeColor},
		{D3DXVECTOR4(SCREEN_WIDTH,SCREEN_HEIGHT,0.0f,1.0f)},
		{D3DXVECTOR4(SCREEN_WIDTH,0.0f,0.0f,1.0f),g_FadeColor},
	};

	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	//FVFの設定
	g_pDevice->SetFVF(FVF_FADE_VERTEX);
	//テクスチャの設定
	g_pDevice->SetTexture(0, NULL);
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(FadeVertex));


}



void Fade_Start(int frame, D3DCOLOR color, bool bFadeOut)
{
	g_FadeColor = color;
	g_FadeFrame = frame;
	g_bFadeOut = bFadeOut;
	g_FadeStartFrame = g_FadeFrameCount;//現在のフレーム
	g_bFade = true;//フェード中
}

bool Fade_IsFade(void)
{
	return g_bFade;
}

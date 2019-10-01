#include "sprite.h"
#include "texture.h"
#include "mydirect3d.h"
#include "common.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include <string.h>
#include "fade.h"



//頂点データ構造体（頂点の形（フォーマット））の宣言
typedef struct Vertex2d_tag
{
	D3DXVECTOR4 position;//頂点座標
	D3DCOLOR color;//頂点の形に色を追加する
	D3DXVECTOR2 uv;//texcoord テクスチャ座標

}Vertex2d;
//FVFの宣言
#define FVF_VERTEX2D (D3DFVF_XYZRHW|D3DFVF_DIFFUSE|D3DFVF_TEX1) //XとYとZとRHWをもつ頂点データを表す


//グローバル変数
static D3DCOLOR g_color = D3DCOLOR_RGBA(255, 255, 255, 255);
static LPDIRECT3DVERTEXBUFFER9 g_VertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;


void Sprite_Draw(int textureId, float dx, float dy)
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[]{
	{D3DXVECTOR4(dx - 0.5f - w / 2,dy - 0.5f + h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,1.0f)},
	{D3DXVECTOR4(dx - 0.5f - w / 2,dy - 0.5f - h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR4(dx - 0.5f + w / 2,dy - 0.5f + h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,1.0f)},
	{D3DXVECTOR4(dx - 0.5f + w / 2,dy - 0.5f - h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(1.0f,0.0f)},
	};
	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));

}

void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h)
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(cut_x / (float)w,(cut_y + cut_h) / (float)h)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(cut_x / (float)w,cut_y / (float)h)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2((cut_x + cut_w) / (float)w,(cut_y + cut_h) / (float)h)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2((cut_x + cut_w) / (float)w,cut_y / (float)h)},
	};

	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}

void Sprite_Draw(int textureId, float dx, float dy,int cut_x,int cut_y,int cut_w,int cut_h,float angle) 
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	//頂点データ(トライアングルストリップ)
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;


	D3DXMATRIX mtxRot;
	D3DXMatrixRotationZ(&mtxRot, angle);

	
	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f- cut_w /2,dy - 0.5f+ cut_h /2,0.0f,1.0f),g_color,D3DXVECTOR2(cut_x / (float)w,(cut_y + cut_h) / (float)h)},
		{D3DXVECTOR4(dx - 0.5f- cut_w /2,dy - 0.5f- cut_h /2,0.0f,1.0f),g_color,D3DXVECTOR2(cut_x / (float)w,cut_y / (float)h)},
		{D3DXVECTOR4(dx - 0.5f+ cut_w /2,dy - 0.5f+ cut_h /2,0.0f,1.0f),g_color,D3DXVECTOR2((cut_x + cut_w) / (float)w,(cut_y + cut_h) / (float)h)},
		{D3DXVECTOR4(dx - 0.5f+ cut_w /2,dy - 0.5f- cut_h /2,0.0f,1.0f),g_color,D3DXVECTOR2((cut_x + cut_w) / (float)w,cut_y / (float)h)},
	};

	//回転　(0,0)が原点
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxRot);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxRot);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxRot);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxRot);
	
	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
	
	
	
}

void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z)
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	//頂点データ(トライアングルストリップ)
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	float u[2] = {};


	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT, mtxS;
	D3DXMatrixIdentity(&mtxW);
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//元に戻す
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, x, y, z);//x,y,z   拡大、縮小
	mtxW = mtxT * mtxS;
	mtxW = mtxW * mtxR * mtxIT;


	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v1)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u0,v0)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v1)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u1,v0)},
	};

	//回転　(0,0)が原点
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));
}


void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, float angle, float cx, float cy, float x, float y, float z,bool isright)
//                                                                                                      回転の中心座標
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	//頂点データ(トライアングルストリップ)
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	float u0 = cut_x / (float)w;
	float v0 = cut_y / (float)h;
	float u1 = (cut_x + cut_w) / (float)w;
	float v1 = (cut_y + cut_h) / (float)h;
	float u[2] = {};
	if (isright)
	{
		u[0] = u1;
		u[1] = u0;
	}
	if (!isright)
	{
		u[0] = u0;
		u[1] = u1;
	}
	
	D3DXMATRIX mtxW, mtxR, mtxT, mtxIT,mtxS;
	D3DXMatrixIdentity(&mtxW);
	D3DXMatrixTranslation(&mtxT, -cx, -cy, 0.0f);
	D3DXMatrixTranslation(&mtxIT, cx, cy, 0.0f);//元に戻す
	D3DXMatrixRotationZ(&mtxR, angle);
	D3DXMatrixScaling(&mtxS, x, y, z);//x,y,z   拡大、縮小
	mtxW = mtxT * mtxS ;
	mtxW = mtxW * mtxR * mtxIT;


	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v1)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[0],v0)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v1)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),g_color,D3DXVECTOR2(u[1],v0)},
	};

	//回転　(0,0)が原点
	D3DXVec4Transform(&v[0].position, &v[0].position, &mtxW);
	D3DXVec4Transform(&v[1].position, &v[1].position, &mtxW);
	D3DXVec4Transform(&v[2].position, &v[2].position, &mtxW);
	D3DXVec4Transform(&v[3].position, &v[3].position, &mtxW);

	Vertex2d*pV;
	g_VertexBuffer->Lock(0, 0, (void**)&pV, D3DLOCK_DISCARD);
	//                          仮想アドレス

	//メモリコピー
	memcpy(pV,v,sizeof(v));
	g_VertexBuffer->Unlock();
	//deviceに画像バッファを与える
	g_pDevice->SetStreamSource(0, g_VertexBuffer,0,sizeof(Vertex2d));
	//deviceにindexバッファを与える
	g_pDevice->SetIndices(g_pIndexBuffer);
	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	g_pDevice->DrawIndexedPrimitive(D3DPT_TRIANGLELIST, 0, 0, 4, 0, 2);
	
	//DrawPrimitiveUP
	//g_pDevice->DrawPrimitive(D3DPT_TRIANGLESTRIP, 0, 2);

	//16ビット　65535
	//g_pDevice->DrawIndexedPrimitiveUP(D3DPT_TRIANGLELIST, 0, 4, 2,index,D3DFMT_INDEX16,v,sizeof(Vertex2d));
	//                                                                 16ビット　D3DFMT_INDEX32


	//頂点データを用意する

	//描く
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, g, sizeof(Vertex2d));

	//g_pDevice->SetTexture(0, g_pTexture[0]);

	//g_pDevice->SetTextureStageState(0, D3DTSS_COLOROP, D3DTOP_SELECTARG2);
	//　　　　　　　　　　　　　　　　 COLORARG0~2,    D3DTA_CURRENT ポリゴンから
	//                                 ALPHAARG0~2,         _DIFFUSE
	//                                                      _TEXTURE
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 4, b, sizeof(Vertex2d));
	//g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 400, a, sizeof(Vertex2d));
	//g_pDevice->DrawPrimitiveUP(D3DPT_POINTLIST, pc, v, sizeof(Vertex2d));//ポリゴン
	//g_pDevice->DrawPrimitiveUP(D3DPT_LINESTRIP, SCREEN_WIDTH-1, c, sizeof(Vertex2d));
	//                                _TRIANGLESTRIP   123 234 345のように三角形をかく
	//                                _TRIANGLEFAN     右回す
	//                                _TRIANGLELIST  　頂点
	//                                _POINTLIST　　　 点
	//                                _LINELIST        2 頂点の線
	//                                _LINESTRIP　     連続の線　離れてはダメ
}

void Sprite_Draw(int textureId, float dx, float dy, int cut_x, int cut_y, int cut_w, int cut_h, int g_FadeAlpha)
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[]{
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),D3DCOLOR_RGBA(0, 0, 0, g_FadeAlpha),D3DXVECTOR2(cut_x / (float)w,(cut_y + cut_h) / (float)h)},
		{D3DXVECTOR4(dx - 0.5f - cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),D3DCOLOR_RGBA(0, 0, 0, g_FadeAlpha),D3DXVECTOR2(cut_x / (float)w,cut_y / (float)h)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f + cut_h / 2,0.0f,1.0f),D3DCOLOR_RGBA(0, 0, 0, g_FadeAlpha),D3DXVECTOR2((cut_x + cut_w) / (float)w,(cut_y + cut_h) / (float)h)},
		{D3DXVECTOR4(dx - 0.5f + cut_w / 2,dy - 0.5f - cut_h / 2,0.0f,1.0f),D3DCOLOR_RGBA(0, 0, 0, g_FadeAlpha),D3DXVECTOR2((cut_x + cut_w) / (float)w,cut_y / (float)h)},
	};

	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));



}
void Sprite_Draw(int textureId, float dx, float dy,D3DCOLOR color)
{
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	int w = Texture_GetWidth(textureId);
	int h = Texture_GetHeight(textureId);

	Vertex2d v[]{
	{D3DXVECTOR4(dx - 0.5f - w / 2,dy - 0.5f + h / 2,0.0f,1.0f),color,D3DXVECTOR2(0.0f,1.0f)},
	{D3DXVECTOR4(dx - 0.5f - w / 2,dy - 0.5f - h / 2,0.0f,1.0f),color,D3DXVECTOR2(0.0f,0.0f)},
	{D3DXVECTOR4(dx - 0.5f + w / 2,dy - 0.5f + h / 2,0.0f,1.0f),color,D3DXVECTOR2(1.0f,1.0f)},
	{D3DXVECTOR4(dx - 0.5f + w / 2,dy - 0.5f - h / 2,0.0f,1.0f),color,D3DXVECTOR2(1.0f,0.0f)},
	};
	//FVFの設定
	g_pDevice->SetFVF(FVF_VERTEX2D);
	//テクスチャの設定
	g_pDevice->SetTexture(0, Texture_GetTexture(textureId));
	//DrawPrimitiveUP
	g_pDevice->DrawPrimitiveUP(D3DPT_TRIANGLESTRIP, 2, v, sizeof(Vertex2d));



}
void Sprite_Init(void)
{
	LPDIRECT3DDEVICE9 pDevice = GetDevice();
	pDevice->CreateVertexBuffer(sizeof(Vertex2d) * 4, D3DUSAGE_WRITEONLY, FVF_VERTEX2D, D3DPOOL_MANAGED, &g_VertexBuffer, NULL);
    //                                 長さ                                    0           復旧
	
	pDevice->CreateIndexBuffer(sizeof(WORD) * 6, D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
	WORD *pIndex;
	g_pIndexBuffer->Lock(0, 0, (void**)&pIndex, D3DLOCK_DISCARD);
	pIndex[0] = 0;
	pIndex[1] = 1;
	pIndex[2] = 2;
	pIndex[3] = 1;
	pIndex[4] = 3;
	pIndex[5] = 2;
	g_pIndexBuffer->Unlock();
}

void Sprite_UnInit(void)
{
	if (g_VertexBuffer)
	{
		g_VertexBuffer->Release();
		g_VertexBuffer = NULL;
	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
}

/*void Sprite_SetColor(D3DCOLOR color)
{
	g_color = color;
}
*/
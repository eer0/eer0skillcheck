#include "texture.h"
#include <d3d9.h>
#include <d3dx9.h>
#include <windows.h>
#include "mydirect3d.h"


static LPDIRECT3DDEVICE9 g_pDevice = NULL;
static TextureData g_TextureData[TEXTUREDATA_MAX] = {};
HRESULT hr[TEXTUREDATA_MAX] = {};

int Texture_SetLoadFile(const char* pFilename, int width, int height)
{
	//同じファイル名を探す
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (strcmp(g_TextureData[i].filename, pFilename) == 0)//見つかった
		{
			return i;
		}
	}

	//新規登録
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		//使用されてない場所を探す
		if (g_TextureData[i].filename[0] != 0)//使われてない
		{
			continue;//打ち止め
		}
		//登録
		strcpy_s(g_TextureData[i].filename, pFilename);//ファイル名をコピー
		g_TextureData[i].width = width;//幅コピー
		g_TextureData[i].height = height;//高さコピー
		return i;
	}
	return -1;
}

int Texture_Load(HWND hWnd)
{
	g_pDevice = GetDevice();
	int error_count = 0;
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_TextureData[i].pTexture != NULL)
		{
			continue;
		}
		if (g_TextureData[i].filename[0] == 0)//ファイル名があって、まだ
		{
			continue;
		}
		//テクスチャ読み込む
		//  テクスチャマッピング
	//  ➀テクスチャを用意
	//  ②頂点にUV設定
	//  ③デバイスにテクスチャを指定する
	//  ④ポリゴン描く
		hr[i]= D3DXCreateTextureFromFile(g_pDevice, g_TextureData[i].filename, &g_TextureData[i].pTexture);
		//                                               exeファイルからの相対パス又は絶対パス
		//絶対パス C:Application\MyApp\Accet\Texture\gazo.png
		//相対パス Accet\Texture\gazo.png
		if (FAILED(hr[i])) {
			MessageBox(hWnd, "テクスチャーを読み込む失敗", "エラー", MB_OKCANCEL | MB_DEFBUTTON2);
			return -1;
		}
		//画像形式 jpg bmp 半透明ダメ
		//         tga 
		//         png おすすめ 
		//         dds メモリー内圧縮可

	}
	return error_count;
}

void Texture_Destroy(int texIds[], int count)
{
	for (int i = 0; i < count; i++)
	{
		if (g_TextureData[texIds[i]].pTexture != NULL)
		{
			g_TextureData[texIds[i]].pTexture->Release();
			g_TextureData[texIds[i]].pTexture = NULL;
			g_TextureData[texIds[i]].filename[0] = 0;
			g_TextureData[texIds[i]].width = 0;
			g_TextureData[texIds[i]].height = 0;
		}
	}
}

void Texture_Destroy(void)
{
	for (int i = 0; i < TEXTUREDATA_MAX; i++)
	{
		if (g_TextureData[i].pTexture != NULL)
		{
			g_TextureData[i].pTexture->Release();
			g_TextureData[i].pTexture = NULL;
			g_TextureData[i].filename[0] = 0;
			g_TextureData[i].width = 0;
			g_TextureData[i].height = 0;
		}
	}
}


LPDIRECT3DTEXTURE9 Texture_GetTexture(int id)
{
	return g_TextureData[id].pTexture;
}

int Texture_GetWidth(int id)
{
	return g_TextureData[id].width;
}

int Texture_GetHeight(int id)
{
	return g_TextureData[id].height;
}

#ifndef _TEXTURE_H_	// ２重インクルード防止のマクロ定義
#define _TEXTURE_H_

#include <d3d9.h>
#include <windows.h>

#define FILENAME_MAX (128)
#define TEXTUREDATA_MAX (128)

typedef struct TextureData_tag
{
	char filename[FILENAME_MAX];
	int width;
	int height;
	LPDIRECT3DTEXTURE9 pTexture;
}TextureData;




int Texture_SetLoadFile(const char* pFilename, int width, int height);//読み込むテクスチャを予約    -1
//↑戻り値は予約番号　　　　　　　　　　　　　　　　幅　　　　　高さ
int Texture_Load(HWND hWnd);//ファイルの読み込み
//↑戻り値は読み込めなかった数
LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);//予約番号
void Texture_Destroy(int texIds[], int count);//テクスチャを部分解放　　　1個　idi
//                       解放したいidが入った配列の先頭アドレス；配列数
void Texture_Destroy(void);//全部解放
int Texture_GetWidth(int id);
int Texture_GetHeight(int id);

#endif


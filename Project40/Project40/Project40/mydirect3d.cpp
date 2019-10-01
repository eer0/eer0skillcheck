/*======================================================================================================
		windowsの表示  [mydirect3d.cpp]
																					Author:コ　笠
																					Date:2019/6/5
--------------------------------------------------------------------------------------------------------

======================================================================================================*/

#include <d3d9.h>
#include <windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "debug_font.h"
#include "input.h"

/*------------------------------------------------------------------------------------------------------
   グローバル変数
------------------------------------------------------------------------------------------------------*/
static LPDIRECT3D9 g_pD3D = NULL;
static LPDIRECT3DDEVICE9 g_pDevice = NULL;

bool MyDirect3D_Init(HWND hWnd)
{
	g_pD3D = Direct3DCreate9(D3D_SDK_VERSION);//Direct3Dインターフェースの取得
	if (g_pD3D == NULL)
	{
		MessageBox(hWnd, "g_pD3DはNULL", "エラー", MB_OKCANCEL | MB_ICONWARNING | MB_DEFBUTTON2);
		return false;
	}
	D3DPRESENT_PARAMETERS d3dpp = {};
	d3dpp.BackBufferWidth = SCREEN_WIDTH;
	d3dpp.BackBufferHeight = SCREEN_HEIGHT;
	d3dpp.BackBufferFormat = D3DFMT_UNKNOWN;
	d3dpp.BackBufferCount = 1;
	d3dpp.SwapEffect = D3DSWAPEFFECT_DISCARD;
	d3dpp.Windowed = TRUE;  //full screen時　Windowed = FALSE;
	d3dpp.EnableAutoDepthStencil = TRUE;//深度バッファ・ステンシルバッファを有効にする
	d3dpp.AutoDepthStencilFormat = D3DFMT_D16;//tex 16ビット    D24S8
	d3dpp.FullScreen_RefreshRateInHz = D3DPRESENT_RATE_DEFAULT;//更新速度の設定
	d3dpp.PresentationInterval = D3DPRESENT_INTERVAL_IMMEDIATE;//   IMMEDIATE　即時

	HRESULT hr = g_pD3D->CreateDevice(D3DADAPTER_DEFAULT, D3DDEVTYPE_HAL, hWnd, D3DCREATE_HARDWARE_VERTEXPROCESSING, &d3dpp, &g_pDevice);
	//                                                                   対象のウィンドウハンドル
	if (FAILED(hr))
	{
		MessageBox(hWnd, "CreateDevice失敗", "エラー", MB_OKCANCEL | MB_DEFBUTTON2);
		return false;
	}

	// デバックフォントモジュールの初期化
	DebugFont_Initialize();



	return true;
}



void MyDirect3D_Uninit(void)
{
	//後片付け  Direct3Dインターフェース　　　Direct3Dデバイス
	if (g_pDevice != NULL)
	{
		g_pDevice->Release();
		g_pDevice = NULL;
	}

	if (g_pD3D != NULL)
	{
		g_pD3D->Release();
		g_pD3D = NULL;
	}
	// デバックフォントモジュールの終了処理
	DebugFont_Finalize();
	Keyboard_Finalize();
}

LPDIRECT3DDEVICE9 GetDevice(void)
{
	return g_pDevice;
}


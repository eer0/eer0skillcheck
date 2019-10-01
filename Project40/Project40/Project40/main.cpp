/*======================================================================================================
		windowsの表示  [main.cpp]
																					Author:陳 昊
																					Date:2019/9/18
--------------------------------------------------------------------------------------------------------

======================================================================================================*/

#include <windows.h>
#include "common.h"
#include "mydirect3d.h"
#include "texture.h"
//ライブラリ　リンクする
#include <d3d9.h>
#include <d3dx9.h>
#include "sprite.h"
#include "system_timer.h"
#include "debug_font.h"
#include "patternanimation.h"
#include "input.h"
#include "Game.h"
#include "sound.h"
#include "Debug.h"
#include "title.h"
#include "fade.h"
#include "result.h"



#pragma comment(lib,"d3d9.lib")
#if defined(DEBUG)||defined(_DEBUG)
#pragma comment(lib,"d3dx9d.lib")
#else
#pragma comment(lib,"d3dx9.lib")
#endif

/*------------------------------------------------------------------------------------------------------
	定数定義

------------------------------------------------------------------------------------------------------*/

#define CLASS_NAME       "GameWindow"
#define WINDOW_CAPTION   "ウインドウ表示処理"
#define r ((unsigned int)100)  //半径
#define pc ((unsigned int)(r * 2 * D3DX_PI))   //点の数
#define r1 ((unsigned int)10)  //半径
#define pc1 ((unsigned int)(r1 * 2 * D3DX_PI))   //点の数
#define FPS_MEASUREMENT_TIME (1.0)





/*------------------------------------------------------------------------------------------------------
   プロトタイプ宣言
------------------------------------------------------------------------------------------------------*/
LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam);
static bool Init(HWND hWnd);
static void Uninit(void);
static void Update(void);
static void Draw(void);

/*------------------------------------------------------------------------------------------------------
   グローバル変数
------------------------------------------------------------------------------------------------------*/

HWND hWnd = NULL;
static float box_x = 0.0f;
static float boxx = 0.0f;
static float r_r = 0.0f;
static float ra = D3DX_PI * 2 / pc;//ラジアン
static float ra1 = D3DX_PI * 2 / pc1;//ラジアン
static int k = 0;
LPDIRECT3DTEXTURE9 g_pTexture[4] = {};
static SCENE g_Scene = SCENE_TITLE;
static bool flag = false;
static int flame = 0;
static int framecount1 = 0;
static float count = 0;
static int tex[4] = {};
static int g_FrameCount = 0;          //フレームカウンター
static int g_FPSBaseFrameCount = 0;   //FPS計測の基となるフレームカウンター
static double g_FPSBaseTime = 0.0;    //FPS計測の基となる時間
static double g_StaticFrameTime = 0.0;//フレーム固定用計測時間
static float g_FPS = 0.0f;            //FPS
static float yido = 0.0f;
static float yido1 = 0.0f;
static float maru = 0.0f;
static float henka = 1.0f;
static bool isright = true;
static float maru_speed = 0.0f;

/*------------------------------------------------------------------------------------------------------
   メイン

------------------------------------------------------------------------------------------------------*/

int APIENTRY WinMain(HINSTANCE hInstance, HINSTANCE hPrevInstance, LPSTR lpCmdLine, int nCmdShow)
{
	UNREFERENCED_PARAMETER(hPrevInstance);
	UNREFERENCED_PARAMETER(lpCmdLine);



	WNDCLASS wc = {};
	wc.lpfnWndProc = WndProc;
	wc.lpszClassName = CLASS_NAME;
	wc.hInstance = hInstance;
	wc.hCursor = LoadCursor(NULL, IDC_ARROW);
	wc.hbrBackground = (HBRUSH)(COLOR_BACKGROUND + 1);

	RegisterClass(&wc);

	DWORD window_style = WS_OVERLAPPEDWINDOW ^ (WS_THICKFRAME | WS_MAXIMIZEBOX);

	RECT window_rect = { 0,0,SCREEN_WIDTH,SCREEN_HEIGHT };
	AdjustWindowRect(&window_rect, window_style, FALSE);

	int window_width = window_rect.right - window_rect.left;
	int window_height = window_rect.bottom - window_rect.top;

	//プライマリモニターの画面解像度の取得
	int desktop_width = GetSystemMetrics(SM_CXSCREEN);
	int desktop_height = GetSystemMetrics(SM_CYSCREEN);

	//真中にウインドウを表示

	int window_x = max((desktop_width - window_width) / 2, 0);
	int window_y = max((desktop_height - window_height) / 2, 0);



	hWnd = CreateWindow(
		CLASS_NAME,
		WINDOW_CAPTION,
		window_style,
		window_x,
		window_y,
		window_width,
		window_height,
		NULL,
		NULL,
		hInstance,
		NULL
	);

	ShowWindow(hWnd, nCmdShow);
	UpdateWindow(hWnd);
	Keyboard_Initialize( hInstance, hWnd);


	MSG msg = {};

	if (!Init(hWnd))
	{
		return -1;
	}

	while (WM_QUIT != msg.message) {
		if (PeekMessage(&msg, NULL, 0, 0, PM_REMOVE)) {
			TranslateMessage(&msg);
			DispatchMessage(&msg);
		}
		else 
		{
			double time = SystemTimer_GetTime();
			if (time - g_StaticFrameTime < 1.0 / 60.0)
			{
				Sleep(0);
			}
			else
			{
				g_StaticFrameTime = time;
				Update();
				Draw();
			}
		}
	}
	Uninit();

	return(int)msg.wParam;
}


LRESULT CALLBACK WndProc(HWND hWnd, UINT uMsg, WPARAM wParam, LPARAM lParam)
{
	switch (uMsg) {
	case WM_KEYDOWN:
		if (wParam == VK_ESCAPE) {
			SendMessage(hWnd, WM_CLOSE, 0, 0);
		}
		break;

	case WM_CLOSE:
		if (MessageBox(hWnd, "本当に終了してよろしいでしょうか？", "確認", MB_OKCANCEL | MB_DEFBUTTON2) == IDOK) {
			DestroyWindow(hWnd);
		}
		return 0;

	case WM_DESTROY:
		PostQuitMessage(0);
		return 0;
	};

	return DefWindowProc(hWnd, uMsg, wParam, lParam);
}

bool Init(HWND hWnd)//初期化
{
	
	//PatternAnim_Init();
	
	InitSound(hWnd);
	MyDirect3D_Init(hWnd);
	Debug_Init();
	Sprite_Init();
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	InitTitle();
	
	Game_Init();
	//InitFade();
	InitResult();
	Fade_Init();
	//tex[1] = Texture_SetLoadFile("Accet\\texture\\airou.png", 512, 512);
	//tex[2] = Texture_SetLoadFile("Accet\\texture\\spice_and_wolf.png", 512, 512);
	
	if (Texture_Load(hWnd) < 0) {
		return false;
	}
	
	//システムタイマーの初期化
	SystemTimer_Initialize();
	//システムタイマーの起動
	SystemTimer_Start();
	//FPS計測用変数群の初期化
	g_FrameCount = g_FPSBaseFrameCount = 0;
	g_FPS = 0.0f;
	g_FPSBaseTime = SystemTimer_GetTime();
	g_StaticFrameTime = g_FPSBaseTime;
	

	return true;
}

void Uninit(void)//終了処理
{
	Debug_Uninit();
	MyDirect3D_Uninit();
	Sprite_UnInit();
	Game_UnInit();
	UninitSound();
	UninitTitle();
	//UninitFade();
	UninitResult();
}


bool flag1 = false;
void Update(void)//更新
{
	Keyboard_Update();
	
	
	//フレームカウントの更新
	g_FrameCount++;
	//現在のシステム時間の取得
	double time = SystemTimer_GetTime();
	
	

	switch (g_Scene)
	{
	case SCENE_TITLE:
		UpdateTitle();
		//UpdateFade();
		break;
	case SCENE_GAME:
		Game_Update();
		//UpdateFade();
		break;
	case SCENE_RESULT:
		UpdateResult();
		//UpdateFade();
		break;
	}
	Fade_Update();


	//前回のFPS計測時間から規定時間経っていたFPS計測
	if (time - g_FPSBaseTime >= FPS_MEASUREMENT_TIME)
	{
		//FPSの計算（前回からの経過フレーム/経過時間）
		g_FPS = (float)((g_FrameCount - g_FPSBaseFrameCount) / (time - g_FPSBaseTime));
		//FPS計測の基になる変数を更新
		g_FPSBaseFrameCount = g_FrameCount;
		g_FPSBaseTime = time;

	}


	if (flame % 2 == 0)
	{
		if (!flag1)
		{
			boxx += 0.05f;
		}
		if (flag1&&boxx > 1.0f)
		{
			boxx -= 0.05f;
		}
		if (flag1&&boxx <= 1.0f&&boxx > 0.5f)
		{
			boxx -= 0.05f;
		}
		if (boxx > 6.0f)
		{
			flag1 = true;
		}
		if (boxx <= 0.5f)
		{
			flag1 = false;
		}
	}

	box_x += 0.03f;
	framecount1 += 1;
	count += 1;
	flame += 1;
	if (flame % 60 == 0)
	{
		k += 1;
	}

	//キー入力の更新
	
	/*if (Keyboard_IsPress(DIK_A)) 
	{
		yido += 2.0f; 
		isright = false;
	}
	if (Keyboard_IsPress(DIK_D))
	{
		yido -= 2.0f;
		isright = true;
	}
	if (Keyboard_IsPress(DIK_W))
	{
		yido1 -= 2.0f;
	}
	if (Keyboard_IsPress(DIK_S))
	{
		yido1 += 2.0f;
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
	*/

}


void Draw(void)//描画
{
	
	//画面をクリア
	LPDIRECT3DDEVICE9 g_pDevice = GetDevice();
	g_pDevice->Clear(0, NULL, D3DCLEAR_TARGET | D3DCLEAR_ZBUFFER, D3DCOLOR_RGBA(255, 255, 255, 255), 1.0f, 0);
	g_pDevice->BeginScene();
	Debug_Begin();
	
	//FPS表示
	//DebugFont_Draw(100,100,"%f",g_FPS);
	//PatternAnim_Draw(SCREEN_WIDTH / 2-300- yido, SCREEN_HEIGHT / 2-200+yido1, framecount1, 0.2*maru, SCREEN_WIDTH / 2 - 300 - yido, SCREEN_HEIGHT / 2 - 200 + yido1, henka, henka, henka,isright);
	//Sprite_Draw1(tex[0], SCREEN_WIDTH/2, SCREEN_HEIGHT/2,128,0,128,256);
	//Sprite_Draw2(tex[1], SCREEN_WIDTH / 2+200, SCREEN_HEIGHT / 2, 256, 0, 256, 512);
	//Sprite_Draw(tex[2], SCREEN_WIDTH / 2 - yido, SCREEN_HEIGHT / 2 + yido1, 128, 128, 128, 128, 0.2*maru, SCREEN_WIDTH / 2 - yido, SCREEN_HEIGHT / 2 + yido1, henka, henka, henka, isright);
	//Sprite_Draw(tex[0], SCREEN_WIDTH / 2-300, SCREEN_HEIGHT / 2, 128, 128, 128, 128, 0.01*boxx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);
	//Sprite_Draw(tex[1], SCREEN_WIDTH / 2+300, SCREEN_HEIGHT / 2, 128, 128, 128, 128, 0.01*boxx, SCREEN_WIDTH / 2, SCREEN_HEIGHT / 2);


	g_pDevice->SetSamplerState(0, D3DSAMP_MINFILTER, D3DTEXF_LINEAR);  //縮小の時
	g_pDevice->SetSamplerState(0, D3DSAMP_MAGFILTER, D3DTEXF_LINEAR);  //拡大のとき
	g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_LINEAR);  //D3DTEXF_NONE:使わない
	//g_pDevice->SetSamplerState(0, D3DSAMP_MIPFILTER, D3DTEXF_ANISOTROPIC); 3Dに関する
	//g_pDevice->SetSamplerState(0, D3DSAMP_MAXANISOTROPY, D3DTEXF_LINEAR); 16 8 4 2
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSU, D3DTADDRESS_WRAP);//重畳　　clamp 挟まる
	g_pDevice->SetSamplerState(0, D3DSAMP_ADDRESSV, D3DTADDRESS_WRAP);
	g_pDevice->SetSamplerState(0, D3DSAMP_BORDERCOLOR, D3DCOLOR_RGBA(255, 255, 255, 255));
	//αブレンド
	g_pDevice->SetRenderState(D3DRS_ALPHABLENDENABLE, TRUE);//αブレンド有効にする
	//今から描画するRGB×今から描画するα+画面のRGB×（１－今から描画するα）  値は１～０
	g_pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);//SRC＝今から
	g_pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);//テクスチャ背景透明する
	//頂点カラーとテクスチャのブレンド
	g_pDevice->SetTextureStageState(0, D3DTSS_ALPHAOP, D3DTOP_MODULATE);//かけ算  D3DTOP=D3DTEXTUREOP
	
	switch (g_Scene)
	{
	case SCENE_TITLE:

		DrawTitle();
		//DrawFade();
		break;
	case SCENE_GAME:
		Game_Draw();
		//DrawFade();
		break;
	case SCENE_RESULT:

		DrawResult();
		//DrawFade();
		break;
	}
	Fade_Draw();

	Debug_End();
	g_pDevice->EndScene();
	g_pDevice->Present(NULL, NULL, NULL, NULL);
}

//テクスチャとポリゴンの関係
//サンプラー
//フィルタリング　－＞デフォルト：ポイントサンプリング
//                                リニアサンプリング


void SetScene(SCENE scene)
{
	switch (g_Scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:UninitTitle();
		break;
	case SCENE_GAME:Game_UnInit();
		break;
	case SCENE_RESULT:UninitResult();
		break;
	}
	g_Scene = scene;
	switch (scene)
	{
	case SCENE_NONE:
		break;
	case SCENE_TITLE:InitTitle();
		break;
	case SCENE_GAME:Game_Init();
		break;
	case SCENE_RESULT:InitResult();
		break;
	}
}

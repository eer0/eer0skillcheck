#include "Debug.h"
#include "collision.h"
#include "mydirect3d.h"


/*------------------------------------------------------------------------------------------------------
定数定義

------------------------------------------------------------------------------------------------------*/
#define DEBUG_CIRCLE_VERTEX_NUM (8)
#define DEBUG_CIRCLE_MAX (4096)

/*------------------------------------------------------------------------------------------------------
構造体

------------------------------------------------------------------------------------------------------*/
typedef struct DebugCircleVetex_tag
{
	D3DXVECTOR4 position;
	D3DCOLOR color;
}DebugCircleVetex;

#define FVF_DEBUG_CIRCLE_VERTEX (D3DFVF_XYZRHW|D3DFVF_DIFFUSE)

/*------------------------------------------------------------------------------------------------------
グローバル変数

------------------------------------------------------------------------------------------------------*/
static LPDIRECT3DVERTEXBUFFER9 g_pVertexBuffer = NULL;
static LPDIRECT3DINDEXBUFFER9 g_pIndexBuffer = NULL;
static Circle g_Circles[DEBUG_CIRCLE_MAX];
static int g_CircleCount = 0;
static const float A = D3DX_PI * 2.0f / DEBUG_CIRCLE_VERTEX_NUM;
static D3DCOLOR g_color = 0xFFFFFFFF;
static D3DCOLOR g_colors[DEBUG_CIRCLE_MAX];
LPDIRECT3DDEVICE9 pDevice;




void Debug_Init(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	pDevice = GetDevice();
	pDevice->CreateVertexBuffer(DEBUG_CIRCLE_VERTEX_NUM * DEBUG_CIRCLE_MAX * sizeof(DebugCircleVetex), D3DUSAGE_WRITEONLY, FVF_DEBUG_CIRCLE_VERTEX, D3DPOOL_MANAGED, &g_pVertexBuffer, NULL);
	pDevice->CreateIndexBuffer(DEBUG_CIRCLE_VERTEX_NUM * 2 * DEBUG_CIRCLE_MAX * sizeof(WORD), D3DUSAGE_WRITEONLY, D3DFMT_INDEX16, D3DPOOL_MANAGED, &g_pIndexBuffer, NULL);
#endif // _DEBUG || DEBUG
}

void Debug_Uninit(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	if (g_pVertexBuffer)
	{
		g_pVertexBuffer->Release();
		g_pVertexBuffer = NULL;
	}
	if (g_pIndexBuffer)
	{
		g_pIndexBuffer->Release();
		g_pIndexBuffer = NULL;
	}
#endif // _DEBUG || DEBUG
}

void Debug_Begin(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	
	g_CircleCount = 0;
#endif // _DEBUG || DEBUG
}

void Debug_End(void)
{
#if defined(_DEBUG) || defined(DEBUG)
	//終了（実は描く）
	DebugCircleVetex * pv;
	g_pVertexBuffer->Lock(0, 0, (void**)&pv, D3DLOCK_DISCARD);
	for (int i = 0; i < g_CircleCount; i++)
	{
		int startIndex = i * DEBUG_CIRCLE_VERTEX_NUM;

		for (int j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++)
		{
			pv[startIndex + j].position.x = cosf(A*j)*g_Circles[i].radius + g_Circles[i].position.x;
			pv[startIndex + j].position.y = sinf(A*j)*g_Circles[i].radius + g_Circles[i].position.y;
			pv[startIndex + j].position.z = 0.0f;
			pv[startIndex + j].position.w = 1.0f;
			pv[startIndex + j].color = g_colors[i];
		}
	}
	g_pVertexBuffer->Unlock();

	WORD * pI;
	g_pIndexBuffer->Lock(0, 0, (void**)&pI, D3DLOCK_DISCARD);
	for (int i = 0; i < g_CircleCount; i++)
	{
		int startIndex = i * DEBUG_CIRCLE_VERTEX_NUM * 2;

		for (int j = 0; j < DEBUG_CIRCLE_VERTEX_NUM; j++)
		{
			pI[startIndex + j * 2 + 0] = i * DEBUG_CIRCLE_VERTEX_NUM + j;
			pI[startIndex + j * 2 + 1] = i * DEBUG_CIRCLE_VERTEX_NUM + ((j + 1) % DEBUG_CIRCLE_VERTEX_NUM);

		}
	}
	g_pIndexBuffer->Unlock();
	pDevice->SetStreamSource(0, g_pVertexBuffer, 0, sizeof(DebugCircleVetex));
	pDevice->SetIndices(g_pIndexBuffer);
	pDevice->SetFVF(FVF_DEBUG_CIRCLE_VERTEX);
	pDevice->SetTexture(0, NULL);
	pDevice->DrawIndexedPrimitive(D3DPT_LINELIST, 0, 0, g_CircleCount * DEBUG_CIRCLE_VERTEX_NUM, 0, g_CircleCount * DEBUG_CIRCLE_VERTEX_NUM);
#endif // _DEBUG || DEBUG
}

void Debug_DrawCircle(float x, float y, float radius)
{
#if defined(_DEBUG) || defined(DEBUG)
	
	g_colors[g_CircleCount] = g_color;
	g_Circles[g_CircleCount].position.x = x;
	g_Circles[g_CircleCount].position.y = y;
	g_Circles[g_CircleCount].radius = radius;
	g_CircleCount++;
#endif // _DEBUG || DEBUG
}

void Debug_SetColor(D3DCOLOR color)
{
#if defined(_DEBUG) || defined(DEBUG)
	g_color = color;
#endif // _DEBUG || DEBUG
}
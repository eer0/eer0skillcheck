#include "effect.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "texture.h"
#include "sprite.h"
#include "mydirect3d.h"


//�O���[�o���ϐ�
static int tex_effect;
static effect g_effect[effect_MAX];
static int g_EffectFrameCount = 0;


void effect_Init()
{
	for (int i = 0; i < effect_MAX; i++)
	{
		g_effect[i].lifeFrame = 0;
		g_effect[i].spawnFrame = -1;
		//���W�̏�����
	
	}
	g_EffectFrameCount = 0;
	//�e�N�X�`��
	tex_effect = Texture_SetLoadFile("Accet\\texture\\effect000.jpg", 40, 40);
}

void effect_Update()
{
	
	//�A�j���[�V�����̍X�V(�t���O��on������)
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
			//���͊e�F�����Ə�Z�����
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
	// �����_�[�X�e�[�g(���Z��������)
    // �F = (SRC�F * SRC�A���t�@) + (DEST�F * (1.0)�A���t�@)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_ONE);		// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0)

	for (int i = 0; i < effect_MAX; i++)
	{
		//�����Ă���
		if (g_effect[i].lifeFrame > 0)
		{
			//effect��`��
			
			Sprite_Draw(tex_effect, g_effect[i].position.x, g_effect[i].position.y,g_effect[i].color);
		}
	}
	// �����_�[�X�e�[�g(�ʏ�u�����h����)
    // �F = (SRC�F * SRC�A���t�@) + (DEST�F * (1.0 - SRC)�A���t�@)
	pDevice->SetRenderState(D3DRS_BLENDOP, D3DBLENDOP_ADD);		// �u�����f�B���O����(�f�t�H���g)
	pDevice->SetRenderState(D3DRS_SRCBLEND, D3DBLEND_SRCALPHA);	// ���\�[�X�J���[�̎w��
	pDevice->SetRenderState(D3DRS_DESTBLEND, D3DBLEND_INVSRCALPHA);	// ���f�X�e�B�l�[�V�����J���[�̎w��(1.0 - SRC)

}

void effect_UnInit()
{

}

void effect_Create(float x, float y,D3DCOLOR color,int lifeFrame)//���G�t�F�N�g�̊g�嗦���������Ɨǂ�
{
	for (int i = 0; i < effect_MAX; i++)

	{
		if (g_effect[i].lifeFrame > 0)//�g���Ă���Ƃ��낾������
		{
			continue;
		}
		g_effect[i].position.x = x;
		g_effect[i].position.y = y;
		g_effect[i].lifeFrame = lifeFrame;
		g_effect[i].spawnFrame = g_EffectFrameCount;
		g_effect[i].color = color;
		//�傫��
		break;
		

	}
}
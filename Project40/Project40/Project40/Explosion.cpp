#include "Explosion.h"
#include <d3d9.h>
#include <d3dx9.h>
#include "texture.h"
#include "sprite.h"


//�O���[�o���ϐ�
static int tex_Explosion;
static Explosion g_Explosion [EXPLOSION_MAX];



void Explosion_Init() 
{
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//�t���O��off�ɂ���
		g_Explosion[i].bUse = false;
		//���W�̏�����
		g_Explosion[i].position.x = 0.0f;
		g_Explosion[i].position.y = 0.0f;
	}
	//�e�N�X�`��
	tex_Explosion = Texture_SetLoadFile("Accet\\texture\\explosion.tga", 1024, 1024);
}

void Explosion_Update()
{
	//�A�j���[�V�����̍X�V(�t���O��on������)
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		if (g_Explosion[i].bUse)
		{
			g_Explosion[i].Animationcount++;
			//�t���Ooff�i�A�j���[�V�������I�������)
			if (g_Explosion[i].Animationcount >= 16)
			{
				g_Explosion[i].bUse = false;
				g_Explosion[i].Animationcount = 0;
			}
		}
	}
	
}

void Explosion_Draw()
{
	
	for (int i = 0; i < EXPLOSION_MAX; i++)
	{
		//�t���O��on
		if (g_Explosion[i].bUse)
		{
	        //������`��
			Sprite_Draw(tex_Explosion, g_Explosion[i].position.x, g_Explosion[i].position.y, g_Explosion[i].Animationcount  % 4 * 256, g_Explosion[i].Animationcount / 4 * 256, 256, 256, 1, g_Explosion[i].position.x, g_Explosion[i].position.y, 0.3,0.3,0.3);
		}

	}
	
}

void Explosion_UnInit()
{
	
}

void Explosion_Create(float x, float y)//�����̈�ԏ��߂ɍ��W
{
	for (int i = 0; i < EXPLOSION_MAX; i++)

	{
		if (!g_Explosion[i].bUse)
		{
			g_Explosion[i].bUse = true;
			g_Explosion[i].position.x = x;
			g_Explosion[i].position.y = y;
			g_Explosion[i].Animationcount = 0;
			break;
		}
		              
	}
}
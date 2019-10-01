#ifndef _TEXTURE_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
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




int Texture_SetLoadFile(const char* pFilename, int width, int height);//�ǂݍ��ރe�N�X�`����\��    -1
//���߂�l�͗\��ԍ��@�@�@�@�@�@�@�@�@�@�@�@�@�@�@�@���@�@�@�@�@����
int Texture_Load(HWND hWnd);//�t�@�C���̓ǂݍ���
//���߂�l�͓ǂݍ��߂Ȃ�������
LPDIRECT3DTEXTURE9 Texture_GetTexture(int id);//�\��ԍ�
void Texture_Destroy(int texIds[], int count);//�e�N�X�`���𕔕�����@�@�@1�@idi
//                       ���������id���������z��̐擪�A�h���X�G�z��
void Texture_Destroy(void);//�S�����
int Texture_GetWidth(int id);
int Texture_GetHeight(int id);

#endif


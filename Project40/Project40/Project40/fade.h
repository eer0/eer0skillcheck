#ifndef _FADE_H_	// �Q�d�C���N���[�h�h�~�̃}�N����`
#define _FADE_H_



void Fade_Init();
void Fade_Uninit();
void Fade_Update();
void Fade_Draw();
void Fade_Start(int frame, D3DCOLOR color, bool bFadeOut);
bool Fade_IsFade(void);



#endif

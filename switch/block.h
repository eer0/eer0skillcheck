#pragma once
void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();
void SetBlock(float x, float y,int type);

#define BLOCK_SIZE 64.0f
#define BLOCK_MAX 100
 
//block�\����
typedef struct
{
	Float2 Position; //���W
	int Type;
	bool isUse; //�g�p�t���O
}BLOCK;

BLOCK *GetBlock(void);


#pragma once
void InitBlock();
void UninitBlock();
void UpdateBlock();
void DrawBlock();
void SetBlock(float x, float y,int type);

#define BLOCK_SIZE 64.0f
#define BLOCK_MAX 100
 
//block構造体
typedef struct
{
	Float2 Position; //座標
	int Type;
	bool isUse; //使用フラグ
}BLOCK;

BLOCK *GetBlock(void);


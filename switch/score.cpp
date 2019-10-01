#include "main.h"
#include "texture.h"
#include "sprite.h"
#include"score.h"

#define SCORE_FIGURE 6

//ÉOÉçÅ[ÉoÉãä÷êî
int g_Score;
unsigned int g_ScoreTexture;

void InitScore()
{
	g_ScoreTexture = LoadTexture("rom:/number.tga");
	g_Score = 0;
}

void UninitScore() 
{
	UnloadTexture(g_ScoreTexture);
}

void UpdateScore()
{

}

void DrawScore()
{
	SetTexture(g_ScoreTexture);
	int score = g_Score;
	for (int i = 0; i < SCORE_FIGURE; i++)
	{
		int n;
		float fx, fy;
		n = score % 10;
		fx = (n % 5)*0.2f;
		fy = (n / 5)*0.2f;

		score /= 10;
		float sx, sy;
		sx = 600.0f + 50.0f*(SCORE_FIGURE - 1 - i);
		sy = 0.0f;
		DrawSprite(sx, sy, 80.0f, 80.0f, fx, fy, 0.2f, 0.2f, MakeFloat4(1.0f, 1.0f, 1.0f, 1.0f));

	}
}
void AddScore(int score)
{
	g_Score += score;
}
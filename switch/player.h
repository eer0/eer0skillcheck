#pragma once

// É}ÉNÉçêÈåæ
#define PLAYER_WIDTH 256.0f
#define PLAYER_HAIGHT 64.0f

typedef struct {
	unsigned int	tex;
	Float2			pos;
}PLAYER;

void InitPlayer();
void UninitPlayer();
void UpdatePlayer();
void DrawPlayer();



PLAYER *GetPlayer();
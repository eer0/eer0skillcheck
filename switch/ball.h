

// マクロ宣言
#define BALL_SIZE 64.0f
#define BALL_SP_X 3.0f
#define BALL_SP_Y 7.0f


// プロトタイプ宣言
void InitBall();
void UninitBall();
void UpdateBall();
void DrawBall();

// ボール構造体
typedef struct {
	unsigned int	tex;
	Float2			pos;
	Float2			sp;
}BALL;

BALL *GetBall(void);
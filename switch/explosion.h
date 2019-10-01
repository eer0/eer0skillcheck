#define EXPLOSION_MAX 10

typedef struct
{
	Float2 pos;
	int frame;
	bool isUse;
}EXPLOSION;

void InitExplosion();
void UninitExplosion();
void UpdateExplosion();
void DrawExplosion();
void SetExplosion(Float2 pos);

EXPLOSION *GetExplosion(void);
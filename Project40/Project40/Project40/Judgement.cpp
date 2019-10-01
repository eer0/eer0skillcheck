#include "Judgement.h"
#include "enemy.h"
#include "bullet.h"
#include "collision.h"
#include "Explosion.h"
#include "score.h"
#include "number.h"
#include "Game.h"
#include "sound.h"



static void hitCheck_Bullet_Enemy(void);
Enemy *pg_Enemy;

void Judgement_Update(void)
{
	hitCheck_Bullet_Enemy();
}

void hitCheck_Bullet_Enemy()
{
	pg_Enemy = GetEnemyPosition();
	for (int i = 0; i < BULLET_MAX; i++)
	{
		for (int j = 0; j < ENEMY_MAX; j++)
		{
			
			if (Bullet_IsUsed(i) && Enemy_IsUsed(j))
			{
				if (Circle_Circle(Bullet_GetCollision(i), Enemy_GetCollision(j)))
				{
					Enemy_Destroy(j);//すぐ壊すではなく、ライフを持ったり    得点を入れるならこのタイミング
					Addscore(1000);
					Explosion_Create((pg_Enemy+j)->position.x, (pg_Enemy + j)->position.y);
					PlaySound(SOUND_LABEL_SE_EXPLOSION);
					Bullet_Destroy(i);//やらなければ、貫通弾 

				}
			}
		}
	}
}
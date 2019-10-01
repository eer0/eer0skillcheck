#include "collision.h"
#include "enemy.h"
#include "bullet.h"

bool Circle_Circle(Circle*pA, Circle*pB)
{
	return(pA->radius + pB->radius)*(pA->radius + pB->radius) > D3DXVec2LengthSq(&(pA->position - pB->position));
	//                                                                      Å@ìÒèÊ
}
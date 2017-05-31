#include"EnemyCircle.h"

using namespace Core;

EnemyCircle::EnemyCircle(const Core::Pos &pos, Color color)
: IEnemy(pos, 300, "¡Ü", 2, color){}
EnemyCircle::~EnemyCircle(){}
void EnemyCircle::update(void)
{
	IEnemy::update();
}
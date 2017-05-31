#include"SceneField.h"

#include"Input.h"

#include"User.h"
#include"SceneSelHero.h"
#include"SceneGameOver.h"
#include"SceneClear.h"

#include<iostream>
#include<initializer_list>
#include<time.h>

using namespace Core;

#define MAPX 50
#define MAPY 35

SceneField::SceneField(int stage, int index) : m_stage(stage)
{
	m_tileMap = new TileMap(MAPX, MAPY);
	int **map = new int*[MAPY];
	for (int i = 0; i < MAPY; i++)
	{
		map[i] = new int[MAPX];
		for (int j = 0; j < MAPX; j++)
		{
			if (i % (MAPY - 1) == 0 || j % (MAPX - 1) == 0)
				map[i][j] = 1;
			else
				map[i][j] = rand() % 8 == 0 ? 2 : 0;
		}
	}
	m_tileMap->setKey(1, false, "■");
	m_tileMap->setKey(2, false, "■");
	m_tileMap->setKey(0, true, "  ");
	m_tileMap->setTiles(map);
	m_tileMap->setTile(Pos(25, 15), 0);
	m_tileMap->setTile(Pos(1, 1), 0);
	m_tileMap->setTile(Pos(1, 2), 0);
	m_tileMap->setTile(Pos(2, 1), 0);
	m_tileMap->setTile(Pos(1, MAPY - 2), 0);
	m_tileMap->setTile(Pos(1, MAPY - 3), 0);
	m_tileMap->setTile(Pos(2, MAPY - 2), 0);
	m_tileMap->setTile(Pos(MAPX - 2, 1), 0);
	m_tileMap->setTile(Pos(MAPX - 3, 1), 0);
	m_tileMap->setTile(Pos(MAPX - 2, 2), 0);
	m_tileMap->setTile(Pos(MAPX - 2, MAPY - 2), 0);
	m_tileMap->setTile(Pos(MAPX - 3, MAPY - 2), 0);
	m_tileMap->setTile(Pos(MAPX - 2, MAPY - 3), 0);

	setTextColor(BRIGHTWHITE);
	m_tileMap->render();
	setTextColor(WHITE);

	User::user = new User(Pos(25, 15), index);
	User::user->render();

	m_nextTimer = time(NULL);

	render<const char*>(Pos(2, 36), "남은 시간 : ");
	gotoxy(Pos(14, 36));
	std::cout << 60 - (time(NULL) - m_nextTimer);
	render<const char*>(Pos(40, 36), "능력 사용 가능!", LIGHTGREEN);
	render<const char*>(Pos(85, 36), "스테이지", LIGHTYELLOW);
	render<int>(Pos(94, 36), m_stage, LIGHTYELLOW);
}
SceneField::~SceneField()
{
	delete User::user;
	User::user = NULL;
	
	Enemy *iter = enemiesHead;
	while (enemiesHead != NULL)
	{
		iter = iter->next;
		delete enemiesHead;
		enemiesHead = iter;
	}
}
void SceneField::update(void)
{
	if (User::user->m_prevSkill == false && *User::user->m_skill == true)
	{
		if (User::user->m_skill == &User::user->m_theWorld)
		{
			m_nextTimer += 3;
			m_dwMakeTimer += 3000;
			for (Enemy *iter = enemiesHead; iter != NULL; iter = iter->next)
			{
				Pos pos = iter->enemy->getPos();
				pos.x *= 2;
				render<const char*>(pos, iter->enemy->getChar(), GRAY);
			}
		}
		render<const char*>(Pos(40, 36), "능력 사용 불가..", LIGHTRED);
	}
	User::user->update();
	if (User::user->m_fly == false && m_tileMap->getKey(User::user->getPos()) != 0)
	{
		changeScene(new SceneGameOver(m_stage));
		return;
	}
	if (User::user->m_theWorld)
		return;
	if (time(NULL) - m_timeRef >= 1)
	{
		gotoxy(Pos(14, 36));
		printf("%2d", 60 - (time(NULL) - m_nextTimer));
		m_timeRef = time(NULL);
	}
	// 클리어, 스테이지 변경
	if (time(NULL) - m_nextTimer >= static_cast<time_t>(60))
	{
		if (m_stage < 10)
			changeScene(new SceneSelHero(++m_stage));
		else
			changeScene(new SceneClear);
		return;
	}
	// 적 생성
	else if (GetTickCount() - m_dwMakeTimer >= static_cast<DWORD>(7000.0 / m_stage))
	{
		if (enemiesTail == NULL)
			enemiesHead = enemiesTail = new Enemy;
		else
			enemiesTail = enemiesTail->next = new Enemy;
		Pos pos;
		switch (rand() % 4)
		{
		case 0: pos.x = pos.y = 1; break;
		case 1: pos.x = 1; pos.y = MAPY - 2; break;
		case 2: pos.x = MAPX - 2; pos.y = 1; break;
		case 3: pos.x = MAPX - 2; pos.y = MAPY - 2; break;
		}
		if (m_stage >= 5)
		{
			if (rand() % static_cast<int>(40.0 / m_stage) == 0)
				enemiesTail->enemy = new EnemyMinion(pos, static_cast<Color>(rand() % 15 + 1));
			else
				enemiesTail->enemy = new EnemyCircle(pos, static_cast<Color>(rand() % 15 + 1));
		}
		else
			enemiesTail->enemy = new EnemyCircle(pos, static_cast<Color>(rand() % 15 + 1));
		m_countEnemy++;
		m_dwMakeTimer = GetTickCount();
	}

	// 업데이트, 충돌판정
	for (Enemy *iter = enemiesHead; iter != NULL; iter = iter->next)
	{
		iter->enemy->update();
		if (iter->enemy->getPos() == User::user->getPos())
		{
			changeScene(new SceneGameOver(m_stage));
			return;
		}
	}
}
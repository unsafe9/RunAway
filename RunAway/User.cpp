#include"User.h"

#include"Input.h"
#include"Scene.h"

#include"SceneField.h"

using namespace Core;

User* User::user = NULL;

User::User(const Pos &pos, int index)
: ICharacter(pos, 150, "■", 2)
{
	switch (index)
	{
	case 0: 
		m_skill = &m_dash;
		m_color = LIGHTRED;
		break;
	case 1: 
		m_skill = &m_fly;
		m_color = LIGHTSKYBLUE;
		break;
	case 2:
		m_skill = &m_theWorld;
		m_color = LIGHTPURPLE;
		break;
	}
}
User::~User(){}
time_t User::getSkillDuration(void) const
{
	return (3 - (time(NULL) - m_skillDuration));
}
bool User::movable(const Pos &pos) const
{
	if (m_fly == true && IScene::nowScene->getTileMap()->getKey(pos) == 2)
		return true;
	if (IScene::nowScene->getTileMap() != NULL)
		return (IScene::nowScene->getTileMap()->movable(pos));
	return false;
}
bool User::move(const Pos &pos)
{
	if (m_pos != pos)
	{
		int sx = m_pos.x - pos.x;
		int sy = m_pos.y - pos.y;
		int abs_sx = abs(sx);
		int abs_sy = abs(sy);
		if (abs_sx > abs_sy)
			m_dir = sx > 0 ? dir_left : dir_right;
		else
			m_dir = sy > 0 ? dir_up : dir_down;
	}
	if (movable(pos))
	{
		m_prevPos = m_pos;
		m_pos = pos;
		return true;
	}
	return false;
}
void User::update(void)
{
	// 스킬
	m_prevSkill = *m_skill;
	if (*m_skill == true && m_skillUsed == true)
	{
		if (time(NULL) - m_skillDuration >= 3)
		{
			if (m_dash == true)
				m_dwMoveSpeedMS = 150;
			*m_skill = false;
		}
		clearRect(Rect(36, 70, 92, 36));
	}
	else if (m_skillUsed == false)
	{
		if (trigger(VK_SPACE))
		{
			*m_skill = m_skillUsed = true;
			if (m_dash == true)
				m_dwMoveSpeedMS = 50;
			m_skillDuration = time(NULL);
		}
	}
	if (GetTickCount() - m_dwMoveTimer >= m_dwMoveSpeedMS)
	{
		Pos pos = m_pos;
		if (press(VK_UP))			pos.y--; // 상
		else if (press(VK_DOWN))	pos.y++; // 하
		else if (press(VK_LEFT))	pos.x--; // 좌
		else if (press(VK_RIGHT))	pos.x++; // 우
		else return;
		if (movable(pos))
		{
			if (IScene::nowScene->getTileMap()->getKey(m_pos) == 2)
			{
				setTextColor(BRIGHTWHITE);
				IScene::nowScene->getTileMap()->render(m_pos);
				setTextColor(WHITE);
			}
			else
				clear();
			move(pos);
			render();
			m_dwMoveTimer = GetTickCount();
		}
	}
}
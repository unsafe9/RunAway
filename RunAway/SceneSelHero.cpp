#include"SceneSelHero.h"

#include"Console.h"
#include"Input.h"
#include"resource.h"

#include"User.h"
#include"SceneField.h"

#include<iostream>

using namespace Core;

#define drawCharacter(index)\
	draw(Pos(41, 2), 201 + (index), "■", 2)
#define drawLeft(color)\
	render<const char*>(Pos(33, 11), "◀", color)
#define drawRight(color)\
	render<const char*>(Pos(65, 11), "▶", color)

SceneSelHero::SceneSelHero(int stage) : m_stage(stage)
{
	m_nowIndex = 0;
	system("cls");
	render<const char*>(Pos(2, 1), "┌────────┐", LIGHTYELLOW);
	render<const char*>(Pos(2, 2), "│                │", LIGHTYELLOW);
	render<const char*>(Pos(2, 3), "└────────┘", LIGHTYELLOW);
	render<const char*>(Pos(7, 2), "스테이지", BRIGHTWHITE);
	render<int>(Pos(16, 2), stage, BRIGHTWHITE);

	drawLeft(WHITE); drawRight(WHITE);
	drawCharacter(m_nowIndex);
	render(Pos(15, 25), "능력 : 이동속도가 빨라진다.(지속 3초)");

	render<const char*>(Pos(15, 29), "설명 :");
	render<const char*>(Pos(17, 30), "- 스킬은 한 스테이지당 한번만 사용 가능합니다.");
	render<const char*>(Pos(17, 31), "- 60초동안 적을 피해다녀 살아남으면 다음 스테이지로 넘어갑니다.");
	render<const char*>(Pos(15, 33), "조작 :");
	render<const char*>(Pos(17, 34), "스페이스바 - 선택, 능력 사용");
	render<const char*>(Pos(17, 35), "방향키     - 이동");
}
SceneSelHero::~SceneSelHero(){}
void SceneSelHero::update(void)
{
	if (trigger(VK_LEFT))
		drawLeft(LIGHTRED);
	if (trigger(VK_RIGHT))
		drawRight(LIGHTRED);
	if (release(VK_LEFT))
		drawLeft(WHITE);
	if (release(VK_RIGHT))
		drawRight(WHITE);

	if (repeat(VK_LEFT) || repeat(VK_RIGHT))
	{
		m_nowIndex = (m_nowIndex + 1) % 3;
		drawCharacter(m_nowIndex);
		clearRect(Rect(26, 15, 100, 25));
		switch (m_nowIndex)
		{
		case 0:
			render<const char*>(Pos(15, 25), "능력 : 이동속도가 빨라진다.(지속 3초)");
			break;
		case 1:
			render<const char*>(Pos(15, 25), "능력 : 날아다닌다. 블럭을 무시하지만 적과 충돌되면 죽는다.");
			render<const char*>(Pos(22, 26), "능력 지속시간이 끝났을 때 벽 위에 있을시 죽는다.(지속 3초)");
			break;
		case 2:
			render<const char*>(Pos(15, 25), "능력 : 시간을 멈추고 혼자 움직인다.");
			render<const char*>(Pos(22, 26), "멈춰진 시간속에서도 적과 충돌시 죽는다.(지속 3초)");
			break;
		}
	}
	else if (trigger(VK_SPACE))
		changeScene(new SceneField(m_stage, m_nowIndex));
}
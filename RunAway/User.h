#ifndef _USER_H_
#define _USER_H_

#include"Character.h"

#include"Console.h"

#include<time.h>

class User : public ICharacter
{
public:
	User(const Core::Pos &pos, int index);
	virtual ~User();

public:
	virtual void update(void);

public:
	static User *user;
	
	bool movable(const Core::Pos &pos) const;
	bool move(const Core::Pos &pos);

	time_t getSkillDuration(void) const;

public:
	bool m_theWorld = false;
	bool m_dash = false;
	bool m_fly = false;
	bool m_prevSkill = false;
	bool *m_skill = NULL;

private:
	bool m_skillUsed = false;
	time_t m_skillDuration;

};

#endif
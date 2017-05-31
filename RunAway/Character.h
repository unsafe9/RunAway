#ifndef _CHARACTER_H_
#define _CHARACTER_H_

#include"Object.h"
#include"Def.h"
#include"Console.h"

typedef class ICharacter : public IObject
{
public:
	ICharacter(const Core::Pos &pos, DWORD dwMoveSpeedMS, char *myChar, int space, Core::Color color = Core::Color::WHITE);
	virtual ~ICharacter() = 0;

public:
	void clear(void) const;
	void render(void) const;

	bool movable(const Core::Pos &pos) const;
	bool move(const Core::Pos &pos);
	bool moveToward(const Core::Pos &pos);
	bool moveForward(void);
	bool moveBackward(void);
	bool moveRandom(void);

	Core::Direction getDirection(void) const;
	Core::Pos getPrevPos(void) const;
	int getSpace(void) const;
	const char* getChar(void) const;

	virtual void update(void) = 0;

protected:
	const int m_space = 2;
	const char *m_myChar = "";

	Core::Pos m_prevPos;
	Core::Color m_color;
	Core::Direction m_dir = Core::Direction::dir_stop;
	DWORD m_dwMoveSpeedMS;
	DWORD m_dwMoveTimer = 0;

}*PCHARACTER;

#endif
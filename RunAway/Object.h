#ifndef _OBJECT_H_
#define _OBJECT_H_

#include"Def.h"

typedef class IObject
{
public:
	IObject(void){}
	virtual ~IObject() = 0{};

public:
	inline Core::Pos getPos(void) const
	{
		return m_pos;
	}

protected:
	Core::Pos m_pos;

}*POBJECT;


#endif
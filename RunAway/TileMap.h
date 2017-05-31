#ifndef _TILEMAP_H_
#define _TILEMAP_H_

#include"Def.h"

typedef class TileMap
{
public:
	TileMap(int Xsize, int Ysize);
	~TileMap();

public:
	void setKey(int key, bool bMovable, char *pszCh);
	Core::RESULT setKeyMovable(int key, bool bMovable);
	Core::RESULT setKeyChar(int key, char *pszCh);
	Core::RESULT setTile(const Core::Pos &pos, int key);
	void setTiles(int **intMap);

	int getKey(const Core::Pos &pos) const;
	int getXsize(void) const;
	int getYsize(void) const;

	bool movable(const Core::Pos &pos) const;

	void render(bool bClearScreen = true) const;
	void render(const Core::Pos &pos) const;
	void render(const Core::Rect &rect) const;

	// Core::RESULT save(const char *pFileName);
	// Core::RESULT load(const char *pFileName);

private:
	const int m_Xsize;
	const int m_Ysize;

	int	 **m_intMap	= NULL;
	struct KeyList
	{
		int  key		= 0;
		bool bMovable	= true;
		char *pszCh		= NULL;
		KeyList *next	= NULL;
	}*m_keyList = NULL, *m_keyListTail = NULL;

private:
	KeyList* searchListFromKey(int key) const;

}*PTILEMAP;

#endif
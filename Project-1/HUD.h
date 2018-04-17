#ifndef HUD_H
#define HUD_H
#include "Text.h"

enum Element
{
	Lives, Score, HighestScore
};

class HUD
{
private:
	Text* _lives = nullptr;
	Text* _score = nullptr;
	Text* _paused = nullptr;
	Text* _gameOver = nullptr;
	Text* _highestScore = nullptr;
	Text* _credits = nullptr;
	Text* _escape = nullptr;
	Text* _restart = nullptr;
	
public:
	HUD();
	~HUD();
	void updateHUD(Element element, int number);
	void draw(bool isPaused, bool isGameOver) const;
};

#endif

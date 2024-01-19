#pragma once
#include "cocos2d.h"

using namespace std;

#define SizePipe Vec2(120,120)

enum class TypePipe
{
	Pipe1 = 1,
	Pipe2,
	Pipe3,
	Pipe4,
	Pipe5,
	Pipe6,
	Pipe7,
	Pipe8,
	Pipe9,
	Pipe10,
	Pipe11,
	Pipe12,

	PlumpingLeft = 20,
	PlumpingRight,
	PlumpingTop,
	PlumpingBottom,
};

enum class TypeDirection
{
	Left,
	Right,
	Top,
	Bottom
};


class Constant 
{
public:
	//Name Animation
	static const string fishNameAnimation;
	static const string effectPop;
};

struct MyCustomScoreUI : public cocos2d::EventCustom {
	int score;
	MyCustomScoreUI(const std::string& eventName, int score)
		: cocos2d::EventCustom(eventName), score(score) {}
};


#pragma once
#include "cocos2d.h"
#include "Constant.h"
#include "spine/SkeletonAnimation.h"

using namespace cocos2d;
using namespace std;

class Particle : public Node
{
public:
	static Particle* create();

	virtual bool init();

	void CreateEffectMushRoomTime(Node* node, Vec2 position);
	void CreateEffectMushRoomAim(Node* node, Vec2 position, float scale);
	void CreateEffectMushRoomExplode(Node* node, Vec2 position);
	void CreateEffectHit(Node* node, Vec2 position);
	void CreateEffectLight(Vec2 position);
};
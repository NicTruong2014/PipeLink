#pragma once
#include "cocos2d.h"
#include "Constant.h"
#include "spine/SkeletonAnimation.h"

using namespace cocos2d;
using namespace std;

class Entity : public Node
{
public:
	static Entity* createEntity();
	virtual bool init();
	virtual Rect GetBoundingBox() { return Rect(); }
	virtual void HitLand(){};
	virtual void CustomPause(){}

	virtual void SetLocationSpawn(Vec2 location) {};
	virtual TypePipe GetTypePipe(){ return TypePipe::Pipe1; }

	virtual Vec2 GetLocationMatrix() { return Vec2::ZERO; }
	virtual void SetLocationMatrix(Vec2 value) { }

	virtual bool GetVisited() { return false; }
	virtual void SetVisied(bool value) { }

	virtual bool GetNeibour() { return false; }
	virtual void SetNeibour(bool value) {};

	virtual void SetDirections(TypePipe value){}
	virtual std::vector<TypeDirection> GetDirections() { return std::vector<TypeDirection>(); }
	
	virtual void SetFullDirection(TypeDirection typeDirection, bool value) {};
	virtual bool IsFullDirection() {return false;}

	Vec2 GetPosition() { return _sprite->getPosition(); }
	int UpdateScore(TypePipe cardType, int score);
	bool IsAlive = true;
	bool IsTouched;

	CREATE_FUNC(Entity);

protected:
	Sprite* _sprite;
};
#pragma once
#include "cocos2d.h"
#include "Constant.h"
#include "Entity.h"
#include "spine/SkeletonAnimation.h"

using namespace cocos2d;
using namespace std;

class Pipe : public Entity
{
public:
	static Pipe* create(TypePipe typePip);
	bool init(TypePipe typePip);

	virtual Rect GetBoundingBox() override;
	virtual void HitLand() override;
	virtual void CustomPause() override;

	virtual void SetLocationSpawn(Vec2 location) override;
	virtual TypePipe GetTypePipe() override { return _typePipe; }

	virtual bool GetNeibour() override { return _isNeibour; }
	virtual void SetNeibour(bool value) override;

	virtual void SetDirections(TypePipe value) override;
	virtual std::vector<TypeDirection> GetDirections() { return _directions; }

	virtual Vec2 GetLocationMatrix() override { return _locationMatrix; }
	virtual void SetLocationMatrix(Vec2 value) override { _locationMatrix = value; }

	virtual bool GetVisited() override { return _isVisited; }
	virtual void SetVisied(bool value) override { _isVisited = value; }

	virtual void SetFullDirection(TypeDirection typeDirection, bool value) override;
	virtual bool IsFullDirection() override;
	
	void DropPipe();
	Vec2 GetPosition() { return _sprite->getPosition(); }
	
	int UpdateScore(TypePipe cardType, int score);
	bool IsAlive = true;
	bool IsTouched;

protected:
	std::map<TypeDirection, bool> _fullDirections;
	std::vector<TypeDirection> _directions;
	TypePipe _typePipe;
	Sprite* _sprite;

private:
	bool _isVisited;
	Vec2 _locationMatrix;
	Vec2 _locationSpawn;
	bool _isNeibour;
};
#pragma once
#include "cocos2d.h"
#include "Constant.h"
#include "spine/SkeletonAnimation.h"
#include "Entity.h"

using namespace cocos2d;
using namespace std;

class Plumping : public Entity
{
public:
	static Plumping* create(TypePipe typePipe);
	bool init(TypePipe typePipe);
	virtual Rect GetBoundingBox() override;
	virtual void HitLand() override;
	virtual void CustomPause() override;

	virtual TypePipe GetTypePipe() override { return _typePipe; }

	virtual bool GetNeibour() override { return _isNeibour; }
	virtual void SetNeibour(bool value) override {
		_isNeibour = value;
	}

	Vec2 GetPosition() { return _sprite->getPosition(); }
	int UpdateScore(TypePipe typePipe, int score);

	virtual Vec2 GetLocationMatrix() override { return _locationMatrix; }
	virtual void SetLocationMatrix(Vec2 value) override { _locationMatrix = value; }

	virtual bool GetVisited() override { return _isVisited; }
	virtual void SetVisied(bool value) override { _isVisited = value; }

	virtual void SetDirections(TypePipe value) override;
	virtual std::vector<TypeDirection> GetDirections() { return _directions; }

	virtual void SetFullDirection(TypeDirection typeDirection, bool value) override;
	virtual bool IsFullDirection() override;

	bool IsAlive = true;
	bool IsTouched;

protected:
	std::map<TypeDirection, bool> _fullDirections;
	bool _isVisited;
	Vec2 _locationMatrix;
	std::vector<TypeDirection> _directions;
	TypePipe _typePipe;
	Sprite* _sprite;
	bool _isNeibour;
};
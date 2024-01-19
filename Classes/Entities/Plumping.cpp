#include "Plumping.h"

Plumping* Plumping::create(TypePipe typePipe)
{
    Plumping* pRet = new(std::nothrow) Plumping();

    if (pRet && pRet->init(typePipe))
    {
        pRet->autorelease();
        return pRet;
    }
    else
    {
        delete pRet;
        pRet = nullptr;
        return nullptr;
    }
}

bool Plumping::init(TypePipe typePipe)
{
	if (!Node::init())
	{
		return false;
	}

    _typePipe = typePipe;
    if (typePipe == TypePipe::PlumpingLeft)
    {
        _sprite = Sprite::create("Sprites/News/quest/pl_quest_blue_2.png");
    }
    else if (typePipe == TypePipe::PlumpingRight)
    {
        _sprite = Sprite::create("Sprites/News/quest/pl_quest_blue_1.png");
    }
    else if (typePipe == TypePipe::PlumpingTop)
    {
        _sprite = Sprite::create("Sprites/News/quest/pl_quest_blue_4.png");
    }
    else if (typePipe == TypePipe::PlumpingBottom)
    {
        _sprite = Sprite::create("Sprites/News/quest/pl_quest_blue_3.png");
    }

    addChild(_sprite);
    SetDirections(_typePipe);
	return true;
}

Rect Plumping::GetBoundingBox()
{
	return Rect();
}

void Plumping::HitLand()
{
}

void Plumping::CustomPause()
{
}

int Plumping::UpdateScore(TypePipe cardType, int score)
{
	
	return score;
}

void Plumping::SetDirections(TypePipe value)
{
    if (value == TypePipe::PlumpingLeft)
    {
        _directions.push_back(TypeDirection::Right);
    }
    else if (value == TypePipe::PlumpingRight)
    {
        _directions.push_back(TypeDirection::Left);
    }
    else if (value == TypePipe::PlumpingTop)
    {
        _directions.push_back(TypeDirection::Bottom);
    }
    else if (value == TypePipe::PlumpingBottom)
    {
        _directions.push_back(TypeDirection::Top);
    }

    for (auto i : _directions)
    {
        _fullDirections.emplace(i, false);
    }
}

void Plumping::SetFullDirection(TypeDirection typeDirection, bool value)
{
    for (auto &i : _fullDirections)
    {
        if (i.first == typeDirection)
        {
            i.second = value;
        }
    }
}

bool Plumping::IsFullDirection()
{
    for (auto i : _fullDirections)
    {
        if (!i.second)
        {
            return false;
        }
    }

    return true;
}

#include "Entity.h"
#include "Pipe.h"

Pipe* Pipe::create(TypePipe typePipe)
{
    Pipe* pRet = new(std::nothrow) Pipe();

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

bool Pipe::init(TypePipe typePipe)
{
	if (!Node::init())
	{
		return false;
	}

    _typePipe = typePipe;
    _sprite = Sprite::create(StringUtils::format("Sprites/News/pipe/pl_pad_nope_%d.png", _typePipe));

    addChild(_sprite);

    SetDirections(_typePipe);
	return true;
}

Rect Pipe::GetBoundingBox()
{
	return Rect();
}

void Pipe::HitLand()
{
}

void Pipe::SetNeibour(bool value)
{
    _isNeibour = value;
    if (_isNeibour)
    {
        auto newTexture = Director::getInstance()->getTextureCache()->addImage(StringUtils::format("Sprites/News/pipe/pl_pad_active_%d.png", _typePipe));
        SpriteFrame* newFrame = SpriteFrame::createWithTexture(newTexture, Rect(0, 0, newTexture->getContentSize().width, newTexture->getContentSize().height));
        _sprite->setSpriteFrame(newFrame);
    }
    else
    {
        auto newTexture = Director::getInstance()->getTextureCache()->addImage(StringUtils::format("Sprites/News/pipe/pl_pad_nope_%d.png", _typePipe));
        SpriteFrame* newFrame = SpriteFrame::createWithTexture(newTexture, Rect(0, 0, newTexture->getContentSize().width, newTexture->getContentSize().height));
        _sprite->setSpriteFrame(newFrame);
    }
}

void Pipe::SetDirections(TypePipe value)
{
    if (value == TypePipe::Pipe1)
    {
        _directions.push_back(TypeDirection::Top);
        _directions.push_back(TypeDirection::Bottom);
    }
    else if (value == TypePipe::Pipe2)
    {
        _directions.push_back(TypeDirection::Right);
        _directions.push_back(TypeDirection::Bottom);
    }
    else if (value == TypePipe::Pipe3)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Bottom);
    }
    else if (value == TypePipe::Pipe4)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Top);
        _directions.push_back(TypeDirection::Right);
    }
    else if (value == TypePipe::Pipe5)
    {
        _directions.push_back(TypeDirection::Bottom);
        _directions.push_back(TypeDirection::Top);
        _directions.push_back(TypeDirection::Right);
    }
    else if (value == TypePipe::Pipe6)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Bottom);
        _directions.push_back(TypeDirection::Top);
        _directions.push_back(TypeDirection::Right);
    }
    else if (value == TypePipe::Pipe7)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Right);
    }
    else if (value == TypePipe::Pipe8)
    {
        _directions.push_back(TypeDirection::Top);
        _directions.push_back(TypeDirection::Right);
    }
    else if (value == TypePipe::Pipe9)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Top);
    }
    else if (value == TypePipe::Pipe10)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Bottom);
        _directions.push_back(TypeDirection::Top);
    }
    else if (value == TypePipe::Pipe11)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Bottom);
        _directions.push_back(TypeDirection::Right);
    }
    else if (value == TypePipe::Pipe12)
    {
        _directions.push_back(TypeDirection::Left);
        _directions.push_back(TypeDirection::Bottom);
        _directions.push_back(TypeDirection::Top);
        _directions.push_back(TypeDirection::Right);
    }

    for (auto i : _directions)
    {
        _fullDirections.emplace(i, false);
    }
}

void Pipe::SetFullDirection(TypeDirection typeDirection, bool value)
{
    for (auto& i : _fullDirections)
    {
        if (i.first == typeDirection)
        {
            i.second = value;
        }
    }
}

bool Pipe::IsFullDirection()
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

void Pipe::DropPipe()
{
    float duration = 0.05f;
    auto moveToAction = MoveTo::create(duration, _locationSpawn);
    this->runAction(moveToAction);
}

void Pipe::CustomPause()
{
}

void Pipe::SetLocationSpawn(Vec2 location)
{
    _locationSpawn = location;
}

int Pipe::UpdateScore(TypePipe cardType, int score)
{

	return score;
}
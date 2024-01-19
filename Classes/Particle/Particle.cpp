#include "Particle.h"

Particle* Particle::create()
{
	auto particle = new Particle();
	if (particle && particle->init())
	{
		particle->autorelease();
		return particle;
	}
	else
	{
		delete particle;
		particle = nullptr;
		return nullptr;
	}
}

bool Particle::init()
{
	if (!Node::init())
	{
		return false;
	}


	return true;
}

void Particle::CreateEffectMushRoomExplode(Node* node, Vec2 position)
{
	Vector<SpriteFrame*> frames;
	auto frame1 = SpriteFrame::create("animation/mushroom_fx_bomb/animation_bomb_fx0.png", Rect(0, 0, 280, 300));
	frames.pushBack(frame1);
	for (int i = 1; i < 20; i++) {
		std::string path = StringUtils::format("animation/mushroom_fx_bomb/animation_bomb_fx%d.png", i);
		auto frame = SpriteFrame::create(path, Rect(0, 0, 280, 300));
		frames.pushBack(frame);
	}

	float delayTime = 0.05f;
	auto animation = Animation::createWithSpriteFrames(frames, delayTime);
	auto animate = Animate::create(animation);
	auto _spriteNormal = Sprite::createWithSpriteFrame(frame1);

	_spriteNormal->setScale(0.5);
	_spriteNormal->setPosition(Vec2(position.x, position.y + 20));

	auto sequence = Sequence::create(DelayTime::create(5), cocos2d::CallFunc::create([=]()
	{
		_spriteNormal->removeFromParent();
	}), nullptr);

	_spriteNormal->runAction(sequence);
	_spriteNormal->runAction(animate);

	node->getParent()->addChild(_spriteNormal, 10);
}

void Particle::CreateEffectMushRoomAim(Node* node, Vec2 position, float scale)
{
	Vector<SpriteFrame*> frames;
	auto frame1 = SpriteFrame::create("animation/mushroom_fx_aim/animation_aim_fx0.png", Rect(0, 0, 260, 320));
	frames.pushBack(frame1);
	for (int i = 1; i < 20; i++) {
		std::string path = StringUtils::format("animation/mushroom_fx_aim/animation_aim_fx%d.png", i);
		auto frame = SpriteFrame::create(path, Rect(0, 0, 260, 320));
		frames.pushBack(frame);
	}

	float delayTime = 0.05f;
	auto animation = Animation::createWithSpriteFrames(frames, delayTime);
	auto animate = Animate::create(animation);
	auto _spriteNormal = Sprite::createWithSpriteFrame(frame1);

	_spriteNormal->setScale(scale);
	_spriteNormal->setPosition(Vec2(position.x, position.y + 20));

	auto sequence = Sequence::create(DelayTime::create(5), cocos2d::CallFunc::create([=]()
	{
		_spriteNormal->removeFromParent();
	}), nullptr);

	_spriteNormal->runAction(sequence);
	_spriteNormal->runAction(animate);

	node->getParent()->addChild(_spriteNormal, 10);
}

void Particle::CreateEffectMushRoomTime(Node* node, Vec2 position)
{
	Vector<SpriteFrame*> frames;
	auto frame1 = SpriteFrame::create("animation/mushroom_fx_time/animation_time_fx0.png", Rect(0, 0, 260, 320));
	frames.pushBack(frame1);
	for (int i = 1; i < 20; i++) {
		std::string path = StringUtils::format("animation/mushroom_fx_time/animation_time_fx%d.png", i);
		auto frame = SpriteFrame::create(path, Rect(0, 0, 260, 320));
		frames.pushBack(frame);
	}

	float delayTime = 0.05f;
	auto animation = Animation::createWithSpriteFrames(frames, delayTime);
	auto animate = Animate::create(animation);
	auto _spriteNormal = Sprite::createWithSpriteFrame(frame1);

	_spriteNormal->setScale(0.5);
	_spriteNormal->setPosition(Vec2(position.x, position.y + 40));

	auto sequence = Sequence::create(DelayTime::create(5), cocos2d::CallFunc::create([=]()
	{
		_spriteNormal->removeFromParent();
	}), nullptr);

	_spriteNormal->runAction(sequence);
	_spriteNormal->runAction(animate);

	node->getParent()->addChild(_spriteNormal, 10);
}

void Particle::CreateEffectHit(Node* node, Vec2 position)
{
	Vector<SpriteFrame*> frames;
	auto frame1 = SpriteFrame::create("animation/bingo/animation_bingo0.png", Rect(0, 0, 500, 250));
	frames.pushBack(frame1);
	for (int i = 1; i < 5; i++) {
		std::string path = StringUtils::format("animation/bingo/animation_bingo%d.png", i);
		auto frame = SpriteFrame::create(path, Rect(0, 0, 500, 250));
		frames.pushBack(frame);
	}

	float delayTime = 0.1f;
	auto animation = Animation::createWithSpriteFrames(frames, delayTime);
	auto animate = Animate::create(animation);
	auto _spriteNormal = Sprite::createWithSpriteFrame(frame1);

	//_spriteNormal->setAnchorPoint(Vec2(0.5, 0));
	//_spriteNormal->setScale(0.5);
	_spriteNormal->setPosition(node->getContentSize().width / 2, 50);

	auto sequence = Sequence::create(DelayTime::create(1.0f), cocos2d::CallFunc::create([=]()
	{
		_spriteNormal->removeFromParent();
	}), nullptr);

	_spriteNormal->runAction(sequence);
	_spriteNormal->runAction(animate);

	node->addChild(_spriteNormal, -1);
}

void Particle::CreateEffectLight(Vec2 position)
{
	auto spriteMusic = cocos2d::Sprite::create("Sprites/UI/icon-Music.png");
	auto moveTo = cocos2d::MoveTo::create(0.2f, position + Vec2(0, 120.0f));
	auto effectScale = cocos2d::ScaleTo::create(0.3f, 1.0f);
	spriteMusic->setLocalZOrder(999);
	spriteMusic->setScale(0.2f);
	spriteMusic->setPosition(position);
	spriteMusic->runAction(moveTo);
	spriteMusic->runAction(effectScale);


	auto effectScaleTo = cocos2d::ScaleTo::create(0.3f, 1.6f);
	auto fadeOut = cocos2d::FadeOut::create(0.3f);
	auto effect = cocos2d::Sprite::create("Sprites/UI/Vungsang-.png");
	effect->setScale(1.2f);
	effect->setPosition(position);
	effect->runAction(effectScaleTo->clone());
	effect->runAction(fadeOut);

	addChild(effect);
	addChild(spriteMusic);

	spriteMusic->runAction(Sequence::create(DelayTime::create(0.5f),
		CallFunc::create([=]()
	{
		this->removeFromParent();
	}), nullptr));
}


#include "HelperManager.h"
#include "AnimationManager.h"
#include <iomanip>

USING_NS_CC;

void HelperManager::disableButton(cocos2d::Ref* sender)
{
	if (auto button = dynamic_cast<ui::Button*>(sender)) {

		button->setTouchEnabled(false);
	}
}

void HelperManager::showWaitingLayer()
{
	//auto waitView = WaitingLayer::createView();
	//waitView->setName("WaitingLayer");
	//irector::getInstance()->getRunningScene()->addChild(waitView, INT_MAX - 1);
}

float HelperManager::lerp(float a, float b, float x, float y, float i)
{
	if (a == b) {
		CCLOG("something wrong!");
		return -1;
	}

	return (((i - a) / (b - a)) * (y - x)) + x;
}

Label* HelperManager::displayToast(const char* text, float duartionSeconds, Node* parent, Color4B color)
{
	auto label = Label::createWithTTF(text, "fonts/arial.ttf", 30);
	label->setPosition(Director::getInstance()->getVisibleSize()/2.f);
	label->setTextColor(color);
	label->enableOutline(color);
	parent->addChild(label, INT_MAX-1);

	//ANIMATION_MANAGER->transitionSlideIn(AnimationManager::Direction::LEFT, 0.25f, label);

	label->runAction(Sequence::createWithTwoActions(DelayTime::create(duartionSeconds), RemoveSelf::create()));
	return label;
}

void HelperManager::attachNodeToSpine(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos)
{
	if (!spine || !node) {
		return;
	}

	node->setContentSize(nodeSize);

	spine->schedule([=](float dt) {

		if (auto slot = spine->findSlot(slotName)) {

			node->setRotation(-slot->bone->rotation);

			node->setScaleX(slot->bone->scaleX);

			node->setScaleY(slot->bone->scaleY);

			node->setPosition({ slot->bone->worldX + offsetPos.x ,slot->bone->worldY + offsetPos.y });
		}

	}, StringUtils::format("update_node_position_%d_%d",random(0,1000),random(0,100)));

	spine->addChild(node);
}

void HelperManager::attachNodeToSpineAndSetPhysic(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos, int physicMask, PhysicType type, bool isDynamic)
{
	if (!spine || !node) {
		return;
	}

	node->setContentSize(nodeSize);

	node->setPosition(spine->getPosition());

	spine->schedule([=](float dt) {

		if (auto slot = spine->findSlot(slotName)) {

			node->setRotation(-slot->bone->rotation);

			node->setScaleX(slot->bone->scaleX);

			node->setScaleY(slot->bone->scaleY);

			node->setPosition({ slot->bone->worldX + offsetPos.x ,slot->bone->worldY + offsetPos.y });
		}

	}, StringUtils::format("update_node_position_%d_%d", random(0, 1000), random(0, 100)));

	PhysicsBody* phyicBody = nullptr;
	
	switch (type)
	{
	case HelperManager::PhysicType::BOX:
		phyicBody =  PhysicsBody::createBox(node->getContentSize());
		break;
	case HelperManager::PhysicType::CIRCLE:
		phyicBody =  PhysicsBody::createCircle(node->getContentSize().width*0.5f);
		break;
	default:
		phyicBody = PhysicsBody::createBox(node->getContentSize());
		break;
	}

	phyicBody->setContactTestBitmask(true);
	phyicBody->setCollisionBitmask(physicMask);
	phyicBody->setDynamic(false);

	node->setPhysicsBody(phyicBody);

	spine->addChild(node);
}


void HelperManager::attachNodeToSpineAndSetPhysicWithoutRotation(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos, int physicMask, PhysicType type, bool isDynamic)
{
    if (!spine || !node) {
        return;
    }

    node->setContentSize(nodeSize);

    node->setPosition(offsetPos);
   
    PhysicsBody* phyicBody = nullptr;
    
    switch (type)
    {
    case HelperManager::PhysicType::BOX:
        phyicBody =  PhysicsBody::createBox(node->getContentSize());
        break;
    case HelperManager::PhysicType::CIRCLE:
        phyicBody =  PhysicsBody::createCircle(node->getContentSize().width*0.5f);
        break;
    default:
        phyicBody = PhysicsBody::createBox(node->getContentSize());
        break;
    }

    phyicBody->setContactTestBitmask(true);
    phyicBody->setCollisionBitmask(physicMask);
    phyicBody->setDynamic(false);

    node->setPhysicsBody(phyicBody);

    spine->addChild(node);
}


float HelperManager::getSpineDuration(spine::SkeletonAnimation *spine, std::string animationName, float defaultDuration)
{
    float delayTime = defaultDuration;

    if(spine)
    {
        if (auto ani = spine->findAnimation(animationName)) {

            delayTime = ani->duration;
            
        }
    }
    
    return delayTime;

}

void HelperManager::addLockLayer(cocos2d::Node* node, cocos2d::Node* popup)
{
	Size visibleSize = Director::getInstance()->getVisibleSize();

	auto layer = cocos2d::LayerColor::create(cocos2d::Color4B(255, 255, 255, 255 * 0.5f), visibleSize.width, visibleSize.height);
	node->addChild(layer);

	auto lockButton = cocos2d::ui::Button::create();
	lockButton->ignoreContentAdaptWithSize(false);
	lockButton->setContentSize(visibleSize * 2.0f);
	lockButton->setPressedActionEnabled(true);
	lockButton->setPosition(layer->getContentSize() * 0.5f);
	lockButton->addTouchEventListener([=](Ref*, cocos2d::ui::Widget::TouchEventType eventType) 
		{
			if (eventType == cocos2d::ui::Widget::TouchEventType::ENDED)
			{
				Point touchPos = lockButton->getTouchEndPosition();
				if (!popup->getBoundingBox().containsPoint(touchPos))
				{
					node->removeFromParent();
				}
			}
		});

	layer->addChild(lockButton);
}

std::string HelperManager::getCurrentDate()
{
    std::time_t currentTime = std::time(nullptr);
    std::tm currentDate = *std::localtime(&currentTime);
    
    std::ostringstream oss;
    oss << std::put_time(&currentDate, "%d-%m-%Y");
    return oss.str();
}

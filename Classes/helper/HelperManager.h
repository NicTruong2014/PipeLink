#pragma once
#include "BaseSingleton.h"
#include "cocos2d.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "spine/SkeletonAnimation.h"

using namespace cocos2d;
using namespace cocos2d::ui;
using namespace spine;

#define HELPER_MANAGER HelperManager::GetInstance()

class HelperManager :public BaseSingleton<HelperManager>
{
public:
    enum class PhysicType {
        BOX,
        CIRCLE
    };
    template<typename T>
    void shuffle(std::vector<T>& v) {
        static std::random_device mj_rd;
        static std::mt19937 mj_g(mj_rd());
        std::shuffle(v.begin(), v.end(), mj_g);
    }

	void disableButton(cocos2d::Ref* sender);

	void showWaitingLayer();

    float lerp(float a, float b, float x, float y, float i);

    static Label* displayToast(const char* text, float duartionSeconds, Node* parent,Color4B color = Color4B::WHITE);

    void attachNodeToSpine(SkeletonAnimation* spine, cocos2d::Node* node,cocos2d::Size nodeSize,std::string slotName, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO);

    void attachNodeToSpineAndSetPhysic(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, std::string slotName, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO,int physicMask = 0, PhysicType type = PhysicType::BOX,bool isDynamic = false);

    void attachNodeToSpineAndSetPhysicWithoutRotation(SkeletonAnimation* spine, cocos2d::Node* node, cocos2d::Size nodeSize, cocos2d::Vec2 offsetPos = cocos2d::Vec2::ZERO,int physicMask = 0, PhysicType type = PhysicType::BOX,bool isDynamic = false);

    float getSpineDuration(spine::SkeletonAnimation *spine,std::string animationName,float defaultDuration = 0.0);
    
    void addLockLayer(cocos2d::Node* node);

    std::string getCurrentDate();

private:
    
};



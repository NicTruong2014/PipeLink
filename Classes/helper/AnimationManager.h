#pragma once
#include "BaseSingleton.h"

USING_NS_CC;

#define ANIMATION_MANAGER AnimationManager::GetInstance()

#define SHAKING_ACTION_TAG_DEFAULT 11223

class AnimationManager : public BaseSingleton<AnimationManager>
{

public:
	
	enum class Direction {
		LEFT,
		RIGHT,
		TOP,
		BOTTOM
	};

	enum class ActionType {
		SHOW,
		HIDE
	};

	cocos2d::Animation* createAnimation(const char* prefixName, int start, int end, float delay, std::string lastFrame);

	cocos2d::Animation* createAnimationWithLoop(const char* prefixName, int start, int end, float delay);

	cocos2d::Animation* createAnimation(const char* prefixName, int start, int end, float delay, int loop = -1);
	
	void runShakingAction(cocos2d::Node* node,int actionTag = SHAKING_ACTION_TAG_DEFAULT);
    
    // duration = 0.3
    void runShakingAction(cocos2d::Node* node,float duration, int actionTag = SHAKING_ACTION_TAG_DEFAULT);

private: //private functions 


public:
	
	AnimationManager();

	~AnimationManager();

	virtual bool init();

	void zoomInEffect(Node *i_node,std::function<void()> i_callback = nullptr);

	void zoomOutEffect(Node *i_node, std::function<void()> i_callback = nullptr);

	void fadeInEffect(Node* i_node, std::function<void()> i_callback = nullptr, float duration = 0.25f);

	void fadeInEffect(std::vector<Node*> i_nodes, std::function<void()> i_callback = nullptr, float duration = 0.25f);

	void moveLeftEffect(Node *i_node, std::function<void()> i_callback = nullptr,float duration = 0.3f);

	void zoomInZoomOutEffectForever(Node* i_node, float duration = 0.125f, float s = 0.0f);

	void zoomInZoomOutEffect(Node *i_node, std::function<void()> i_callback = nullptr, float duration = 0.125f, float s = 0.0f);

	void zoomInZoomOutEffect(std::vector<Node*> i_nodes, std::function<void()> i_callback = nullptr, float duration = 0.125f);

	void fadeInAndZoomInEffectForNodes(std::vector<Node*> i_nodes,float fadeInZommInDuration = 0.125f, float fadeInDurationBetweenItems = 0.5f, std::function<void()> i_callback = nullptr);

	void transitionSlideIn(Direction i_direction, float i_duration, std::vector<Node*> i_nodes, std::function<void()> i_callback = nullptr);

	void transitionSlideIn(Direction i_direction, float i_duration, std::vector<std::pair<std::vector<Node*>, float>> i_nodesAndDelaytime, std::function<void()> i_callback = nullptr);

	void transitionSlideIn(Direction i_direction, float i_duration, Node* i_node, std::function<void()> i_callback = nullptr);

	void transitionSlideOut(Direction i_direction, float i_duration, std::vector<Node*> i_nodes, std::function<void()> i_callback = nullptr);
	
	void transitionSlideOut(Direction i_direction, float i_duration, std::vector<std::pair<std::vector<Node*>, float>> i_nodesAndDelaytime, std::function<void()> i_callback = nullptr);

	void transitionSlideOut(Direction i_direction, float i_duration, Node* i_node, std::function<void()> i_callback = nullptr);

	void popupCustomAnimation(cocos2d::Node* popupBackground, ActionType actionType,float actionTime, std::function<void()> callback = nullptr);

	void tintAnimation(cocos2d::Node* node, float actionTime, std::function<void()> callback = nullptr);

	void tintAnimation(cocos2d::Node* node, float actionTime,int actionTag,Color3B color = Color3B::MAGENTA);

private:

	cocos2d::Size _screenSize;

	cocos2d::Vec2 _origin;
};


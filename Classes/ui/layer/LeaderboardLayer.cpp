#include "LeaderboardLayer.h"
#include "HelperManager.h"
#include "SoundManager.h"
#include "Utils.h"

USING_NS_CC;

#define MAX_LEADERBOARD_ITEM 10

Scene* LeaderboardLayer::createScene()
{
	auto scene = Scene::create();

	if (scene)
	{
		auto view = LeaderboardLayer::create();
		scene->addChild(view);
	}
	else
	{
		CC_SAFE_DELETE(scene);
	}

	return scene;
}

void LeaderboardLayer::UpdateUserGem(int gem)
{
	UserDefault::getInstance()->setIntegerForKey("user_gem", gem);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("user_gem_change_ev");
}

void LeaderboardLayer::IncreaseUserGem(int gem)
{
	int currentGem = UserDefault::getInstance()->getIntegerForKey("user_gem", 0);

	UserDefault::getInstance()->setIntegerForKey("user_gem", currentGem + gem);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("user_gem_change_ev");
}

void LeaderboardLayer::DecreaseUserGem(int gem)
{
	int currentGem = UserDefault::getInstance()->getIntegerForKey("user_gem", 0);

	currentGem = currentGem - gem;

	currentGem = currentGem < 0 ? 0 : currentGem;

	UserDefault::getInstance()->setIntegerForKey("user_gem", currentGem);

	Director::getInstance()->getEventDispatcher()->dispatchCustomEvent("user_gem_change_ev");
}

bool LeaderboardLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto scale = 0.8f;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	HelperManager::GetInstance()->addLockLayer(this);

	Sprite* background = Sprite::create("Sprites/popup/leaderboard/sh_popup_leaderboard.png");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setScale(scale);
	background->setName("background");
	this->addChild(background);

	auto closeButton = cocos2d::ui::Button::create("Sprites/icon/sh_icon_cancel.png");
	closeButton->setPosition(Vec2(background->getContentSize().width - closeButton->getContentSize().width / 4 + 5,
		background->getContentSize().height - closeButton->getContentSize().height - 10));
	closeButton->setPressedActionEnabled(true);
	closeButton->addClickEventListener([=](Ref* sender)
	{
		SOUND_MANAGER->playClickEffect();
		this->removeFromParent();
	});
	background->addChild(closeButton);


	updateHighScore();

	int j = 0;
	int t = 0;
	for (int i = 0; i < MAX_LEADERBOARD_ITEM; i++)
	{
		if (i == 5)
		{
			t = 0;
			j = 1;
		}

		auto rectScore = Sprite::create("Sprites/popup/leaderboard/sh_popup_leaderboard_bar.png");
		rectScore->setPosition(Vec2(background->getContentSize().width / 2 - 280 + j * (rectScore->getContentSize().width + 10),
			background->getContentSize().height - 280 - t * (rectScore->getContentSize().height + 5)));
		background->addChild(rectScore);

		auto index = std::to_string(i + 1);
		auto labelPos = cocos2d::Label::createWithTTF("Score", "fonts/SVNMergeBold.ttf", 30);
		labelPos->setString(index);
		labelPos->setPosition(Vec2(37, 40));
		labelPos->setColor(Color3B::BLACK);
		rectScore->addChild(labelPos);

		const std::string k_scoreKey = StringUtils::format("rank_%d_score", i);
		auto score = UserDefault::getInstance()->getIntegerForKey(k_scoreKey.c_str(), 0);
		auto labelScor = cocos2d::Label::createWithTTF("Score", "fonts/SVNMergeBold.ttf", 25);
		labelScor->setString(Utils::FormatIntToString(score));
		labelScor->setPosition(Vec2(rectScore->getContentSize().width / 2 + 200, 40));
		rectScore->addChild(labelScor);

		auto labelName = cocos2d::Label::createWithTTF("You", "fonts/SVNMergeBold.ttf", 25);
		labelName->setPosition(Vec2(rectScore->getContentSize().width / 2 - 150, 40));
		rectScore->addChild(labelName);

		t++;
	}


	return true;
}

void LeaderboardLayer::updateHighScore(int newScore)
{
	std::vector<int> leaderboards;

	leaderboards.push_back(newScore);

	for (int i = 0; i < MAX_LEADERBOARD_ITEM; i++) {

		const std::string k_scoreKey = StringUtils::format("rank_%d_score", i);
		auto score = UserDefault::getInstance()->getIntegerForKey(k_scoreKey.c_str(), 0);

		leaderboards.push_back({ score});
	}

	std::sort(leaderboards.begin(), leaderboards.end(), [](int a, int b) {
		return a > b;
	});

	for (int i = 0, j = 0; i < MAX_LEADERBOARD_ITEM; i++, j++) 
	{
		if (j >= leaderboards.size()) {
			return;
		}

		auto b = leaderboards.at(j);
		const std::string k_scoreKey = StringUtils::format("rank_%d_score", i);

		UserDefault::getInstance()->setIntegerForKey(k_scoreKey.c_str(), b);
	}
}

void LeaderboardLayer::updateHighScore()
{
	std::vector<int> leaderboards;

	for (int i = 0; i <= MAX_LEADERBOARD_ITEM; i++) {

		const std::string k_scoreKey = StringUtils::format("rank_%d_score", i);
		auto score = UserDefault::getInstance()->getIntegerForKey(k_scoreKey.c_str(), 0);

		leaderboards.push_back(score);
	}

	std::sort(leaderboards.begin(), leaderboards.end(), [](int a, int b) {
		return a > b;
	});

	for (int i = 0, j = 0; i <= MAX_LEADERBOARD_ITEM; i++, j++) {

		if (j >= leaderboards.size()) {
			return;
		}

		auto b = leaderboards.at(j);

		const std::string k_scoreKey = StringUtils::format("rank_%d_score", i);

		UserDefault::getInstance()->setIntegerForKey(k_scoreKey.c_str(), b);
	}
}

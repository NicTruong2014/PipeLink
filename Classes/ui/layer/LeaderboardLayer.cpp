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

bool LeaderboardLayer::init()
{
	if (!Layer::init())
	{
		return false;
	}

	auto scale = 1.0f;
	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();


	Sprite* background = Sprite::create("Sprites/News/popup/pl_popup_leaderboard.png");
	HelperManager::GetInstance()->addLockLayer(this, background);

	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	background->setScale(scale);
	background->setName("background");
	this->addChild(background);

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

		auto rectScore = Sprite::create("Sprites/News/popup/pl_popup_leaderboard_bar.png");
		rectScore->setPosition(Vec2(background->getContentSize().width / 2 - 240 + j * (rectScore->getContentSize().width + 10),
			background->getContentSize().height - 190 - t * (rectScore->getContentSize().height + 20)));
		background->addChild(rectScore);

		auto index = std::to_string(i + 1);
		auto labelPos = cocos2d::Label::createWithTTF("Score", "fonts/SVNMergeBold.ttf", 30);
		labelPos->setString(index);
		labelPos->setPosition(Vec2(33, 40));
		labelPos->setColor(Color3B::YELLOW);
		rectScore->addChild(labelPos);

		const std::string k_scoreKey = StringUtils::format("rank_%d_score", i);
		auto score = UserDefault::getInstance()->getIntegerForKey(k_scoreKey.c_str(), 0);
		auto labelScor = cocos2d::Label::createWithTTF("Score", "fonts/SVNMergeBold.ttf", 30);
		labelScor->setString(Utils::FormatIntToString(score));
		labelScor->setPosition(Vec2(rectScore->getContentSize().width / 2 + 150, 40));
		rectScore->addChild(labelScor);

		auto labelName = cocos2d::Label::createWithTTF("You", "fonts/SVNMergeBold.ttf", 30);
		labelName->setPosition(Vec2(rectScore->getContentSize().width / 2 - 100, 40));
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

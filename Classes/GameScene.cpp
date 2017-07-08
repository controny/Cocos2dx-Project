#include "GameScene.h"

USING_NS_CC;

Scene* GameScene::createScene()
{
	// 'scene' is an autorelease object
	auto scene = Scene::create();

	// 'layer' is an autorelease object
	auto layer = GameScene::create();

	// add layer as a child to scene
	scene->addChild(layer);

	// return the scene
	return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();

	// set background
	background = Sprite::create("level-background-0.jpg");
	background->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	this->addChild(background, 0);

	// add the stone layer
	stoneLayer = Layer::create();
	stoneLayer->setAnchorPoint(Vec2::ZERO);
	stoneLayer->setPosition(Vec2::ZERO);
	stone = Sprite::create("stone.png");
	stone->setPosition(560, 480);
	stoneLayer->addChild(stone, 0);
	this->addChild(stoneLayer, 1);

	// add mouse layer
	mouseLayer = Layer::create();
	mouseLayer->setAnchorPoint(Vec2::ZERO);
	mouseLayer->setPosition(Vec2::ZERO);
	mouse = Sprite::createWithSpriteFrameName("gem-mouse-0.png");
	Animate* mouseAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("mouseAnimation"));
	mouse->runAction(RepeatForever::create(mouseAnimate));
	mouse->setPosition(visibleSize.width/2, visibleSize.height/2);
	mouseLayer->addChild(mouse, 0);
	this->addChild(mouseLayer, 1);

	// add shoot label
	shoot = Label::createWithTTF("Shoot", "fonts/arial.ttf", 34);
	shoot->setPosition(Vec2(visibleSize.width - shoot->getContentSize().width - 50,
							stone->getPosition().y));
	this->addChild(shoot, 1);

	//add touch listener
	EventListenerTouchOneByOne* listener = EventListenerTouchOneByOne::create();
	listener->setSwallowTouches(true);
	listener->onTouchBegan = CC_CALLBACK_2(GameScene::onTouchBegan, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(listener->clone(), shoot);

	return true;
}

bool GameScene::onTouchBegan(Touch *touch, Event *event) {
	auto location = touch->getLocation();
	auto target = static_cast<Label*>(event->getCurrentTarget());

	if (target == shoot) {
		Size s = target->getContentSize();
		CCLOG("size: %f, %f", s.width, s.height);
		CCLOG("Shoot");
		target->setScale(1.5);
		auto mouseLocation = mouse->getPosition();
		auto rock = Sprite::create("stone.png");
		rock->setPosition(stone->getPosition());
		this->addChild(rock);
		auto rockMove = MoveBy::create(1, rock->convertToNodeSpaceAR(mouseLocation));
		auto fadeOut = FadeOut::create(4);
		auto seq = Sequence::create(rockMove, fadeOut, nullptr);
		rock->runAction(seq);
		// move the mouse to a random position
		Size bgSize = background->getContentSize();
		srand(unsigned(time(0)));
		double ranRatio = (rand() % 100) / (double)100;
		CCLOG("ranRatio: %f", ranRatio);
		double newPosX = bgSize.width * ranRatio;
		ranRatio = (rand() % 100) / (double)100;
		double newPosY = bgSize.height * ranRatio;
		CCLOG("new position: %f, %f", newPosX, newPosY);
		auto mouseMove = MoveTo::create(1, Vec2(newPosX, newPosY));
		mouse->runAction(mouseMove);
		// leave a diamond
		auto diamond = Sprite::create("diamond.png");
		diamond->setPosition(diamond->convertToNodeSpaceAR(mouseLocation));
		this->addChild(diamond);
	} else {
		CCLOG("Put");
		// put a cheese
		auto cheese = Sprite::create("cheese.png");
		cheese->setPosition(location);
		this->addChild(cheese);
		// make the cheese fade out in some time
		auto fadeOut = FadeOut::create(4);
		cheese->runAction(fadeOut);
		// make the mouse move to the cheese
		auto nodeLocation = mouse->convertToNodeSpaceAR(location);
		auto move = MoveBy::create(2, nodeLocation);
		mouse->runAction(move);
		CCLOG("location: %f, %f", location.x, location.y);
		CCLOG("nodeLocation: %f, %f", nodeLocation.x, nodeLocation.y);
		CCLOG("currentLocation: %f, %f", mouse->getPosition().x, mouse->getPosition().y);
	}

	return true;
}

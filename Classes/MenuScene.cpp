#include "MenuScene.h"
#include "GameScene.h"
USING_NS_CC;

Scene* MenuScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = MenuScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool MenuScene::init()
{

    if ( !Layer::init() )
    {
        return false;
    }

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Vec2 origin = Director::getInstance()->getVisibleOrigin();

	auto bg_sky = Sprite::create("menu-background-sky.jpg");
	bg_sky->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y + 150));
	this->addChild(bg_sky, 0);

	auto bg = Sprite::create("menu-background.png");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y - 60));
	this->addChild(bg, 0);

	auto miner = Sprite::create("menu-miner.png");
	miner->setPosition(Vec2(150 + origin.x, visibleSize.height / 2 + origin.y - 60));
	this->addChild(miner, 1);

	auto leg = Sprite::createWithSpriteFrameName("miner-leg-0.png");
	Animate* legAnimate = Animate::create(AnimationCache::getInstance()->getAnimation("legAnimation"));
	leg->runAction(RepeatForever::create(legAnimate));
	leg->setPosition(110 + origin.x, origin.y + 102);
	this->addChild(leg, 1);

    // Add title
    auto title = Sprite::create("gold-miner-text.png");
    title->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 4 * 3 + origin.y));
    this->addChild(title, 1);

    // Add a start button to switch to game scene
    auto start = MenuItemImage::create(
                                           "start-0.png",
                                           "start-1.png",
                                           CC_CALLBACK_1(MenuScene::startMenuCallback, this));
    
    start->setPosition(0, 40);

    auto menuStart = Sprite::create("menu-start-gold.png");
    menuStart->setPosition(Vec2(origin.x + visibleSize.width - menuStart->getContentSize().width + 50 ,
                                origin.y + menuStart->getContentSize().height/2));

    auto menu = Menu::create(start, NULL);
    menu->setPosition(Vec2(origin.x + visibleSize.width - menuStart->getContentSize().width + 50 ,
                                origin.y + menuStart->getContentSize().height/2));
	this->addChild(menuStart, 0);
    this->addChild(menu, 1);

    return true;
}

void MenuScene::startMenuCallback(Ref* pSender) {
    CCLOG("Start!");
    // Switch scene
    auto gameScene = GameScene::createScene();
    Director::getInstance()->replaceScene(TransitionFade::create(0.5, gameScene));
}

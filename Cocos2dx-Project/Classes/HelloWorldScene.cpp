#pragma execution_character_set("utf-8")
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include <iostream>

USING_NS_CC;
using namespace CocosDenshion;

Scene* HelloWorld::createScene()
{
    auto scene = Scene::create();
    auto layer = HelloWorld::create();
    scene->addChild(layer);
	
    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool HelloWorld::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    visibleSize = Director::getInstance()->getVisibleSize();

	hasStart = false;

	preloadMusic(); // Ô¤¼ÓÔØÒôÐ§

	addListener();  // Ìí¼Ó¼àÌýÆ÷
	addBall();    // Ìí¼ÓÐ¡Çò

	coun = 0;
	isMove = false;

	obstacle = new Obstacle();
	this->addChild(obstacle, 2);

	// update 
	scheduleUpdate();

    return true;
}

void HelloWorld::preloadMusic()
{
}

void HelloWorld::update(float time) {
	static int count = 0;
	obstacle->update();
	count++;
	auto list = obstacle->obstacleList;

	if (count == 100) {
		obstacle->deleteOne();
		count = 0;
	}

	// add a new obstacle
	if (coun == 5) {
		if (list->count() - 1 >= 0) {
			auto lastone = (Sprite*)list->getObjectAtIndex(list->count() - 1);
			obstacle->addOne(lastone->getPositionY() + 250);
		}
		else {
			obstacle->addOne(150);
		}

		coun = 0;
	}

	// move the obstacle 
	auto pos = ball->getPosition();

	if (pos.y > visibleSize.height / 2) {
		++coun;
		if (velocity >= 0.000001) obV = velocity;
		ball->setPosition(ball->getPosition() + Vec2(0, -2));
		isMove = true;
		velocity = 0;
	}
	else {

		velocity -= GRAVITY;
		ball->setPositionY(ball->getPositionY() + velocity);
	}
	if (isMove) {
		obV -= GRAVITY;
		for (int i = 0; i < list->count(); ++i) {
			auto s = (Sprite*)list->getObjectAtIndex(i);

			s->setPositionY(s->getPositionY() - obV);
		}
		if (obV <= 0.00001) isMove = false;
	}
	// judge whether there is a collission
	auto body = ball->getBoundingBox();
	for (int i = 0; i < list->count(); ++i) {
		auto obst = ((Sprite*)list->getObjectAtIndex(i))->getBoundingBox();
		if (body.intersectsRect(obst)) {
			obstacle->getProperty(i);
		}
	}


	// gameover if the ball is out of the screen
	if (ball->getPositionY() < 0.00001) {

	}
}

void HelloWorld::addListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	log("test");
	static int offsetY = 100;
	if (code == cocos2d::EventKeyboard::KeyCode::KEY_SPACE) {
		// add an obstacle and a prop
		obstacle->addOne(offsetY);
		addProp(offsetY - 150);
		offsetY += 300;
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
		velocity = 5;
	}
	else if (code == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
		velocity = 5;
	}
}

bool HelloWorld::addBall()
{
	ball = Sprite::create("Ball/Ball3.png");
	ball->setScale(0.5f);
	ball->setPosition(Vec2(visibleSize.width / 2, 200));
	ball->setTag(TAG_BALL);
	addChild(ball, 1);
	return true;
}

void HelloWorld::addProp(int offsetY)
{
	auto prop = Sprite::create(IMG_PROP);
	prop->setScale(0.1);
	prop->setPosition(Vec2(visibleSize.width / 2, offsetY));
	prop->setTag(TAG_PROP);
	addChild(prop, 1);
}

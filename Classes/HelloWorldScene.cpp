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
	hasGameOver = false;
	coun = 0;
	isMove = false;

	preloadMusic(); // Ô¤¼ÓÔØÒôÐ§

	addListener();  // Ìí¼Ó¼àÌýÆ÷
	addBall();    // Ìí¼ÓÐ¡Çò

	obstacle = new Obstacle();
	this->addChild(obstacle, 2);

	score = 0;
	scoreLabel = Label::createWithTTF("score : 0", "fonts/arial.TTF",30);
	scoreLabel->setPosition(Vec2(80, visibleSize.height - 30));
	addChild(scoreLabel, 0);
	// update 
	scheduleUpdate();

	obstacle->addOne(300);
	addProp(425);

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
		if (list->count() - 1 >= 0 && props.size() - 1 >= 0) {
			auto lastone = (Sprite*)list->getObjectAtIndex(list->count() - 1);
			obstacle->addOne(lastone->getPositionY() + 275);
			auto last = props.back();
			int dy = last->getPositionY() + 275;
			addProp(dy);
		}
		else {
			addProp(275);
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
		for (int i = 0; i < props.size(); ++i) {
			auto p = props.at(i);
			p->setPositionY(p->getPositionY() - obV);
		}
		for (int i = 0; i < list->count(); ++i) {
			auto s = (Sprite*)list->getObjectAtIndex(i);

			s->setPositionY(s->getPositionY() - obV);
		}
		if (obV <= 0.00001) isMove = false;
	}
	// judge whether there is a collission with obstacles
	auto body = ball->getBoundingBox();
	for (int i = 0; i < list->count(); ++i) {
		auto obst = ((Sprite*)list->getObjectAtIndex(i));
		auto r = obst->getContentSize().height * 0.5;
		auto dangerDis = r * 5 / 39;
		auto dis = fabs(obst->getPositionY() - ball->getPositionY());
		auto disInnerToObst = dis + ball->getContentSize().height * 0.3 * 0.5;
		auto disOutToObst = dis - ball->getContentSize().height * 0.3 * 0.5;
		
		if (dis > r / 2 - 20) {
			if (disOutToObst < r / 2 - 150) {
				if (ball->getPosition() > obst->getPosition()) {
					auto color = obstacle->getTopProperty(i);
					if (ball->getTag() - 2001 == color || (ball->getTag() - 2001 + 2) % 5 == color) {
						log("safe");
					}
					else {
						gameOver();
						break;
					}
				}
				else {
					auto color = obstacle->getBottomProperty(i);
					if (ball->getTag() - 2001 == color || (ball->getTag() - 2001 + 2) % 5 == color) {
						log("safe");
					}
					else {
						gameOver();
						break;
					}
				}
				
			}
			
		}
		else {
			if (disInnerToObst > r / 2 - dangerDis - 30) {
				if (ball->getPosition() > obst->getPosition()) {
					auto color = obstacle->getTopProperty(i);
					if (ball->getTag() - 2001 == color || (ball->getTag() - 2001 + 2) % 5 == color) {
						log("safe");
					}
					else {
						gameOver();
						break;
					}
				}
				else {
					auto color = obstacle->getBottomProperty(i);
					if (ball->getTag() - 2001 == color || (ball->getTag() - 2001 + 2) % 5 == color) {
						log("safe");
					}
					else {
						gameOver();
						break;
					}
				}
			}
		}
	}

	// judge whether there is a collision with props
	for (int i = 0; i < props.size(); ++i) {
		auto rect = props.at(i)->getBoundingBox();
		if (body.intersectsRect(rect)) {
			onBallCrashProps();
			removeChild(props.at(i));
			props.erase(i);
			break;
		}
	}


	// gameover if the ball is out of the screen
	if (!hasGameOver && ball->getPositionY() < 0.00001) {
		gameOver();
	}
}

void HelloWorld::addListener()
{
	auto keyboardListener = EventListenerKeyboard::create();
	keyboardListener->onKeyPressed = CC_CALLBACK_2(HelloWorld::onKeyPressed, this);
	_eventDispatcher->addEventListenerWithSceneGraphPriority(keyboardListener, this);
}

void HelloWorld::onKeyPressed(EventKeyboard::KeyCode code, Event* event) {
	if (code == cocos2d::EventKeyboard::KeyCode::KEY_UP_ARROW) {
		velocity = 6;
	}
}
/*
* When ball clash obstacle and the color is error 
* Or ball drop under the game scene
*/
void HelloWorld::gameOver() {
	hasGameOver = true;
	this->unscheduleUpdate();
	ball->removeFromParentAndCleanup(true);
	auto label1 = Label::createWithTTF("Game Over", "fonts/arial.TTF", 60);
	label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(label1, 3);

	auto label2 = Label::createWithTTF("Play again", "fonts/arial.TTF", 30);
	auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::replayCallback, this));
	Menu* replay = Menu::create(replayBtn , NULL);
	replay->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100);
	this->addChild(replay, 3);

	auto label3 = Label::createWithTTF("Submit score", "fonts/arial.TTF", 30);
	auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(HelloWorld::submitCallback, this));
	Menu* exit = Menu::create(exitBtn, NULL);
	exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);
	this->addChild(exit, 3);
}
/*
* Please elminate the Props before call this function
* Ball will change its color in this function
*/
void HelloWorld::onBallCrashProps() {
	score++;
	std::string s = "score : " + std::to_string(score);
	scoreLabel->setString(s);
	int before = ball->getTag();
	int r;
	do {
		r = random(0, 5) % 5;
	} while (TAG_BALL[r] == before);
	ball->setTexture(IMG_BALL[r]);
	ball->setTag(TAG_BALL[r]);
	// when score reach 5 times then improve the velocity of rotate

}

bool HelloWorld::addBall()
{
	ball = Sprite::create(IMG_BALL[0]);
	ball->setScale(0.3f);
	ball->setPosition(Vec2(visibleSize.width / 2, 200));
	ball->setTag(TAG_BALL[0]);
	addChild(ball, 1);
	return true;
}

void HelloWorld::addProp(int offsetY)
{
	auto prop = Sprite::create(IMG_PROP);
	prop->setScale(0.1);
	prop->setPosition(Vec2(visibleSize.width / 2, offsetY));
	prop->setTag(TAG_PROP);
	props.pushBack(prop);
	addChild(prop, 1);
}
void HelloWorld::replayCallback(Ref * pSender)
{
	Director::getInstance()->replaceScene(HelloWorld::createScene());
}

void HelloWorld::submitCallback(Ref * pSender)
{

}

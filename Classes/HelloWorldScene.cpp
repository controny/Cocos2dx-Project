#pragma execution_character_set("utf-8")
#include "HelloWorldScene.h"
#include "SimpleAudioEngine.h"
#include "ui/CocosGUI.h"
#include <iostream>
#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Global.h"
#include "GameScene.h"
#include "network/HttpClient.h"
#define database UserDefault::getInstance()

using namespace cocos2d::network;

#include <regex>
using std::to_string;
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;
USING_NS_CC;

using namespace cocostudio::timeline;

#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"

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
	
	if (!database->getBoolForKey("isExist")) {
		database->setBoolForKey("isExist", true);
		database->setIntegerForKey("value", 0);
	}
	string temp = "Local highest score : " + to_string(database->getIntegerForKey("value"));
	highest = Label::createWithTTF(temp, "fonts/arial.TTF", 30);
	highest->setPosition(Vec2(highest->getContentSize().width / 2, scoreLabel->getPosition().y - scoreLabel->getContentSize().height));
	addChild(highest, 0);
	//xmx
	scheduleUpdate();

	obstacle->addOne(300);
	addProp(475);

	obstacle->addOne(675);
	addProp(850);

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
			obstacle->addOne(lastone->getPositionY() + 375);
			auto last = props.back();
			int dy = last->getPositionY() + 375;
			addProp(dy);
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
	//xmx
	float visibleHeight;
	float visibleWidth;
	Size size = Director::getInstance()->getVisibleSize();
	visibleHeight = size.height;
	visibleWidth = size.width;
	if (database->getIntegerForKey("value") < score)
	{
		database->setIntegerForKey("value", score);
		highest->setString("Local highest score : " + to_string(score));

	}
	//xmx
	hasGameOver = true;
	this->unscheduleUpdate();
	ball->removeFromParentAndCleanup(true);
	auto label1 = Label::createWithTTF("Game Over", "fonts/arial.TTF", 60);
	label1->setPosition(visibleSize.width / 2, visibleSize.height / 2);
	this->addChild(label1, 3);

	auto label2 = Label::createWithTTF("Play again", "fonts/arial.TTF", 30);
	auto replayBtn = MenuItemLabel::create(label2, CC_CALLBACK_1(HelloWorld::replayCallback, this));
	Menu* replay = Menu::create(replayBtn, NULL);
	replay->setPosition(visibleSize.width / 2 - 80, visibleSize.height / 2 - 100);
	this->addChild(replay, 3);

	auto label3 = Label::createWithTTF("Submit score", "fonts/arial.TTF", 30);
	auto exitBtn = MenuItemLabel::create(label3, CC_CALLBACK_1(HelloWorld::submitCallback, this));
	Menu* exit = Menu::create(exitBtn, NULL);
	exit->setPosition(visibleSize.width / 2 + 90, visibleSize.height / 2 - 100);
	this->addChild(exit, 3);
	//xmx
	auto button = Button::create();
	button->setTitleText("Submit my score");
	button->setTitleFontSize(30);
	button->setPosition(Size(visibleWidth / 2, visibleHeight / 6));
	this->addChild(button, 2);
	button->addClickEventListener(CC_CALLBACK_1(HelloWorld::onclickSubmit, this));
	//xmx
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
	ball->setPosition(Vec2(visibleSize.width / 2, 50));
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

void HelloWorld::onclickSubmit(cocos2d::Ref* p)
{
	HttpRequest* request = new HttpRequest();

	request->setRequestType(HttpRequest::Type::POST);

	request->setUrl("http://localhost:8080/submit");

	string s = "score=" + std::to_string(score);

	const char* postData = s.c_str();
	CCLOG("GetParseError %s\n", postData);
	request->setRequestData(postData, strlen(postData));

	request->setResponseCallback(CC_CALLBACK_2(HelloWorld::onSubmitHttpComplete, this));

	std::vector<string> headers;
	s = "Cookie: GAMESESSIONID=" + Global::gameSessionId;
	headers.push_back(s);
	request->setHeaders(headers);

	cocos2d::network::HttpClient::getInstance()->send(request);

	request->release();
}
//xmx
void HelloWorld::onSubmitHttpComplete(HttpClient* sender, HttpResponse* response)
{
	if (!response) return;
	if (!response->isSucceed()) {
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
	}
	rapidjson::Document d;
	std::vector<char> *buffer = response->getResponseData();
	std::string str = Global::toString(buffer);

	d.Parse<0>(str.c_str());
	if (d.HasParseError()) CCLOG("GetParseError %s\n", d.GetParseError());
	if (d.IsObject() && d.HasMember("info"))
	{
		sscanf(d["info"].GetString(), "%d", &(Global::score));
		char str[100];
		sprintf(str, "%d", Global::score);
		Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
	}
}
//xmx
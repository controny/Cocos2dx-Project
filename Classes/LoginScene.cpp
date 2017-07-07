#include "LoginScene.h"
#include "cocostudio/CocoStudio.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "Global.h"
#include "GameScene.h"
#include "network/HttpClient.h"
#include "HelloWorldScene.h"
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
using namespace  rapidjson;

Scene* LoginScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = LoginScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}





// on "init" you need to initialize your instance
bool LoginScene::init()
{

	if (!Layer::init())
	{
		return false;
	}

	Size visibleSize = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();



	float winw = Director::getInstance()->getWinSize().width; //获取屏幕宽度
	float winh = Director::getInstance()->getWinSize().height;//获取屏幕高度
	auto bg = Sprite::create("bg.jpeg");
	bg->setPosition(Vec2(visibleSize.width / 2 + origin.x, visibleSize.height / 2 + origin.y));
	bg->setScaleX(winw / bg->getTextureRect().getMaxX()); //设置精灵宽度缩放比例
	bg->setScaleY(winh / bg->getTextureRect().getMaxY());
	this->addChild(bg, 0);

	//创建词典类实例，将xml文件加载到词典中
	auto *chnStrings = __Dictionary::createWithContentsOfFile("test.xml");
	//通过xml文件中的key获取value
	const char *str1 = ((__String*)chnStrings->objectForKey("string1"))->getCString();

	auto title = Label::create(str1, "fonts/AdobeFangsongStd-Regular.otf", 50);
	title->setPosition(Vec2(visibleSize.width / 4 + origin.x + 20, (visibleSize.height - visibleSize.height / 4) + origin.y));
	this->addChild(title, 2);

	const char *str2 = ((__String*)chnStrings->objectForKey("string2"))->getCString();
	auto content = Label::create(str2, "fonts/AdobeFangsongStd-Regular.otf", 15);
	content->setPosition(Vec2(visibleSize.width / 3 + origin.x + 20, title->getPosition().y - title->getContentSize().height - 60));
	content->setWidth(500);
	this->addChild(content, 2);

	auto f = Sprite::create("name.png");
	const char *str3 = ((__String*)chnStrings->objectForKey("string3"))->getCString();
	name = TextField::create(str3, "fonts/AdobeFangsongStd-Regular.otf", 30);
	name->setPosition(Vec2((visibleSize.width / 4) + origin.x, (visibleSize.height / 5) + origin.y - 10));
	//name->setCursorEnabled(true);
	name->setPlaceHolder(str3);
	name->setTextColor(Color4B::WHITE);
	name->setPlaceHolderColor(Color4B::WHITE);

	f->setContentSize(Size(visibleSize.width/12 * 1.5, visibleSize.width/12));
	f->setPosition(Vec2((visibleSize.width / 5) + origin.x, (visibleSize.height / 5) + origin.y));

	this->addChild(f, 2);
	this->addChild(name, 3);


	auto color = Sprite::create("color.jpeg");
	
	color->setPosition(Vec2((visibleSize.width - visibleSize.width / 4), visibleSize.height*0.65));
	color->setScaleX(0.6);
	color->setScaleY(0.6);
	this->addChild(color, 2);

	auto S = Sprite::create("s.jpeg");

	S->setPosition(Vec2(origin.x + visibleSize.width-S->getContentSize().width/2,
		origin.y));
	S->setScaleX(winw / bg->getTextureRect().getMaxX()); //设置精灵宽度缩放比例
	S->setScaleY(winh / bg->getTextureRect().getMaxY());
	addChild(S, 2);

	auto startItem = MenuItemImage::create(
		"start-0.png",
		"start-1.png",
		CC_CALLBACK_1(LoginScene::onclick, this));
	startItem->setScaleX(winw / bg->getTextureRect().getMaxX()); //设置精灵宽度缩放比例
	startItem->setScaleY(winh / bg->getTextureRect().getMaxY());

	startItem->setPosition(Vec2(origin.x + visibleSize.width - S->getContentSize().width/2,
		origin.y + startItem->getContentSize().height));
	auto menu = Menu::create(startItem, NULL);
	menu->setPosition(Vec2::ZERO);

	this->addChild(menu, 2);


	return true;
  /*  Size size = Director::getInstance()->getVisibleSize();
    visibleHeight = size.height;
    visibleWidth = size.width;

    textField = TextField::create("Player Name", "Arial", 30);
    textField->setPosition(Size(visibleWidth / 2, visibleHeight / 4 * 3));
    this->addChild(textField, 2);
	
    auto button = Button::create();
    button->setTitleText("Login");
    button->setTitleFontSize(30);
    button->setPosition(Size(visibleWidth / 2, visibleHeight / 2));
    this->addChild(button, 2);
	button->addClickEventListener(CC_CALLBACK_1(LoginScene::onclick, this));

    return true;*/
}

void LoginScene::onclick(cocos2d::Ref* p)
{
	
	HttpRequest* request = new HttpRequest();

	request->setRequestType(HttpRequest::Type::POST);

	request->setUrl("http://localhost:8080/login");
	string s = "username=" + name->getString();
	const char* postData = s.c_str();
	
	request->setRequestData(postData, strlen(postData));

	request->setResponseCallback(CC_CALLBACK_2(LoginScene::onHttpComplete, this));

	cocos2d::network::HttpClient::getInstance()->send(request);

	request->release();
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, HelloWorld::createScene()));

}

void LoginScene::onHttpComplete(HttpClient* sender, HttpResponse* response) {
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
	}
	
	
	std::vector<char> *buffer2 = response->getResponseHeader();
	std::string str2 = Global::toString(buffer2);
	Global::gameSessionId = Global::getSessionIdFromHeader(str2);
	CCLOG(Global::gameSessionId.c_str());
}
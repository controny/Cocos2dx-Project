#include "GameScene.h"
#include "json/rapidjson.h"
#include "json/document.h"
#include "json/writer.h"
#include "json/stringbuffer.h"
#include "network/HttpClient.h"
#include <regex>
#include "SimpleAudioEngine.h"
#include "LoginScene.h"
using std::regex;
using std::match_results;
using std::regex_match;
using std::cmatch;
using namespace rapidjson;

USING_NS_CC;

cocos2d::Scene* GameScene::createScene() {
    // 'scene' is an autorelease object
    auto scene = Scene::create();

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

bool GameScene::init() {
    if (!Layer::init())
    {
        return false;
    }

    Size size = Director::getInstance()->getVisibleSize();
	Vec2 origin = Director::getInstance()->getVisibleOrigin();
    visibleHeight = size.height;
    visibleWidth = size.width;
	float winw = Director::getInstance()->getWinSize().width; //获取屏幕宽度
	float winh = Director::getInstance()->getWinSize().height;//获取屏幕高度
	auto bg = Sprite::create("bg.jpeg");
	bg->setPosition(Vec2(visibleWidth / 2 + origin.x, visibleHeight / 2 + origin.y));
	bg->setScaleX(winw / bg->getTextureRect().getMaxX()); //设置精灵宽度缩放比例
	bg->setScaleY(winh / bg->getTextureRect().getMaxY());
	this->addChild(bg, 0);
    score_field = TextField::create("Score", "Arial", 30);
    score_field->setPosition(Size(visibleWidth / 4, visibleHeight / 4 * 3));
	if (Global::gameSessionId.length() == 0)
	{
		score_field->setText("Only record login users' scores");
	}
	else {
		char str[100];
		sprintf(str, "%d", Global::score);
		score_field->setText(str);
	}
	this->addChild(score_field, 2);

	auto label2 = Label::createWithTTF("Best Score", "fonts/arial.TTF", 50);
	label2->setPosition(Size(visibleWidth / 4, visibleHeight / 4));
	this->addChild(label2, 2);
	ParticleSpiral* lizi = ParticleSpiral::create();
	lizi->setPosition(label2->getPosition());
	this->addChild(lizi, 1);

    rank_field = TextField::create("", "Arial", 30);
    rank_field->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4 * 2.5));
    this->addChild(rank_field, 2);

    rank_button = Button::create();
    rank_button->setTitleText("Rank");
    rank_button->setTitleFontSize(50);
    rank_button->setPosition(Size(visibleWidth / 4 * 3, visibleHeight / 4));
	rank_button->addClickEventListener(CC_CALLBACK_1(GameScene::onclickRank, this));
    this->addChild(rank_button, 2);
	ParticleSpiral* lizi2 = ParticleSpiral::create();
	lizi2->setPosition(rank_button->getPosition());
	this->addChild(lizi2, 1);

	auto back_button = Button::create();
	back_button->setTitleText("Back");
	back_button->setTitleFontSize(50);
	back_button->setPosition(Size(visibleWidth / 4 * 2, visibleHeight / 5));
	back_button->addClickEventListener(CC_CALLBACK_1(GameScene::onclickBack, this));
	this->addChild(back_button, 2);
    return true;
}

void GameScene::onclickBack(cocos2d::Ref* p)
{
	Director::getInstance()->replaceScene(LoginScene::createScene());
}
/*
void GameScene::onSubmitHttpComplete(HttpClient* sender, HttpResponse* response)
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
		score_field->setText(str);
	}
}*/
void GameScene::onclickRank(cocos2d::Ref* p)
{
	HttpRequest* request = new HttpRequest();

	request->setRequestType(HttpRequest::Type::GET);

	string url = Global::remoteServer + "/rank?top=10";
	request->setUrl(url.c_str());

	request->setResponseCallback(CC_CALLBACK_2(GameScene::onRankHttpComplete, this));
	
	std::vector<string> headers;
	string s = "Cookie: GAMESESSIONID=" + Global::gameSessionId;
	headers.push_back(s);
	request->setHeaders(headers);

	cocos2d::network::HttpClient::getInstance()->send(request);

	request->release();
}

void GameScene::onRankHttpComplete(HttpClient* sender, HttpResponse* response)
{
	if (!response) return;
	if (!response->isSucceed()) {
		log("response failed");
		log("error buffer: %s", response->getErrorBuffer());
	}
	rapidjson::Document d;
	std::vector<char> *buffer = response->getResponseData();
	std::string str = Global::toString(buffer);
	CCLOG("%s\n", str.c_str());
	
	d.Parse<0>(str.c_str());
	string temp = "";
	if (d.HasParseError()) CCLOG("GetParseError %s\n", d.GetParseError());
	if (d.IsObject() && d.HasMember("info")) 
	{
		str = d["info"].GetString();
		if (Global::gameSessionId.length() == 0) {
			rank_field->setText("Log in before you check the scores");
		}
		else {
			const char * delim = "|";
			char* p = const_cast<char*>(str.c_str());

			char* t = strtok(p, delim);
			while (t)
			{
				temp += t;
				temp += "\n";
				CCLOG("%s\n", t);
				t = strtok(NULL, delim);
			}
			rank_field->setText(temp);
		}
	}

}
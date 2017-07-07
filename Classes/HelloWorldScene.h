
#include "cocos2d.h"
#include "Obstacle.h"
#include "resource.h"
#include "ui/CocosGUI.h"
#include <string>
#include "Global.h"
using namespace cocos2d::ui;

#include "network/HttpClient.h"
using namespace cocos2d::network;
USING_NS_CC;

class HelloWorld : public cocos2d::Layer
{
public:
    static cocos2d::Scene* createScene();

    virtual bool init();
   
	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);

	virtual void update(float time);

	void addListener();
	void gameOver();
	void onBallCrashProps();
	bool addBall();

	void addProp(int offsetY);
	void replayCallback(Ref * pSender);
	void submitCallback(Ref * pSender);
	void preloadMusic(); 

	void onclickSubmit(cocos2d::Ref* p);

	void onSubmitHttpComplete(HttpClient* sender, HttpResponse* response);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

private:
	bool hasStart;
	Sprite* ball;
	float velocity;
	Obstacle* obstacle;
	Vector<Sprite *> props;
	Size visibleSize;
	int score;
	bool isMove;
	float obV;
	int coun;
	Label* scoreLabel;
	bool hasGameOver;
	Label* highest; //  xmx
};


#ifndef __HELLOWORLD_SCENE_H__
#define __HELLOWORLD_SCENE_H__

#include "cocos2d.h"
#include "Obstacle.h"
#include "resource.h"

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
};

#endif // __HELLOWORLD_SCENE_H__
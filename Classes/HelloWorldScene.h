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
	bool onConcactBegin(bool isObstacle, std::string color);
	bool addBall();

	void addProp(int offsetY);

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

};

#endif // __HELLOWORLD_SCENE_H__
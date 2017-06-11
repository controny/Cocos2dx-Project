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
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);

	void onKeyPressed(EventKeyboard::KeyCode code, Event* event);

	virtual void update(float time);

    // implement the "static create()" method manually
    CREATE_FUNC(HelloWorld);

	Obstacle* obstacle;
	Size visibleSize;

};

#endif // __HELLOWORLD_SCENE_H__

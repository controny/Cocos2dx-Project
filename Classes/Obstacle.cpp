#include "Obstacle.h"
#include "resource.h"

void Obstacle::onEnter()
{
	Node::onEnter();
	obstacleList = Array::create();
	obstacleList->retain();
}

void Obstacle::update()
{
	if (obstacleList == nullptr)
		return;
	for (int i = obstacleList->count() - 1; i >= 0; i--)
	{
		auto s = (Sprite*)obstacleList->getObjectAtIndex(i);
		float rotation = 1;
		s->setRotation(s->getRotation() + rotation);
	}
}

void Obstacle::addOne(int offsetY)
{
	Size visibleSize = Director::getInstance()->getWinSize();
	auto obstacle = Sprite::create(IMG_OBSTACLE);
	obstacle->setScale(0.5);
	Size obstacleSize = obstacle->getContentSize();
	obstacleList->addObject(obstacle);
	this->addChild(obstacle);

	// set positon
	obstacle->setPosition(Vec2(visibleSize.width / 2, offsetY));
	obstacle->setTag(TAG_OBSTACLE);
	cocos2d::log("a obstacle added");
}

void Obstacle::deleteOne()
{
	if (obstacleList == nullptr || obstacleList->count() == 0)
		return;
	auto s = (Sprite*)obstacleList->getObjectAtIndex(0);
	if (s && s->getPositionY() < -s->getContentSize().height / 2) {
		obstacleList->removeObjectAtIndex(0);
		this->removeChild(s);
		cocos2d::log("a obstacle removed");
	}
}

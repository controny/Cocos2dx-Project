#include "Obstacle.h"
#include "resource.h"

Obstacle::Obstacle()
{
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

Property Obstacle::getBottomProperty(int index)
{
	auto obstacle = (Sprite *)obstacleList->getObjectAtIndex(index);
	auto rotation = (int)(obstacle->getRotation()) % 360;
	return getPropertyByRotation(rotation);
}

Property Obstacle::getTopProperty(int index)
{
	auto obstacle = (Sprite *)obstacleList->getObjectAtIndex(index);
	// Suppose that the obstacle ratates another half circle
	auto rotation = (int)(obstacle->getRotation() + 180) % 360;
	return getPropertyByRotation(rotation);
}

Property Obstacle::getPropertyByRotation(int rotation)
{
	static const int Section = 72;
	static const int Half_Section = 36;
	static const int Circle = 360;
	static const int CIRCLE_SHUI_MIN = Half_Section;
	static const int CIRCLE_SHUI_MAX = Circle - Half_Section;
	static const int CIRCLE_MU_MIN = Half_Section;
	static const int CIRCLE_MU_MAX = CIRCLE_MU_MIN + Section;
	static const int CIRCLE_JIN_MIN = Half_Section + Section;
	static const int CIRCLE_JIN_MAX = CIRCLE_JIN_MIN + Section;
	static const int CIRCLE_HUO_MIN = Half_Section + Section * 2;
	static const int CIRCLE_HUO_MAX = CIRCLE_HUO_MIN + Section;
	static const int CIRCLE_TU_MIN = Half_Section + Section * 3;
	static const int CIRCLE_TU_MAX = CIRCLE_TU_MIN + Section;

	if ((rotation >= 0 && rotation < CIRCLE_SHUI_MIN) || rotation >= CIRCLE_SHUI_MAX)
		return Shui;
	else if (rotation >= CIRCLE_MU_MIN && rotation < CIRCLE_MU_MAX)
		return Mu;
	else if (rotation >= CIRCLE_JIN_MIN && rotation < CIRCLE_JIN_MAX)
		return Jin;
	else if (rotation >= CIRCLE_HUO_MIN && rotation < CIRCLE_HUO_MAX)
		return Huo;
	else if (rotation >= CIRCLE_TU_MIN && rotation < CIRCLE_TU_MAX)
		return Tu;
}

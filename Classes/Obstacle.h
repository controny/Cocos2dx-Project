#ifndef OBSTACLE
#define OBSTACLE

#include "cocos2d.h"

using namespace cocos2d;

class  Obstacle :public Node
{
public:
	Array* obstacleList;

	virtual void onEnter();

	// 令障碍旋转
	void update(); 

	// 添加障碍
	void addOne(int offsetY);

	// 删除界面外的障碍
	void deleteOne();
};

#endif

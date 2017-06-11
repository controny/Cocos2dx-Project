#ifndef OBSTACLE
#define OBSTACLE

#include "cocos2d.h"

using namespace cocos2d;

class  Obstacle :public Node
{
public:
	Array* obstacleList;

	virtual void onEnter();

	// rotate  the obstacle
	void update(); 

	// add an obstacle
	void addOne(int offsetY);

	// delete the obstacles outside the window
	void deleteOne();
};

#endif

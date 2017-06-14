#ifndef OBSTACLE
#define OBSTACLE

#include "cocos2d.h"
#include "resource.h"

using namespace cocos2d;

class  Obstacle :public Node
{
public:
	Array* obstacleList;

	virtual void onEnter();

	/**
	 * Rotate  the obstacle
	 */
	void update(); 

	/**
	 * Add an obstacle
	 * @param offsetY position Y of the new obstacle
	 */
	void addOne(int offsetY);

	/**
	 * Delete the obstacle outside the window
	 */
	void deleteOne();

	/**
	 * Get the bottom property of an obstacle specified by index
	 * @param  index the index of the obstacle in the array
	 * @return       a constant in enumeration Property
	 */
	Property getBottomProperty(int index);

	/**
	 * Get the top property of an obstacle specified by index
	 * @param  index the index of the obstacle in the array
	 * @return       a constant in enumeration Property
	 */
	Property getTopProperty(int index);

private:

	/**
	 * Get the responding property based on rotation
	 * @param  rotation the rotation of an obstacle
	 * @return       a constant in enumeration Property   
	 */
	Property getPropertyByRotation(int rotation);
};

#endif

#ifndef __CUSTOM_FOLLOW__
#define __CUSTOM_FOLLOW__

#include "cocos2d.h"

class CustomFollow : public cocos2d::Follow
{
public:
	CustomFollow(){}
	~CustomFollow(){}

	bool initWithTarget(cocos2d::Node *followedNode, const cocos2d::Rect& rect = cocos2d::Rect::ZERO);
	void step(float dt) override;
	static CustomFollow* create(cocos2d::Node *followedNode, const cocos2d::Rect& rect = cocos2d::Rect::ZERO);

private:

};

#endif
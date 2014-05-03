#pragma once

#include "cocos2d.h"

class PlayerFollower : public cocos2d::Sprite
{
public:
	PlayerFollower(){}
	CREATE_FUNC(PlayerFollower);
	static PlayerFollower* createWithTexture(cocos2d::Texture2D *texture);
	void Init(){ _opacity = 255; }

private:
	float _opacity;

};
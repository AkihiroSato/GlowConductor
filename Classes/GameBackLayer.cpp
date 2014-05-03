#include "GameBackLayer.h"

USING_NS_CC;


// on "init" you need to initialize your instance
bool GameBackLayer::init()
{
    //////////////////////////////
    // 1. super init first
	if (!LayerColor::initWithColor(Color4B(0, 100, 30, 255)))
    {
        return false;
    }    

    return true;
}


// XVˆ—
void GameBackLayer::Update()
{
	this->setPosition(_pCameraTargetPos);
}

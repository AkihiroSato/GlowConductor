#include "ResultScene.h"
#include "TitleScene.h"
#include "SDataMgr.h"

USING_NS_CC;

Scene* ResultScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = ResultScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool ResultScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);

    /////////////////////////////
    // 3. add your codes below...
    auto label = LabelTTF::create("Hello World", "Arial", 200);
    
    // position the label on the center of the screen
    label->setPosition(Point(	Director::getInstance()->getWinSize().width / 2,
								Director::getInstance()->getWinSize().height / 2));
	String* scoreString = String::createWithFormat("%d", SDataMgr::Instance()->GetScore());
	label->setString(scoreString->getCString());

    // add the label as a child to this layer
    this->addChild(label, 1);

    // add "HelloWorld" splash screen"
    auto sprite = Sprite::create("result_back_graph.png");

    // position the sprite on the center of the screen
    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));
	sprite->setColor(Color3B(255, 0, 0));

    // add the sprite as a child to this layer
    this->addChild(sprite, 0);
    
    return true;
}


// タッチ開始時
bool ResultScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, TitleScene::createScene()));
	return false;
}
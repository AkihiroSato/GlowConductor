#include "TitleScene.h"
#include "GameScene.h"
#include "SGraphMgr.h"

USING_NS_CC;

Scene* TitleScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
    
    // 'layer' is an autorelease object
    auto layer = TitleScene::create();

    // add layer as a child to scene
    scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool TitleScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init() )
    {
        return false;
    }
    
	SGraphMgr::Instance()->SetUsingGraph(eScene_title);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);

	// スタートボタン作成
	MenuItemImage *pStartItem =
		MenuItemImage::create(
		"title_start_button.png",
		"title_start_button.png",
		this,
		menu_selector(TitleScene::TapStartbutton));

	Menu* pStartMenu = Menu::create(pStartItem, NULL); // NULLを忘れては動かない
	pStartMenu->setPosition(
		Point(Director::getInstance()->getWinSize().width / 2, 
		Director::getInstance()->getWinSize().height / 5));

	// アクション設定
	pStartItem->setRotation(-5);
	ActionInterval* rotateAct = Sequence::create(
		EaseInOut::create(RotateBy::create(0.6f, 10), 2.0f),
		EaseInOut::create(RotateBy::create(0.6f, -10), 2.0f),
		nullptr);
	pStartItem->runAction(RepeatForever::create(rotateAct));
	this->addChild(pStartMenu, 2);

	// タイトル文字表示
	Sprite* pTitleSprite_1 = Sprite::createWithTexture(SGraphMgr::Instance()->GetBatchTexture(SGraphMgr::eGraph_title_name_1));
	Sprite* pTitleSprite_2 = Sprite::createWithTexture(SGraphMgr::Instance()->GetBatchTexture(SGraphMgr::eGraph_title_name_2));

	pTitleSprite_1->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 4 * 3);
	pTitleSprite_2->setPosition(Director::getInstance()->getWinSize().width / 2.0f, Director::getInstance()->getWinSize().height / 2);

	this->addChild(pTitleSprite_1, 1);
	this->addChild(pTitleSprite_2, 1);

    // タイトルバック表示
	auto sprite = Sprite::createWithTexture(SGraphMgr::Instance()->GetBatchTexture(SGraphMgr::eGraph_title_back_graph));

    sprite->setPosition(Point(visibleSize.width/2 + origin.x, visibleSize.height/2 + origin.y));

    this->addChild(sprite, 0);
    
    return true;
}


void TitleScene::menuCloseCallback(Ref* pSender)
{
#if (CC_TARGET_PLATFORM == CC_PLATFORM_WP8) || (CC_TARGET_PLATFORM == CC_PLATFORM_WINRT)
	MessageBox("You pressed the close button. Windows Store Apps do not implement a close button.","Alert");
    return;
#endif

    Director::getInstance ()->end();

#if (CC_TARGET_PLATFORM == CC_PLATFORM_IOS)
    exit(0);
#endif
}

// タッチ開始時
bool TitleScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	return true;
}

// スタートボタンをタップしたときに呼ばれる関数
void TitleScene::TapStartbutton(Ref* sender)
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, GameScene::createScene()));
}
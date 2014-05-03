#include "GameScene.h"
#include "CPlayer.h"
#include "CDark.h"
#include "Collision.h"
#include "ObjectMgr.h"
#include "CustomFollow.h"
#include "ObjectFactory.h"
#include "SGraphMgr.h"
#include "GameBackLayer.h"
#include "ResultScene.h"
#include "SDataMgr.h"
#include "SCameraTargetMgr.h"
#include "CustomParticle.h"
#include "GameLayer.h"
#include "PlayerFollower.h"

USING_NS_CC;

// 仮のタグ定義
static const int PLAYER_TAG = 1;
static const int TARGET_CAMERA_TAG = 2;
static const int TOUCH_NUM_TAG = 3;
static const int TOUCH_BACK_TAG = 4;
static const int BACK_LAYER_TAG = 5;	// 背景レイヤーのタグ
static const int UI_LAYER_TAG = 6;		// UIレイヤーのタグ
static const int OBJ_FACTORY_TAG = 7;

Scene* GameScene::_spGameScene = nullptr;

Scene* GameScene::createScene()
{
    // 'scene' is an autorelease object
    auto scene = Scene::create();
	_spGameScene = scene;

    // 'layer' is an autorelease object
    auto layer = GameScene::create();

	scene->addChild(layer);

    // return the scene
    return scene;
}

// on "init" you need to initialize your instance
bool GameScene::init()
{
    //////////////////////////////
    // 1. super init first
    if ( !Layer::init())
    {
        return false;
    }    

	// 各レイヤーを初期化する
	_pGameLayer = GameLayer::create();
	_pBackLayer = GameBackLayer::create();
	_pUiLayer = Layer::create();
	this->addChild(_pBackLayer);
	this->addChild(_pGameLayer);
	this->addChild(_pUiLayer);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// タッチモードを設定する
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);

	// スケジュールを設定
	this->scheduleUpdate();

	// フラグの初期化
	_gameEndFlag = false;

	// 使用画像の読み込み
	SGraphMgr::Instance()->SetUsingGraph(eScene_Game);
	SGraphMgr::Instance()->AddUsingScene(this);

	// カメラターゲットを設定
	SCameraTargetMgr::Instance()->SetCameraTarget(CameraTarget::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_Ball)->getTexture()));
	_pGameLayer->addChild(TargetPointer);

	// オブジェクト生成関数を生成する
	ObjectFactory* objFactory = ObjectFactory::create();
	objFactory->SetNode(_pGameLayer);
	objFactory->setTag(OBJ_FACTORY_TAG);
	objFactory->InitObjectData();
	_pGameLayer->addChild(objFactory);

	// オブジェクト管理変数を生成
	objectMgr = ObjectMgr::create();
	objectMgr->InitObjMgr();
	_pGameLayer->addChild(objectMgr);

	// プレイヤー生成
	CPlayer* pPlayer = CPlayer::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_Ball)->getTexture());
	pPlayer->setPosition(Point(pPlayer->GetRadius(), Director::getInstance()->getWinSize().height * 0.5f));
	pPlayer->setTag(PLAYER_TAG);
	objectMgr->SetPlayerStateChanger(pPlayer);
	_pGameLayer->addChild(pPlayer, 2);
	objectMgr->RegistObject(0, pPlayer);

	// スコアを表示させる
	pPlayer->ShowState(_pUiLayer);

	// カメラをターゲットに追従させる
	CustomFollow* actFollow = CustomFollow::create(TargetPointer);
	_pGameLayer->runAction(actFollow);
    
    return true;
}

// タッチ開始時
bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	// 各ノードを取得
	CPlayer* pPlayer = (CPlayer*)_pGameLayer->getChildByTag(PLAYER_TAG);

	if (pPlayer->GetTouchRemain() <= 0) return true;

	// 画面移動に伴うタップ位置のずれを補正し、プレイヤーに渡す
	Point hosei = Point(TargetPointer->getPosition().x - Director::getInstance()->getWinSize().width * 0.5f, 0);
	pPlayer->SetTouchPoint(touch->getLocation() + hosei);

	// タッチ残り回数を減らす
	pPlayer->DownTouch(1);

	// タッチのパーティクルを表示
	ParticleSystemQuad* particle = MyParticles::TouchParticle::create();
	particle->setPosition(touch->getLocation() + hosei);

	_pGameLayer->addChild(particle);

	return true;
}

// 更新処理
void GameScene::update(float time)
{
	// 各ノードをレイヤーより取得する
	CPlayer* pPlayer = (CPlayer*)_pGameLayer->getChildByTag(PLAYER_TAG);
	ObjectFactory* objFactory = (ObjectFactory*)_pGameLayer->getChildByTag(OBJ_FACTORY_TAG);

	// ターゲットを更新
	TargetPointer->Update(pPlayer->getPosition());

	// プレイヤー情報を更新
	pPlayer->Move();
	pPlayer->UpdateScore();
	pPlayer->UpdateTapRemain();

	//// プレイヤーに追従する残影を表示させる
	//PlayerFollower* pFollower = PlayerFollower::createWithTexture(pPlayer->getTexture());
	//pFollower->setPosition(pPlayer->getPosition());
	//pFollower->setScale(pPlayer->getScale());
	//_pGameLayer->addChild(pFollower);

	// プレイヤーの位置によってオブジェクトを自動生成
	CObject* obj = objFactory->AutoCraeteObject(TargetPointer->getPosition());
	if (obj != nullptr)
	{
		objectMgr->RegistObject(1, obj);
	}

	// 衝突判定を行う
	objectMgr->CalcCollision();

	// オブジェクトマネージャの更新
	objectMgr->Update(TargetPointer->getPosition());

	// プレイヤーのキルフラグを取得し、フラグが立っていたら殺す
	if (pPlayer->GetKillFlag())
	{
		SDataMgr::Instance()->SetScore(pPlayer->GetScore());
		ChangeSceneResult();
		this->unscheduleUpdate();
	}
}

// リザルトシーンへ移行
void GameScene::ChangeSceneResult()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ResultScene::createScene()));
}
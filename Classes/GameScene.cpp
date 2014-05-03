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

// ���̃^�O��`
static const int PLAYER_TAG = 1;
static const int TARGET_CAMERA_TAG = 2;
static const int TOUCH_NUM_TAG = 3;
static const int TOUCH_BACK_TAG = 4;
static const int BACK_LAYER_TAG = 5;	// �w�i���C���[�̃^�O
static const int UI_LAYER_TAG = 6;		// UI���C���[�̃^�O
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

	// �e���C���[������������
	_pGameLayer = GameLayer::create();
	_pBackLayer = GameBackLayer::create();
	_pUiLayer = Layer::create();
	this->addChild(_pBackLayer);
	this->addChild(_pGameLayer);
	this->addChild(_pUiLayer);

    Size visibleSize = Director::getInstance()->getVisibleSize();
    Point origin = Director::getInstance()->getVisibleOrigin();

	// �^�b�`���[�h��ݒ肷��
	this->setTouchEnabled(true);
	this->setTouchMode(kCCTouchesOneByOne);

	// �X�P�W���[����ݒ�
	this->scheduleUpdate();

	// �t���O�̏�����
	_gameEndFlag = false;

	// �g�p�摜�̓ǂݍ���
	SGraphMgr::Instance()->SetUsingGraph(eScene_Game);
	SGraphMgr::Instance()->AddUsingScene(this);

	// �J�����^�[�Q�b�g��ݒ�
	SCameraTargetMgr::Instance()->SetCameraTarget(CameraTarget::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_Ball)->getTexture()));
	_pGameLayer->addChild(TargetPointer);

	// �I�u�W�F�N�g�����֐��𐶐�����
	ObjectFactory* objFactory = ObjectFactory::create();
	objFactory->SetNode(_pGameLayer);
	objFactory->setTag(OBJ_FACTORY_TAG);
	objFactory->InitObjectData();
	_pGameLayer->addChild(objFactory);

	// �I�u�W�F�N�g�Ǘ��ϐ��𐶐�
	objectMgr = ObjectMgr::create();
	objectMgr->InitObjMgr();
	_pGameLayer->addChild(objectMgr);

	// �v���C���[����
	CPlayer* pPlayer = CPlayer::createWithTexture(SGraphMgr::Instance()->GetSpriteBatch(SGraphMgr::eGraph_Ball)->getTexture());
	pPlayer->setPosition(Point(pPlayer->GetRadius(), Director::getInstance()->getWinSize().height * 0.5f));
	pPlayer->setTag(PLAYER_TAG);
	objectMgr->SetPlayerStateChanger(pPlayer);
	_pGameLayer->addChild(pPlayer, 2);
	objectMgr->RegistObject(0, pPlayer);

	// �X�R�A��\��������
	pPlayer->ShowState(_pUiLayer);

	// �J�������^�[�Q�b�g�ɒǏ]������
	CustomFollow* actFollow = CustomFollow::create(TargetPointer);
	_pGameLayer->runAction(actFollow);
    
    return true;
}

// �^�b�`�J�n��
bool GameScene::onTouchBegan(Touch* touch, Event* unused_event)
{
	// �e�m�[�h���擾
	CPlayer* pPlayer = (CPlayer*)_pGameLayer->getChildByTag(PLAYER_TAG);

	if (pPlayer->GetTouchRemain() <= 0) return true;

	// ��ʈړ��ɔ����^�b�v�ʒu�̂����␳���A�v���C���[�ɓn��
	Point hosei = Point(TargetPointer->getPosition().x - Director::getInstance()->getWinSize().width * 0.5f, 0);
	pPlayer->SetTouchPoint(touch->getLocation() + hosei);

	// �^�b�`�c��񐔂����炷
	pPlayer->DownTouch(1);

	// �^�b�`�̃p�[�e�B�N����\��
	ParticleSystemQuad* particle = MyParticles::TouchParticle::create();
	particle->setPosition(touch->getLocation() + hosei);

	_pGameLayer->addChild(particle);

	return true;
}

// �X�V����
void GameScene::update(float time)
{
	// �e�m�[�h�����C���[���擾����
	CPlayer* pPlayer = (CPlayer*)_pGameLayer->getChildByTag(PLAYER_TAG);
	ObjectFactory* objFactory = (ObjectFactory*)_pGameLayer->getChildByTag(OBJ_FACTORY_TAG);

	// �^�[�Q�b�g���X�V
	TargetPointer->Update(pPlayer->getPosition());

	// �v���C���[�����X�V
	pPlayer->Move();
	pPlayer->UpdateScore();
	pPlayer->UpdateTapRemain();

	//// �v���C���[�ɒǏ]����c�e��\��������
	//PlayerFollower* pFollower = PlayerFollower::createWithTexture(pPlayer->getTexture());
	//pFollower->setPosition(pPlayer->getPosition());
	//pFollower->setScale(pPlayer->getScale());
	//_pGameLayer->addChild(pFollower);

	// �v���C���[�̈ʒu�ɂ���ăI�u�W�F�N�g����������
	CObject* obj = objFactory->AutoCraeteObject(TargetPointer->getPosition());
	if (obj != nullptr)
	{
		objectMgr->RegistObject(1, obj);
	}

	// �Փ˔�����s��
	objectMgr->CalcCollision();

	// �I�u�W�F�N�g�}�l�[�W���̍X�V
	objectMgr->Update(TargetPointer->getPosition());

	// �v���C���[�̃L���t���O���擾���A�t���O�������Ă�����E��
	if (pPlayer->GetKillFlag())
	{
		SDataMgr::Instance()->SetScore(pPlayer->GetScore());
		ChangeSceneResult();
		this->unscheduleUpdate();
	}
}

// ���U���g�V�[���ֈڍs
void GameScene::ChangeSceneResult()
{
	Director::getInstance()->replaceScene(TransitionFade::create(1.0f, ResultScene::createScene()));
}
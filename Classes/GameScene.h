#ifndef __GAME_SCENE_H__
#define __GAME_SCENE_H__

#include "cocos2d.h"

class ObjectMgr;
class CameraTarget;
class GameBackLayer;
class GameLayer;

class GameScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
    CREATE_FUNC(GameScene);

	// �^�b�`�J�n���ɌĂ΂��֐�
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// �X�V����
	void update(float time);

private:
	// ���U���g�V�[���֑J�ڂ���
	void ChangeSceneResult();

	// �I�u�W�F�N�g�Ǘ�
	ObjectMgr* objectMgr;

	// �Q�[���I���t���O
	bool _gameEndFlag;

	// �Q�[���V�[���̃A�h���X
	static cocos2d::Scene* _spGameScene;

	//****************************************
	// ���C���[�Ǘ�
	//****************************************
	GameLayer* _pGameLayer;
	GameBackLayer* _pBackLayer;
	Layer*	_pUiLayer;

};

#endif // __HELLOWORLD_SCENE_H__

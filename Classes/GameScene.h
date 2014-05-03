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

	// タッチ開始時に呼ばれる関数
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// 更新処理
	void update(float time);

private:
	// リザルトシーンへ遷移する
	void ChangeSceneResult();

	// オブジェクト管理
	ObjectMgr* objectMgr;

	// ゲーム終了フラグ
	bool _gameEndFlag;

	// ゲームシーンのアドレス
	static cocos2d::Scene* _spGameScene;

	//****************************************
	// レイヤー管理
	//****************************************
	GameLayer* _pGameLayer;
	GameBackLayer* _pBackLayer;
	Layer*	_pUiLayer;

};

#endif // __HELLOWORLD_SCENE_H__

#ifndef __GAME_BACK_H__
#define __GAME_BACK_H__

#include "cocos2d.h"

class GameBackLayer : public cocos2d::LayerColor
{
public:
    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // implement the "static create()" method manually
	CREATE_FUNC(GameBackLayer);

	// 更新処理
	void Update();

	// カメラターゲットのセット
	void SetCameraTarget(cocos2d::Point target){ _pCameraTargetPos = target; }

private:
	// カメラターゲットの位置座標を保存
	cocos2d::Point _pCameraTargetPos;
};

#endif // __HELLOWORLD_SCENE_H__

#pragma once

#include "cocos2d.h"

class CameraTarget : public cocos2d::Sprite
{
public:
	CameraTarget();
	~CameraTarget(){}
	
	// 更新処理
	void Update(const cocos2d::Point& playerPoint);

	// クリエイト関数
	CREATE_FUNC(CameraTarget);
	static CameraTarget* createWithTexture(cocos2d::Texture2D *texture);

	// 

private:
	float _movedX;	// 1フレームでどれだけ動いたか
};


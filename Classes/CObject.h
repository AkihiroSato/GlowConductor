#ifndef __C_OBJECT_H__
#define __C_OBJECT_H__

#include "cocos2d.h"
#include "BaseAI.h"
#include "IPlayerStateChange.h"

static const float BALL_RADIUS = 256;
static const float TOUCH_UP_RADIAN = 256.0f;
class CPlayer;

class CObject : public cocos2d::Sprite
{
public:
	CObject(){}
	CObject(float radius, float x, float y){ 
		_radius = radius;
		this->setPosition(cocos2d::Point(x, y));
		this->setScale(_radius / BALL_RADIUS);
	}

	// 衝突時に実行される関数
	virtual void CollisionFunction(IPlayerStateChange* playerStateChanger){}

	// オブジェクトの更新処理
	virtual void Update(){}

	// 半径取得
	float GetRadius(){ return _radius; }

	// クリエイト関数
	CREATE_FUNC(CObject);

	// ステータスを設定する
	void SetState(float radius, float x, float y, BaseAI* ai = nullptr)
	{
		_radius = radius;
		this->setPosition(cocos2d::Point(x, y));
		this->setScale(_radius / BALL_RADIUS);
		pAi = ai;
		_hitDeleteFlag = false;
	}

	// 衝突時に消えるかどうか取得
	bool GetDeleteFlag(){ return _hitDeleteFlag; }

protected:
	float _radius;		// 半径
	BaseAI* pAi;		// AI
	bool _hitDeleteFlag;

};

#endif
#ifndef __C_DARK_H__
#define __C_DARK_H__

#include "CObject.h"

class CDark : public CObject
{
public:
	CDark();
	CDark(float radius, float x, float y);
	virtual ~CDark();

	// 更新処理
	void update(float delta);

	// 衝突時に実行される関数
	void CollisionFunction(IPlayerStateChange* playerStateChanger);

	// クリエイト関数
	CREATE_FUNC(CDark);
	static CDark* createWithTexture(cocos2d::Texture2D *texture);

private:
	//++++++++++++++++++++++++++++++++++++++
	// プライベート変数
	//++++++++++++++++++++++++++++++++++++++
			

	//++++++++++++++++++++++++++++++++++++++
	// プライベート関数
	//++++++++++++++++++++++++++++++++++++++
	
};

#endif

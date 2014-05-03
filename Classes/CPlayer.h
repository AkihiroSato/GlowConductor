#ifndef __C_PLAYER_H__
#define __C_PLAYER_H__

#include "CObject.h"
#include "IPlayerStateChange.h"

static const int TOUCH_REMAIN_INIT = 10;

class CPlayer : public CObject, public IPlayerStateChange
{
public:
	CPlayer();
	~CPlayer();

	// 親レイヤーノードを登録する
	void SetParent(cocos2d::Node* parentNode);

	// 更新処理
	void Update(){}

	// 進む処理
	void Move();

	// スコアを更新する
	void UpdateScore();
	// タップ回数を更新
	void UpdateTapRemain();

	// スコアを表示する関数
	void ShowState(cocos2d::Node* parentNode);

	// スコアを取得する
	int GetScore(){ return _score; }

	// タッチされた座標を取得する
	void SetTouchPoint(const cocos2d::Point& point);

	// クリエイト関数
	CREATE_FUNC(CPlayer);
	static CPlayer* createWithTexture(cocos2d::Texture2D *texture);

	// オブジェクトにあたった時の処理
	void CollisionFunction(IPlayerStateChange* playerStateChanger) override;

	int GetTouchRemain(){ return _remainTap; }

	// プレイヤーのキルフラグを取得する
	bool GetKillFlag(){ return _killFlag; }

	//**************************************
	// プレイヤーの状態変化をオーバーライド
	//**************************************
	// 残りタッチ回数を加える
	void AddTouch(int add);
	void DownTouch(int down);
	void ScoreUp(int score);
	void ScoreDown(int score);
	void KillPlayer();

private:
	//++++++++++++++++++++++++++++++++++++++
	// プライベート変数
	//++++++++++++++++++++++++++++++++++++++

	bool _killFlag;						// 死亡フラグ
	bool _turnFlag;						// 曲がる必要がある場合、曲げるフラグ

	float _speed;						// 速さ
	float _moveRadian;					// 進む角度(右方向を0とした場合)
	float _turnRadianMax;				// 曲がり角度の最大値

	int _remainTap;						// タップできる回数
	cocos2d::Sprite* _pTapRemainBack;	// 残りタップ回数の背景
	cocos2d::Label* _pTapRemainLabel;	// 残りタップ回数を表示するラベル

	cocos2d::Point _touchedPoint;		// 最後にタッチされたポイント

	float _score;						// スコア
	cocos2d::Label* _pScoreLabel;		// スコアを表示するためのラベル

	cocos2d::Node*	_pParentNode;		//	親のノードを設定する

	//++++++++++++++++++++++++++++++++++++++
	// プライベート関数
	//++++++++++++++++++++++++++++++++++++++

	// 曲がる処理
	void Turn();		

};

#endif // __HELLOWORLD_SCENE_H__

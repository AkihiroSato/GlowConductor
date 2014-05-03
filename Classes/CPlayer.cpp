#include "CPlayer.h"
#include "CalclateMcr.h"
#include "CCScriptSupport.h"
#include "SCameraTargetMgr.h"
#include "CustomParticle.h"
#include "SGraphMgr.h"

USING_NS_CC;

// コンストラクタ
CPlayer::CPlayer()
{
	// パラメータの設定
	_turnFlag = false;
	_speed = 6.0f;
	_moveRadian = 0.0f;
	_turnRadianMax = 0.03f;
	_radius = 64.0f;
	_remainTap = TOUCH_REMAIN_INIT;
	_hitDeleteFlag = false;
	_killFlag = false;

	// スコアの設定
	_score = 0;
	_pScoreLabel = Label::create("a", "fonts/sp-setofont.ttf", 100);
	_pScoreLabel->setAnchorPoint(Point(1.0f, 0.0f));
	_pScoreLabel->setPosition(
		Director::getInstance()->getWinSize().width, 
		0);

	// 残りタップ回数の背景設定
	_pTapRemainBack = Sprite::createWithTexture(SGraphMgr::Instance()->GetBatchTexture(SGraphMgr::eGraph_TouchBack));
	_pTapRemainBack->setPosition(Point(
		_pTapRemainBack->getContentSize().width / 2,
		Director::getInstance()->getWinSize().height - _pTapRemainBack->getContentSize().height / 2));

	// 残りタップ回数設定
	String* pTapRemain = String::createWithFormat("%d", _remainTap);
	_pTapRemainLabel = Label::create(pTapRemain->getCString(), "", 100);
	_pTapRemainLabel->setPosition(_pTapRemainBack->getPosition());
	_pTapRemainLabel->setColor(Color3B(0, 0, 255));

	// 大きさを合わせる
	this->setScale(_radius / BALL_RADIUS);
}

// デストラクタ
CPlayer::~CPlayer()
{

}

//**********************************************************************
// 親ノードを設定する
//**********************************************************************
void CPlayer::SetParent(Node* parentNode)
{
	_pParentNode = parentNode;
}

//**********************************************************************
// 進む処理
//**********************************************************************
void CPlayer::Move()
{
	// 曲がる必要がある場合、曲げる
	if (_turnFlag == true) Turn();

	// X,Y方向の移動距離を計算
	float moveX = _speed * cosf(_moveRadian);
	float moveY = _speed * sinf(_moveRadian);

	// 現在の位置に、移動分を加算する
	this->setPosition(Point(this->getPosition().x + moveX, this->getPosition().y + moveY));

	// プレイヤーが画面外に出た場合、キルフラグを立てる
	if (TargetPointer->getPositionX() - Director::getInstance()->getWinSize().width / 2 + this->GetRadius() > this->getPosition().x ||
		this->getPosition().y < this->GetRadius() ||
		this->getPosition().y > Director::getInstance()->getWinSize().height - this->GetRadius())
	{
		this->KillPlayer();
	}
}

//**********************************************************************
// 曲がる処理
//**********************************************************************
void CPlayer::Turn()
{
	// タッチポイントと現在地との角度を求める
	float distanceX = _touchedPoint.x - this->getPosition().x;
	float distanceY = _touchedPoint.y - this->getPosition().y;

	float radian = atan2f(distanceY, distanceX);

	// 差によって、右回り、左回りを決める
	float defRadian = radian - _moveRadian;

	if (defRadian > 0.0f)
	{
		if (defRadian < PI)
		{
			// 角度が、最大曲がり角度より小さい場合、その差分回転をさせ、フラグを切る
			if (defRadian < _turnRadianMax)
			{
				_moveRadian -= defRadian;
				_turnFlag = false;
			}
			else	_moveRadian += _turnRadianMax;
		}
		if (defRadian > PI){
			if ((defRadian - PI * 2) > _turnRadianMax)
			{
				_moveRadian += (defRadian - PI * 2);
				_turnFlag = false;
			}
			else	_moveRadian -= _turnRadianMax;
		}
	}
	else if (defRadian < 0.0f)
	{
		if (defRadian > -PI)
		{
			// 角度が、最大曲がり角度より小さい場合、その差分回転をさせ、フラグを切る
			if (-defRadian < _turnRadianMax)
			{
				_moveRadian += defRadian;
				_turnFlag = false;
			}
			else	_moveRadian -= _turnRadianMax;
		}
		if (defRadian < -PI)
		{
			if ((defRadian + PI * 2) < _turnRadianMax)
			{
				_moveRadian += (defRadian + PI * 2);
				_turnFlag = false;
			}
			else	_moveRadian += _turnRadianMax;
		}
	}

	// 進行角度の補正を行う
	if (_moveRadian > PI * 2)	_moveRadian = _moveRadian - 2 * PI;
	if (_moveRadian < -PI * 2)	_moveRadian = _moveRadian + 2 * PI;

}

//**********************************************************
// タッチされた座標を取得する
//**********************************************************
void CPlayer::SetTouchPoint(const Point& point)
{
	_touchedPoint = point;
	_turnFlag = true;
}

//**********************************************************
// クリエイト関数
//**********************************************************
CPlayer* CPlayer::createWithTexture(Texture2D *texture)
{
	CPlayer *sprite = new CPlayer();
	if (sprite && sprite->initWithTexture(texture))
	{
		sprite->autorelease();
		return sprite;
	}
	CC_SAFE_DELETE(sprite);
	return nullptr;
}

//**********************************************************
// 衝突時
//**********************************************************
void CPlayer::CollisionFunction(IPlayerStateChange* playerStateChanger)
{

}

//**********************************************************
// スコアを加算する
//**********************************************************
void CPlayer::UpdateScore()
{
	_score = (_score < this->getPosition().x ? this->getPosition().x : _score) / 10;
	String* scoreString = String::createWithFormat("Score : %d", (int)_score );
	_pScoreLabel->setString(scoreString->getCString());
	_pScoreLabel->setPosition(Director::getInstance()->getWinSize().width, 0.0f);
}

//**********************************************************
// タップ回数の更新
//**********************************************************
void CPlayer::UpdateTapRemain()
{
	String* pTapRemain = String::createWithFormat("%d", _remainTap);
	_pTapRemainLabel->setString(pTapRemain->getCString());
}

//**********************************************************
//	スコアとタップ回数を表示
//**********************************************************
void CPlayer::ShowState(Node* pUiLayer)
{
	pUiLayer->addChild(_pScoreLabel);
	pUiLayer->addChild(_pTapRemainBack);
	pUiLayer->addChild(_pTapRemainLabel);
}


//**************************************
// プレイヤーの状態変化をオーバーライド
//**************************************
void CPlayer::AddTouch(int add)
{ 
	this->_remainTap += add;

	// タップ回数アップのアクションをつける
	ActionInterval* scaleUp = Sequence::createWithTwoActions(EaseOut::create(ScaleTo::create(0.1f, 1.4f), 1.0f), EaseOut::create(ScaleTo::create(0.5f, 1.0f), 1.f));
	//ActionInterval* scaleUp = Sequence::createWithTwoActions(EaseOut::create(TintBy::create(0.1f, 255.0f, 0.0f, 0.0f ), 1.0f), EaseOut::create(ScaleTo::create(0.5f, 1.0f), 1.f));

	_pTapRemainLabel->runAction(scaleUp);
}
void CPlayer::DownTouch(int down)
{ 
	_remainTap -= down;
	if (_remainTap < 0) _remainTap = 0;
}
void CPlayer::ScoreUp(int score)
{
	// スコアを挙げる
	_score += score;
}
void CPlayer::ScoreDown(int score){ _score -= score; }
void CPlayer::KillPlayer(){ _killFlag = true; }
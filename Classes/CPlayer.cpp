#include "CPlayer.h"
#include "CalclateMcr.h"
#include "CCScriptSupport.h"
#include "SCameraTargetMgr.h"
#include "CustomParticle.h"
#include "SGraphMgr.h"

USING_NS_CC;

// �R���X�g���N�^
CPlayer::CPlayer()
{
	// �p�����[�^�̐ݒ�
	_turnFlag = false;
	_speed = 6.0f;
	_moveRadian = 0.0f;
	_turnRadianMax = 0.03f;
	_radius = 64.0f;
	_remainTap = TOUCH_REMAIN_INIT;
	_hitDeleteFlag = false;
	_killFlag = false;

	// �X�R�A�̐ݒ�
	_score = 0;
	_pScoreLabel = Label::create("a", "fonts/sp-setofont.ttf", 100);
	_pScoreLabel->setAnchorPoint(Point(1.0f, 0.0f));
	_pScoreLabel->setPosition(
		Director::getInstance()->getWinSize().width, 
		0);

	// �c��^�b�v�񐔂̔w�i�ݒ�
	_pTapRemainBack = Sprite::createWithTexture(SGraphMgr::Instance()->GetBatchTexture(SGraphMgr::eGraph_TouchBack));
	_pTapRemainBack->setPosition(Point(
		_pTapRemainBack->getContentSize().width / 2,
		Director::getInstance()->getWinSize().height - _pTapRemainBack->getContentSize().height / 2));

	// �c��^�b�v�񐔐ݒ�
	String* pTapRemain = String::createWithFormat("%d", _remainTap);
	_pTapRemainLabel = Label::create(pTapRemain->getCString(), "", 100);
	_pTapRemainLabel->setPosition(_pTapRemainBack->getPosition());
	_pTapRemainLabel->setColor(Color3B(0, 0, 255));

	// �傫�������킹��
	this->setScale(_radius / BALL_RADIUS);
}

// �f�X�g���N�^
CPlayer::~CPlayer()
{

}

//**********************************************************************
// �e�m�[�h��ݒ肷��
//**********************************************************************
void CPlayer::SetParent(Node* parentNode)
{
	_pParentNode = parentNode;
}

//**********************************************************************
// �i�ޏ���
//**********************************************************************
void CPlayer::Move()
{
	// �Ȃ���K�v������ꍇ�A�Ȃ���
	if (_turnFlag == true) Turn();

	// X,Y�����̈ړ��������v�Z
	float moveX = _speed * cosf(_moveRadian);
	float moveY = _speed * sinf(_moveRadian);

	// ���݂̈ʒu�ɁA�ړ��������Z����
	this->setPosition(Point(this->getPosition().x + moveX, this->getPosition().y + moveY));

	// �v���C���[����ʊO�ɏo���ꍇ�A�L���t���O�𗧂Ă�
	if (TargetPointer->getPositionX() - Director::getInstance()->getWinSize().width / 2 + this->GetRadius() > this->getPosition().x ||
		this->getPosition().y < this->GetRadius() ||
		this->getPosition().y > Director::getInstance()->getWinSize().height - this->GetRadius())
	{
		this->KillPlayer();
	}
}

//**********************************************************************
// �Ȃ��鏈��
//**********************************************************************
void CPlayer::Turn()
{
	// �^�b�`�|�C���g�ƌ��ݒn�Ƃ̊p�x�����߂�
	float distanceX = _touchedPoint.x - this->getPosition().x;
	float distanceY = _touchedPoint.y - this->getPosition().y;

	float radian = atan2f(distanceY, distanceX);

	// ���ɂ���āA�E���A���������߂�
	float defRadian = radian - _moveRadian;

	if (defRadian > 0.0f)
	{
		if (defRadian < PI)
		{
			// �p�x���A�ő�Ȃ���p�x��菬�����ꍇ�A���̍�����]�������A�t���O��؂�
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
			// �p�x���A�ő�Ȃ���p�x��菬�����ꍇ�A���̍�����]�������A�t���O��؂�
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

	// �i�s�p�x�̕␳���s��
	if (_moveRadian > PI * 2)	_moveRadian = _moveRadian - 2 * PI;
	if (_moveRadian < -PI * 2)	_moveRadian = _moveRadian + 2 * PI;

}

//**********************************************************
// �^�b�`���ꂽ���W���擾����
//**********************************************************
void CPlayer::SetTouchPoint(const Point& point)
{
	_touchedPoint = point;
	_turnFlag = true;
}

//**********************************************************
// �N���G�C�g�֐�
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
// �Փˎ�
//**********************************************************
void CPlayer::CollisionFunction(IPlayerStateChange* playerStateChanger)
{

}

//**********************************************************
// �X�R�A�����Z����
//**********************************************************
void CPlayer::UpdateScore()
{
	_score = (_score < this->getPosition().x ? this->getPosition().x : _score) / 10;
	String* scoreString = String::createWithFormat("Score : %d", (int)_score );
	_pScoreLabel->setString(scoreString->getCString());
	_pScoreLabel->setPosition(Director::getInstance()->getWinSize().width, 0.0f);
}

//**********************************************************
// �^�b�v�񐔂̍X�V
//**********************************************************
void CPlayer::UpdateTapRemain()
{
	String* pTapRemain = String::createWithFormat("%d", _remainTap);
	_pTapRemainLabel->setString(pTapRemain->getCString());
}

//**********************************************************
//	�X�R�A�ƃ^�b�v�񐔂�\��
//**********************************************************
void CPlayer::ShowState(Node* pUiLayer)
{
	pUiLayer->addChild(_pScoreLabel);
	pUiLayer->addChild(_pTapRemainBack);
	pUiLayer->addChild(_pTapRemainLabel);
}


//**************************************
// �v���C���[�̏�ԕω����I�[�o�[���C�h
//**************************************
void CPlayer::AddTouch(int add)
{ 
	this->_remainTap += add;

	// �^�b�v�񐔃A�b�v�̃A�N�V����������
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
	// �X�R�A��������
	_score += score;
}
void CPlayer::ScoreDown(int score){ _score -= score; }
void CPlayer::KillPlayer(){ _killFlag = true; }
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

	// �e���C���[�m�[�h��o�^����
	void SetParent(cocos2d::Node* parentNode);

	// �X�V����
	void Update(){}

	// �i�ޏ���
	void Move();

	// �X�R�A���X�V����
	void UpdateScore();
	// �^�b�v�񐔂��X�V
	void UpdateTapRemain();

	// �X�R�A��\������֐�
	void ShowState(cocos2d::Node* parentNode);

	// �X�R�A���擾����
	int GetScore(){ return _score; }

	// �^�b�`���ꂽ���W���擾����
	void SetTouchPoint(const cocos2d::Point& point);

	// �N���G�C�g�֐�
	CREATE_FUNC(CPlayer);
	static CPlayer* createWithTexture(cocos2d::Texture2D *texture);

	// �I�u�W�F�N�g�ɂ����������̏���
	void CollisionFunction(IPlayerStateChange* playerStateChanger) override;

	int GetTouchRemain(){ return _remainTap; }

	// �v���C���[�̃L���t���O���擾����
	bool GetKillFlag(){ return _killFlag; }

	//**************************************
	// �v���C���[�̏�ԕω����I�[�o�[���C�h
	//**************************************
	// �c��^�b�`�񐔂�������
	void AddTouch(int add);
	void DownTouch(int down);
	void ScoreUp(int score);
	void ScoreDown(int score);
	void KillPlayer();

private:
	//++++++++++++++++++++++++++++++++++++++
	// �v���C�x�[�g�ϐ�
	//++++++++++++++++++++++++++++++++++++++

	bool _killFlag;						// ���S�t���O
	bool _turnFlag;						// �Ȃ���K�v������ꍇ�A�Ȃ���t���O

	float _speed;						// ����
	float _moveRadian;					// �i�ފp�x(�E������0�Ƃ����ꍇ)
	float _turnRadianMax;				// �Ȃ���p�x�̍ő�l

	int _remainTap;						// �^�b�v�ł����
	cocos2d::Sprite* _pTapRemainBack;	// �c��^�b�v�񐔂̔w�i
	cocos2d::Label* _pTapRemainLabel;	// �c��^�b�v�񐔂�\�����郉�x��

	cocos2d::Point _touchedPoint;		// �Ō�Ƀ^�b�`���ꂽ�|�C���g

	float _score;						// �X�R�A
	cocos2d::Label* _pScoreLabel;		// �X�R�A��\�����邽�߂̃��x��

	cocos2d::Node*	_pParentNode;		//	�e�̃m�[�h��ݒ肷��

	//++++++++++++++++++++++++++++++++++++++
	// �v���C�x�[�g�֐�
	//++++++++++++++++++++++++++++++++++++++

	// �Ȃ��鏈��
	void Turn();		

};

#endif // __HELLOWORLD_SCENE_H__

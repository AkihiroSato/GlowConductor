#ifndef __TITLE_SCENE_H__
#define __TITLE_SCENE_H__

#include "cocos2d.h"

class TitleScene : public cocos2d::Layer
{
public:
    // there's no 'id' in cpp, so we recommend returning the class instance pointer
    static cocos2d::Scene* createScene();

    // Here's a difference. Method 'init' in cocos2d-x returns bool, instead of returning 'id' in cocos2d-iphone
    virtual bool init();  
    
    // a selector callback
    void menuCloseCallback(cocos2d::Ref* pSender);
    
    // implement the "static create()" method manually
    CREATE_FUNC(TitleScene);

	// �^�b�`�J�n���ɌĂ΂��֐�
	virtual bool onTouchBegan(cocos2d::Touch* touch, cocos2d::Event* unused_event);

	// �X�^�[�g�{�^�����������Ƃ��ɌĂ΂��֐�
	void TapStartbutton(cocos2d::Ref* sender);
	
};

#endif // __HELLOWORLD_SCENE_H__

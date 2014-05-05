#pragma once
#include "BaseAI.h"

class AI_UpDown : public BaseAI
{
public:
	AI_UpDown();
	void AI(cocos2d::Node* pObject) override;

private:
	float _count;
};
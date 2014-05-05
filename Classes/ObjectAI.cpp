#include "ObjectAI.h"
USING_NS_CC;

// コンストラクタ
AI_UpDown::AI_UpDown()
{
	_count = 0.0f;
}


// 上下に移動するAI
void AI_UpDown::AI(Node* pObject)
{
	_count += 0.02f;
	pObject->setPositionY(pObject->getPositionY() + 6.0f * cosf(_count));
}
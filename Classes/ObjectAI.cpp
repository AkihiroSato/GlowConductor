#include "ObjectAI.h"
USING_NS_CC;

// �㉺�Ɉړ�����AI
void AI_UpDown::AI(Node* pObject)
{
	_count += 3.0f;
	pObject->setPositionY(pObject->getPositionY() + 200 * cosf(_count));
}
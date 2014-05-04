#include "ObjectAI.h"
USING_NS_CC;

// ã‰º‚ÉˆÚ“®‚·‚éAI
void AI_UpDown::AI(Node* pObject)
{
	_count += 3.0f;
	pObject->setPositionY(pObject->getPositionY() + 200 * cosf(_count));
}
#include "CObject.h"

// デストラクタ
CObject::~CObject()
{
	if (pAi != nullptr)
		delete pAi;
}
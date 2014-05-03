#pragma once
#include "Singleton.h"
#include "CameraTarget.h"
#define TargetPointer SCameraTargetMgr::Instance()->GetCameraTarget()

class SCameraTargetMgr : public Singleton<SCameraTargetMgr>
{
	friend Singleton;
public:
	void SetCameraTarget(CameraTarget* pTarget){ _pTarget = pTarget; }
	CameraTarget* GetCameraTarget(){ return _pTarget; }
	void DeleteCameraTarget(){ delete _pTarget; }

private:
	CameraTarget* _pTarget;
};
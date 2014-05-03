#pragma once

class IPlayerStateChange
{
public:
	virtual void ScoreUp(int score) = 0;
	virtual void ScoreDown(int score) = 0;
	virtual void AddTouch(int add) = 0;
	virtual void DownTouch(int down) = 0;
	virtual void KillPlayer() = 0;
};
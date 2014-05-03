#pragma once
#include "CCParticleSystemQuad.h"

NS_CC_BEGIN

namespace MyParticles{

	// 闇オブジェクトを中心に発生するパーティクル
	class DarkParticle : public cocos2d::ParticleSystemQuad
	{
	public:
		static DarkParticle* create();
		static DarkParticle* createWithTotalParticles(int numberOfParticles);

	protected:
		DarkParticle(){}

		virtual ~DarkParticle(){}

		bool init(){ return initWithTotalParticles(100); }
		virtual bool initWithTotalParticles(int numberOfParticles);

	private:
		CC_DISALLOW_COPY_AND_ASSIGN(DarkParticle);
	};

	// タッチ時に発生するパーティクル
	class TouchParticle : public cocos2d::ParticleSystemQuad
	{
	public:
		static TouchParticle* create();
		static TouchParticle* createWithTotalParticles(int numberOfParticles);

	protected:
		TouchParticle(){}

		virtual ~TouchParticle(){}

		bool init(){ return initWithTotalParticles(500); }
		virtual bool initWithTotalParticles(int numberOfParticles);

	private:
		CC_DISALLOW_COPY_AND_ASSIGN(TouchParticle);
	};

	// プレイヤーに追従するパーティクル
	class GlowFollowParticle : public cocos2d::ParticleSystemQuad
	{
	public:
		static GlowFollowParticle* create();
		static GlowFollowParticle* createWithTotalParticles(int numberOfParticles);

	protected:
		GlowFollowParticle(){}

		virtual ~GlowFollowParticle(){}

		bool init(){ return initWithTotalParticles(250); }
		virtual bool initWithTotalParticles(int numberOfParticles);

	private:
		CC_DISALLOW_COPY_AND_ASSIGN(GlowFollowParticle);
	};

}

NS_CC_END
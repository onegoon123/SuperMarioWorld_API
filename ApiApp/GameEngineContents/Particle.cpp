#include "Particle.h"
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"

Particle::Particle() {

}

void Particle::CreateParticle(GameEngineLevel* _Level, const float4& _Pos, const std::string_view& _Anim)
{
	Particle* NewParticle = _Level->CreateActor<Particle>(RenderOrder::Player);
	NewParticle->SetPos(_Pos);
	NewParticle->SetAnimation(_Anim);
}

Particle::~Particle() {

}

void Particle::Start()
{
	AnimationRender = CreateRender(RenderOrder::Player);
	AnimationRender->CreateAnimation({ .AnimationName = "SMOKE1", .ImageName = "SMOKE.BMP", .Start = 0, .End = 4, .InterTime = 0.07f ,.Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "SKID", .ImageName = "SKIDDUST.BMP", .Start = 0, .End = 3, .InterTime = 0.07f ,.Loop = false });
	AnimationRender->CreateAnimation({ .AnimationName = "KICK", .ImageName = "KICK.BMP", .Start = 0, .End = 2, .InterTime = 0.05f ,.Loop = false });

	AnimationRender->SetScale({ 64, 64 });
}

void Particle::Update(float _DeltaTime)
{
	if (1 < GetLiveTime())
	{
		Death();
	}
}

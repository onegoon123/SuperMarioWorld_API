#pragma once
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineActor.h>

class Particle : public GameEngineActor
{
public:
	static void CreateParticle(GameEngineLevel* _Level , const float4& _Pos, const std::string_view& _Anim);
	static void CreateParticle(GameEngineLevel* _Level , const float4& _Pos, const float4& _Scale, const std::string_view& _Anim);
	Particle();
	~Particle();

	void SetAnimation(const std::string_view& _Str)
	{
		if (nullptr != AnimationRender)
		{
			AnimationRender->ChangeAnimation(_Str);
		}
	}
	void SetScale(const float4& _Scale)
	{
		AnimationRender->SetScale(_Scale);
	}

	Particle(const Particle& _Other) = delete;
	Particle(Particle&& _Other) noexcept = delete;
	Particle& operator=(const Particle& _Other) = delete;
	Particle& operator=(Particle&& _Other) noexcept = delete;

protected:
	void Start();
	void Update(float _DeltaTime);
private:
	GameEngineRender* AnimationRender = nullptr;

};


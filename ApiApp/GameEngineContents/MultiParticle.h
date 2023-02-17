#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineRender.h>

class MultiParticle : public GameEngineActor
{
public:
	MultiParticle();
	~MultiParticle();

	static void CreateParticle(GameEngineLevel* _Level, const float4& _Pos, const std::string_view& _Image);
	static void CreateParticle(GameEngineLevel* _Level, const float4& _Pos, const float4& _Scale, const std::string_view& _Image);

	void SetAnimation(const std::string_view& _Str);
	void SetScale(const float4& _Scale);

	MultiParticle(const MultiParticle& _Other) = delete;
	MultiParticle(MultiParticle&& _Other) noexcept = delete;
	MultiParticle& operator=(const MultiParticle& _Other) = delete;
	MultiParticle& operator=(MultiParticle&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

private:
	std::vector<GameEngineRender*> Renders = std::vector<GameEngineRender*>();
};


#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>

class Fire : public GameEngineActor
{
public:
	Fire();
	~Fire();

	void SetDir(const float4& _Dir)
	{
		Dir = _Dir;
	}
	static bool IsMax()
	{
		return Max <= Num;
	}
	Fire(const Fire& _Other) = delete;
	Fire(Fire&& _Other) noexcept = delete;
	Fire& operator=(const Fire& _Other) = delete;
	Fire& operator=(Fire&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

private:

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	static int Num;
	static const int Max = 2;

	const float Speed = 850.0f;
	float4 Dir = float4::Zero;
};

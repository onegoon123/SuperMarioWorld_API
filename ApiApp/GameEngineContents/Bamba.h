#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include <GameEngineCore/GameEngineCollision.h>
class GameEngineImage;
class Bamba : public GameEngineActor
{
public:
	Bamba();
	~Bamba();

	Bamba(const Bamba& _Other) = delete;
	Bamba(Bamba&& _Other) noexcept = delete;
	Bamba& operator=(const Bamba& _Other) = delete;
	Bamba& operator=(Bamba&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
	void Turn();
private:

	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* BodyCollision = nullptr;

	const float Speed = 100;
	const float GravityMax = 1000;
	const float GravityAcceleration = 2000;

	GameEngineImage* ColMap = nullptr;
	float4 MoveDir = float4::Zero;
	float DirValue = -1;
};


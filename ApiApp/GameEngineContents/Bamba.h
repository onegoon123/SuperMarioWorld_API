#pragma once
#include "EnemyActor.h"
class GameEngineImage;
class Bamba : public EnemyActor
{
public:
	Bamba();
	~Bamba();

	void BlockHit() override;

	Bamba(const Bamba& _Other) = delete;
	Bamba(Bamba&& _Other) noexcept = delete;
	Bamba& operator=(const Bamba& _Other) = delete;
	Bamba& operator=(Bamba&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
	void Turn() override;
	void TurnLeft() override;
	void TurnRight() override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* Collision = nullptr;
};


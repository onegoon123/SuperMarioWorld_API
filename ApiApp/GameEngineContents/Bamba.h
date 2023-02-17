#pragma once
#include "EnemyActor.h"

enum class State
{
	Normal,
	Overturn,
	Hold,
	Die
};

class GameEngineImage;
class Bamba : public EnemyActor
{
public:
	Bamba();
	~Bamba();
	
	void SpinHit() override;
	void JumpHit() override;
	void FireHit() override;
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

	State StateValue = State::Normal;

	void OverturnUpdate(float _DeltaTime);
};


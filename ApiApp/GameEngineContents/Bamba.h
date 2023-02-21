#pragma once
#include "EnemyActor.h"

enum class State
{
	Normal,
	Overturn,
	Hold,
	Kick,
	Die
};

class GameEngineImage;
class Bamba : public EnemyActor
{
public:
	Bamba();
	~Bamba();
	
	bool IsCollisionAttack() override;
	bool IsHold() override;
	void SpinHit() override;
	void JumpHit() override;
	void FireHit() override;
	void BlockHit() override;
	void MonsterHit() override;
	void Hold() override;
	void Kick(const float4& _Force) override;

	Bamba(const Bamba& _Other) = delete;
	Bamba(Bamba&& _Other) noexcept = delete;
	Bamba& operator=(const Bamba& _Other) = delete;
	Bamba& operator=(Bamba&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void OffCamera() override;
	void OnCamera() override;

	void Turn() override;
	void TurnLeft() override;
	void TurnRight() override;

private:
	GameEngineRender* AnimationRender = nullptr;
	GameEngineCollision* Collision = nullptr;
	const float4 RenderScale = {64, 64};
	const float4 RenderPos = {0, -28};
	const float4 CollisionScale = {48, 48};
	const float4 CollisionPos = {0, -24};
	State StateValue = State::Normal;
	float4 MoveDir = { 0,0 };
	const float BrakeForce = 1000;
	bool IsOnCamera = false;

	void OverturnUpdate(float _DeltaTime);
	void KickUpdate(float _DeltaTime);
};


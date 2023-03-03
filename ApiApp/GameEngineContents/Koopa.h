#pragma once
#include "EnemyActor.h"

enum class KoopaState
{
	Appear,
	Move,
	Minions,
	Attack,
	Hit,
	Die,
};

class Koopa : public EnemyActor
{
public:
	Koopa();
	~Koopa();

	bool IsCollisionAttack() override;
	bool IsHold() override;
	bool IsHoldable() override;
	void SpinHit() override;
	void JumpHit(bool IsLeft) override;
	void FireHit() override;
	void BlockHit() override;
	void MonsterHit(bool IsLeft) override;
	void Hold() override;
	void Kick(const float4& _Force) override;

	Koopa(const Koopa& _Other) = delete;
	Koopa(Koopa&& _Other) noexcept = delete;
	Koopa& operator=(const Koopa& _Other) = delete;
	Koopa& operator=(Koopa&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	GameEngineRender* KoopaRender = nullptr;
	GameEngineRender* PierrotRender = nullptr;
	GameEngineRender* PropellerRender = nullptr;
	const float4 KoopaRenderScale = { 256, 160 };
	const float4 KoopaRenderPos = { 0, 0 };
	const float4 PierrotRenderScale = { 256, 224 };
	const float4 PierrotRenderPos = { 0, 160 };
	const float4 PropellerRenderScale = { 160, 32 };
	const float4 PropellerRenderPos = { 0, 284 };
	const float4 KoopaCollisionScale = { 200, 100 };
	const float4 KoopaCollisionPos = { 0, 0 };
};


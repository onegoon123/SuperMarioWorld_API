#pragma once
#include "EnemyActor.h"

enum class ShellState
{
	Idle,
	Hold,
	Kick,
	Spin,
	Die
};

class Shell : public EnemyActor
{
public:
	Shell();
	~Shell();

	/// <summary>
	/// 현재 액터가 공격판정이 있으면 true를 리턴하는 함수
	/// </summary>
	/// <returns></returns>
	bool IsCollisionAttack() override;
	/// <summary>
	/// 현재 액터가 플레이어에게 잡힌 상태면 true를 리턴하는 함수
	/// </summary>
	/// <returns></returns>
	bool IsHold() override;
	/// <summary>
	/// 현재 액터를 잡을 수 있는 상태면 true를 리턴하는 함수
	/// </summary>
	/// <returns></returns>
	bool IsHoldable() override;
	bool IsDie() override;
	/// <summary>
	/// 스핀점프로 밟히면 실행되는 함수
	/// </summary>
	void SpinHit() override;
	/// <summary>
	/// 점프로 밟히면 실행되는 함수
	/// </summary>
	void JumpHit(bool IsLeft) override;
	/// <summary>
	/// 불꽃에 맞으면 실행되는 함수
	/// </summary>
	void FireHit() override;
	/// <summary>
	/// 블록위 서있을때 해당 블록이 히트하면 실행되는 함수
	/// </summary>
	void BlockHit() override;
	/// <summary>
	/// 다른 몬스터를 던져서 맞았을때 실행되는 함수, 두 몬스터 중 왼쪽에 있으면 true를 받는다
	/// </summary>
	/// <param name="IsLeft"></param>
	void MonsterHit(bool IsLeft) override;
	/// <summary>
	/// 플레이어에게 잡히면 실행되는 함수
	/// </summary>
	void Hold() override;
	/// <summary>
	/// 플레이어에게 발로 치이면 실행되는 함수 (잡힌 후 차는 경우)
	/// </summary>
	/// <param name="_Force"></param>
	void Kick(const float4& _Force) override;


	Shell(const Shell& _Other) = delete;
	Shell(Shell&& _Other) noexcept = delete;
	Shell& operator=(const Shell& _Other) = delete;
	Shell& operator=(Shell&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;

	void Turn() override;
	void TurnLeft() override;
	void TurnRight() override;
private:
	GameEngineRender* AnimationRender = nullptr;
	ShellState StateValue = ShellState::Idle;
	const float4 RenderScale = { 64, 64 };
	const float4 RenderPos = { 0, -26 };
	const float4 CollisionScale = { 48, 48 };
	const float4 CollisionPos = { 0, -24 };
	const float4 MonsterHitForce = { 250, -750 };
	const float ActorSpeed = 920;
	const float ActorSlopeSpeed = ActorSpeed * 0.5f;
	const float HeadingReaction = 100;
	const float StateWaitTime = 0.1f;
	const float KickWaitTime = 0.5f;
	float Timer = 0;
	const int Score = 100;
	bool IsOn = false;
	
	void IdleUpdate(float _DeltaTime);
	void KickUpdate(float _DeltaTime);
	void SpinUpdate(float _DeltaTime);
	void MonsterCheck();
};


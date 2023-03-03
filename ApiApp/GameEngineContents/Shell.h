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
	/// ���� ���Ͱ� ���������� ������ true�� �����ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	bool IsCollisionAttack() override;
	/// <summary>
	/// ���� ���Ͱ� �÷��̾�� ���� ���¸� true�� �����ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	bool IsHold() override;
	/// <summary>
	/// ���� ���͸� ���� �� �ִ� ���¸� true�� �����ϴ� �Լ�
	/// </summary>
	/// <returns></returns>
	bool IsHoldable() override;
	bool IsDie() override;
	/// <summary>
	/// ���������� ������ ����Ǵ� �Լ�
	/// </summary>
	void SpinHit() override;
	/// <summary>
	/// ������ ������ ����Ǵ� �Լ�
	/// </summary>
	void JumpHit(bool IsLeft) override;
	/// <summary>
	/// �Ҳɿ� ������ ����Ǵ� �Լ�
	/// </summary>
	void FireHit() override;
	/// <summary>
	/// ����� �������� �ش� ����� ��Ʈ�ϸ� ����Ǵ� �Լ�
	/// </summary>
	void BlockHit() override;
	/// <summary>
	/// �ٸ� ���͸� ������ �¾����� ����Ǵ� �Լ�, �� ���� �� ���ʿ� ������ true�� �޴´�
	/// </summary>
	/// <param name="IsLeft"></param>
	void MonsterHit(bool IsLeft) override;
	/// <summary>
	/// �÷��̾�� ������ ����Ǵ� �Լ�
	/// </summary>
	void Hold() override;
	/// <summary>
	/// �÷��̾�� �߷� ġ�̸� ����Ǵ� �Լ� (���� �� ���� ���)
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
	void Render(float _DeltaTime) override;

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


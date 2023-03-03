#pragma once
#include "EnemyActor.h"

enum class NokoState
{
	Normal,
	Overturn,
	Naked,
	Die
};

class Nokonoko : public EnemyActor
{
public:
	Nokonoko();
	~Nokonoko();
	
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

	Nokonoko(const Nokonoko& _Other) = delete;
	Nokonoko(Nokonoko&& _Other) noexcept = delete;
	Nokonoko& operator=(const Nokonoko& _Other) = delete;
	Nokonoko& operator=(Nokonoko&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;

	void Turn() override;
	void TurnLeft() override;
	void TurnRight() override;
private:
	GameEngineRender* AnimationRender = nullptr;
	NokoState StateValue = NokoState::Normal;
	const float4 RenderScale = { 64, 108 };
	const float4 RenderPos = { 0, -50 };
	const float4 CollisionScale = { 48, 84 };
	const float4 CollisionPos = { 0, -42 };
	const float4 MonsterHitForce = { 250, -750 };
	const float HeadingReaction = 100;
	const float ActorSpeed = 50;
	const float ActorSlopeSpeed = ActorSpeed * 0.6f;

	void OverturnUpdate(float _DeltaTime);
};
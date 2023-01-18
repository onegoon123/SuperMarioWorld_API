#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MarioGameCore.h"
#include "ContentsEnums.h"

enum class MarioState
{
	IDLE,
	WALK,
	RUN,
	BRAKE,
	JUMP,
	SPIN
};
enum class Dir
{
	Left,
	Right
};

// �÷��̾ �����ϰ� �Ǵ� ������ ĳ����
// �⺻ ������	�̵�, ����, ���, ��������
// �Ŀ��� ���¿� ���� �Ҳɽ��, ���� ���� �����ϴ�
// ��� ž�� ���¿� ���� ��Ű��, ���, ����, ������ ���� �����ϴ�
// ��� ž�½� ���۵� �ش� Ŭ�������� �����ȴ�

class Mario : public GameEngineActor
{
public:

	static Mario* MainPlayer;

	Mario();
	~Mario();

	Mario(const Mario& _Other) = delete;
	Mario(Mario&& _Other) noexcept = delete;
	Mario& operator=(const Mario& _Other) = delete;
	Mario& operator=(Mario&& _Other) noexcept = delete;

protected:
	void Start() override;
	void Update(float _DeltaTime) override;
	void Render(float _DeltaTime) override;
private:
	const float Speed = 250.0f;		// �̵� �ӵ�
	const float RunSpeed = 300.0f;		// �̵� �ӵ�
	const float JumpForce = 500.0f;	// ������
	const float JumpHeight = 500;
	const float Gravity = 100;
	const float BrakingForce = 10;
	const float StoppingForce = 2;
	const float Acceleration = 3;
	const float DashAcceleration = 3;

	//			 MarioPower	   StockState
	// Normal : �⺻������		�������
	// Super  : ���۸�����		����
	// Fire   : ���̾����	��
	// Cape   : ���丶����		����
	PowerState MarioPower = PowerState::Normal;
	PowerState StockState = PowerState::Normal;

	bool IsRidedYoshi = false;	// ��� ž�� ����
	bool IsGrounded = true;		// �������� �� ���� �ִ��� ����
	float HorizontalForce = 0;	// �������� �������� ��
	float JumpingTime = 0;
	float RunChargeTime = 0;

	MarioState StateValue = MarioState::IDLE;
	Dir DirValue = Dir::Right;

	GameEngineRender* AnimationRender = nullptr;

#pragma region __________ State ���� �Լ� _________
	void ChangeState(MarioState _State);
	void UpdateState(float _DeltaTime);

	void IdleStart();
	void IdleUpdate(float _DeltaTime);
	void IdleEnd();

	void WalkStart();
	void WalkUpdate(float _DeltaTime);
	void WalkEnd();

	void RunStart();
	void RunUpdate(float _DeltaTime);
	void RunEnd();

	void BrakeStart();
	void BrakeUpdate(float _DeltaTime);
	void BrakeEnd();

	void JumpStart();
	void JumpUpdate(float _DeltaTime);
	void JumpEnd();

	void SpinStart();
	void SpinUpdate(float _DeltaTime);
	void SpinEnd();

	void ChangeAnimation(const std::string_view& _AnimationName);
#pragma endregion



#pragma region __________ �ǰ� ���� �Լ� __________

	// �ε����� ������� �޴� ��� ����Ǵ� �Լ�
	void GetDamaged() {
		switch (MarioPower)
		{
		case PowerState::Normal:
			GameOver();		// Normal�� ��� ���ӿ��� �Լ� ������ ����
			return;
		case PowerState::Super:
			MarioPower = PowerState::Normal;
			break;
		case PowerState::Fire:
			MarioPower = PowerState::Normal;
			break;
		case PowerState::Cape:
			MarioPower = PowerState::Normal;
			break;
		default:
			break;
		}
		InvincibilityTime();	// ���� �ð� Ȱ��
		TakeOutStock();	// ���� ������ ��ȯ
	}
	// �߶��ϰų� Normal ���¿��� ������� ���� ��� ����Ǵ� ���ӿ��� �Լ�
	void GameOver() {

	}
	// �ǰ��� �����ð� ������ �����ϴ� ���� �Լ�
	void InvincibilityTime() {

	}


#pragma endregion

#pragma region __________ ���� ���� �Լ� __________

#pragma endregion

#pragma region __________ �̵� ���� �Լ� __________

#pragma endregion

#pragma region __________ ��� ���� �Լ� __________

#pragma endregion

#pragma region __________ �Ŀ� ���� �Լ� __________
	void TakeOutStock() {
		if (PowerState::Normal == StockState) {
			return;
		}
		// ( �̱��� ���忡 �ش��ϴ� �Ŀ��������� ����)
		StockState = PowerState::Normal;
	}
#pragma endregion

#pragma region __________ �浹 ���� �Լ� __________

#pragma endregion

};


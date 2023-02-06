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
	CROUCH,
	LOOKUP,
	JUMP,
	FALL,
	RUNJUMP,
	SPIN,
	SLIDE,
	KICK,
	CHANGEPOWER,
	VICTORY
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
class GameEngineImage;
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
	void LevelChangeStart(GameEngineLevel* _PrevLevel) override;
private:
	float Speed = 705;					// �̵� �ӵ�
	float RunSpeed = 850.0f;			// �̵� �ӵ�
	const float JumpForce = 950;		// ������
	const float DashJumpForce = 1100;	// ������
	const float RunJumpForce = 1200;	// ������
	const float JumpPressForce = 3350;	// ���� ������
	const float SpinPressForce = 2500;	// ���� ������
	const float SlopeForce = 1000;
	const float JumpTime = 0.325f;
	const float GravityMax = 1750;
	const float GravityAcceleration = 4600;
	const float BrakingForce = 5;
	const float StoppingForce = 1;
	const float Acceleration = 1.5;
	const float DashAcceleration = 2;

	//			 MarioPower	   StockState
	// Normal : �⺻������		�������
	// Super  : ���۸�����		����
	// Fire   : ���̾����	��
	// Cape   : ���丶����		����
	PowerState MarioPower = PowerState::Normal;
	PowerState StockState = PowerState::Normal;

	bool IsRidedYoshi = false;	// ��� ž�� ����
	bool IsGrounded = true;		// �������� �� ���� �ִ��� ����
	bool IsSlope = false;		// �������� ��Ż�� ���� �ִ��� ����
	float4 MoveDir = float4::Zero;	// �������� �������� ��
	float HorizontalForce = 0;
	float JumpTimeCounter = 0;
	float RunChargeTime = 0;	// ��ø� �� �ð��� ����ؼ� �޸��� ��ȯ�� �Ǵ��ϴ� ����

	MarioState StateValue = MarioState::IDLE;
	Dir DirValue = Dir::Right;
	Dir SlopeDir = Dir::Right;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineImage* ColMap = nullptr;

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

	void CrouchStart();
	void CrouchUpdate(float _DeltaTime);
	void CrouchEnd();

	void LookUpStart();
	void LookUpUpdate(float _DeltaTime);
	void LookUpEnd();

	void RunJumpStart();
	void RunJumpUpdate(float _DeltaTime);
	void RunJumpEnd();

	void FallStart();
	void FallUpdate(float _DeltaTime);
	void FallEnd();
#pragma endregion

#pragma region __________Animation ���� �Լ� ________
	void ChangeAnimation(const std::string_view& _AnimationName);

#pragma endregion

#pragma region __________ �̵� ���� �Լ� __________
	void MoveCalculation(float _DeltaTime);
	void MoveCalculation2(float _DeltaTime);
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

#pragma region __________ �Ŀ� ���� �Լ� __________
	void TakeOutStock() {
		if (PowerState::Normal == StockState) {
			return;
		}
		// ( �̱��� ���忡 �ش��ϴ� �Ŀ��������� ����)
		StockState = PowerState::Normal;
	}
#pragma endregion

};


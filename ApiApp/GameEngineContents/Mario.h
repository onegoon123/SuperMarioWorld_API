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

// 플레이어가 조작하게 되는 마리오 캐릭터
// 기본 조작은	이동, 점프, 대시, 스핀점프
// 파워업 상태에 따라 불꽃쏘기, 비행 등이 가능하다
// 요시 탑승 상태에 따라 삼키기, 뱉기, 비행, 내리기 등이 가능하다
// 요시 탑승시 조작도 해당 클래스에서 구현된다
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
	float Speed = 705;					// 이동 속도
	float RunSpeed = 850.0f;			// 이동 속도
	const float JumpForce = 950;		// 점프력
	const float DashJumpForce = 1100;	// 점프력
	const float RunJumpForce = 1200;	// 점프력
	const float JumpPressForce = 3350;	// 점프 유지력
	const float SpinPressForce = 2500;	// 스핀 유지력
	const float SlopeForce = 1000;
	const float JumpTime = 0.325f;
	const float GravityMax = 1750;
	const float GravityAcceleration = 4600;
	const float BrakingForce = 5;
	const float StoppingForce = 1;
	const float Acceleration = 1.5;
	const float DashAcceleration = 2;

	//			 MarioPower	   StockState
	// Normal : 기본마리오		비어있음
	// Super  : 슈퍼마리오		버섯
	// Fire   : 파이어마리오	꽃
	// Cape   : 망토마리오		깃털
	PowerState MarioPower = PowerState::Normal;
	PowerState StockState = PowerState::Normal;

	bool IsRidedYoshi = false;	// 요시 탑승 여부
	bool IsGrounded = true;		// 마리오가 땅 위에 있는지 여부
	bool IsSlope = false;		// 마리오가 비탈길 위에 있는지 여부
	float4 MoveDir = float4::Zero;	// 수평으로 가해지는 힘
	float HorizontalForce = 0;
	float JumpTimeCounter = 0;
	float RunChargeTime = 0;	// 대시를 한 시간을 기록해서 달리기 전환을 판단하는 변수

	MarioState StateValue = MarioState::IDLE;
	Dir DirValue = Dir::Right;
	Dir SlopeDir = Dir::Right;

	GameEngineRender* AnimationRender = nullptr;
	GameEngineImage* ColMap = nullptr;

#pragma region __________ State 관련 함수 _________
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

#pragma region __________Animation 관련 함수 ________
	void ChangeAnimation(const std::string_view& _AnimationName);

#pragma endregion

#pragma region __________ 이동 관련 함수 __________
	void MoveCalculation(float _DeltaTime);
	void MoveCalculation2(float _DeltaTime);
#pragma endregion

#pragma region __________ 피격 관련 함수 __________

	// 부딪혀서 대미지를 받는 경우 실행되는 함수
	void GetDamaged() {
		switch (MarioPower)
		{
		case PowerState::Normal:
			GameOver();		// Normal일 경우 게임오버 함수 실행후 리턴
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
		InvincibilityTime();	// 무적 시간 활성
		TakeOutStock();	// 스톡 아이템 소환
	}
	// 추락하거나 Normal 상태에서 대미지를 받을 경우 실행되는 게임오버 함수
	void GameOver() {

	}
	// 피격후 일정시간 공격을 방지하는 무적 함수
	void InvincibilityTime() {

	}

#pragma endregion

#pragma region __________ 파워 관련 함수 __________
	void TakeOutStock() {
		if (PowerState::Normal == StockState) {
			return;
		}
		// ( 미구현 스톡에 해당하는 파워아이템을 생성)
		StockState = PowerState::Normal;
	}
#pragma endregion

};


#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MarioGameCore.h"
#include "ContentsEnums.h"

// 플레이어가 조작하게 되는 마리오 캐릭터
// 기본 조작은	이동, 점프, 대시, 스핀점프
// 파워업 상태에 따라 불꽃쏘기, 비행 등이 가능하다
// 요시 탑승 상태에 따라 삼키기, 뱉기, 비행, 내리기 등이 가능하다
// 요시 탑승시 조작도 해당 클래스에서 구현된다

class Mario : public GameEngineActor
{
public:
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
	
	const float Speed = 50.0f;		// 이동 속도
	const float JumpForce = 10.0f;	// 점프력

	//			 MyState	   StockState
	// Normal : 기본마리오		비어있음
	// Super  : 슈퍼마리오		버섯
	// Fire   : 파이어마리오	꽃
	// Cape   : 망토마리오		깃털
	MarioState MyState = MarioState::Normal;
	MarioState StockState = MarioState::Normal;

	bool IsRidedYoshi = false;	// 요시 탑승 여부
	bool IsGrounded = true;		// 마리오가 땅 위에 있는지 여부

	
	
#pragma region __________ 피격 관련 함수 __________

	// 부딪혀서 대미지를 받는 경우 실행되는 함수
	void GetDamaged() {
		switch (MyState)
		{
		case MarioState::Normal:
			GameOver();		// Normal일 경우 게임오버 함수 실행후 리턴
			return;
		case MarioState::Super:
			MyState = MarioState::Normal;
			break;
		case MarioState::Fire:
			MyState = MarioState::Normal;
			break;
		case MarioState::Cape:
			MyState = MarioState::Normal;
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

#pragma region __________ 점프 관련 함수 __________

#pragma endregion

#pragma region __________ 이동 관련 함수 __________

#pragma endregion

#pragma region __________ 요시 관련 함수 __________

#pragma endregion

#pragma region __________ 파워 관련 함수 __________
	void TakeOutStock() {
		if (MarioState::Normal == StockState) {
			return;
		}
		// ( 미구현 스톡에 해당하는 파워아이템을 생성)
		StockState = MarioState::Normal;
	}
#pragma endregion

#pragma region __________ 충돌 관련 함수 __________

#pragma endregion\
};


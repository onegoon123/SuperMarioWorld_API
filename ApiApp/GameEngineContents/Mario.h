#pragma once
#include <GameEngineCore/GameEngineActor.h>
#include "MarioGameCore.h"
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
	enum State
	{
		Normal, Super, Fire, Cape
	};
	State MarioState = State::Normal;
	bool IsRidedYoshi = false;
	float Speed = 50.0f;
	float JumpForce = 10.0f;
	bool IsGrounded = true;

	// 부딪혀서 대미지를 받는 경우 실행되는 함수
	void GetDamaged() {
		switch (MarioState)
		{
		case Mario::Normal:
			GameOver();		// Normal일 경우 게임오버 함수 실행후 리턴
			return;
		case Mario::Super:
			MarioState = Normal;
			break;
		case Mario::Fire:
			MarioState = Normal;
			break;
		case Mario::Cape:
			MarioState = Normal;
			break;
		default:
			break;
		}
		InvincibilityTime();	// 무적 시간 활성
		MarioGameCore::GetInst().TakeOutStock();	// 스톡 아이템 소환
	}
	// 추락하거나 Normal 상태에서 대미지를 받을 경우 실행되는 게임오버 함수
	void GameOver() {

	}
	// 피격후 일정시간 공격을 방지하는 무적 함수
	void InvincibilityTime() {

	}
};


#include "Mario.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "ContentsEnums.h"


void Mario::ChangeState(MarioState _State)
{
	MarioState NextState = _State;
	MarioState PrevState = StateValue;

	StateValue = _State;

	switch (PrevState)
	{
	case MarioState::IDLE:
		IdleEnd();
		break;
	case MarioState::WALK:
		WalkEnd();
		break;
	case MarioState::RUN:
		RunEnd();
		break;
	case MarioState::JUMP:
		JumpEnd();
		break;
	case MarioState::SPIN:
		SpinEnd();
		break;
	case MarioState::BRAKE:
		BrakeEnd();
		break;
	case MarioState::CROUCH:
		CrouchEnd();
		break;
	case MarioState::LOOKUP:
		LookUpEnd();
		break;
	case MarioState::RUNJUMP:
		RunJumpEnd();
		break;
	case MarioState::FALL:
		FallEnd();
		break;
	default:
		break;
	}

	switch (NextState)
	{
	case MarioState::IDLE:
		IdleStart();
		break;
	case MarioState::WALK:
		WalkStart();
		break;
	case MarioState::RUN:
		RunStart();
		break;
	case MarioState::JUMP:
		JumpStart();
		break;
	case MarioState::SPIN:
		SpinStart();
		break;
	case MarioState::BRAKE:
		BrakeStart();
		break;
	case MarioState::CROUCH:
		CrouchStart();
		break;
	case MarioState::LOOKUP:
		LookUpStart();
		break;
	case MarioState::RUNJUMP:
		RunJumpStart();
		break;
	case MarioState::FALL:
		FallStart();
		break;
	default:
		break;
	}

}

void Mario::UpdateState(float _DeltaTime)
{
	switch (StateValue)
	{
	case MarioState::IDLE:
		IdleUpdate(_DeltaTime);
		break;
	case MarioState::WALK:
		WalkUpdate(_DeltaTime);
		break;
	case MarioState::RUN:
		RunUpdate(_DeltaTime);
		break;
	case MarioState::JUMP:
		JumpUpdate(_DeltaTime);
		break;
	case MarioState::SPIN:
		SpinUpdate(_DeltaTime);
		break;
	case MarioState::BRAKE:
		BrakeUpdate(_DeltaTime);
		break;
	case MarioState::CROUCH:
		CrouchUpdate(_DeltaTime);
		break;
	case MarioState::LOOKUP:
		LookUpUpdate(_DeltaTime);
		break;
	case MarioState::RUNJUMP:
		RunJumpUpdate(_DeltaTime);
		break;
	case MarioState::FALL:
		FallUpdate(_DeltaTime);
		break;
	default:
		break;
	}
}

void Mario::IdleStart()
{
	ChangeAnimation("Idle");
}

void Mario::IdleUpdate(float _DeltaTime)
{
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::JUMP);
		return;
	}
	// 스핀 키를 입력한 경우
	else if (GameEngineInput::IsDown("Spin"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::SPIN);
		return;
	}
	// 아래 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Down"))
	{
		// 앉은 상태로 전환
		ChangeState(MarioState::CROUCH);
		return;
	}
	// 양쪽 방향키를 동시에 입력한 경우
	else if (GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right"))
	{
		return;
	}
	// 왼쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Left"))
	{
		// 왼쪽으로 방향전환 및 걷기상태로 전환
		DirValue = Dir::Left;
		ChangeState(MarioState::WALK);
		return;
	}
	// 오른쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Right"))
	{
		// 오른쪽으로 방향전환 및 걷기상태로 전환
		DirValue = Dir::Right;
		ChangeState(MarioState::WALK);
		return;
	}
	else if (GameEngineInput::IsPress("Up"))
	{
		ChangeState(MarioState::LOOKUP);
		return;
	}
}

void Mario::IdleEnd()
{
}

void Mario::WalkStart()
{
	// 걷기 애니메이션으로 전환
	ChangeAnimation("Walk");
}

void Mario::WalkUpdate(float _DeltaTime)
{
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::JUMP);
		return;
	}
	// 아래 방향기를 입력한 경우
	else if (GameEngineInput::IsPress("Down"))
	{
		// 앉은 상태로 전환
		ChangeState(MarioState::CROUCH);
		return;
	}
	// 미입력 (방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우)
	else if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// 이전까지 오른쪽으로 이동하고 있던 경우
		if (0.1f < HorizontalForce)
		{
			// 서서히 속도를 낮춤
			HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
		}
		// 이전까지 왼쪽으로 이동하고 있던 경우
		else if (-0.1f > HorizontalForce)
		{
			// 서서히 속도를 낮춤
			HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
		}
		// 일정속도 이하 (멈춘경우)
		else
		{
			// IDLE 상태로 전환
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	// 왼쪽 방향키를 누른경우
	else if (GameEngineInput::IsPress("Left"))
	{
		// 이전까지 오른쪽 방향을 보고있던 경우
		if (Dir::Right == DirValue)
		{
			// 방향전환
			DirValue = Dir::Left;
			// 이전까지 오른쪽으로 이동하고 있던 경우
			if (0.1 < HorizontalForce)
			{
				// 브레이크 상태로 변경
				ChangeState(MarioState::BRAKE);
				return;
			}
			RunChargeTime = 0;
		}
		// 대시 키를 누르고 있는 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시처리
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -2);
			RunChargeTime += _DeltaTime;	// 대시를 한 시간 기록
		}
		// 대시 키를 누르지 않는 경우 (걷기)
		else
		{
			// 걷기처리

			// 이전까지 대시로 이동중에는
			if (-1 > HorizontalForce)
			{
				// 서서히 느리게
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -1);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷는 속도 지정
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -1);
			}
			RunChargeTime = 0;
		}
	}
	// 오른쪽 방향키를 누른 경우
	else if (GameEngineInput::IsPress("Right"))
	{
		// 이전까지 왼쪽 방향을 본 경우
		if (Dir::Left == DirValue)
		{
			// 방향전환
			DirValue = Dir::Right;
			// 이전까지 왼쪽 방향으로 이동한 경우
			if (-0.1 > HorizontalForce)
			{
				// 브레이크 상태로 전환
				ChangeState(MarioState::BRAKE);
				return;
			}
			RunChargeTime = 0;
		}

		// 대시키를 누른 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시 처리
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 2);
			RunChargeTime += _DeltaTime;	// 대시를 한 시간 기록
		}
		// 대시 키를 누르지 않은 경우 (일반 걷기 처리)
		else
		{
			// 이전까지 대시를 한 경우
			if (1 < HorizontalForce)
			{
				// 서서히 속도를 줄임
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 1);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷기 처리
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 1);
			}
			RunChargeTime = 0;
		}
	}
	// 속도가 1이상인 경우
	if (1.5f < std::abs(HorizontalForce))
	{
		if (1 < RunChargeTime)
		{
			// 런 상태로 전환
			ChangeState(MarioState::RUN);
			return;
		}
		ChangeAnimation("Dash");
	}
	else
	{
		ChangeAnimation("Walk");
	}
	// 대시를 입력한 시간이 1초를 넘긴 경우
	
	
	// 이동처리 및 카메라 이동처리
	SetMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
	GetLevel()->SetCameraMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
}

void Mario::WalkEnd()
{
	RunChargeTime = 0;
}

void Mario::RunStart()
{
	HorizontalForce = DirValue == Dir::Right ? 2 : -2;
	ChangeAnimation("Run");
}

void Mario::RunUpdate(float _DeltaTime)
{
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::JUMP);
		return;
	}
	// 아래 방향기를 입력한 경우
	if (GameEngineInput::IsPress("Down"))
	{
		// 앉은 상태로 전환
		ChangeState(MarioState::CROUCH);
		return;
	}
	// 방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우
	else if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// 걷기상태로 전환
		ChangeState(MarioState::WALK);
		return;
	}
	// 왼쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Left"))
	{
		// 이전까지 오른쪽 방향을 보고 있던 경우
		if (Dir::Right == DirValue)
		{
			// 왼쪽으로 방향전환 및 브레이크로 상태 전환
			DirValue = Dir::Left;
			ChangeState(MarioState::BRAKE);
			return;
		}
	}
	// 오른쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Right"))
	{
		// 이전까지 왼쪽방향을 보고 있던 경우
		if (Dir::Left == DirValue)
		{
			// 오른쪽으로 방향전환 및 브레이크로 상태전환
			DirValue = Dir::Right;
			ChangeState(MarioState::BRAKE);
			return;
		}
	}
	// 대시 키 입력을 땐 경우
	if (GameEngineInput::IsUp("Dash"))
	{
		// 걷기로 상태 전환
		ChangeState(MarioState::WALK);
		return;
	}
	
	// 위에 모든 조건에 해당되지 않으면 달리기 처리 (마리오 및 카메라처리)
	SetMove(float4::Right * HorizontalForce * RunSpeed * _DeltaTime);
	GetLevel()->SetCameraMove(float4::Right * HorizontalForce * RunSpeed * _DeltaTime);
}

void Mario::RunEnd()
{
}

void Mario::BrakeStart()
{
	ChangeAnimation("Brake");
}

void Mario::BrakeUpdate(float _DeltaTime)
{
	// 아래 방향기를 입력한 경우
	if (GameEngineInput::IsPress("Down"))
	{
		// 앉은 상태로 전환
		ChangeState(MarioState::CROUCH);
		return;
	}
	// 좌우키를 동시에 누르거나 좌우키 둘다 누르지 않은 경우
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// IDLE 상태로 전환
		ChangeState(MarioState::WALK);
		return;
	}
	// 왼쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Left"))
	{
		// 이전까지 오른쪽을 보고있는 경우
		if (Dir::Right == DirValue)
		{
			// 왼쪽으로 방향을 전환 및 걷기 상태로 전환
			DirValue = Dir::Left;
			ChangeState(MarioState::WALK);
			return;
		}
		// 관성으로 오른쪽으로 이동중인 경우
		if (0.1f < HorizontalForce)
		{
			// 속도를 점차 줄임
			HorizontalForce = std::max<float>(HorizontalForce - (BrakingForce * _DeltaTime), 0);
		}
		// 관성으로 왼쪽으로 이동중인 경우
		else if (-0.1f > HorizontalForce)
		{
			// 속도를 점차 줄임
			HorizontalForce = std::min<float>(HorizontalForce + (BrakingForce * _DeltaTime), 0);
		}
		// 현재 멈춘 경우
		else
		{
			// IDLE 상태로 전환
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	// 오른쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Right"))
	{
		// 이전까지 왼쪽을 본 경우
		if (Dir::Left == DirValue)
		{
			// 오른쪽으로 방향 전환 및 걷기 상태로 전환
			DirValue = Dir::Right;
			ChangeState(MarioState::WALK);
			return;
		}
		// 관성으로 오른쪽으로 이동중인 경우
		if (0.1f < HorizontalForce)
		{
			// 속도를 줄임
			HorizontalForce = std::max<float>(HorizontalForce - (BrakingForce * _DeltaTime), 0);
		}
		// 관성으로 왼쪽으로 이동중인 경우
		else if (-0.1f > HorizontalForce)
		{
			// 속도를 줄임
			HorizontalForce = std::min<float>(HorizontalForce + (BrakingForce * _DeltaTime), 0);
		}
		// 멈춘 상태인 경우
		else
		{
			// IDLE 상태로 전환
			ChangeState(MarioState::IDLE);
			return;
		}
	}

	// 관성으로 남은 힘만큼 이동
	SetMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
	GetLevel()->SetCameraMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
}

void Mario::BrakeEnd()
{
}

void Mario::JumpStart()
{
	ChangeAnimation("Jump");
}

void Mario::JumpUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsUp("Jump"))
	{
		ChangeState(MarioState::IDLE);
		return;
	}
}

void Mario::JumpEnd()
{
}

void Mario::SpinStart()
{
	ChangeAnimation("Spin");
}

void Mario::SpinUpdate(float _DeltaTime)
{
	if (GameEngineInput::IsUp("Spin"))
	{
		ChangeState(MarioState::IDLE);
		return;
	}
}

void Mario::SpinEnd()
{
}

void Mario::CrouchStart()
{
	ChangeAnimation("Crouch");
}

void Mario::CrouchUpdate(float _DeltaTime)
{

	if (GameEngineInput::IsUp("Down"))
	{
		if (0.1f < std::abs(HorizontalForce))
		{
			ChangeState(MarioState::WALK);
			return;
		}
		else
		{
			ChangeState(MarioState::IDLE);
			return;
		}
	}

	// 현재 관성으로 오른쪽으로 이동하는 경우
	if (0.1f < HorizontalForce)
	{
		// 속도를 점차 줄인다
		HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
	}
	// 현재 관성으로 왼쪽으로 이동하는 경우
	else if (-0.1f > HorizontalForce)
	{
	// 속도를 점차 줄인다
		HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
	}
	else
	{
		return;
	}
	
	

	// 관성으로 남은 힘만큼 이동
	SetMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
	GetLevel()->SetCameraMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
}

void Mario::CrouchEnd()
{
}

void Mario::LookUpStart()
{
	ChangeAnimation("LookUp");
}

void Mario::LookUpUpdate(float _DeltaTime)
{
	// 위쪽 방향키를 땐 경우
	if (GameEngineInput::IsUp("Up"))
	{
		ChangeState(MarioState::IDLE);
		return;
	}
	// 양쪽 방향키를 동시에 입력한 경우
	else if (GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right"))
	{
		return;
	}
	// 왼쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Left"))
	{
		// 왼쪽으로 방향전환 및 걷기상태로 전환
		DirValue = Dir::Left;
		ChangeState(MarioState::WALK);
		return;
	}
	// 오른쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Right"))
	{
		// 오른쪽으로 방향전환 및 걷기상태로 전환
		DirValue = Dir::Right;
		ChangeState(MarioState::WALK);
		return;
	}
}

void Mario::LookUpEnd()
{
}

void Mario::RunJumpStart()
{
}

void Mario::RunJumpUpdate(float _DeltaTime)
{
}

void Mario::RunJumpEnd()
{
}

void Mario::FallStart()
{
}

void Mario::FallUpdate(float _DeltaTime)
{
}

void Mario::FallEnd()
{
}



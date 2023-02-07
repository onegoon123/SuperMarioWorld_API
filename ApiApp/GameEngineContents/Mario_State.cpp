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

	switch (StateValue)
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
	case MarioState::SLIDE:
		SlideEnd();
		break;
	case MarioState::KICK:
		break;
	case MarioState::CHANGEPOWER:
		break;
	case MarioState::VICTORY:
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
	case MarioState::SLIDE:
		SlideStart();
		break;
	case MarioState::KICK:
		break;
	case MarioState::CHANGEPOWER:
		break;
	case MarioState::VICTORY:
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
	case MarioState::SLIDE:
		SlideUpdate(_DeltaTime);
		break;
	case MarioState::KICK:
		break;
	case MarioState::CHANGEPOWER:
		break;
	case MarioState::VICTORY:
		break;
	default:
		break;
	}
}

void Mario::IdleStart()
{
	HorizontalForce = 0;
	ChangeAnimation("Idle");
}

void Mario::IdleUpdate(float _DeltaTime)
{
	// 스타트 키가 눌린 경우
	if (GameEngineInput::IsDown("Start"))
	{
		// 테스트용 코드
		MarioPower = PowerState::Super;
	}
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
	// 양쪽 방향키를 동시에 입력하거나 둘다 입력하지 않은 경우
	else if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (false == GameEngineInput::IsPress("Left") && false == GameEngineInput::IsPress("Right")))
	{
		// 비탈길에 있는 경우
		if (true == IsSlope)
		{
			ChangeState(MarioState::WALK);
		}
		// 위를 입력한 경우
		else if (GameEngineInput::IsPress("Up"))
		{
			ChangeState(MarioState::LOOKUP);
		}
		return;
	}
	// 왼쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Left"))
	{
		if (RGB(0, 0, 0) == ColMap->GetPixelColor(GetPos() + float4::Left * 4, RGB(0, 0, 0)))
		{
			return;
		}
		// 왼쪽으로 방향전환 및 걷기상태로 전환
		DirValue = Dir::Left;
		ChangeState(MarioState::WALK);
		return;
	}
	// 오른쪽 방향키를 입력한 경우
	else if (GameEngineInput::IsPress("Right"))
	{
		if (RGB(0, 0, 0) == ColMap->GetPixelColor(GetPos() + float4::Right * 4, RGB(0, 0, 0)))
		{
			return;
		}
		// 오른쪽으로 방향전환 및 걷기상태로 전환
		DirValue = Dir::Right;
		ChangeState(MarioState::WALK);
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
	// 스핀 키를 입력한 경우
	if (GameEngineInput::IsDown("Spin"))
	{
		// 스핀 상태로 전환
		ChangeState(MarioState::SPIN);
		return;
	}
	// 아래 방향기를 입력한 경우
	if (GameEngineInput::IsPress("Down"))
	{
		// 앉은 상태로 전환
		ChangeState(MarioState::CROUCH);
		return;
	}

	
	// 미입력 (방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// 비탈길에 있는 상황이 아닌 경우
		if (false == IsSlope)
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
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
			RunChargeTime += _DeltaTime;	// 대시를 한 시간 기록
		}
		// 대시 키를 누르지 않는 경우 (걷기)
		else
		{
			// 걷기처리

			// 경사로인 경우
			if (true == IsSlope)
			{
				// 걷기 처리
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -1.0f);
			}
			// 이전까지 대시로 이동중에는
			else if (-0.5f > HorizontalForce)
			{
				// 서서히 느리게
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷는 속도 지정
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
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
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
			RunChargeTime += _DeltaTime;	// 대시를 한 시간 기록
		}
		// 대시 키를 누르지 않은 경우 (일반 걷기 처리)
		else
		{
			// 경사로인 경우
			if (true == IsSlope)
			{
				// 걷기 처리
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 1.0f);
			}
			// 이전까지 대시를 한 경우
			else if (0.5f < HorizontalForce)
			{
				// 서서히 속도를 줄임
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷기 처리
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 0.5f);
			}
			RunChargeTime = 0;
		}
	}

	if (true == IsSlope)
	{
		// 왼쪽으로 미끄러지는 경우
		if (Dir::Left == SlopeDir)
		{
			// 오른쪽으로 이동중인 경우
			if (0 < HorizontalForce)
			{
				if (GameEngineInput::IsPress("Dash"))
				{
					HorizontalForce = std::min<float>(HorizontalForce - _DeltaTime, 0.8f);
				}
				else
				{
					HorizontalForce = std::min<float>(HorizontalForce - _DeltaTime, 0.4f);
				}
			}
			// 왼쪽으로 이동중인 경우
			else
			{
				HorizontalForce = std::max<float>(HorizontalForce - _DeltaTime, -1.0f);
			}
		}
		// 오른쪽으로 미끄러지는 경우
		else
		{
			// 왼쪽으로 이동중인 경우
			if (0 > HorizontalForce)
			{
				if (GameEngineInput::IsPress("Dash"))
				{
					HorizontalForce = std::max<float>(HorizontalForce + _DeltaTime, -0.8f);
				}
				else
				{
					HorizontalForce = std::max<float>(HorizontalForce + _DeltaTime, -0.4f);
				}
			}
			// 오른쪽으로 이동중인 경우
			else
			{
				HorizontalForce = std::min<float>(HorizontalForce + _DeltaTime, 1.0f);
			}
		}
	}

	// 속도가 0.7이상인 경우
	if (0.7f < std::abs(HorizontalForce))
	{
		// 대시를 입력한 시간이 1초를 넘긴 경우
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
	
}

void Mario::WalkEnd()
{
	RunChargeTime = 0;
}

void Mario::RunStart()
{
	HorizontalForce = DirValue == Dir::Right ? 1.0f : -1.0f;
	ChangeAnimation("Run");
}

void Mario::RunUpdate(float _DeltaTime)
{
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::RUNJUMP);
		return;
	}
	// 스핀 키를 입력한 경우
	if (GameEngineInput::IsDown("Spin"))
	{
		// 스핀 상태로 전환
		ChangeState(MarioState::SPIN);
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
	
	if (true == IsSlope)
	{
		// 왼쪽으로 미끄러지는 경우
		if (Dir::Left == SlopeDir)
		{
			// 오른쪽으로 이동중인 경우
			if (0 < HorizontalForce)
			{
				HorizontalForce = 0.8f;
			}
			// 왼쪽으로 이동중인 경우
			else
			{
				HorizontalForce = -1.0f;
			}
		}
		// 오른쪽으로 미끄러지는 경우
		else
		{
			// 왼쪽으로 이동중인 경우
			if (0 > HorizontalForce)
			{
				HorizontalForce = -0.8f;
			}
			// 오른쪽으로 이동중인 경우
			else
			{
				HorizontalForce = 1.0f;
			}
		}
	}
	else
	{
		// 오른쪽으로 이동중인 경우
		if (0 < HorizontalForce)
		{
			HorizontalForce = 1.0f;
		}
		// 왼쪽으로 이동중인 경우
		else
		{
			HorizontalForce = -1.0f;
		}
	}

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
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::JUMP);
		return;
	}
	// 스핀 키를 입력한 경우
	if (GameEngineInput::IsDown("Spin"))
	{
		// 스핀 상태로 전환
		ChangeState(MarioState::SPIN);
		return;
	}
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
}

void Mario::BrakeEnd()
{
}

void Mario::JumpStart()
{
	IsGrounded = false;
	ChangeAnimation("Jump");
	JumpTimeCounter = JumpTime;
	if (0.5f < std::abs(HorizontalForce))
	{
		MoveDir += float4::Up * DashJumpForce;
	}
	else
	{
		MoveDir += float4::Up * JumpForce;
	}
}

void Mario::JumpUpdate(float _DeltaTime)
{
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsPress("Jump"))
	{
		if (0 < JumpTimeCounter)
		{
			MoveDir += float4::Up * JumpPressForce * _DeltaTime;
			JumpTimeCounter -= _DeltaTime;
		}
	}
	// 미입력 (방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
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
			HorizontalForce = 0;
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
			ChangeAnimation("Jump");
		}
		// 대시 키를 누르고 있는 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시처리
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// 대시 키를 누르지 않는 경우 (걷기)
		else
		{
			// 걷기처리

			// 이전까지 대시로 이동중에는
			if (-0.5f > HorizontalForce)
			{
				// 서서히 느리게
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷는 속도 지정
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
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
			ChangeAnimation("Jump");
		}

		// 대시키를 누른 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시 처리
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// 대시 키를 누르지 않은 경우 (일반 걷기 처리)
		else
		{
			// 이전까지 대시를 한 경우
			if (0.5f < HorizontalForce)
			{
				// 서서히 속도를 줄임
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷기 처리
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 0.5f);
			}
		}
	}
}

void Mario::JumpEnd()
{
}

void Mario::SpinStart()
{
	IsGrounded = false;
	ChangeAnimation("Spin");
	MoveDir += float4::Up * JumpForce;
	JumpTimeCounter = JumpTime;
}

void Mario::SpinUpdate(float _DeltaTime)
{
	if (true == IsGrounded)
	{
		if (0 < std::abs(HorizontalForce))
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
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsPress("Spin"))
	{
		if (0 < JumpTimeCounter)
		{
			MoveDir += float4::Up * SpinPressForce * _DeltaTime;
			JumpTimeCounter -= _DeltaTime;
		}
	}
	// 미입력 (방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
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
			HorizontalForce = 0;
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
		}
		// 대시 키를 누르고 있는 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시처리
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// 대시 키를 누르지 않는 경우 (걷기)
		else
		{
			// 걷기처리

			// 이전까지 대시로 이동중에는
			if (-0.5f > HorizontalForce)
			{
				// 서서히 느리게
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷는 속도 지정
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
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
		}

		// 대시키를 누른 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시 처리
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// 대시 키를 누르지 않은 경우 (일반 걷기 처리)
		else
		{
			// 이전까지 대시를 한 경우
			if (0.5f < HorizontalForce)
			{
				// 서서히 속도를 줄임
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷기 처리
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 0.5f);
			}
		}
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

	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::JUMP);
		return;
	}
	// 스핀 키를 입력한 경우
	if (GameEngineInput::IsDown("Spin"))
	{
		// 스핀 상태로 전환
		ChangeState(MarioState::SPIN);
		return;
	}
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
	// 경사로인 경우
	if (true == IsSlope)
	{
		ChangeState(MarioState::SLIDE);
		return;
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
		HorizontalForce = 0;
		return;
	}
	
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
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::JUMP);
		return;
	}
	// 스핀 키를 입력한 경우
	if (GameEngineInput::IsDown("Spin"))
	{
		// 스핀 상태로 전환
		ChangeState(MarioState::SPIN);
		return;
	}
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
	IsGrounded = false;
	ChangeAnimation("RunJump");
	JumpTimeCounter = JumpTime;
	MoveDir += float4::Up * RunJumpForce;
}

void Mario::RunJumpUpdate(float _DeltaTime)
{
	if (true == IsGrounded)
	{
		if ((Dir::Right == DirValue && 0.5f < HorizontalForce) || (Dir::Left == DirValue && -0.5f > HorizontalForce))
		{
			ChangeState(MarioState::RUN);
			return;
		}
		else if (0 < std::abs(HorizontalForce))
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
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsPress("Jump"))
	{
		if (0 < JumpTimeCounter)
		{
			MoveDir += float4::Up * JumpPressForce * _DeltaTime;
			JumpTimeCounter -= _DeltaTime;
		}
	}
	// 미입력 (방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
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
			HorizontalForce = 0;
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
			ChangeAnimation("RunJump");
		}
		// 대시 키를 누르고 있는 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시처리
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// 대시 키를 누르지 않는 경우 (걷기)
		else
		{
			// 걷기처리

			// 이전까지 대시로 이동중에는
			if (-0.5f > HorizontalForce)
			{
				// 서서히 느리게
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷는 속도 지정
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
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
			ChangeAnimation("RunJump");
		}

		// 대시키를 누른 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시 처리
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// 대시 키를 누르지 않은 경우 (일반 걷기 처리)
		else
		{
			// 이전까지 대시를 한 경우
			if (0.5f < HorizontalForce)
			{
				// 서서히 속도를 줄임
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷기 처리
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 0.5f);
			}
		}
	}
}

void Mario::RunJumpEnd()
{
}

void Mario::FallStart()
{
	ChangeAnimation("Fall");
}

void Mario::FallUpdate(float _DeltaTime)
{

	if (true == IsGrounded)
	{
		if (0 < std::abs(HorizontalForce))
		{
			if (-0.1f > HorizontalForce && true == GameEngineInput::IsPress("Right"))
			{
				ChangeState(MarioState::BRAKE);
				return;
			}
			if (0.1f < HorizontalForce && true == GameEngineInput::IsPress("Left"))
			{
				ChangeState(MarioState::BRAKE);
				return;
			}
			ChangeState(MarioState::WALK);
			return;
		}
		else
		{
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsPress("Jump"))
	{
	}
	// 미입력 (방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
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
			HorizontalForce = 0;
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
			ChangeAnimation("Fall");
		}
		// 대시 키를 누르고 있는 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시처리
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// 대시 키를 누르지 않는 경우 (걷기)
		else
		{
			// 걷기처리

			// 이전까지 대시로 이동중에는
			if (-0.5f > HorizontalForce)
			{
				// 서서히 느리게
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷는 속도 지정
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
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
			ChangeAnimation("Fall");
		}

		// 대시키를 누른 경우
		if (GameEngineInput::IsPress("Dash"))
		{
			// 대시 처리
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// 대시 키를 누르지 않은 경우 (일반 걷기 처리)
		else
		{
			// 이전까지 대시를 한 경우
			if (0.5f < HorizontalForce)
			{
				// 서서히 속도를 줄임
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// 그외 경우 (일반적인 걷기)
			else
			{
				// 걷기 처리
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 0.5f);
			}
		}
	}
}

void Mario::FallEnd()
{
}

void Mario::SlideStart()
{
	ChangeAnimation("Slide");
}

void Mario::SlideUpdate(float _DeltaTime)
{
	// 점프 키를 입력한 경우
	if (GameEngineInput::IsDown("Jump"))
	{
		// 점프 상태로 전환
		ChangeState(MarioState::JUMP);
		return;
	}
	// 스핀 키를 입력한 경우
	if (GameEngineInput::IsDown("Spin"))
	{
		// 스핀 상태로 전환
		ChangeState(MarioState::SPIN);
		return;
	}
	if (GameEngineInput::IsUp("Down"))
	{
		ChangeState(MarioState::WALK);
		return;
	}
	if (false == IsSlope)
	{
		if (0 != std::abs(HorizontalForce))
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
				ChangeState(MarioState::CROUCH);
			}
		}
		else
		{
			ChangeState(MarioState::CROUCH);
		}
		return;
	}

	// 왼쪽으로 미끄러지는 경우
	if (Dir::Left == SlopeDir)
	{
		// 오른쪽으로 이동중인 경우
		if (0 < HorizontalForce)
		{
			HorizontalForce = HorizontalForce - StoppingForce * _DeltaTime;
		}
		// 왼쪽으로 이동중인 경우
		else
		{
			HorizontalForce = std::max<float>(HorizontalForce - DashAcceleration * _DeltaTime, -1.2f);
		}
	}
	// 오른쪽으로 미끄러지는 경우
	else
	{
		// 왼쪽으로 이동중인 경우
		if (0 > HorizontalForce)
		{
			HorizontalForce = HorizontalForce + StoppingForce * _DeltaTime;
		}
		// 오른쪽으로 이동중인 경우
		else
		{
			HorizontalForce = std::min<float>(HorizontalForce + DashAcceleration * _DeltaTime, 1.2f);
		}
	}
}

void Mario::SlideEnd()
{
}



#include "Mario.h"
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEngineBase/GameEnginePath.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEnginePlatform/GameEngineInput.h>
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
	if (GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right"))
	{
		return;
	}
	if (GameEngineInput::IsPress("Left"))
	{
		DirValue = Dir::Left;
		ChangeState(MarioState::WALK);
		return;
	}
	else if (GameEngineInput::IsPress("Right"))
	{
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
	ChangeAnimation("Walk");
}

void Mario::WalkUpdate(float _DeltaTime)
{

	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// 방향키를 입력하지 않는경우 or 양쪽 방향키를 동시에 입력한 경우

		if (0.1f < HorizontalForce)
		{
			HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
		}
		else if (-0.1f > HorizontalForce)
		{
			HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
		}
		else
		{
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	else if (GameEngineInput::IsPress("Left"))
	{
		if (Dir::Right == DirValue)
		{
			RunChargeTime = 0;
			DirValue = Dir::Left;
			if (0.1 < HorizontalForce)
			{
				ChangeState(MarioState::BRAKE);
				return;
			}
			ChangeAnimation("Walk");
		}
		if (GameEngineInput::IsPress("Dash"))
		{
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -2);
			RunChargeTime += _DeltaTime;
		}
		else
		{
			HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -1);
		}
	}
	else if (GameEngineInput::IsPress("Right"))
	{
		if (Dir::Left == DirValue)
		{
			RunChargeTime = 0;
			DirValue = Dir::Right;
			if (-0.1 > HorizontalForce)
			{
				ChangeState(MarioState::BRAKE);
				return;
			}
			ChangeAnimation("Walk");
		}
		if (GameEngineInput::IsPress("Dash"))
		{
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 2);
			RunChargeTime += _DeltaTime;
		}
		else
		{
			HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 1);
		}
	}
	if (1 < RunChargeTime)
	{
		ChangeState(MarioState::RUN);
		return;
	}
	SetMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
}

void Mario::WalkEnd()
{
	RunChargeTime = 0;
}

void Mario::RunStart()
{
	ChangeAnimation("Run");
}

void Mario::RunUpdate(float _DeltaTime)
{
	SetMove(float4::Right * HorizontalForce * RunSpeed * _DeltaTime);
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
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		if (0.1f < HorizontalForce)
		{
			HorizontalForce = std::max<float>(HorizontalForce - (BrakingForce * _DeltaTime), 0);
		}
		else if (-0.1f > HorizontalForce)
		{
			HorizontalForce = std::min<float>(HorizontalForce + (BrakingForce * _DeltaTime), 0);
		}
		else
		{
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	else if (GameEngineInput::IsPress("Left"))
	{
		if (Dir::Right == DirValue)
		{
			DirValue = Dir::Left;
			ChangeState(MarioState::WALK);
			return;
		}
		if (0.1f < HorizontalForce)
		{
			HorizontalForce = std::max<float>(HorizontalForce - (BrakingForce * _DeltaTime), 0);
		}
		else if (-0.1f > HorizontalForce)
		{
			HorizontalForce = std::min<float>(HorizontalForce + (BrakingForce * _DeltaTime), 0);
		}
		else
		{
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	else if (GameEngineInput::IsPress("Right"))
	{
		if (Dir::Left == DirValue)
		{
			DirValue = Dir::Right;
			ChangeState(MarioState::WALK);
			return;
		}
		if (0.1f < HorizontalForce)
		{
			HorizontalForce = std::max<float>(HorizontalForce - (BrakingForce * _DeltaTime), 0);
		}
		else if (-0.1f > HorizontalForce)
		{
			HorizontalForce = std::min<float>(HorizontalForce + (BrakingForce * _DeltaTime), 0);
		}
		else
		{
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	SetMove(float4::Right * HorizontalForce * Speed * _DeltaTime);
}

void Mario::BrakeEnd()
{
}

void Mario::JumpStart()
{
}

void Mario::JumpUpdate(float _DeltaTime)
{
}

void Mario::JumpEnd()
{
}

void Mario::SpinStart()
{
}

void Mario::SpinUpdate(float _DeltaTime)
{
}

void Mario::SpinEnd()
{
}



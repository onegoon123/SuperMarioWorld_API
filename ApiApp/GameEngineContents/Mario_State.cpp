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
	// ��ŸƮ Ű�� ���� ���
	if (GameEngineInput::IsDown("Start"))
	{
		// �׽�Ʈ�� �ڵ�
		MarioPower = PowerState::Super;
	}
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::JUMP);
		return;
	}
	// ���� Ű�� �Է��� ���
	else if (GameEngineInput::IsDown("Spin"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::SPIN);
		return;
	}
	// �Ʒ� ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Down"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::CROUCH);
		return;
	}
	// ���� ����Ű�� ���ÿ� �Է��ϰų� �Ѵ� �Է����� ���� ���
	else if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (false == GameEngineInput::IsPress("Left") && false == GameEngineInput::IsPress("Right")))
	{
		// ��Ż�濡 �ִ� ���
		if (true == IsSlope)
		{
			ChangeState(MarioState::WALK);
		}
		// ���� �Է��� ���
		else if (GameEngineInput::IsPress("Up"))
		{
			ChangeState(MarioState::LOOKUP);
		}
		return;
	}
	// ���� ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Left"))
	{
		if (RGB(0, 0, 0) == ColMap->GetPixelColor(GetPos() + float4::Left * 4, RGB(0, 0, 0)))
		{
			return;
		}
		// �������� ������ȯ �� �ȱ���·� ��ȯ
		DirValue = Dir::Left;
		ChangeState(MarioState::WALK);
		return;
	}
	// ������ ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		if (RGB(0, 0, 0) == ColMap->GetPixelColor(GetPos() + float4::Right * 4, RGB(0, 0, 0)))
		{
			return;
		}
		// ���������� ������ȯ �� �ȱ���·� ��ȯ
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
	// �ȱ� �ִϸ��̼����� ��ȯ
	ChangeAnimation("Walk");
}

void Mario::WalkUpdate(float _DeltaTime)
{
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::JUMP);
		return;
	}
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Spin"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::SPIN);
		return;
	}
	// �Ʒ� ����⸦ �Է��� ���
	if (GameEngineInput::IsPress("Down"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::CROUCH);
		return;
	}

	
	// ���Է� (����Ű�� �Է����� �ʴ°�� or ���� ����Ű�� ���ÿ� �Է��� ���)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// ��Ż�濡 �ִ� ��Ȳ�� �ƴ� ���
		if (false == IsSlope)
		{
				// �������� ���������� �̵��ϰ� �ִ� ���
				if (0.1f < HorizontalForce)
				{
					// ������ �ӵ��� ����
					HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
				}
				// �������� �������� �̵��ϰ� �ִ� ���
				else if (-0.1f > HorizontalForce)
				{
					// ������ �ӵ��� ����
					HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
				}
				// �����ӵ� ���� (������)
				else
				{
					// IDLE ���·� ��ȯ
					ChangeState(MarioState::IDLE);
					return;
				}
		}
	}
	// ���� ����Ű�� �������
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� ������ ������ �����ִ� ���
		if (Dir::Right == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Left;
			// �������� ���������� �̵��ϰ� �ִ� ���
			if (0.1 < HorizontalForce)
			{
				// �극��ũ ���·� ����
				ChangeState(MarioState::BRAKE);
				return;
			}
			RunChargeTime = 0;
		}
		// ��� Ű�� ������ �ִ� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ���ó��
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
			RunChargeTime += _DeltaTime;	// ��ø� �� �ð� ���
		}
		// ��� Ű�� ������ �ʴ� ��� (�ȱ�)
		else
		{
			// �ȱ�ó��

			// ������ ���
			if (true == IsSlope)
			{
				// �ȱ� ó��
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -1.0f);
			}
			// �������� ��÷� �̵��߿���
			else if (-0.5f > HorizontalForce)
			{
				// ������ ������
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȴ� �ӵ� ����
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
			RunChargeTime = 0;
		}
	}
	// ������ ����Ű�� ���� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// �������� ���� ������ �� ���
		if (Dir::Left == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Right;
			// �������� ���� �������� �̵��� ���
			if (-0.1 > HorizontalForce)
			{
				// �극��ũ ���·� ��ȯ
				ChangeState(MarioState::BRAKE);
				return;
			}
			RunChargeTime = 0;
		}

		// ���Ű�� ���� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ��� ó��
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
			RunChargeTime += _DeltaTime;	// ��ø� �� �ð� ���
		}
		// ��� Ű�� ������ ���� ��� (�Ϲ� �ȱ� ó��)
		else
		{
			// ������ ���
			if (true == IsSlope)
			{
				// �ȱ� ó��
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 1.0f);
			}
			// �������� ��ø� �� ���
			else if (0.5f < HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȱ� ó��
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 0.5f);
			}
			RunChargeTime = 0;
		}
	}

	if (true == IsSlope)
	{
		// �������� �̲������� ���
		if (Dir::Left == SlopeDir)
		{
			// ���������� �̵����� ���
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
			// �������� �̵����� ���
			else
			{
				HorizontalForce = std::max<float>(HorizontalForce - _DeltaTime, -1.0f);
			}
		}
		// ���������� �̲������� ���
		else
		{
			// �������� �̵����� ���
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
			// ���������� �̵����� ���
			else
			{
				HorizontalForce = std::min<float>(HorizontalForce + _DeltaTime, 1.0f);
			}
		}
	}

	// �ӵ��� 0.7�̻��� ���
	if (0.7f < std::abs(HorizontalForce))
	{
		// ��ø� �Է��� �ð��� 1�ʸ� �ѱ� ���
		if (1 < RunChargeTime)
		{
			// �� ���·� ��ȯ
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::RUNJUMP);
		return;
	}
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Spin"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::SPIN);
		return;
	}
	// �Ʒ� ����⸦ �Է��� ���
	if (GameEngineInput::IsPress("Down"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::CROUCH);
		return;
	}
	// ����Ű�� �Է����� �ʴ°�� or ���� ����Ű�� ���ÿ� �Է��� ���
	else if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// �ȱ���·� ��ȯ
		ChangeState(MarioState::WALK);
		return;
	}
	// ���� ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� ������ ������ ���� �ִ� ���
		if (Dir::Right == DirValue)
		{
			// �������� ������ȯ �� �극��ũ�� ���� ��ȯ
			DirValue = Dir::Left;
			ChangeState(MarioState::BRAKE);
			return;
		}
	}
	// ������ ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// �������� ���ʹ����� ���� �ִ� ���
		if (Dir::Left == DirValue)
		{
			// ���������� ������ȯ �� �극��ũ�� ������ȯ
			DirValue = Dir::Right;
			ChangeState(MarioState::BRAKE);
			return;
		}
	}
	// ��� Ű �Է��� �� ���
	if (GameEngineInput::IsUp("Dash"))
	{
		// �ȱ�� ���� ��ȯ
		ChangeState(MarioState::WALK);
		return;
	}
	
	if (true == IsSlope)
	{
		// �������� �̲������� ���
		if (Dir::Left == SlopeDir)
		{
			// ���������� �̵����� ���
			if (0 < HorizontalForce)
			{
				HorizontalForce = 0.8f;
			}
			// �������� �̵����� ���
			else
			{
				HorizontalForce = -1.0f;
			}
		}
		// ���������� �̲������� ���
		else
		{
			// �������� �̵����� ���
			if (0 > HorizontalForce)
			{
				HorizontalForce = -0.8f;
			}
			// ���������� �̵����� ���
			else
			{
				HorizontalForce = 1.0f;
			}
		}
	}
	else
	{
		// ���������� �̵����� ���
		if (0 < HorizontalForce)
		{
			HorizontalForce = 1.0f;
		}
		// �������� �̵����� ���
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::JUMP);
		return;
	}
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Spin"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::SPIN);
		return;
	}
	// �Ʒ� ����⸦ �Է��� ���
	if (GameEngineInput::IsPress("Down"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::CROUCH);
		return;
	}
	// �¿�Ű�� ���ÿ� �����ų� �¿�Ű �Ѵ� ������ ���� ���
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// IDLE ���·� ��ȯ
		ChangeState(MarioState::WALK);
		return;
	}
	// ���� ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� �������� �����ִ� ���
		if (Dir::Right == DirValue)
		{
			// �������� ������ ��ȯ �� �ȱ� ���·� ��ȯ
			DirValue = Dir::Left;
			ChangeState(MarioState::WALK);
			return;
		}
		// �������� ���������� �̵����� ���
		if (0.1f < HorizontalForce)
		{
			// �ӵ��� ���� ����
			HorizontalForce = std::max<float>(HorizontalForce - (BrakingForce * _DeltaTime), 0);
		}
		// �������� �������� �̵����� ���
		else if (-0.1f > HorizontalForce)
		{
			// �ӵ��� ���� ����
			HorizontalForce = std::min<float>(HorizontalForce + (BrakingForce * _DeltaTime), 0);
		}
		// ���� ���� ���
		else
		{
			// IDLE ���·� ��ȯ
			ChangeState(MarioState::IDLE);
			return;
		}
	}
	// ������ ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// �������� ������ �� ���
		if (Dir::Left == DirValue)
		{
			// ���������� ���� ��ȯ �� �ȱ� ���·� ��ȯ
			DirValue = Dir::Right;
			ChangeState(MarioState::WALK);
			return;
		}
		// �������� ���������� �̵����� ���
		if (0.1f < HorizontalForce)
		{
			// �ӵ��� ����
			HorizontalForce = std::max<float>(HorizontalForce - (BrakingForce * _DeltaTime), 0);
		}
		// �������� �������� �̵����� ���
		else if (-0.1f > HorizontalForce)
		{
			// �ӵ��� ����
			HorizontalForce = std::min<float>(HorizontalForce + (BrakingForce * _DeltaTime), 0);
		}
		// ���� ������ ���
		else
		{
			// IDLE ���·� ��ȯ
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsPress("Jump"))
	{
		if (0 < JumpTimeCounter)
		{
			MoveDir += float4::Up * JumpPressForce * _DeltaTime;
			JumpTimeCounter -= _DeltaTime;
		}
	}
	// ���Է� (����Ű�� �Է����� �ʴ°�� or ���� ����Ű�� ���ÿ� �Է��� ���)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// �������� ���������� �̵��ϰ� �ִ� ���
		if (0.1f < HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
		}
		// �������� �������� �̵��ϰ� �ִ� ���
		else if (-0.1f > HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
		}
		// �����ӵ� ���� (������)
		else
		{
			HorizontalForce = 0;
		}
	}
	// ���� ����Ű�� �������
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� ������ ������ �����ִ� ���
		if (Dir::Right == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Left;
			ChangeAnimation("Jump");
		}
		// ��� Ű�� ������ �ִ� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ���ó��
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// ��� Ű�� ������ �ʴ� ��� (�ȱ�)
		else
		{
			// �ȱ�ó��

			// �������� ��÷� �̵��߿���
			if (-0.5f > HorizontalForce)
			{
				// ������ ������
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȴ� �ӵ� ����
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
		}
	}
	// ������ ����Ű�� ���� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// �������� ���� ������ �� ���
		if (Dir::Left == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Right;
			ChangeAnimation("Jump");
		}

		// ���Ű�� ���� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ��� ó��
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// ��� Ű�� ������ ���� ��� (�Ϲ� �ȱ� ó��)
		else
		{
			// �������� ��ø� �� ���
			if (0.5f < HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȱ� ó��
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsPress("Spin"))
	{
		if (0 < JumpTimeCounter)
		{
			MoveDir += float4::Up * SpinPressForce * _DeltaTime;
			JumpTimeCounter -= _DeltaTime;
		}
	}
	// ���Է� (����Ű�� �Է����� �ʴ°�� or ���� ����Ű�� ���ÿ� �Է��� ���)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// �������� ���������� �̵��ϰ� �ִ� ���
		if (0.1f < HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
		}
		// �������� �������� �̵��ϰ� �ִ� ���
		else if (-0.1f > HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
		}
		// �����ӵ� ���� (������)
		else
		{
			HorizontalForce = 0;
		}
	}
	// ���� ����Ű�� �������
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� ������ ������ �����ִ� ���
		if (Dir::Right == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Left;
		}
		// ��� Ű�� ������ �ִ� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ���ó��
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// ��� Ű�� ������ �ʴ� ��� (�ȱ�)
		else
		{
			// �ȱ�ó��

			// �������� ��÷� �̵��߿���
			if (-0.5f > HorizontalForce)
			{
				// ������ ������
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȴ� �ӵ� ����
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
		}
	}
	// ������ ����Ű�� ���� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// �������� ���� ������ �� ���
		if (Dir::Left == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Right;
		}

		// ���Ű�� ���� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ��� ó��
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// ��� Ű�� ������ ���� ��� (�Ϲ� �ȱ� ó��)
		else
		{
			// �������� ��ø� �� ���
			if (0.5f < HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȱ� ó��
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

	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::JUMP);
		return;
	}
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Spin"))
	{
		// ���� ���·� ��ȯ
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
	// ������ ���
	if (true == IsSlope)
	{
		ChangeState(MarioState::SLIDE);
		return;
	}

	// ���� �������� ���������� �̵��ϴ� ���
	if (0.1f < HorizontalForce)
	{
		// �ӵ��� ���� ���δ�
		HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
	}
	// ���� �������� �������� �̵��ϴ� ���
	else if (-0.1f > HorizontalForce)
	{
	// �ӵ��� ���� ���δ�
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::JUMP);
		return;
	}
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Spin"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::SPIN);
		return;
	}
	// ���� ����Ű�� �� ���
	if (GameEngineInput::IsUp("Up"))
	{
		ChangeState(MarioState::IDLE);
		return;
	}
	// ���� ����Ű�� ���ÿ� �Է��� ���
	else if (GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right"))
	{
		return;
	}
	// ���� ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� ������ȯ �� �ȱ���·� ��ȯ
		DirValue = Dir::Left;
		ChangeState(MarioState::WALK);
		return;
	}
	// ������ ����Ű�� �Է��� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// ���������� ������ȯ �� �ȱ���·� ��ȯ
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsPress("Jump"))
	{
		if (0 < JumpTimeCounter)
		{
			MoveDir += float4::Up * JumpPressForce * _DeltaTime;
			JumpTimeCounter -= _DeltaTime;
		}
	}
	// ���Է� (����Ű�� �Է����� �ʴ°�� or ���� ����Ű�� ���ÿ� �Է��� ���)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// �������� ���������� �̵��ϰ� �ִ� ���
		if (0.1f < HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
		}
		// �������� �������� �̵��ϰ� �ִ� ���
		else if (-0.1f > HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
		}
		// �����ӵ� ���� (������)
		else
		{
			HorizontalForce = 0;
		}
	}
	// ���� ����Ű�� �������
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� ������ ������ �����ִ� ���
		if (Dir::Right == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Left;
			ChangeAnimation("RunJump");
		}
		// ��� Ű�� ������ �ִ� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ���ó��
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// ��� Ű�� ������ �ʴ� ��� (�ȱ�)
		else
		{
			// �ȱ�ó��

			// �������� ��÷� �̵��߿���
			if (-0.5f > HorizontalForce)
			{
				// ������ ������
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȴ� �ӵ� ����
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
		}
	}
	// ������ ����Ű�� ���� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// �������� ���� ������ �� ���
		if (Dir::Left == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Right;
			ChangeAnimation("RunJump");
		}

		// ���Ű�� ���� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ��� ó��
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// ��� Ű�� ������ ���� ��� (�Ϲ� �ȱ� ó��)
		else
		{
			// �������� ��ø� �� ���
			if (0.5f < HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȱ� ó��
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsPress("Jump"))
	{
	}
	// ���Է� (����Ű�� �Է����� �ʴ°�� or ���� ����Ű�� ���ÿ� �Է��� ���)
	if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
	{
		// �������� ���������� �̵��ϰ� �ִ� ���
		if (0.1f < HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
		}
		// �������� �������� �̵��ϰ� �ִ� ���
		else if (-0.1f > HorizontalForce)
		{
			// ������ �ӵ��� ����
			HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
		}
		// �����ӵ� ���� (������)
		else
		{
			HorizontalForce = 0;
		}
	}
	// ���� ����Ű�� �������
	else if (GameEngineInput::IsPress("Left"))
	{
		// �������� ������ ������ �����ִ� ���
		if (Dir::Right == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Left;
			ChangeAnimation("Fall");
		}
		// ��� Ű�� ������ �ִ� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ���ó��
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -1);
		}
		// ��� Ű�� ������ �ʴ� ��� (�ȱ�)
		else
		{
			// �ȱ�ó��

			// �������� ��÷� �̵��߿���
			if (-0.5f > HorizontalForce)
			{
				// ������ ������
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȴ� �ӵ� ����
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -0.5f);
			}
		}
	}
	// ������ ����Ű�� ���� ���
	else if (GameEngineInput::IsPress("Right"))
	{
		// �������� ���� ������ �� ���
		if (Dir::Left == DirValue)
		{
			// ������ȯ
			DirValue = Dir::Right;
			ChangeAnimation("Fall");
		}

		// ���Ű�� ���� ���
		if (GameEngineInput::IsPress("Dash"))
		{
			// ��� ó��
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 1);
		}
		// ��� Ű�� ������ ���� ��� (�Ϲ� �ȱ� ó��)
		else
		{
			// �������� ��ø� �� ���
			if (0.5f < HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0.5f);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȱ� ó��
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::JUMP);
		return;
	}
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Spin"))
	{
		// ���� ���·� ��ȯ
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
			// �������� ���������� �̵��ϰ� �ִ� ���
			if (0.1f < HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 0);
			}
			// �������� �������� �̵��ϰ� �ִ� ���
			else if (-0.1f > HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), 0);
			}
			// �����ӵ� ���� (������)
			else
			{
				// IDLE ���·� ��ȯ
				ChangeState(MarioState::CROUCH);
			}
		}
		else
		{
			ChangeState(MarioState::CROUCH);
		}
		return;
	}

	// �������� �̲������� ���
	if (Dir::Left == SlopeDir)
	{
		// ���������� �̵����� ���
		if (0 < HorizontalForce)
		{
			HorizontalForce = HorizontalForce - StoppingForce * _DeltaTime;
		}
		// �������� �̵����� ���
		else
		{
			HorizontalForce = std::max<float>(HorizontalForce - DashAcceleration * _DeltaTime, -1.2f);
		}
	}
	// ���������� �̲������� ���
	else
	{
		// �������� �̵����� ���
		if (0 > HorizontalForce)
		{
			HorizontalForce = HorizontalForce + StoppingForce * _DeltaTime;
		}
		// ���������� �̵����� ���
		else
		{
			HorizontalForce = std::min<float>(HorizontalForce + DashAcceleration * _DeltaTime, 1.2f);
		}
	}
}

void Mario::SlideEnd()
{
}



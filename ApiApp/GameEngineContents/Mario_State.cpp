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
	// �Ʒ� ����⸦ �Է��� ���
	else if (GameEngineInput::IsPress("Down"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::CROUCH);
		return;
	}
	// ���Է� (����Ű�� �Է����� �ʴ°�� or ���� ����Ű�� ���ÿ� �Է��� ���)
	else if ((GameEngineInput::IsPress("Left") && GameEngineInput::IsPress("Right")) || (!GameEngineInput::IsPress("Left") && !GameEngineInput::IsPress("Right")))
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
			HorizontalForce = std::max<float>(HorizontalForce - (DashAcceleration * _DeltaTime), -2);
			RunChargeTime += _DeltaTime;	// ��ø� �� �ð� ���
		}
		// ��� Ű�� ������ �ʴ� ��� (�ȱ�)
		else
		{
			// �ȱ�ó��

			// �������� ��÷� �̵��߿���
			if (-1 > HorizontalForce)
			{
				// ������ ������
				HorizontalForce = std::min<float>(HorizontalForce + (StoppingForce * _DeltaTime), -1);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȴ� �ӵ� ����
				HorizontalForce = std::max<float>(HorizontalForce - (Acceleration * _DeltaTime), -1);
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
			HorizontalForce = std::min<float>(HorizontalForce + (DashAcceleration * _DeltaTime), 2);
			RunChargeTime += _DeltaTime;	// ��ø� �� �ð� ���
		}
		// ��� Ű�� ������ ���� ��� (�Ϲ� �ȱ� ó��)
		else
		{
			// �������� ��ø� �� ���
			if (1 < HorizontalForce)
			{
				// ������ �ӵ��� ����
				HorizontalForce = std::max<float>(HorizontalForce - (StoppingForce * _DeltaTime), 1);
			}
			// �׿� ��� (�Ϲ����� �ȱ�)
			else
			{
				// �ȱ� ó��
				HorizontalForce = std::min<float>(HorizontalForce + (Acceleration * _DeltaTime), 1);
			}
			RunChargeTime = 0;
		}
	}
	// �ӵ��� 1�̻��� ���
	if (1.5f < std::abs(HorizontalForce))
	{
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
	// ��ø� �Է��� �ð��� 1�ʸ� �ѱ� ���
	
	
	// �̵�ó�� �� ī�޶� �̵�ó��
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
	// ���� Ű�� �Է��� ���
	if (GameEngineInput::IsDown("Jump"))
	{
		// ���� ���·� ��ȯ
		ChangeState(MarioState::JUMP);
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
	
	// ���� ��� ���ǿ� �ش���� ������ �޸��� ó�� (������ �� ī�޶�ó��)
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

	// �������� ���� ����ŭ �̵�
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
		return;
	}
	
	

	// �������� ���� ����ŭ �̵�
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



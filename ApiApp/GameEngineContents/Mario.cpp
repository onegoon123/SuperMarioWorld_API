#include "Mario.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MarioGameCore.h"
#include "Map.h"

Mario* Mario::MainPlayer = nullptr;

Mario::Mario() {
	if (MainPlayer != nullptr)
	{
		MsgAssert("�ι�° �������� �����Ǿ����ϴ�");
	}
	MainPlayer = this;
}

Mario::~Mario() {

}

void Mario::Start()
{
	// �������� ��� �����͸� �ҷ��´�
	MarioGameCore& GameCore = MarioGameCore::GetInst();
	MarioPower = GameCore.GetMarioStateData();
	StockState = GameCore.GetStockStateData();
	IsRidedYoshi = GameCore.GetRidedYoshiData();

	// ���� ����
	{
		AnimationRender = CreateRender(RenderOrder::Player);
		AnimationRender->SetScale({ 192, 192 });
		AnimationRender->SetPosition({ 0, -56 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 1, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 2, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Run", .ImageName = "RIGHT_MARIO.BMP", .Start = 6, .End = 8, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Brake", .ImageName = "RIGHT_MARIO.BMP", .Start = 9, .End = 9,});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 10, .End = 10,});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 11, .End = 11,});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fall", .ImageName = "RIGHT_MARIO.BMP", .Start = 12, .End = 12,});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_RunJump", .ImageName = "RIGHT_MARIO.BMP", .Start = 13, .End = 13,});
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Spin", .ImageName = "RIGHT_MARIO.BMP", .Start = 14, .End = 16, .InterTime = 0.035f});

		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 0 + 53, .End = 0 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 1 + 53, .End = 1 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 2 + 53, .End = 2 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Run", .ImageName = "RIGHT_MARIO.BMP", .Start = 6 + 53, .End = 8 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Brake", .ImageName = "RIGHT_MARIO.BMP", .Start = 9 + 53, .End = 9 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 10 + 53, .End = 10 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 11 + 53, .End = 11 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Fall", .ImageName = "RIGHT_MARIO.BMP", .Start = 12 + 53, .End = 12 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_RunJump", .ImageName = "RIGHT_MARIO.BMP", .Start = 13 + 53, .End = 13 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Spin", .ImageName = "RIGHT_MARIO.BMP", .Start = 14 + 53, .End = 16 + 53, .InterTime = 0.035f });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName =	"Left_MARIO.BMP", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_LookUp", .ImageName =	"Left_MARIO.BMP", .Start = 1, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Crouch", .ImageName =	"Left_MARIO.BMP", .Start = 2, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Walk", .ImageName =	"Left_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.06f, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Dash", .ImageName =	"Left_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.03f, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Run", .ImageName =	"Left_MARIO.BMP", .Start = 6, .End = 8, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Brake", .ImageName =	"Left_MARIO.BMP", .Start = 9, .End = 9, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Pipe", .ImageName =	"Left_MARIO.BMP", .Start = 10, .End = 10, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Jump", .ImageName =	"Left_MARIO.BMP", .Start = 11, .End = 11, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fall", .ImageName =	"Left_MARIO.BMP", .Start = 12, .End = 12, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_RunJump", .ImageName ="Left_MARIO.BMP", .Start = 13, .End = 13, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Spin", .ImageName =	"Left_MARIO.BMP", .Start = 14, .End = 16, .InterTime = 0.035f });

		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Idle",		.ImageName = "Left_MARIO.BMP", .Start = 0 + 53, .End = 0 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_LookUp",	.ImageName = "Left_MARIO.BMP", .Start = 1 + 53, .End = 1 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Crouch",	.ImageName = "Left_MARIO.BMP", .Start = 2 + 53, .End = 2 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Walk",		.ImageName = "Left_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Dash",		.ImageName = "Left_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Run",		.ImageName = "Left_MARIO.BMP", .Start = 6 + 53, .End = 8 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Brake",		.ImageName = "Left_MARIO.BMP", .Start = 9 + 53, .End = 9 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Pipe",		.ImageName = "Left_MARIO.BMP", .Start = 10 + 53, .End = 10 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Jump",		.ImageName = "Left_MARIO.BMP", .Start = 11 + 53, .End = 11 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Fall",		.ImageName = "Left_MARIO.BMP", .Start = 12 + 53, .End = 12 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_RunJump",	.ImageName = "Left_MARIO.BMP", .Start = 13 + 53, .End = 13 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Spin",		.ImageName = "Left_MARIO.BMP", .Start = 14 + 53, .End = 16 + 53, .InterTime = 0.035f });
	}
	ChangeAnimation("Idle");
}

void Mario::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

void Mario::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	MoveCalculation(_DeltaTime);
	GetLevel()->DebugTextPush(GetPos().ToString());

	// ġƮ
	if (GameEngineInput::IsDown("3"))
	{
		Speed *= 2;
		RunSpeed *= 2;
		ColMap = GameEngineResources::GetInst().ImageFind("STAGE0COL.bmp");
	}
}

void Mario::ChangeAnimation(const std::string_view& _AnimationName)
{
	std::string AnimStr = DirValue == Dir::Left ? "Left_" : "Right_";

	switch (DirValue)
	{
	case Dir::Left:
		AnimStr = "Left_";
		break;
	case Dir::Right:
		AnimStr = "Right_";
		break;
	default:
		break;
	}

	switch (MarioPower)
	{
	case PowerState::Normal:
		break;
	case PowerState::Super:
	case PowerState::Cape:
		AnimStr += "Super_";
		break;
	case PowerState::Fire:
		AnimStr += "Fire_";
		break;
	default:
		break;
	}

	AnimationRender->ChangeAnimation(AnimStr + _AnimationName.data());
}

void Mario::MoveCalculation(float _DeltaTime)
{
	// ���� ��ġ
	float4 DownPos = GetPos() + float4::Down * 4; 
	// ���� ��ġ
	float4 ForwardPos = GetPos();
	ForwardPos.x += HorizontalForce * 4;
	// MoveDir �߷� ����
	MoveDir += float4::Down * GravityAcceleration * _DeltaTime;

	// ���� �߷��� �ִ� �߷��� �ʰ��� ���
	if (GravityMax < MoveDir.y)
	{
		// �ִ� �߷� ����
		MoveDir.y = GravityMax;
	}
	// ���߿� �����鼭 �߷¿� ���� �������� �ִ� ���
	else if (false == IsGrounded && 0 < MoveDir.y)
	{
		if (MarioState::SPIN != StateValue && MarioState::RUNJUMP != StateValue)
		{
			ChangeState(MarioState::FALL);
		}
	}

	// MoveDir �¿� �̵� ����
	if (MarioState::RUN == StateValue || MarioState::RUNJUMP == StateValue)
	{
		MoveDir.x = HorizontalForce * RunSpeed;
	}
	else
	{
		MoveDir.x = HorizontalForce * Speed;
	}

	// �̹� �����ӿ� �̵��� ��ġ
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;
	// �� ��Ż ����
	if (0 >= NextPos.ix())
	{
		MoveDir.x = 0;
	}
	else if (Map::MainMap->GetStageSize().ix() <= NextPos.ix())
	{
		MoveDir.x = 0;
	}
	if (0 >= NextPos.iy())
	{
		MoveDir.y = 0;
	}
	else if (Map::MainMap->GetStageSize().iy() <= NextPos.iy())
	{
		Death();
		MoveDir.y = 0;
	}
	
	// ______�� �浹 üũ______

	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	
	

	// �� �浹 üũ�� �÷� ����
	DWORD PixelColor = ColMap->GetPixelColor(DownPos, RGB(255, 255, 255));
	// �ٴ� üũ
	if (RGB(0, 0, 0) == PixelColor)
	{
		IsSlope = false;
		if (MarioState::FALL == StateValue || (MarioState::SPIN == StateValue && 0 < MoveDir.y) || (MarioState::RUNJUMP == StateValue && 0 < MoveDir.y))
		{
			IsGrounded = true;
			DownPos.y = std::round(DownPos.y);
			// �ٴڿ��� ���� ���� �ö󰣴�
			while (true)
			{
				DownPos.y -= 1;
				PixelColor = ColMap->GetPixelColor(DownPos, RGB(0, 0, 0));
				if (RGB(0, 0, 0) != PixelColor)
				{
					SetPos(DownPos);
					ForwardPos.y = DownPos.y;
					MoveDir.y = 0.0f;
					break;
				}
			}
			
		}
		else if (MarioState::JUMP != StateValue && MarioState::SPIN != StateValue && MarioState::RUNJUMP != StateValue)
		{
			MoveDir.y = 0.0f;
		}

	}
	// �������� �ƴѰ��
	else if (MarioState::JUMP != StateValue && (MarioState::SPIN != StateValue || 0 < MoveDir.y) && (MarioState::RUNJUMP != StateValue || 0 < MoveDir.y))
	{
		// �Ʒ����� ����Ǵ� ��ϵ� üũ ex) ����
		if (RGB(0, 255, 0) == PixelColor)
		{
			IsSlope = false;
			if (MarioState::FALL == StateValue || (MarioState::SPIN == StateValue && 0 < MoveDir.y) || (MarioState::RUNJUMP == StateValue && 0 < MoveDir.y))
			{
				IsGrounded = true;
				DownPos.y = std::round(DownPos.y);
				// �ٴڿ��� ���� ���� �ö󰣴�
				while (true)
				{
					DownPos.y -= 1;
					PixelColor = ColMap->GetPixelColor(DownPos, RGB(0, 0, 0));
					if (RGB(255, 255, 255) == PixelColor)
					{
						SetPos(DownPos);
						ForwardPos.y = DownPos.y;
						MoveDir.y = 0.0f;
						break;
					}
				}

			}
			else if (MarioState::RUNJUMP != StateValue && MarioState::JUMP != StateValue && MarioState::SPIN != StateValue)
			{
				MoveDir.y = 0.0f;
			}
		}
		// ��Ż�� üũ
		else if (RGB(255, 0, 0) == PixelColor)
		{
			IsSlope = true;
			IsGrounded = true;
			DownPos.y = std::round(DownPos.y);
			// �ٴڿ��� ���� ���� �ö󰣴�
			while (true)
			{
				DownPos.y -= 1;
				PixelColor = ColMap->GetPixelColor(DownPos, RGB(0, 0, 0));
				if (RGB(255, 255, 255) == PixelColor)
				{
					SetPos(DownPos);
					ForwardPos.y = DownPos.y;
					MoveDir.y = 0.0f;
					break;
				}
			}
			DownPos.x += 1;
			PixelColor = ColMap->GetPixelColor(DownPos, RGB(0, 0, 0));
			// ���ΰ� ����
			if (RGB(255, 0, 0) == PixelColor)
			{
				MoveDir.x -= SlopeForce * _DeltaTime;
			}
			// ���ΰ� ������
			else
			{
				MoveDir.x += SlopeForce * _DeltaTime;
			}
		}
		// �������� �ٴڿ� �־����� ���� ���߿� �ִ°��
		else if (true == IsGrounded)
		{
			IsSlope = false;
			ChangeState(MarioState::FALL);
			IsGrounded = false;
		}
	}
	
	// �� üũ
	if (RGB(0, 0, 0) == ColMap->GetPixelColor(ForwardPos, RGB(255, 255, 255)))
	{
		HorizontalForce = 0;
		MoveDir.x = 0;
		if (true == IsGrounded)
		{
			ChangeState(MarioState::IDLE);
		}
	}

	// ������ �̵� �� ī�޶� �̵�
	SetMove(MoveDir * _DeltaTime);
	//GetLevel()->SetCameraMove(MoveDir * _DeltaTime);
	GetLevel()->SetCameraMove(float4::Right * MoveDir.x * _DeltaTime);
}

void Mario::MoveCalculation2(float _DeltaTime)
{
	MoveDir += float4::Down * GravityAcceleration * _DeltaTime;

	if (GravityMax < MoveDir.y)
	{
		MoveDir.y = GravityMax;
	}

	if (MarioState::RUN == StateValue)
	{
		MoveDir.x = HorizontalForce * RunSpeed;
	}
	else
	{
		MoveDir.x = HorizontalForce * Speed;
	}

	float4 NextPos = GetPos() + MoveDir * _DeltaTime;
	if (0 >= NextPos.ix())
	{
		NextPos.x = 0;
	}

	bool Check = true;

	GameEngineImage* ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	if (RGB(0, 0, 0) == ColMap->GetPixelColor(NextPos, RGB(255, 255, 255)))
	{
		Check = false;
	}

	if (false == Check)
	{
		int i = 0;
		while (true)
		{
			MoveDir.y -= 1;
			i++;
			float4 NextPos = GetPos() + MoveDir * _DeltaTime;

			if (RGB(0, 0, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
			{
				if (1000 < i)
				{
					return;
				}
				continue;
			}
			IsGrounded = true;
			break;
		}
	}
	SetMove(MoveDir * _DeltaTime);
	GetLevel()->SetCameraMove(MoveDir * _DeltaTime);
}

void Mario::Render(float _DeltaTime)
{ 
}


/*
// �߷�, ����, ��Ÿ��
void Player::MoveCalculation(float _DeltaTime)
{
	///////////////////////////////////////////////////  �߷�  ///////////////////////////////////////////////////

	if (true == IsGravity)
	{
		MoveDir += float4::Down * 3000.0f * _DeltaTime;
	}

	///////////////////////////////////////////////////  ����  ///////////////////////////////////////////////////

	if (GameEngineInput::IsDown("Jump") && false == IsJump)
	{
		MoveDir.y += -1300.0f;
	}

	if (false == IsJump)
	{
		Fall = true;
	}

	/////////////////////////////////////////////////// ��Ÿ�� ///////////////////////////////////////////////////

	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	//////// RGB(0, 248, 0) ////////
	// �¿�
	ForwardPosR = GetPos() + (float4::Up * 5) + (float4::Right * 30);
	ForwardPosL = GetPos() + (float4::Up * 5) + (float4::Left * 30);
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosR, RGB(0, 0, 0)))
	{
		MoveSpeed = 0.0f;

		if (GameEngineInput::IsPress("LeftMove"))
		{
			MoveSpeed = 600.0f;
		}
	}
	else if (RGB(0, 248, 0) == ColMap->GetPixelColor(ForwardPosL, RGB(0, 0, 0)))
	{
		MoveSpeed = 0.0f;

		if (GameEngineInput::IsPress("RightMove"))
		{
			MoveSpeed = 600.0f;
		}
	}
	else
	{
		MoveSpeed = 600.0f;
	}

	// ��
	UpPos = GetPos() + (float4::Up * 100);
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(UpPos, RGB(0, 0, 0)))
	{
		Fall = true;
		MoveDir.y = 100.0f;
	}

	// ��
	NextPos = GetPos() + MoveDir * _DeltaTime;
	if (RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		Fall = false;
		MoveDir.y = 0.0f;
	}

	if (RGB(74, 65, 42) != ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(0, 248, 0) != ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		FallTime += _DeltaTime;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0))
		|| RGB(0, 248, 0) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		FallTime = 0.0f;
	}

	//////// RGB(74, 65, 42) ////////
	// ������, ��� ����
	if (true == IsJump && 1.0f <= MoveDir.y)
	{
		Pass = 1;
	}

	if (RGB(74, 65, 42) == ColMap->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		if (1 == Pass) // ����
		{
			Fall = false;

			MoveDir.y = 0;

			float4 HillPosR = GetPos() + (float4::Right * 1);
			float4 HillPosL = GetPos() + (float4::Left * 1);

			if (RGB(74, 65, 42) == ColMap->GetPixelColor(HillPosR, RGB(0, 0, 0)))
			{
				while (true)
				{
					MoveDir.y -= 1.0f;
					SetMove(MoveDir);

					if (RGB(74, 65, 42) != ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
					{
						break;
					}
				}
			}
			if (RGB(74, 65, 42) == ColMap->GetPixelColor(HillPosL, RGB(0, 0, 0)))
			{
				while (true)
				{
					MoveDir.y -= 1.0f;
					SetMove(MoveDir);

					if (RGB(74, 65, 42) != ColMap->GetPixelColor(GetPos(), RGB(0, 0, 0)))
					{
						break;
					}
				}
			}
		}
	}

	if (true == IsJump || true == Fall)
	{
		AirAttack = true;
	}
	else
	{
		AirAttack = false;
	}


	//////// ���� ��ġ ////////
	UpdateState(_DeltaTime);

	SetMove(MoveDir * _DeltaTime);

	// y�� ī�޶�
	// GetLevel()->SetCameraMove(MoveDir* _DeltaTime);

	
}
*/
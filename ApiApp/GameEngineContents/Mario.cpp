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
		MsgAssert("두번째 마리오가 생성되었습니다");
	}
	MainPlayer = this;
}

Mario::~Mario() {

}

void Mario::Start()
{
	// 마리오의 기록 데이터를 불러온다
	MarioGameCore& GameCore = MarioGameCore::GetInst();
	MarioPower = GameCore.GetMarioStateData();
	StockState = GameCore.GetStockStateData();
	IsRidedYoshi = GameCore.GetRidedYoshiData();

	// 렌더 생성
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

void Mario::Update(float _DeltaTime)
{
	UpdateState(_DeltaTime);
	MoveCalculation(_DeltaTime);
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

	bool Check = true;

	GameEngineImage* ColImage = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
	if (nullptr == ColImage)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
	{
		Check = false;
	}

	if (false == Check)
	{
		while (true)
		{
			MoveDir.y -= 1;

			float4 NextPos = GetPos() + MoveDir * _DeltaTime;

			if (RGB(0, 0, 0) == ColImage->GetPixelColor(NextPos, RGB(0, 0, 0)))
			{
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

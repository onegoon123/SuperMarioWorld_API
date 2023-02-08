#include "Mario.h"
#include <GameEngineBase/GameEnginePath.h>
#include <GameEnginePlatform/GameEngineWindow.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineLevel.h>
#include "MarioGameCore.h"
#include "Map.h"
#include "Fire.h"

Mario* Mario::MainPlayer = nullptr;

void Mario::NewItem(ItemType _Item)
{
	if (MarioState::CHANGEPOWER == StateValue)
	{
		return;
	}
	switch (_Item)
	{
	case ItemType::Coin:
		break;
	case ItemType::UpMushroom:
		break;
	case ItemType::SuperMushroom:
	{
		if (PowerState::Super == MarioPower)
		{

		}
		else
		{
			MarioPower = PowerState::Super;
			ChangeState(MarioState::CHANGEPOWER);
		}
		break;
	}
	case ItemType::FireFlower:
		if (PowerState::Fire == MarioPower)
		{

		}
		else
		{
			MarioPower = PowerState::Fire;
			ChangeState(MarioState::CHANGEPOWER);
		}
		break;
		break;
	case ItemType::Feather:
		break;
	default:
		break;
	}
}

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

		AnimationRender->CreateAnimation({ .AnimationName = "Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 23, .End = 23, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 39, .End = 39, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Super_Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 39 + 53, .End = 39 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "GameOver1", .ImageName = "LEFT_MARIO.BMP", .Start = 48, .End = 48,});
		AnimationRender->CreateAnimation({ .AnimationName = "GameOver2", .ImageName = "LEFT_MARIO.BMP", .Start = 48, .End = 49, .InterTime = 0.1f});

		// 오른쪽 기본
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
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Slide", .ImageName = "RIGHT_MARIO.BMP", .Start = 18, .End = 18, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Kick", .ImageName = "RIGHT_MARIO.BMP", .Start = 19, .End = 19, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Grow", .ImageName = "RIGHT_MARIO.BMP", .InterTime = 0.07f, .Loop = false, .FrameIndex = {50, 51, 50, 51, 50, 51, 52, 51, 52, 51, 52}, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Shrink", .ImageName = "RIGHT_MARIO.BMP", .InterTime = 0.07f, .Loop = false, .FrameIndex = {52, 51, 52, 51, 52, 51, 50, 51, 50, 51, 50}, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_GetFire", .ImageName = "RIGHT_MARIO.BMP", .InterTime = 0.1f, .FrameIndex = {103, 53}, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 19, .End = 19, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 20, .End = 20, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 21, .End = 21, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 22, .End = 24, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 22, .End = 24, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 22, .End = 22 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 33, .End = 33, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Attack", .ImageName = "RIGHT_MARIO.BMP", .Start = 34, .End = 35, .InterTime = 0.3f});
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Turn", .ImageName = "RIGHT_MARIO.BMP", .Start = 36, .End = 36, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 35, .End = 35, });
		// 오른쪽 슈퍼
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
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Slide", .ImageName = "RIGHT_MARIO.BMP", .Start = 18 + 53, .End = 18 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Kick", .ImageName = "RIGHT_MARIO.BMP", .Start = 19 + 53, .End = 19 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_PowerUp", .ImageName = "RIGHT_MARIO.BMP", .FrameIndex = {53, 104} });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 19 + 53, .End = 19 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 20 + 53, .End = 20 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 21 + 53, .End = 21 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 22 + 53, .End = 24 + 53, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 22 + 53, .End = 24 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 22 + 53, .End = 22 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 33 + 53, .End = 33 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Attack", .ImageName = "RIGHT_MARIO.BMP", .Start = 34 + 53, .End = 35 + 53, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Turn", .ImageName = "RIGHT_MARIO.BMP", .Start = 36 + 53, .End = 36 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 35 + 53, .End = 35 + 53, });
		// 오른쪽 불꽃
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 0 + 103, .End = 0 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 1 + 103, .End = 1 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 2 + 103, .End = 2 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Run", .ImageName = "RIGHT_MARIO.BMP", .Start = 6 + 103, .End = 8 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Brake", .ImageName = "RIGHT_MARIO.BMP", .Start = 9 + 103, .End = 9 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 10 + 103, .End = 10 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 11 + 103, .End = 11 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Fall", .ImageName = "RIGHT_MARIO.BMP", .Start = 12 + 103, .End = 12 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_RunJump", .ImageName = "RIGHT_MARIO.BMP", .Start = 13 + 103, .End = 13 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Spin", .ImageName = "RIGHT_MARIO.BMP", .Start = 14 + 103, .End = 16 + 103, .InterTime = 0.035f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Slide", .ImageName = "RIGHT_MARIO.BMP", .Start = 18 + 103, .End = 18 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Kick", .ImageName = "RIGHT_MARIO.BMP", .Start = 19 + 103, .End = 19 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_PowerUp", .ImageName = "RIGHT_MARIO.BMP", .FrameIndex = {104, 104} });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Attack", .ImageName = "RIGHT_MARIO.BMP", .Start = 152, .End = 152 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_JumpAttack", .ImageName = "RIGHT_MARIO.BMP", .Start = 32 + 103, .End = 32 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 19 + 103, .End = 19 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 20 + 103, .End = 20 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 21 + 103, .End = 21 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 22 + 103, .End = 24 + 103, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 22 + 103, .End = 24 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 22 + 103, .End = 22 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 33 + 103, .End = 33 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Attack", .ImageName = "RIGHT_MARIO.BMP", .Start = 34 + 103, .End = 35 + 103, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Turn", .ImageName = "RIGHT_MARIO.BMP", .Start = 36 + 103, .End = 36 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 35 + 103, .End = 35 + 103, });
		// 왼쪽 기본
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_LookUp", .ImageName = "LEFT_MARIO.BMP", .Start = 1, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Crouch", .ImageName = "LEFT_MARIO.BMP", .Start = 2, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Dash", .ImageName =	"LEFT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Run", .ImageName =	"LEFT_MARIO.BMP", .Start = 6, .End = 8, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Brake", .ImageName =	"LEFT_MARIO.BMP", .Start = 9, .End = 9, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Pipe", .ImageName =	"LEFT_MARIO.BMP", .Start = 10, .End = 10, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Jump", .ImageName =	"LEFT_MARIO.BMP", .Start = 11, .End = 11, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fall", .ImageName =	"LEFT_MARIO.BMP", .Start = 12, .End = 12, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_RunJump", .ImageName ="LEFT_MARIO.BMP", .Start = 13, .End = 13, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Spin", .ImageName =	"LEFT_MARIO.BMP", .Start = 14, .End = 16, .InterTime = 0.035f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Slide", .ImageName =	"LEFT_MARIO.BMP", .Start = 18, .End = 18, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Kick", .ImageName =	"LEFT_MARIO.BMP", .Start = 19, .End = 19, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Grow", .ImageName = "Left_MARIO.BMP", .InterTime = 0.07f, .Loop = false, .FrameIndex = {50, 51, 50, 51, 50, 51, 52, 51, 52, 51, 52}, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Shrink", .ImageName = "Left_MARIO.BMP", .InterTime = 0.07f, .Loop = false, .FrameIndex = {52, 51, 52, 51, 52, 51, 50, 51, 50, 51, 50}, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_GetFire", .ImageName = "Left_MARIO.BMP", .InterTime = 0.1f, .FrameIndex = {103, 53}, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 19, .End = 19, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_LookUp", .ImageName ="LEFT_MARIO.BMP", .Start = 20, .End = 20, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Crouch", .ImageName ="LEFT_MARIO.BMP", .Start = 21, .End = 21, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 22, .End = 24, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Dash", .ImageName =	"LEFT_MARIO.BMP", .Start = 22, .End = 24, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Jump", .ImageName =	"LEFT_MARIO.BMP", .Start = 22, .End = 22 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Idle", .ImageName ="LEFT_MARIO.BMP", .Start = 33, .End = 33, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Attack", .ImageName="LEFT_MARIO.BMP", .Start = 34, .End = 35, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Turn", .ImageName = "LEFT_MARIO.BMP", .Start = 36, .End = 36, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Pipe", .ImageName = "LEFT_MARIO.BMP", .Start = 35, .End = 35, });
		// 오른쪽 슈퍼
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 0 + 53, .End = 0 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_LookUp", .ImageName =	"LEFT_MARIO.BMP", .Start = 1 + 53, .End = 1 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Crouch", .ImageName =	"LEFT_MARIO.BMP", .Start = 2 + 53, .End = 2 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Dash", .ImageName =	"LEFT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Run", .ImageName =		"LEFT_MARIO.BMP", .Start = 6 + 53, .End = 8 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Brake", .ImageName =	"LEFT_MARIO.BMP", .Start = 9 + 53, .End = 9 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Pipe", .ImageName =	"LEFT_MARIO.BMP", .Start = 10 + 53, .End = 10 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Jump", .ImageName =	"LEFT_MARIO.BMP", .Start = 11 + 53, .End = 11 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Fall", .ImageName =	"LEFT_MARIO.BMP", .Start = 12 + 53, .End = 12 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_RunJump", .ImageName = "LEFT_MARIO.BMP", .Start = 13 + 53, .End = 13 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Spin", .ImageName =	"LEFT_MARIO.BMP", .Start = 14 + 53, .End = 16 + 53, .InterTime = 0.035f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Slide", .ImageName =	"LEFT_MARIO.BMP", .Start = 18 + 53, .End = 18 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Kick", .ImageName =	"LEFT_MARIO.BMP", .Start = 19 + 53, .End = 19 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_PowerUp", .ImageName = "LEFT_MARIO.BMP", .FrameIndex = {53, 104} });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 19 + 53, .End = 19 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_LookUp", .ImageName =	"LEFT_MARIO.BMP", .Start = 20 + 53, .End = 20 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Crouch", .ImageName =	"LEFT_MARIO.BMP", .Start = 21 + 53, .End = 21 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 22 + 53, .End = 24 + 53, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Dash", .ImageName =	"LEFT_MARIO.BMP", .Start = 22 + 53, .End = 24 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Jump", .ImageName =	"LEFT_MARIO.BMP", .Start = 22 + 53, .End = 22 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 33 + 53, .End = 33 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Attack", .ImageName = "LEFT_MARIO.BMP", .Start = 34 + 53, .End = 35 + 53, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Turn", .ImageName =	"LEFT_MARIO.BMP", .Start = 36 + 53, .End = 36 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Pipe", .ImageName =	"LEFT_MARIO.BMP", .Start = 35 + 53, .End = 35 + 53, });
		// 오른쪽 불꽃
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Idle", .ImageName =		"LEFT_MARIO.BMP", .Start = 0 + 103, .End = 0 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_LookUp", .ImageName =	"LEFT_MARIO.BMP", .Start = 1 + 103, .End = 1 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Crouch", .ImageName =	"LEFT_MARIO.BMP", .Start = 2 + 103, .End = 2 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Walk", .ImageName =		"LEFT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Dash", .ImageName =		"LEFT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Run", .ImageName =		"LEFT_MARIO.BMP", .Start = 6 + 103, .End = 8 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Brake", .ImageName =		"LEFT_MARIO.BMP", .Start = 9 + 103, .End = 9 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Pipe", .ImageName =		"LEFT_MARIO.BMP", .Start = 10 + 103, .End = 10 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Jump", .ImageName =		"LEFT_MARIO.BMP", .Start = 11 + 103, .End = 11 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Fall", .ImageName =		"LEFT_MARIO.BMP", .Start = 12 + 103, .End = 12 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_RunJump", .ImageName =	"LEFT_MARIO.BMP", .Start = 13 + 103, .End = 13 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Spin", .ImageName =		"LEFT_MARIO.BMP", .Start = 14 + 103, .End = 16 + 103, .InterTime = 0.035f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Slide", .ImageName =		"LEFT_MARIO.BMP", .Start = 18 + 103, .End = 18 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Kick", .ImageName =		"LEFT_MARIO.BMP", .Start = 19 + 103, .End = 19 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_PowerUp", .ImageName =	"LEFT_MARIO.BMP", .FrameIndex = {104, 104} });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Attack", .ImageName = "LEFT_MARIO.BMP", .Start = 152, .End = 152 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_JumpAttack", .ImageName = "LEFT_MARIO.BMP", .Start = 32 + 103, .End = 32 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Idle", .ImageName = "LEFT_MARIO.BMP", .Start = 19 + 103, .End = 19 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_LookUp", .ImageName =	"LEFT_MARIO.BMP", .Start = 20 + 103, .End = 20 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Crouch", .ImageName =	"LEFT_MARIO.BMP", .Start = 21 + 103, .End = 21 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Walk", .ImageName =		"LEFT_MARIO.BMP", .Start = 22 + 103, .End = 24 + 103, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Dash", .ImageName =		"LEFT_MARIO.BMP", .Start = 22 + 103, .End = 24 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Jump", .ImageName =		"LEFT_MARIO.BMP", .Start = 22 + 103, .End = 22 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 33 + 103, .End = 33 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Attack", .ImageName =	"LEFT_MARIO.BMP", .Start = 34 + 103, .End = 35 + 103, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Turn", .ImageName =	"LEFT_MARIO.BMP", .Start = 36 + 103, .End = 36 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Pipe", .ImageName =	"LEFT_MARIO.BMP", .Start = 35 + 103, .End = 35 + 103, });
	}
	ChangeAnimation("Idle");
	
	// Collision 생성
	{
		BodyCollision = CreateCollision(CollisionOrder::Player);
		BodyCollision->SetScale({ 52, 72 });
		BodyCollision->SetPosition({ 0, -36 });
		BodyCollision->SetDebugRenderType(CollisionType::CT_Rect);
	}
}

void Mario::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
}

void Mario::Update(float _DeltaTime)
{
	FireAnimTimer += _DeltaTime;
	UpdateState(_DeltaTime);
	GetLevel()->DebugTextPush(GetPos().ToString());

	// 시간 멈춘 상태 체크
	if (MarioState::CHANGEPOWER == StateValue || MarioState::GameOver == StateValue)
	{
		return;
	}
	MoveCalculation(_DeltaTime);
	CheckCollision();

	FireAttack();

	// 무적시간 체크
	if (true == IsInvincibility)
	{
		Timer -= _DeltaTime;
		if (static_cast<int>((Timer * 20)) % 2 == 0)
		{
			AnimationRender->On();
		}
		else
		{
			AnimationRender->Off();
		}
		if (0 >= Timer)
		{
			AnimationRender->On();
			IsInvincibility = false;
		}
	}

	// 치트
	if (GameEngineInput::IsDown("3"))
	{
		Speed *= 2;
		RunSpeed *= 2;
		ColMap = GameEngineResources::GetInst().ImageFind("STAGE0COL.bmp");
		MarioPower = PowerState::Fire;
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
	// 밑의 위치
	float4 DownPos = GetPos() + float4::Down * 10; 
	// 앞의 위치
	float4 ForwardPos = GetPos();
	ForwardPos.x += HorizontalForce * 4;
	// MoveDir 중력 증가
	MoveDir += float4::Down * GravityAcceleration * _DeltaTime;

	// 현제 중력이 최대 중력을 초과한 경우
	if (GravityMax < MoveDir.y)
	{
		// 최대 중력 제한
		MoveDir.y = GravityMax;
	}
	// 공중에 있으면서 중력에 의해 떨어지고 있는 경우
	else if (false == IsGrounded && 0 < MoveDir.y)
	{
		if (MarioState::SPIN != StateValue && MarioState::RUNJUMP != StateValue)
		{
			ChangeState(MarioState::FALL);
		}
	}

	// MoveDir 좌우 이동 증가
	if (MarioState::RUN == StateValue || MarioState::RUNJUMP == StateValue)
	{
		MoveDir.x = HorizontalForce * RunSpeed;
	}
	else
	{
		MoveDir.x = HorizontalForce * Speed;
	}

	// 이번 프레임에 이동할 위치
	float4 NextPos = GetPos() + MoveDir * _DeltaTime;
	// 맵 이탈 방지
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
	
	// ______맵 충돌 체크______

	if (nullptr == ColMap)
	{
		MsgAssert("충돌용 맵 이미지가 없습니다.");
	}

	
	

	// 맵 충돌 체크용 컬러 변수
	DWORD PixelColor = ColMap->GetPixelColor(DownPos, RGB(255, 255, 255));
	// 이전까지 비탈길에 있던 경우
	if (true == IsSlope && true == IsGrounded)
	{
		// 내 밑에 비탈길이 있는 경우
		if (RGB(255, 0, 0) == PixelColor)
		{
			IsSlope = true;
			IsGrounded = true;
			DownPos.y = std::round(DownPos.y);
			// 바닥에서 제일 위로 올라간다
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
			// 경사로가 왼쪽
			if (RGB(255, 0, 0) == PixelColor)
			{
				SlopeDir = Dir::Left;
			}
			// 경사로가 오른쪽
			else
			{
				SlopeDir = Dir::Right;
			}
		}
		// 이젠 내 밑에 비탈길이 없는 경우
		else
		{
			// 바닥 체크
			if (RGB(0, 0, 0) == PixelColor || RGB(0, 255, 0) == PixelColor)
			{
				IsSlope = false;
				if (MarioState::FALL == StateValue || (MarioState::SPIN == StateValue && 0 < MoveDir.y) || (MarioState::RUNJUMP == StateValue && 0 < MoveDir.y))
				{
					IsGrounded = true;
					DownPos.y = std::round(DownPos.y);
					// 바닥에서 제일 위로 올라간다
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
			else
			{
				StateValue;
				IsSlope = false;
				IsGrounded = false;
			}
		}
	}
	// 바닥 체크
	else if (RGB(0, 0, 0) == PixelColor)
	{
		IsSlope = false;
		if (MarioState::FALL == StateValue || (MarioState::SPIN == StateValue && 0 < MoveDir.y) || (MarioState::RUNJUMP == StateValue && 0 < MoveDir.y))
		{
			IsGrounded = true;
			DownPos.y = std::round(DownPos.y);
			// 바닥에서 제일 위로 올라간다
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
	// 점프중이 아닌경우
	else if (MarioState::JUMP != StateValue && (MarioState::SPIN != StateValue || 0 < MoveDir.y) && (MarioState::RUNJUMP != StateValue || 0 < MoveDir.y))
	{
		// 아래에서 통과되는 블록들 체크 ex) 구름
		if (RGB(0, 255, 0) == PixelColor)
		{
			IsSlope = false;
			if (MarioState::FALL == StateValue || (MarioState::SPIN == StateValue && 0 < MoveDir.y) || (MarioState::RUNJUMP == StateValue && 0 < MoveDir.y))
			{
				IsGrounded = true;
				DownPos.y = std::round(DownPos.y);
				// 바닥에서 제일 위로 올라간다
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
		// 비탈길 체크
		else if (RGB(255, 0, 0) == PixelColor)
		{
			IsSlope = true;
			IsGrounded = true;
			DownPos.y = std::round(DownPos.y);
			// 바닥에서 제일 위로 올라간다
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
			// 경사로가 왼쪽
			if (RGB(255, 0, 0) == PixelColor)
			{
				SlopeDir = Dir::Left;
			}
			// 경사로가 오른쪽
			else
			{
				SlopeDir = Dir::Right;
			}
		}
		// 이전까지 바닥에 있었으나 현제 공중에 있는경우
		else if (true == IsGrounded)
		{
			IsSlope = false;
			ChangeState(MarioState::FALL);
			IsGrounded = false;
		}
	}
	
	// 벽 체크
	if (RGB(0, 0, 0) == ColMap->GetPixelColor(ForwardPos, RGB(255, 255, 255)))
	{
		HorizontalForce = 0;
		MoveDir.x = 0;
		if (true == IsGrounded)
		{
			ChangeState(MarioState::IDLE);
		}
	}

	// 마리오 이동 및 카메라 이동
	SetMove(MoveDir * _DeltaTime);
	//GetLevel()->SetCameraMove(MoveDir * _DeltaTime);
	GetLevel()->SetCameraMove(float4::Right * MoveDir.x * _DeltaTime);
}

void Mario::FireAttack()
{
	// 파이어 마리오 상태일때만 실행
	if (PowerState::Fire != MarioPower) { return; }
	if (MarioState::SPIN == StateValue || MarioState::CROUCH == StateValue || MarioState::SLIDE == StateValue) { return; }
	if (FireAnimTime > FireAnimTimer)
	{
		if (true == IsGrounded)
		{
			ChangeAnimation("Attack");
		}
		else
		{
			ChangeAnimation("JumpAttack");
		}
	}
	// 대시 키를 입력한 순간에만 실행
	if (false == GameEngineInput::IsDown("Dash")) { return; }
	if (true == Fire::IsMax()) { return; }

	Fire* NewFire = GetLevel()->CreateActor<Fire>(RenderOrder::Player);
	NewFire->SetPos(GetPos());
	NewFire->SetMove(float4::Up * 50);
	if (Dir::Left == DirValue)
	{
		NewFire->SetMove(float4::Left * 40);
		NewFire->SetDir(float4::Left);
	}
	else
	{
		NewFire->SetMove(float4::Right * 40);
		NewFire->SetDir(float4::Right);
	}

	FireAnimTimer = 0;
	if (true == IsGrounded)
	{
		ChangeAnimation("Attack");
	}
	else
	{
		ChangeAnimation("JumpAttack");
	}
}

void Mario::CheckCollision()
{
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == BodyCollision->Collision(Check, Collisions))
	{
		GameEngineActor* ColActor = Collisions[0]->GetActor();
		//ColActor->GetOwner<Mario>(); 전환 방식
		
		// 슬라이딩을 하고있는 경우
		if (MarioState::SLIDE == StateValue)
		{
			// 몬스터 처치
			ColActor->Death();
			return;
		}
		// 플레이어가 몬스터보다 위에 있는 경우
		if (GetPos().y < ColActor->GetPos().y)
		{
			if (0 > MoveDir.y)
			{
				return;
			}
			ColActor->Death();
			MoveDir.y = 0;
			// 스핀으로 밟으면 다시 스핀점프, 그 외에는 점프로
			ChangeState(StateValue == MarioState::SPIN ? MarioState::SPIN : MarioState::JUMP);
			return;
		}
		// 그 외 경우
		else
		{
			if (true == IsInvincibility)
			{
				return;
			}
			// 대미지
			GetDamaged();
		}
	}
}


void Mario::Render(float _DeltaTime)
{ 
	//BodyCollision->DebugRender();
}

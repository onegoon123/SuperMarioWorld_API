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
#include "Particle.h"
#include "Block.h"
#include "StageLevel.h"
#include "EnemyActor.h"
#include "LevelLoader.h"
Mario* Mario::MainPlayer = nullptr;

void Mario::NewItem(ItemType _Item)
{
	
	if (MarioState::GameOver == StateValue)
	{
		return;
	}
	
	switch (_Item)
	{
	case ItemType::Coin:
		CurrentLevel->AddCoin();
		break;
	case ItemType::UpMushroom:
		break;
	case ItemType::SuperMushroom:
		NewPower(PowerState::Super);
		break;
	case ItemType::FireFlower:
		NewPower(PowerState::Fire);
		break;
	case ItemType::Feather:
		NewPower(PowerState::Cape);
		break;
	default:
		break;
	}
}

void Mario::Die()
{
	ChangeState(MarioState::GameOver);
}

void Mario::StageClear()
{
	StateValue = MarioState::VICTORY;
	DirValue = Dir::Right;
	AnimationRender->On();
	ChangeAnimation("ClearWalk");
	Timer = 0;

	switch (MarioPower)
	{
	case PowerState::Normal:
		break;
	case PowerState::Super:
	case PowerState::Cape:
		BeforeAnim = "Super_";
		break;
	case PowerState::Fire:
		BeforeAnim = "Fire_";
		break;
	default:
		break;
	}
}

void Mario::DropHold()
{
	IsHold = false;
	HoldActor = nullptr;
}

void Mario::PipeIn(const float4& _PipePos, const float4& _Dir)
{
	IsHold = false;
	GameEngineResources::GetInst().SoundPlay("Pipe.wav");
	AnimationRender->On();
	AnimationRender->SetOrder(static_cast<int>(RenderOrder::BackGround));
	SetPos(_PipePos);
	StateValue = MarioState::Pipe;
	Timer = 100;
	MoveDir = _Dir;

	if (0 < _Dir.x || 0 > _Dir.x)
	{
		ChangeAnimation("Walk");
	}
	else
	{
		ChangeAnimation("Pipe");
	}
}

void Mario::PipeOut(const float4& _Dir)
{
	GameEngineResources::GetInst().SoundPlay("Pipe.wav");
	AnimationRender->SetOrder(static_cast<int>(RenderOrder::BackGround));
	StateValue = MarioState::Pipe;
	Timer = PipeOutTime;
	MoveDir = _Dir;

	if (0 < _Dir.x || 0 > _Dir.x)
	{
		ChangeAnimation("Walk");
	}
	else
	{
		ChangeAnimation("Pipe");
	}
}


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
	IsRidedYoshi = GameCore.GetRidedYoshiData();

	// ���� ����
	{
		AnimationRender = CreateRender(RenderOrder::Player);
		AnimationRender->SetScale(RenderScale);
		AnimationRender->SetPosition(RenderPos);

		AnimationRender->CreateAnimation({ .AnimationName = "Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 23, .End = 23, });
		AnimationRender->CreateAnimation({ .AnimationName = "Super_Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 23 + 53, .End = 23 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Fire_Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 23 + 103, .End = 23 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 39, .End = 39, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Super_Goal", .ImageName = "LEFT_MARIO.BMP", .Start = 39 + 53, .End = 39 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "GameOver1", .ImageName = "LEFT_MARIO.BMP", .Start = 48, .End = 48,});
		AnimationRender->CreateAnimation({ .AnimationName = "GameOver2", .ImageName = "LEFT_MARIO.BMP", .Start = 48, .End = 49, .InterTime = 0.1f});

		// ������ �⺻
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 1, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 2, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_ClearWalk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.2f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.08f });
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
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 24, .End = 24, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Brake", .ImageName = "RIGHT_MARIO.BMP", .Start = 24, .End = 24, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 25, .End = 25, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 26, .End = 26, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 27, .End = 29, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 27, .End = 29, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Run", .ImageName = "RIGHT_MARIO.BMP", .Start = 27, .End = 29, .InterTime = 0.02f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 28, .End = 28 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_RunJump", .ImageName = "RIGHT_MARIO.BMP", .Start = 28, .End = 28 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Hold_Fall", .ImageName = "RIGHT_MARIO.BMP", .Start = 28, .End = 28 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 33, .End = 33, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Attack", .ImageName = "RIGHT_MARIO.BMP", .Start = 34, .End = 35, .InterTime = 0.3f});
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Turn", .ImageName = "RIGHT_MARIO.BMP", .Start = 36, .End = 36, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 35, .End = 35, });
		// ������ ����
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 0 + 53, .End = 0 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 1 + 53, .End = 1 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 2 + 53, .End = 2 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.08f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_ClearWalk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.2f });
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
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 24 + 53, .End = 24 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Brake", .ImageName = "RIGHT_MARIO.BMP", .Start = 24 + 53, .End = 24 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 25 + 53, .End = 25 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 26 + 53, .End = 26 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 27 + 53, .End = 29 + 53, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 27 + 53, .End = 29 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Run", .ImageName = "RIGHT_MARIO.BMP", .Start = 27 + 53, .End = 29 + 53, .InterTime = 0.02f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 28 + 53, .End = 28 + 53 });						
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_RunJump", .ImageName = "RIGHT_MARIO.BMP", .Start = 28 + 53, .End = 28 + 53 });						
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Super_Hold_Fall", .ImageName = "RIGHT_MARIO.BMP", .Start = 28 + 53, .End = 28 + 53 });						
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 33 + 53, .End = 33 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Attack", .ImageName = "RIGHT_MARIO.BMP", .Start = 34 + 53, .End = 35 + 53, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Turn", .ImageName = "RIGHT_MARIO.BMP", .Start = 36 + 53, .End = 36 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Super_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 35 + 53, .End = 35 + 53, });
		// ������ �Ҳ�
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 0 + 103, .End = 0 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 1 + 103, .End = 1 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 2 + 103, .End = 2 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.08f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_ClearWalk", .ImageName = "RIGHT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.2f });
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
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 24 + 103, .End = 24 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Brake", .ImageName = "RIGHT_MARIO.BMP", .Start = 24 + 103, .End = 24 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_LookUp", .ImageName = "RIGHT_MARIO.BMP", .Start = 25 + 103, .End = 25 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Crouch", .ImageName = "RIGHT_MARIO.BMP", .Start = 26 + 103, .End = 26 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Walk", .ImageName = "RIGHT_MARIO.BMP", .Start = 27 + 103, .End = 29 + 103, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Dash", .ImageName = "RIGHT_MARIO.BMP", .Start = 27 + 103, .End = 29 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Run", .ImageName = "RIGHT_MARIO.BMP", .Start = 27 + 103, .End = 29 + 103, .InterTime = 0.02f });
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Jump", .ImageName = "RIGHT_MARIO.BMP", .Start = 28 + 103, .End = 28 + 103 });						
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_RunJump", .ImageName = "RIGHT_MARIO.BMP", .Start = 28 + 103, .End = 28 + 103 });						
		AnimationRender->CreateAnimation({ .AnimationName = "Right_Fire_Hold_Fall", .ImageName = "RIGHT_MARIO.BMP", .Start = 28 + 103, .End = 28 + 103 });						
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Idle", .ImageName = "RIGHT_MARIO.BMP", .Start = 33 + 103, .End = 33 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Attack", .ImageName = "RIGHT_MARIO.BMP", .Start = 34 + 103, .End = 35 + 103, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Turn", .ImageName = "RIGHT_MARIO.BMP", .Start = 36 + 103, .End = 36 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Right_Fire_Pipe", .ImageName = "RIGHT_MARIO.BMP", .Start = 35 + 103, .End = 35 + 103, });
		// ���� �⺻
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 0, .End = 0 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_LookUp", .ImageName = "LEFT_MARIO.BMP", .Start = 1, .End = 1 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Crouch", .ImageName = "LEFT_MARIO.BMP", .Start = 2, .End = 2 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.08f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_ClearWalk", .ImageName =	"LEFT_MARIO.BMP", .Start = 3, .End = 5, .InterTime = 0.2f });
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
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 24, .End = 24, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Brake", .ImageName = "LEFT_MARIO.BMP", .Start = 24, .End = 24, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_LookUp", .ImageName ="LEFT_MARIO.BMP", .Start = 25, .End = 25, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Crouch", .ImageName ="LEFT_MARIO.BMP", .Start = 26, .End = 26, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 27, .End = 29, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Dash", .ImageName =	"LEFT_MARIO.BMP", .Start = 27, .End = 29, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Run", .ImageName =	"LEFT_MARIO.BMP", .Start = 27, .End = 29, .InterTime = 0.02f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Jump", .ImageName =	"LEFT_MARIO.BMP", .Start = 28, .End = 28 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_RunJump", .ImageName="LEFT_MARIO.BMP", .Start = 28, .End = 28 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Hold_Fall", .ImageName =	"LEFT_MARIO.BMP", .Start = 28, .End = 28 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Idle", .ImageName ="LEFT_MARIO.BMP", .Start = 33, .End = 33, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Attack", .ImageName="LEFT_MARIO.BMP", .Start = 34, .End = 35, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Turn", .ImageName = "LEFT_MARIO.BMP", .Start = 36, .End = 36, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Pipe", .ImageName = "LEFT_MARIO.BMP", .Start = 35, .End = 35, });
		// ������ ����
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 0 + 53, .End = 0 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_LookUp", .ImageName =	"LEFT_MARIO.BMP", .Start = 1 + 53, .End = 1 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Crouch", .ImageName =	"LEFT_MARIO.BMP", .Start = 2 + 53, .End = 2 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.08f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_ClearWalk", .ImageName =	"LEFT_MARIO.BMP", .Start = 3 + 53, .End = 5 + 53, .InterTime = 0.2f });
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
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 24 + 53, .End = 24 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Brake", .ImageName =	"LEFT_MARIO.BMP", .Start = 24 + 53, .End = 24 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_LookUp", .ImageName = "LEFT_MARIO.BMP", .Start = 25 + 53, .End = 25 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Crouch", .ImageName = "LEFT_MARIO.BMP", .Start = 26 + 53, .End = 26 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Walk", .ImageName =	"LEFT_MARIO.BMP", .Start = 27 + 53, .End = 29 + 53, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Dash", .ImageName =	"LEFT_MARIO.BMP", .Start = 27 + 53, .End = 29 + 53, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Run", .ImageName =	"LEFT_MARIO.BMP", .Start = 27 + 53, .End = 29 + 53, .InterTime = 0.02f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Jump", .ImageName =	"LEFT_MARIO.BMP", .Start = 28 + 53, .End = 28 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_RunJump", .ImageName ="LEFT_MARIO.BMP", .Start = 28 + 53, .End = 28 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Super_Hold_Fall", .ImageName =	"LEFT_MARIO.BMP", .Start = 28 + 53, .End = 28 + 53 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 33 + 53, .End = 33 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Attack", .ImageName = "LEFT_MARIO.BMP", .Start = 34 + 53, .End = 35 + 53, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Turn", .ImageName =	"LEFT_MARIO.BMP", .Start = 36 + 53, .End = 36 + 53, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Super_Pipe", .ImageName =	"LEFT_MARIO.BMP", .Start = 35 + 53, .End = 35 + 53, });
		// ������ �Ҳ�
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Idle", .ImageName =		"LEFT_MARIO.BMP", .Start = 0 + 103, .End = 0 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_LookUp", .ImageName =	"LEFT_MARIO.BMP", .Start = 1 + 103, .End = 1 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Crouch", .ImageName =	"LEFT_MARIO.BMP", .Start = 2 + 103, .End = 2 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Walk", .ImageName =		"LEFT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.08f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_ClearWalk", .ImageName =		"LEFT_MARIO.BMP", .Start = 3 + 103, .End = 5 + 103, .InterTime = 0.2f });
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
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_JumpAttack", .ImageName ="LEFT_MARIO.BMP", .Start = 32 + 103, .End = 32 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Idle", .ImageName =		"LEFT_MARIO.BMP", .Start = 24 + 103, .End = 24 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Brake", .ImageName =	"LEFT_MARIO.BMP", .Start = 24 + 103, .End = 24 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_LookUp", .ImageName =	"LEFT_MARIO.BMP", .Start = 25 + 103, .End = 25 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Crouch", .ImageName =	"LEFT_MARIO.BMP", .Start = 26 + 103, .End = 26 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Walk", .ImageName =		"LEFT_MARIO.BMP", .Start = 27 + 103, .End = 29 + 103, .InterTime = 0.06f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Dash", .ImageName =		"LEFT_MARIO.BMP", .Start = 27 + 103, .End = 29 + 103, .InterTime = 0.03f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Run", .ImageName =		"LEFT_MARIO.BMP", .Start = 27 + 103, .End = 29 + 103, .InterTime = 0.02f });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Jump", .ImageName =		"LEFT_MARIO.BMP", .Start = 28 + 103, .End = 28 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_RunJump", .ImageName =	"LEFT_MARIO.BMP", .Start = 28 + 103, .End = 28 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Left_Fire_Hold_Fall", .ImageName =		"LEFT_MARIO.BMP", .Start = 28 + 103, .End = 28 + 103 });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Idle", .ImageName =	"LEFT_MARIO.BMP", .Start = 33 + 103, .End = 33 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Attack", .ImageName =	"LEFT_MARIO.BMP", .Start = 34 + 103, .End = 35 + 103, .InterTime = 0.3f });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Turn", .ImageName =	"LEFT_MARIO.BMP", .Start = 36 + 103, .End = 36 + 103, });
		AnimationRender->CreateAnimation({ .AnimationName = "Yoshi_Left_Fire_Pipe", .ImageName =	"LEFT_MARIO.BMP", .Start = 35 + 103, .End = 35 + 103, });
	}
	ChangeAnimation("Idle");
	
	// Collision ����
	{
		Collision = CreateCollision(CollisionOrder::Player);
		Collision->SetScale(CollisionScale);
		Collision->SetPosition(CollisionPos);
		Collision->SetDebugRenderType(CollisionType::CT_Rect);
		
		FootCollision = CreateCollision(CollisionOrder::Check);
		FootCollision->SetScale(FootCollisionScale);
		FootCollision->SetPosition(FootCollisionPos);
		FootCollision->SetDebugRenderType(CollisionType::CT_Rect);
	}

	ScreenSize = GameEngineWindow::GetScreenSize();
}

void Mario::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
	CurrentLevel = dynamic_cast<StageLevel*>(GetLevel());
	MarioPower = MarioGameCore::GetInst().GetMarioStateData();
	MapSize = Map::MainMap->GetStageSize();
	CameraMove(1);
}

void Mario::LevelChangeEnd(GameEngineLevel* _NextLevel)
{

	MarioGameCore::GetInst().SetMarioStateData(MarioPower);
}

void Mario::Update(float _DeltaTime)
{
	if (MarioState::VICTORY == StateValue)
	{
		VictoryUpdate(_DeltaTime);
		return;
	}
	FireAnimTimer += _DeltaTime;
	KickAnimTimer += _DeltaTime;
	UpdateState(_DeltaTime);

	// �ð� ���� ���� üũ
	if (MarioState::CHANGEPOWER == StateValue || MarioState::GameOver == StateValue || MarioState::Pipe == StateValue)
	{
		return;
	}
	CheckCollision();
	// �ð� ���� ���� üũ
	if (MarioState::CHANGEPOWER == StateValue || MarioState::GameOver == StateValue)
	{
		return;
	}
	BlockCheck();
	MoveCalculation(_DeltaTime);
	KickAttack();
	FireAttack();
	CameraMove(_DeltaTime);

	

	// �����ð� üũ
	if (true == IsInvincibility && MarioState::CHANGEPOWER != StateValue)
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

	// ġƮ
	if (GameEngineInput::IsDown("1"))
	{
		Speed *= 2;
		RunSpeed *= 2;
		IsInvincibility = true;
		Timer = 9999;
		ColMap = GameEngineResources::GetInst().ImageFind("STAGE0COL.bmp");
	}
	if (GameEngineInput::IsDown("2"))
	{
		Speed = 705;
		RunSpeed = 850.0f;
		ColMap = GameEngineResources::GetInst().ImageFind(Map::MainMap->GetStageColName());
	}
	if (GameEngineInput::IsDown("3"))
	{
		LevelLoader::ChangeLevel("World");
	}

	GameEngineLevel::DebugTextPush(GetPos().ToString());
	GameEngineLevel::DebugTextPush(ToGridPos(GetPos()).ToString());
}

void Mario::ChangeAnimation(const std::string_view& _AnimationName)
{
	std::string AnimStr = DirValue == Dir::Left ? "Left_" : "Right_";
	
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

	AnimStr += IsHold ? "Hold_" : "";

	AnimationRender->ChangeAnimation(AnimStr + _AnimationName.data());
}

void Mario::MoveCalculation(float _DeltaTime)
{
	if (MarioState::GameOver == StateValue) { return; }
	// ���� ��ġ
	float4 DownPos = GetPos() + float4::Down * 10; 
	// ���� ��ġ
	float4 ForwardPos = GetPos();
	ForwardPos.x += HorizontalForce * Speed * _DeltaTime;
	// ���� ��ġ
	float4 UpPos = GetPos() + float4::Up * 64;
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
	else if (Map::MainMap->GetStageSize().iy() + 100 <= NextPos.iy())
	{
		MarioPower = PowerState::Normal;
		Die();
		MoveDir.y = 0;
	}
	
	// ______�� �浹 üũ______

	if (nullptr == ColMap)
	{
		MsgAssert("�浹�� �� �̹����� �����ϴ�.");
	}

	// �� �浹 üũ�� �÷� ����
	DWORD PixelColor = ColMap->GetPixelColor(DownPos, White);
	// �������� ��Ż�濡 �ִ� ���
	if (true == IsSlope && true == IsGrounded)
	{
		// �� �ؿ� ��Ż���� �ִ� ���
		if (Red == PixelColor)
		{
			IsSlope = true;
			IsGrounded = true;
			DownPos.y = std::round(DownPos.y);
			// �ٴڿ��� ���� ���� �ö󰣴�
			while (true)
			{
				DownPos.y -= 1;
				PixelColor = ColMap->GetPixelColor(DownPos, Black);
				if (White == PixelColor)
				{
					SetPos(DownPos);
					MoveDir.y = 0.0f;
					break;
				}
			}
			DownPos.x += 1;
			PixelColor = ColMap->GetPixelColor(DownPos, Black);
			// ���ΰ� ����
			if (Red == PixelColor)
			{
				SlopeDir = Dir::Left;
			}
			// ���ΰ� ������
			else
			{
				SlopeDir = Dir::Right;
			}
		}
		// ���� �� �ؿ� ��Ż���� ���� ���
		else
		{
			// �ٴ� üũ
			if (Black == PixelColor || Green == PixelColor)
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
						PixelColor = ColMap->GetPixelColor(DownPos, Black);
						if (Black != PixelColor)
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
	// �ٴ� üũ
	else if (Black == PixelColor)
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
				PixelColor = ColMap->GetPixelColor(DownPos, Black);
				if (Black != PixelColor)
				{
					SetPos(DownPos);
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
		if (Green == PixelColor)
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
					PixelColor = ColMap->GetPixelColor(DownPos, Black);
					if (White == PixelColor)
					{
						SetPos(DownPos);
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
		else if (Red == PixelColor)
		{
			IsSlope = true;
			IsGrounded = true;
			DownPos.y = std::round(DownPos.y);
			// �ٴڿ��� ���� ���� �ö󰣴�
			while (true)
			{
				DownPos.y -= 1;
				PixelColor = ColMap->GetPixelColor(DownPos, Black);
				if (White == PixelColor)
				{
					SetPos(DownPos);
					ForwardPos.y = DownPos.y;
					MoveDir.y = 0.0f;
					break;
				}
			}
			DownPos.x += 1;
			PixelColor = ColMap->GetPixelColor(DownPos, Black);
			// ���ΰ� ����
			if (Red == PixelColor)
			{
				SlopeDir = Dir::Left;
			}
			// ���ΰ� ������
			else
			{
				SlopeDir = Dir::Right;
			}
		}
		// �������� �ٴڿ� �־����� ���� ���߿� �ִ°��
		else if (true == IsGrounded && false == IsOnBlock)
		{
			IsSlope = false;
			ChangeState(MarioState::FALL);
			IsGrounded = false;
		}
	}
	
	// õ�� üũ
	if (Black == ColMap->GetPixelColor(UpPos, White))
	{
		if (0 > MoveDir.y)
		{
			GameEngineResources::GetInst().SoundPlay("bump.wav");
			MoveDir.y = HeadingReaction;
		}
	}
	// �� üũ
	if (Black == ColMap->GetPixelColor(ForwardPos, White))
	{
		if (0 < HorizontalForce)
		{
			int i = 0;
			while (true)
			{
				if (20 < ++i) {
					break;
				}
				// �ڲ� ���� �ݺ���
				ForwardPos.x = std::round(ForwardPos.x);
				ForwardPos.x -= 1;
				PixelColor = ColMap->GetPixelColor(ForwardPos, Black);
				if (Black != PixelColor)
				{
					SetPos(ForwardPos);
					MoveDir.x = 0.0f;
					break;
				}
			}
		}
		else
		{
			int i = 0;
			while (true)
			{
				if (20 < ++i) {
					break;
				}
				ForwardPos.x = std::round(ForwardPos.x);
				ForwardPos.x += 1;
				PixelColor = ColMap->GetPixelColor(ForwardPos, Black);
				if (Black != PixelColor)
				{
					SetPos(ForwardPos);
					MoveDir.x = 0.0f;
					break;
				}
			}
		}

		HorizontalForce = 0;
		MoveDir.x = 0;
		if (true == IsGrounded)
		{
			ChangeState(MarioState::IDLE);
		}
	}

	// ������ �̵�
	SetMove(MoveDir * _DeltaTime);
}

void Mario::CameraMove(float _DeltaTime)
{
	float4 CameraPos = GetPos();
	CameraPos.x -= 350;

	if (750 > GetPos().y)
	{
		CameraPos.y -= 550;
		CameraPos.y = std::lerp(GetLevel()->GetCameraPos().y, CameraPos.y, _DeltaTime);
		
	}
	else
	{
		CameraPos.y = 850;
		CameraPos.y = std::lerp(GetLevel()->GetCameraPos().y, CameraPos.y, _DeltaTime);
	}


	if (CameraPos.x < 0)
	{
		CameraPos.x = 0;
	}
	else if (MapSize.x - ScreenSize.x < CameraPos.x)
	{
		CameraPos.x = MapSize.x - ScreenSize.x;
	}

	if (CameraPos.y < 0)
	{
		CameraPos.y = 0;
	}
	else if (MapSize.y - ScreenSize.y < CameraPos.y)
	{
		CameraPos.y = MapSize.y - ScreenSize.y;
	}

	GetLevel()->SetCameraPos(CameraPos);
}

void Mario::GetDamaged()
{
	switch (MarioPower)
	{
	case PowerState::Normal:
		ChangeState(MarioState::GameOver);
		return;
	case PowerState::Super:
		MarioPower = PowerState::Normal;
		ChangeState(MarioState::CHANGEPOWER);
		break;
	case PowerState::Fire:
		MarioPower = PowerState::Normal;
		ChangeState(MarioState::CHANGEPOWER);
		break;
	case PowerState::Cape:
		MarioPower = PowerState::Normal;
		break;
	default:
		break;
	}
	GameEngineResources::GetInst().SoundPlay("damage.wav");
	
}

void Mario::FireAttack()
{
	// ���̾� ������ �����϶��� ����
	if (PowerState::Fire != MarioPower) { return; }
	if (MarioState::SPIN == StateValue || MarioState::CROUCH == StateValue || MarioState::SLIDE == StateValue) { return; }
	if (FireAnimTime > FireAnimTimer && false == IsHold)
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
	// ��� Ű�� �Է��� �������� ����
	if (false == GameEngineInput::IsDown("Dash")) { return; }
	if (true == Fire::IsMax()) { return; }

	GameEngineResources::GetInst().SoundPlay("fireball.wav");
	Fire* NewFire = GetLevel()->CreateActor<Fire>(RenderOrder::PlayerAttack);
	NewFire->SetPos(GetPos());
	NewFire->SetMove(float4::Up * FireCreatePos.y);
	if (Dir::Left == DirValue)
	{
		NewFire->SetMove(float4::Left * FireCreatePos.x);
		NewFire->SetDir(float4::Left);
	}
	else
	{
		NewFire->SetMove(float4::Right * FireCreatePos.x);
		NewFire->SetDir(float4::Right);
	}

	FireAnimTimer = 0;
}

void Mario::NewPower(PowerState _Power)
{
	if (MarioPower == _Power)
	{
		switch (_Power)
		{
		case PowerState::Super:
			CurrentLevel->NewStockItem(ItemType::SuperMushroom);
			break;
		case PowerState::Fire:
			CurrentLevel->NewStockItem(ItemType::FireFlower);
			break;
		case PowerState::Cape:
			CurrentLevel->NewStockItem(ItemType::Feather);
			break;
		default:
			break;
		}
		return;
	}

	if (PowerState::Super == _Power)
	{
		if (PowerState::Normal != MarioPower)
		{
			CurrentLevel->NewStockItem(ItemType::SuperMushroom);
			return;
		}
	}
	else
	{
		switch (MarioPower)
		{
		case PowerState::Super:
			CurrentLevel->NewStockItem(ItemType::SuperMushroom);
			break;
		case PowerState::Fire:
			CurrentLevel->NewStockItem(ItemType::FireFlower);
			break;
		case PowerState::Cape:
			CurrentLevel->NewStockItem(ItemType::Feather);
			break;
		default:
			break;
		}

	}

	MarioPower = _Power;
	GameEngineResources::GetInst().SoundPlay("powerup.wav");
	ChangeState(MarioState::CHANGEPOWER);
}

void Mario::KickAttack()
{
	if (KickAnimTime > KickAnimTimer && false == IsHold)
	{
		ChangeAnimation("Kick");
	}
	if (true == IsHold)
	{
		if (false == GameEngineInput::IsPress("Dash"))
		{
			IsHold = false;
			float4 KickForce;
			
			if (GameEngineInput::IsPress("Down"))
			{
				KickForce.x = DirValue == Dir::Left ? -250.0f : 250.0f;
				KickForce.y = 100;
			}
			else
			{
				if (GameEngineInput::IsPress("Up")) {
					KickForce.y = -1500;
				}
				else
				{
					KickForce.x = DirValue == Dir::Left ? -1000.0f : 1000.0f;
					KickForce.y = -250;
				}
				float4 Pos = GetPos();
				Pos.x += DirValue == Dir::Right ? HoldPos.x : -HoldPos.x;
				Pos.y += HoldPos.y;
				Particle::CreateParticle(GetLevel(), Pos, "KICK");
				GameEngineResources::GetInst().SoundPlay("kick.wav");
				KickAnimTimer = 0;
			}

			if (nullptr != HoldActor)
			{
				HoldActor->Kick(KickForce);
			}
		}
		else
		{
			float4 MovePos = GetPos();
			MovePos.x += DirValue == Dir::Right ? HoldPos.x : -HoldPos.x;
			MovePos.y += HoldPos.y;
			if (nullptr != HoldActor)
			{
				HoldActor->SetPos(MovePos);
			}
		}
	}
}

void Mario::CheckCollision()
{
	std::vector<GameEngineCollision*> Collisions;
	// ���� üũ
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Monster), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == Collision->Collision(Check, Collisions))
	{
		std::vector<GameEngineCollision*>::iterator Start = Collisions.begin();
		std::vector<GameEngineCollision*>::iterator End = Collisions.end();
		bool IsKill = false;
		for (; Start != End; Start++)
		{
			EnemyActor* ColActor = (*Start)->GetOwner<EnemyActor>();
			//ColActor->GetOwner<Mario>(); ��ȯ ���

			// �����̵��� �ϰ��ִ� ���
			if (MarioState::SLIDE == StateValue)
			{
				// ���� óġ
				ColActor->Death();
				Particle::CreateParticle(GetLevel(), GetPos(), "KICK");
				GameEngineResources::GetInst().SoundPlay("kick.wav");
				continue;
			}
			if (true == ColActor->IsHold())
			{
				continue;
			}
			// ���
			if (true == GameEngineInput::IsPress("Dash") && true == ColActor->IsHoldable() && MarioState::SPIN != StateValue && false == IsHold && KickAnimTime < KickAnimTimer)
			{
				// ��´�
				IsHold = true;
				ColActor->Hold();
				HoldActor = ColActor;
				continue;
			}
			// �÷��̾ ���ͺ��� ���� �����鼭 �������� �ִ� ���
			if (GetPos().y < ColActor->GetPos().y - 28 && -500 < MoveDir.y)
			{
				if (IsKill == true) {
					continue;
				}
				switch (StateValue)
				{
				case MarioState::FALL:
				case MarioState::RUNJUMP:
					ColActor->JumpHit(GetPos().x > ColActor->GetPos().x);
					break;
				case MarioState::SPIN:
					ColActor->SpinHit();
					break;
				case MarioState::SLIDE:

					break;
				default:
					ColActor->Death();
					break;
				}

				Particle::CreateParticle(GetLevel(), GetPos(), "KICK");
				GameEngineResources::GetInst().SoundPlay("kick.wav");
				
				IsKill = true;

			}
			// �� �� ���� �ð��� �ƴ� ��� �����
			else if (false == IsInvincibility && true == ColActor->IsCollisionAttack() && false == IsKill)
			{
				// �����
				GetDamaged();
				IsInvincibility = true;
			}
		}
		if (true == IsKill)
		{
			MoveDir.y = 0;
			IsGrounded = false;
			JumpTimeCounter = JumpTime;
			MoveDir += float4::Up * JumpForce;
			if (MarioState::RUNJUMP != StateValue && MarioState::SPIN != StateValue)
			{
				StateValue = MarioState::JUMP;
			}
		}
	}
}

void Mario::BlockCheck()
{
	std::vector<GameEngineCollision*> Collisions;
	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Block), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (true == FootCollision->Collision(Check, Collisions))
	{
		std::vector<GameEngineCollision*>::iterator Start = Collisions.begin();
		std::vector<GameEngineCollision*>::iterator End = Collisions.end();
		bool IsHeading = false;
		bool IsReJump = false;
		float4 Pos = GetPos();
		for (; Start != End; Start++)
		{
			Block* ColBlock = (*Start)->GetOwner<Block>();
			if (true == ColBlock->GetIsRoll())
			{
				continue;
			}
			float4 ColPos = ColBlock->GetPos();
			// ���Ͱ� ������� ���ִ�
			if (Pos.y < ColPos.y - BlockYSize)
			{
				if (0 >= MoveDir.y)
				{
					continue;
				}
				// �Ŀ��� ���¿��� �������� ������
				if (MarioState::SPIN == StateValue && PowerState::Normal != MarioPower)
				{
					// ��� �ı� �� �ٽ� ����
					if (true == ColBlock->Damage())
					{
						IsReJump = true;
						continue;
					}
				}
				// �� �ܿ� ��� ������� ����
				IsSlope = false;
				IsGrounded = true;
				IsOnBlock = true;
				float4 Pos = GetPos();
				Pos.y = ColPos.y - BlockOnPos;
				Pos.y = std::round(Pos.y);
				SetPos(Pos);
				MoveDir.y = 0.0f;
				continue;
			}
			else if (Pos.y > ColPos.y + BlockYSize)
			{
				if (0 <= MoveDir.y)
				{
					continue;
				}
				IsHeading = true;
				ColBlock->Hit();
				
			}
			else if (Pos.x + FootCollisionScale.hx() < ColPos.x - BlockXSize)
			{
				float4 Pos = GetPos();
				Pos.x = ColPos.x - BlockXSize - FootCollisionScale.hx() - 2;
				Pos.x = std::round(Pos.x);

				SetPos(Pos);
				if (true == IsGrounded)
				{
					ChangeState(MarioState::IDLE);
				}
				HorizontalForce = 0;
				MoveDir.x = 0;
			}
			else if (ColPos.x + BlockXSize < Pos.x - FootCollisionScale.hx())
			{
				float4 Pos = GetPos();
				Pos.x = ColPos.x + BlockXSize + FootCollisionScale.hx() + 2;
				Pos.x = std::round(Pos.x);

				SetPos(Pos);
				if (true == IsGrounded)
				{
					ChangeState(MarioState::IDLE);
				}
				HorizontalForce = 0;
				MoveDir.x = 0;
			}
		}
		if (true == IsReJump)
		{
			IsGrounded = false;
			JumpTimeCounter = JumpTime;
			MoveDir.y = 0;
			MoveDir.y -= JumpForce;
		}
		if (true == IsHeading) {
			GameEngineResources::GetInst().SoundPlay("bump.wav");
			MoveDir.y = HeadingReaction;
		}
	}
	else if (true == IsOnBlock)
	{
		IsOnBlock = false;
		IsGrounded = false;
	}
}

void Mario::Render(float _DeltaTime)
{ 
	//BodyCollision->DebugRender();
	//FootCollision->DebugRender();
}

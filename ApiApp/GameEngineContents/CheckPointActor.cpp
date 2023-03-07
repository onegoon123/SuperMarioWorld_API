#include "CheckPointActor.h"
#include <GameEngineCore/GameEngineCollision.h>
#include <GameEngineCore/GameEngineRender.h>
#include <GameEngineCore/GameEngineResources.h>
#include "StageLevel.h"
#include "ContentsEnums.h"
#include "MarioGameCore.h"
CheckPointActor::CheckPointActor() {

}

CheckPointActor::~CheckPointActor() {

}

void CheckPointActor::SetCheckPoint(int _CheckPoint, const float4& _Pos)
{
	CheckPoint = _CheckPoint;
	SetPos(_Pos);

	if (CheckPoint == dynamic_cast<StageLevel*>(GetLevel())->GetCheckPoint())
	{
		CheckPointRender->SetImage("CheckPointPass.bmp");
		IsPass = true;
	}
}

void CheckPointActor::Start()
{
	CheckPointRender = CreateRender("CheckPoint.bmp", RenderOrder::Map);
	CheckPointRender->SetScaleToImage();
	CheckPointRender->SetPosition(RenderPos);

	GameEngineRender* FrontRender = CreateRender("CheckPointFront.bmp", RenderOrder::ForeGround);
	FrontRender->SetScaleToImage();
	FrontRender->SetPosition(RenderPos);

	Collision = CreateCollision(CollisionOrder::Check);
	Collision->SetScale(CollisionScale);
	Collision->SetPosition(CollisionPos);
	Collision->SetDebugRenderType(CT_Rect);
}

void CheckPointActor::Update(float _DeltaTime)
{
	if (true == IsPass)
	{
		return;
	}

	CollisionCheckParameter Check = { .TargetGroup = static_cast<int>(CollisionOrder::Player), .TargetColType = CT_Rect, .ThisColType = CT_Rect };
	if (Collision->Collision(Check))
	{
		GameEngineResources::GetInst().SoundPlay("checkpoint.wav");
		CheckPointRender->SetImage("CheckPointPass.bmp");
		IsPass = true;

		dynamic_cast<StageLevel*>(GetLevel())->SetCheckPoint(CheckPoint);

	}

}

void CheckPointActor::Render(float _DeltaTime)
{
	if (true == MarioGameCore::GetInst().GetCollisionDebug())
	{
		Collision->DebugRender();
	}
}

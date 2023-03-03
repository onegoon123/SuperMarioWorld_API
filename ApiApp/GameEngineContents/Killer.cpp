#include "Killer.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
Killer::Killer() {

}

Killer::~Killer() {

}

bool Killer::IsCollisionAttack()
{
	return false == IsDie;
}

bool Killer::IsHold()
{
	return false;
}

bool Killer::IsHoldable()
{
	return false;
}

void Killer::SpinHit()
{
	IsDie = true;
}

void Killer::JumpHit(bool IsLeft)
{
	IsDie = true;
}

void Killer::FireHit()
{
}

void Killer::BlockHit()
{
}

void Killer::MonsterHit(bool IsLeft)
{
}

void Killer::Hold()
{
}

void Killer::Kick(const float4& _Force)
{
}

void Killer::Start()
{
	EnemyActor::Start();
	SpriteRender = CreateRender("Killer.bmp", RenderOrder::Monster);
	SpriteRender->SetScaleToImage();
	SpriteRender->SetPosition(RenderPos);

	Collision = CreateCollision(CollisionOrder::Monster);
	Collision->SetScale(CollisionScale);
	Collision->SetPosition(CollisionPos);
	Collision->SetDebugRenderType(CollisionType::CT_Rect);
}

void Killer::Update(float _DeltaTime)
{
	if (true == IsDie)
	{
		DieUpdate(_DeltaTime);
		return;
	}

	CameraInCheck();
	if (false == IsOnCamera) { return; }
	SetMove(float4::Left * ActorSpeed * _DeltaTime);

	GameEngineLevel::DebugTextPush(GetPos().ToString());
}

void Killer::Render(float _DeltaTime)
{
	//Collision->DebugRender();
}

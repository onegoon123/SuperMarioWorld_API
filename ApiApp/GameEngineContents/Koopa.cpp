#include "Koopa.h"
#include <GameEngineCore/GameEngineRender.h>
#include "ContentsEnums.h"
Koopa::Koopa() {

}

Koopa::~Koopa() {

}

bool Koopa::IsCollisionAttack()
{
    return false;
}

bool Koopa::IsHold()
{
    return false;
}


bool Koopa::IsHoldable()
{
    return false;
}

void Koopa::SpinHit()
{
}

void Koopa::JumpHit(bool IsLeft)
{
}

void Koopa::FireHit()
{
}

void Koopa::BlockHit()
{
}

void Koopa::MonsterHit(bool IsLeft)
{
}

void Koopa::Hold()
{
}

void Koopa::Kick(const float4& _Force)
{
}

void Koopa::Start()
{
	EnemyActor::Start();
	KoopaRender = CreateRender("LEFT_KOOPA.bmp", RenderOrder::Monster);
	KoopaRender->SetScale(KoopaRenderScale);
	KoopaRender->SetPosition(KoopaRenderPos);

	PierrotRender = CreateRender("LEFT_Pierrot.bmp", RenderOrder::Monster);
	PierrotRender->SetScale(PierrotRenderScale);
	PierrotRender->SetPosition(PierrotRenderPos);

	PropellerRender = CreateRender(RenderOrder::Monster);
	PropellerRender->SetScale(PropellerRenderScale);
	PropellerRender->SetPosition(PropellerRenderPos);
	PropellerRender->CreateAnimation({ .AnimationName = "Idle", .ImageName = "Propeller.BMP", .Start = 0, .End = 0,});
	PropellerRender->CreateAnimation({ .AnimationName = "Spin", .ImageName = "Propeller.BMP", .Start = 0, .End = 3, .InterTime = 0.2f });
	PropellerRender->ChangeAnimation("Spin");

	Collision = CreateCollision(CollisionOrder::Monster);
	Collision->SetScale(KoopaCollisionScale);
	Collision->SetPosition(KoopaCollisionPos);
	Collision->SetDebugRenderType(CollisionType::CT_Rect);
}

void Koopa::Update(float _DeltaTime)
{
}

void Koopa::Render(float _DeltaTime)
{
}

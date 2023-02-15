#include "WorldMario.h"
#include "ContentsEnums.h"
WorldMario::WorldMario() {

}

WorldMario::~WorldMario() {

}

void WorldMario::Start()
{
	AnimationRender = CreateRender(RenderOrder::Player);
	AnimationRender->SetScale({64, 64});

	AnimationRender->CreateAnimation({ .AnimationName = "DOWN", .ImageName = "MARIO.BMP", .Start = 0, .End = 3, .InterTime = 0.15f});

	AnimationRender->ChangeAnimation("Down");
}

void WorldMario::Update(float _DeltaTime)
{
}

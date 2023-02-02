#include "StageLevel4.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineRender.h>

#include "Mario.h"
#include "Map.h"
#include "ContentsEnums.h"

StageLevel4::StageLevel4() {

}

StageLevel4::~StageLevel4() {

}

void StageLevel4::Loading()
{
	BackGroundName = "BACKGROUND4.BMP";
	StageName = "STAGE4.BMP";
	StageColName = "STAGE4COL.BMP";

	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	//GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(SkyName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(BackGroundName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName(StageColName));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("ENDING.BMP"));

}

void StageLevel4::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("1"))
	{
		GameEngineActor* EndingImage = CreateActor<GameEngineActor>();
		GameEngineRender* EndingRender = EndingImage->CreateRender("ENDING.BMP", RenderOrder::UI);
		EndingRender->SetScale(EndingRender->GetImage()->GetImageScale());
		EndingRender->SetPosition(EndingRender->GetImage()->GetImageScale().half());
		EndingRender->EffectCameraOff();
	}
}

void StageLevel4::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	if (nullptr != Mario::MainPlayer)
	{
		Mario::MainPlayer->Death();
		Mario::MainPlayer = nullptr;
	}
	SetCameraPos(float4::Zero);
}

void StageLevel4::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	CreateActor<Mario>()->SetPos({ 350, 1000 });
	SetCameraMove({ 0, 222 });
	Map* Map1 = CreateActor<Map>();
	Map1->SetImage(BackGroundName, StageName, StageColName);
	Map1->GetStageRender()->SetOrder(static_cast<int>(RenderOrder::ForeGround));
	Map1->MoveMap(1);

}
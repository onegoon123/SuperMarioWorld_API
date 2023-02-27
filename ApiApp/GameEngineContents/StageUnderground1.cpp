#include "StageUnderground1.h"
#include "Map.h"
#include "Mario.h"
#include "Pipe.h"
StageUnderground1::StageUnderground1() {

}

StageUnderground1::~StageUnderground1() {

}

void StageUnderground1::Loading()
{
	StageLevel::Loading();
	//SetName()
}

void StageUnderground1::LevelChangeStart(GameEngineLevel* _Prev)
{
	if ("Stage1" == _Prev->GetName())
	{
		SetTimer(dynamic_cast<StageLevel*>(_Prev)->GetTimer());
	}

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Underground.mp3");
	BGMPlayer.LoopCount(0);

	Map* MainMap = CreateActor<Map>();
	MainMap->SetImage(BackGroundName, StageName, StageColName);

	MainMap->AddStartPos({128, 1408});

	MainMap->GetBackGroundRender()->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
	MainMap->GetBackGroundRender()->SetScale({ 2048, 1728 });
	MainMap->GetBackGroundRender()->SetPosition({ 1024, 864 });
	MainMap->GetBackGroundRender()->ChangeAnimation("BackGroundAnim");

	CreateActor<Mario>();
	UI = CreateActor<UIManager>();

	Pipe* NewPipe = CreateActor<Pipe>(RenderOrder::Map);
	NewPipe->SetPos({1772, 1532});

	NewPipe->SetPipe("Stage1", Right);

	MainMap->MoveMap(0);

	StageLevel::LevelChangeStart(_Prev);
}

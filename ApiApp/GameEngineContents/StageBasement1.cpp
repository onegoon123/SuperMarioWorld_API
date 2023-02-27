#include "StageBasement1.h"
#include "Map.h"
#include "Mario.h"

StageBasement1::StageBasement1() {

}

StageBasement1::~StageBasement1() {

}

void StageBasement1::Loading()
{
	StageLevel::Loading();
}

void StageBasement1::LevelChangeStart(GameEngineLevel* _Prev)
{
	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("Overworld.mp3");
	BGMPlayer.LoopCount(0);

	Map* MainMap = CreateActor<Map>();
	MainMap->SetImage(BackGroundName, StageName, StageColName);
	MainMap->AddStartPos(GridPos(5, 0));

	MainMap->GetBackGroundRender()->CreateAnimation({ .AnimationName = "BackGroundAnim", .ImageName = BackGroundName, .Start = 0, .End = 3 });
	MainMap->GetBackGroundRender()->SetScale({ 2048, 1728 });
	MainMap->GetBackGroundRender()->SetPosition({ 1024, 864 });
	MainMap->GetBackGroundRender()->ChangeAnimation("BackGroundAnim");

	CreateActor<Mario>();
	UI = CreateActor<UIManager>();

	MainMap->MoveMap(0);
	StageLevel::LevelChangeStart(_Prev);


}

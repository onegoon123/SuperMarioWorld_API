#include "WorldLevel.h"
#include "WorldImage.h"
#include "WorldMario.h"
#include "LevelLoader.h"

WorldLevel::WorldLevel() {

}

WorldLevel::~WorldLevel() {

}

void WorldLevel::Loading()
{
	CreateActor<WorldImage>();
	CreateActor<WorldMario>()->SetPos({ 475, 650 });
	CreateActor<LevelLoader>();
}

void WorldLevel::Update(float _DeltaTime)
{

}

void WorldLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{

	BGMPlayer = GameEngineResources::GetInst().SoundPlayToControl("YoshiIsland.mp3");
}

void WorldLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	BGMPlayer.Stop();
}

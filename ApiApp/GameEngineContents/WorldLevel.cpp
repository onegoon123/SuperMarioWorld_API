#include "WorldLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include "WorldImage.h"
#include "WorldMario.h"
WorldLevel::WorldLevel() {

}

WorldLevel::~WorldLevel() {

}

void WorldLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	Dir.Move("World");
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WORLD1.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("WORLD1FRONT.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("SEA.BMP"));
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"))->Cut(4, 5);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("CLOUD.BMP"))->Cut(1, 4);
	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("TIDE.BMP"))->Cut(1,8);
	CreateActor<WorldImage>();
	CreateActor<WorldMario>()->SetPos({ 475, 650 });
}

void WorldLevel::Update(float _DeltaTime)
{

}

void WorldLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
}

void WorldLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
}

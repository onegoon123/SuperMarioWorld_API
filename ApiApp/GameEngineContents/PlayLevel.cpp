#include "PlayLevel.h"
#include "Mario.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	GameEngineDirectory Dir;
	Dir.Move("ContentsResources");
	Dir.Move("Image");

	GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"));

	CreateActor<Mario>();
}

void PlayLevel::Update()
{

}

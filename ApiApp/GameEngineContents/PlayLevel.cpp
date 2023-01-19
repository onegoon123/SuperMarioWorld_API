#include "PlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include "Mario.h"
#include "Map.h"

PlayLevel::PlayLevel()
{
}

PlayLevel::~PlayLevel()
{
}

void PlayLevel::Loading()
{
	//GameEngineDirectory Dir;
	//Dir.Move("ContentsResources");
	//Dir.Move("Image");
	//{
	//	GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"));
	//	Image->Cut(19, 37);
	//}

	CreateActor<Mario>();
	CreateActor<Map>();
}

void PlayLevel::Update(float _DeltaTime)
{

}

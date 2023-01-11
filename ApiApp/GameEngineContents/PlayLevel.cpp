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
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("MARIO.BMP"));
		Image->Cut(19, 37);
	}


	//if (true == Path.IsExistsToPlusString("\\Heros.bmp"))
	//{
	//	int a = 0;
	//}

	CreateActor<Mario>();
}

void PlayLevel::Update()
{

}

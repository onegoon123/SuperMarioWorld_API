#include "PlayLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
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
	GameEngineDirectory Dir;
	Dir.MoveParentToDirectory("ContentsResources");
	Dir.Move("ContentsResources");
	Dir.Move("Image");
	{
		GameEngineImage* Image = GameEngineResources::GetInst().ImageLoad(Dir.GetPlusFileName("STAGE0COL.BMP"));
	}

	CreateActor<Mario>();
	CreateActor<Map>();
}

void PlayLevel::Update(float _DeltaTime)
{
	if (GameEngineInput::IsDown("1"))
	{
		GameEngineCore::GetInst()->ChangeLevel("Title");
	}
}

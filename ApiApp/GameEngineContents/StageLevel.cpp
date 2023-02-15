#include "StageLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include "Mario.h"
#include "ContentsEnums.h"

#include <GameEnginePlatform/GameEngineInput.h>
StageLevel::StageLevel() {

}

StageLevel::~StageLevel() {

}

void StageLevel::Loading()
{
}

void StageLevel::Update(float _DeltaTime)
{
	
	Timer -= _DeltaTime * 30;
	UI->SetTime(static_cast<int>(Timer));
	if (GameEngineInput::IsPress("3"))
	{
		UI->SetLife(++Life);
		UI->SetScore(++Score);
		UI->SetCoin(++Coin);
	}
}

void StageLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Timer = Time;
}

void StageLevel::LevelChangeEnd(GameEngineLevel* _NextLevel)
{
	for (int i = 0; i < static_cast<int>(RenderOrder::UI); i++)
	{
		std::vector<GameEngineActor*> Actors = GetActors(i);
		std::vector<GameEngineActor*>::iterator Start = Actors.begin();
		std::vector<GameEngineActor*>::iterator End = Actors.end();

		for (; Start != End; Start++)
		{
			if (nullptr != *Start)
			{
				(*Start)->Death();
			}
		}
		Mario::MainPlayer = nullptr;
	}
	SetCameraPos(float4::Zero);
	BGMPlayer.Stop();
}


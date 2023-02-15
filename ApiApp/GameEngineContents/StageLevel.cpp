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

void StageLevel::MarioDie()
{
	Life--;
}

void StageLevel::Loading()
{
}

void StageLevel::Update(float _DeltaTime)
{
	Timer -= _DeltaTime;
	if (0 > Timer) {
		MarioGameCore::GetInst().ChangeLevel("Title");
	}
	UI->SetTime(static_cast<int>(Timer));
}

void StageLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Timer = Time;
	Life = MarioGameCore::GetInst().GetLife();
	Star = MarioGameCore::GetInst().GetStar();
	Coin = MarioGameCore::GetInst().GetCoin();
	Score = MarioGameCore::GetInst().GetScore();
	UI->SetValue(Life, Star, Coin, Score);
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


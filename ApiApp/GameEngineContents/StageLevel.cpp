#include "StageLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include "Mario.h"
#include "ContentsEnums.h"
#include "LevelLoader.h"
StageLevel::StageLevel()
{
}

StageLevel::~StageLevel() {

}

void StageLevel::AddCoin()
{
	GameEngineResources::GetInst().SoundPlay("Coin.WAV");
	if (++CoinNum >= 100)
	{
		CoinNum -= 100;
		AddLife();
	}
	UI->SetCoin(CoinNum);
	AddScore(100);
}

void StageLevel::AddLife()
{
	GameEngineResources::GetInst().SoundPlay("1UP.WAV");
	if (++Life >= 10)
	{
		Life = 9;
	}
	UI->SetLife(Life);
}

void StageLevel::AddScore(int _Score)
{
	Score += _Score;
	UI->SetScore(Score);
}

void StageLevel::MarioDie()
{
	Life--;
	MarioGameCore::GetInst().SetCoin(CoinNum);
	MarioGameCore::GetInst().SetLife(Life);
	MarioGameCore::GetInst().SetScore(Score);
	MarioGameCore::GetInst().SetStar(Star);

	if (0 >= Life)
	{
		LevelLoader::ChangeLevel("GameOver");
		return;
	}

	LevelLoader::ChangeLevel("World");
}

void StageLevel::Loading()
{
}

void StageLevel::Update(float _DeltaTime)
{
	if (true == Mario::MainPlayer->GetIsGameOver())
	{
		return;
	}
	Timer -= _DeltaTime;
	if (0 > Timer) {
		Mario::MainPlayer->Die();
		UI->SetTime(0);
		return;
	}
	UI->SetTime(static_cast<int>(Timer));
}

void StageLevel::LevelChangeStart(GameEngineLevel* _PrevLevel)
{
	Timer = Time;
	Life = MarioGameCore::GetInst().GetLife();
	Star = MarioGameCore::GetInst().GetStar();
	CoinNum = MarioGameCore::GetInst().GetCoin();
	Score = MarioGameCore::GetInst().GetScore();
	UI->SetValue(Life, Star, CoinNum, Score);

	CreateActor<LevelLoader>();
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


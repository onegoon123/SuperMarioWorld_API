#include "StageLevel.h"
#include <GameEngineBase/GameEngineDirectory.h>
#include <GameEnginePlatform/GameEngineInput.h>
#include <GameEngineCore/GameEngineResources.h>
#include <GameEngineCore/GameEngineActor.h>
#include "Mario.h"
#include "LevelLoader.h"
#include "SuperMushroom.h"
#include "FireFlower.h"

StageLevel::StageLevel()
{
}

StageLevel::~StageLevel() {

}

void StageLevel::NewStockItem(ItemType _Item)
{
	switch (_Item)
	{
	case ItemType::UpMushroom:
		break;
	case ItemType::SuperMushroom:
		break;
	case ItemType::FireFlower:
		break;
	case ItemType::Feather:
		break;
	default:
		break;
	}

	Item = _Item;
	UI->SetStockItem(_Item);
}

void StageLevel::DropStockItem()
{
	GameEngineActor* NewActor = nullptr;
	switch (Item)
	{
	case ItemType::Coin:
		return;
	case ItemType::UpMushroom:
		return;
	case ItemType::SuperMushroom:
		NewActor = CreateActor<SuperMushroom>(RenderOrder::Item);
		break;
	case ItemType::FireFlower:
		NewActor = CreateActor<FireFlower>(RenderOrder::Item);
		break;
	case ItemType::Feather:
		break;
	default:
		return;
	}

	float4 SpawnPos = Mario::MainPlayer->GetPos();
	SpawnPos.y = GetCameraPos().y;

	NewActor->SetPos(SpawnPos);
	Item = ItemType::Coin;

	UI->SetStockItem(ItemType::Coin);
}

void StageLevel::AddCoin()
{
	GameEngineResources::GetInst().SoundPlay("Coin.WAV");
	while (++CoinNum >= 100)
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
	Item = MarioGameCore::GetInst().GetStockStateData();

	UI->SetValue(Life, Star, CoinNum, Score);
	UI->SetStockItem(Item);
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

	MarioGameCore::GetInst().SetCoin(CoinNum);
	MarioGameCore::GetInst().SetLife(Life);
	MarioGameCore::GetInst().SetScore(Score);
	MarioGameCore::GetInst().SetStar(Star);
	MarioGameCore::GetInst().SetStockStateData(Item);

	BGMPlayer.Stop();
}

